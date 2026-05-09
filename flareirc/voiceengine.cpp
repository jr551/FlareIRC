#include "voiceengine.h"
#include <QAudioInput>
#include <QAudioOutput>
#include <QAudioDeviceInfo>
#include <QDebug>
#include <cmath>

VoiceEngine::VoiceEngine(QObject *parent) :
    QObject(parent),
    opusEncoder(0),
    opusDecoder(0),
    audioInput(0),
    audioOutput(0),
    audioInputDevice(0),
    audioOutputDevice(0),
    frameSizeMs(20),
    sampleRate(48000),
    bitrate(32000),
    channels(1),
    bPushToTalk(false),
    bPttActive(false),
    bVoiceActivityDetection(true),
    bCapturing(false),
    bPlaying(false),
    vadThreshold(1000),
    currentVadLevel(VAD_SILENCE)
{
    // Initialize audio format for low latency (20ms frames)
    audioFormat.setSampleRate(sampleRate);
    audioFormat.setChannelCount(channels);
    audioFormat.setCodec("audio/pcm");
    audioFormat.setByteOrder(QAudioFormat::LittleEndian);
    audioFormat.setSampleType(QAudioFormat::SignedInt);

    // Create Opus encoder
    int err;
    opusEncoder = opus_encoder_create(sampleRate, channels, OPUS_APPLICATION_VOIP, &err);
    if (err != OPUS_OK) {
        qWarning() << "Failed to create Opus encoder:" << opus_strerror(err);
        emit errorOccurred(QString("Opus encoder creation failed: %1").arg(opus_strerror(err)));
    } else {
        opus_encoder_ctl(opusEncoder, OPUS_SET_BITRATE(bitrate));
        opus_encoder_ctl(opusEncoder, OPUS_SET_FRAME_SIZE(frameSizeMs * sampleRate / 1000));
        opus_encoder_ctl(opusEncoder, OPUS_SET_COMPLEXITY(10));
    }

    // Create Opus decoder
    opusDecoder = opus_decoder_create(sampleRate, channels, &err);
    if (err != OPUS_OK) {
        qWarning() << "Failed to create Opus decoder:" << opus_strerror(err);
        emit errorOccurred(QString("Opus decoder creation failed: %1").arg(opus_strerror(err)));
    }
}

VoiceEngine::~VoiceEngine()
{
    stopCapture();
    stopPlayback();

    if (opusEncoder) {
        opus_encoder_destroy(opusEncoder);
        opusEncoder = 0;
    }
    if (opusDecoder) {
        opus_decoder_destroy(opusDecoder);
        opusDecoder = 0;
    }
}

void VoiceEngine::captureAudio()
{
    if (bCapturing)
        return;

    QAudioDeviceInfo inputDevice = QAudioDeviceInfo::defaultInputDevice();
    if (!inputDevice.isFormatSupported(audioFormat)) {
        // Try to find a supported format with different sample rates
        QList<int> rates = {48000, 44100, 22050, 11025};
        for (int rate : rates) {
            QAudioFormat testFormat = audioFormat;
            testFormat.setSampleRate(rate);
            if (inputDevice.isFormatSupported(testFormat)) {
                audioFormat = testFormat;
                sampleRate = rate;
                if (opusEncoder) {
                    opus_encoder_ctl(opusEncoder, OPUS_SET_SAMPLE_RATE(rate));
                }
                if (opusDecoder) {
                    opus_decoder_ctl(opusDecoder, OPUS_SET_SAMPLE_RATE(rate));
                }
                break;
            }
        }
    }

    audioInput = new QAudioInput(inputDevice, audioFormat, this);
    audioInputDevice = audioInput->start();

    connect(audioInputDevice, SIGNAL(readyRead()), this, SLOT(onAudioDataAvailable()));

    bCapturing = true;
}

void VoiceEngine::stopCapture()
{
    if (!bCapturing)
        return;

    if (audioInput) {
        audioInput->stop();
        delete audioInput;
        audioInput = 0;
    }
    if (audioInputDevice) {
        audioInputDevice = 0;
    }

    bCapturing = false;
}

QByteArray VoiceEngine::encodeFrame(const QByteArray &pcmData)
{
    if (!opusEncoder) {
        emit errorOccurred("Encoder not initialized");
        return QByteArray();
    }

    int frameSize = frameSizeMs * sampleRate / 1000;
    if (frameSize <= 0) {
        emit errorOccurred("Invalid frame size");
        return QByteArray();
    }

    QByteArray encoded;
    encoded.resize(4000); // Max Opus packet size

    const opus_int16 *pcm = reinterpret_cast<const opus_int16*>(pcmData.constData());
    int samples = pcmData.size() / sizeof(opus_int16);

    // Process in chunks of frameSize
    int offset = 0;
    while (offset + frameSize <= samples) {
        int len = opus_encode(opusEncoder, pcm + offset, frameSize,
                               reinterpret_cast<opus_uint8*>(encoded.data()), encoded.size());
        if (len < 0) {
            qWarning() << "Opus encode error:" << opus_strerror(len);
            emit errorOccurred(QString("Encode error: %1").arg(opus_strerror(len)));
            return QByteArray();
        }
        encoded.truncate(len);
        offset += frameSize;
    }

    return encoded;
}

QByteArray VoiceEngine::decodeFrame(const QByteArray &opusData)
{
    if (!opusDecoder) {
        emit errorOccurred("Decoder not initialized");
        return QByteArray();
    }

    QByteArray decoded;
    decoded.resize(frameSizeMs * sampleRate * channels * sizeof(opus_int16) / 1000);

    opus_int16 *pcm = reinterpret_cast<opus_int16*>(decoded.data());
    int frameSize = frameSizeMs * sampleRate / 1000;

    int samples = opus_decode(opusDecoder,
                              reinterpret_cast<const opus_uint8*>(opusData.constData()),
                              opusData.size(),
                              pcm,
                              frameSize,
                              0);

    if (samples < 0) {
        qWarning() << "Opus decode error:" << opus_strerror(samples);
        emit errorOccurred(QString("Decode error: %1").arg(opus_strerror(samples)));
        return QByteArray();
    }

    decoded.truncate(samples * sizeof(opus_int16));
    return decoded;
}

void VoiceEngine::playAudio(const QByteArray &pcmData)
{
    if (pcmData.isEmpty())
        return;

    if (!bPlaying) {
        QAudioDeviceInfo outputDevice = QAudioDeviceInfo::defaultOutputDevice();
        if (audioOutput) {
            delete audioOutput;
            audioOutput = 0;
        }
        audioOutput = new QAudioOutput(outputDevice, audioFormat, this);
        audioOutputDevice = audioOutput->start();
        bPlaying = true;
    }

    if (audioOutputDevice) {
        audioOutputDevice->write(pcmData);
    }
}

void VoiceEngine::stopPlayback()
{
    if (!bPlaying)
        return;

    if (audioOutput) {
        audioOutput->stop();
        delete audioOutput;
        audioOutput = 0;
    }
    if (audioOutputDevice) {
        audioOutputDevice = 0;
    }

    bufferMutex.lock();
    playbackQueue.clear();
    bufferMutex.unlock();

    bPlaying = false;
}

void VoiceEngine::setPushToTalk(bool enabled)
{
    bPushToTalk = enabled;
}

bool VoiceEngine::isPushToTalk() const
{
    return bPushToTalk;
}

void VoiceEngine::setPttActive(bool active)
{
    bPttActive = active;

    if (bPushToTalk && !active) {
        stopCapture();
    } else if (bPushToTalk && active) {
        captureAudio();
    }
}

void VoiceEngine::setVoiceActivityDetection(bool enabled)
{
    bVoiceActivityDetection = enabled;
}

bool VoiceEngine::isVoiceActivityDetection() const
{
    return bVoiceActivityDetection;
}

VoiceEngine::VoiceActivityLevel VoiceEngine::getVoiceActivityLevel() const
{
    return currentVadLevel;
}

void VoiceEngine::setFrameSizeMs(int ms)
{
    frameSizeMs = ms;
    if (opusEncoder) {
        opus_encoder_ctl(opusEncoder, OPUS_SET_FRAME_SIZE(ms * sampleRate / 1000));
    }
}

int VoiceEngine::getFrameSizeMs() const
{
    return frameSizeMs;
}

void VoiceEngine::setSampleRate(int rate)
{
    sampleRate = rate;
    audioFormat.setSampleRate(rate);
}

int VoiceEngine::getSampleRate() const
{
    return sampleRate;
}

void VoiceEngine::setBitrate(int br)
{
    bitrate = br;
    if (opusEncoder) {
        opus_encoder_ctl(opusEncoder, OPUS_SET_BITRATE(br));
    }
}

int VoiceEngine::getBitrate() const
{
    return bitrate;
}

bool VoiceEngine::isCapturing() const
{
    return bCapturing;
}

bool VoiceEngine::isPlaying() const
{
    return bPlaying;
}

void VoiceEngine::onAudioDataAvailable()
{
    if (!audioInputDevice)
        return;

    QByteArray data = audioInputDevice->readAll();
    if (data.isEmpty())
        return;

    // Check push-to-talk state
    if (bPushToTalk && !bPttActive) {
        return; // Not transmitting due to PTT
    }

    // Process VAD if enabled
    if (bVoiceActivityDetection) {
        int energy = calculateEnergy(data);
        VoiceActivityLevel level;

        if (energy < vadThreshold * 0.3) {
            level = VAD_SILENCE;
        } else if (energy < vadThreshold) {
            level = VAD_LOW;
        } else if (energy < vadThreshold * 3) {
            level = VAD_MEDIUM;
        } else {
            level = VAD_HIGH;
        }

        currentVadLevel = level;
        emit voiceActivityChanged(level);

        // Only transmit if above silence threshold
        if (level == VAD_SILENCE) {
            return;
        }
    }

    // Add to capture buffer and process
    bufferMutex.lock();
    captureBuffer.append(data);
    bufferMutex.unlock();

    processAudioBuffer();
}

void VoiceEngine::processAudioBuffer()
{
    int frameSize = frameSizeMs * sampleRate * channels * sizeof(opus_int16) / 1000;

    bufferMutex.lock();
    if (captureBuffer.size() >= frameSize) {
        QByteArray frame = captureBuffer.left(frameSize);
        captureBuffer.remove(0, frameSize);
        bufferMutex.unlock();

        QByteArray encoded = encodeFrame(frame);
        if (!encoded.isEmpty()) {
            emit voiceCaptured(encoded);
        }
    } else {
        bufferMutex.unlock();
    }
}

int VoiceEngine::calculateEnergy(const QByteArray &data)
{
    const opus_int16 *samples = reinterpret_cast<const opus_int16*>(data.constData());
    int count = data.size() / sizeof(opus_int16);

    if (count == 0)
        return 0;

    double sum = 0;
    for (int i = 0; i < count; ++i) {
        sum += std::abs(samples[i]);
    }

    return static_cast<int>(sum / count);
}
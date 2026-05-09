#ifndef VOICEENGINE_H
#define VOICEENGINE_H

#include <QObject>
#include <QAudioInput>
#include <QAudioOutput>
#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include <QIODevice>
#include <QByteArray>
#include <QQueue>
#include <QMutex>
#include <opus/opus.h>

class VoiceEngine : public QObject
{
    Q_OBJECT
public:
    enum VoiceActivityLevel {
        VAD_SILENCE = 0,
        VAD_LOW,
        VAD_MEDIUM,
        VAD_HIGH
    };

    explicit VoiceEngine(QObject *parent = 0);
    ~VoiceEngine();

    // Audio capture
    void captureAudio();
    void stopCapture();

    // Encoding / decoding
    QByteArray encodeFrame(const QByteArray &pcmData);
    QByteArray decodeFrame(const QByteArray &opusData);

    // Playback
    void playAudio(const QByteArray &pcmData);
    void stopPlayback();

    // Push-to-talk
    void setPushToTalk(bool enabled);
    bool isPushToTalk() const;
    void setPttActive(bool active);

    // Voice activity detection
    void setVoiceActivityDetection(bool enabled);
    bool isVoiceActivityDetection() const;
    VoiceActivityLevel getVoiceActivityLevel() const;

    // Configuration
    void setFrameSizeMs(int ms);
    int getFrameSizeMs() const;
    void setSampleRate(int sampleRate);
    int getSampleRate() const;
    void setBitrate(int bitrate);
    int getBitrate() const;

    // State
    bool isCapturing() const;
    bool isPlaying() const;

signals:
    void voiceCaptured(const QByteArray &encodedData);
    void audioFrameReady(const QByteArray &pcmData);
    void voiceActivityChanged(VoiceActivityLevel level);
    void errorOccurred(const QString &errorString);

private:
    // Opus encoder/decoder
    OpusEncoder *opusEncoder;
    OpusDecoder *opusDecoder;

    // Audio devices
    QAudioInput *audioInput;
    QAudioOutput *audioOutput;
    QIODevice *audioInputDevice;
    QIODevice *audioOutputDevice;

    // Audio format
    QAudioFormat audioFormat;
    int frameSizeMs;
    int sampleRate;
    int bitrate;
    int channels;

    // Buffers
    QByteArray captureBuffer;
    QQueue<QByteArray> playbackQueue;
    QMutex bufferMutex;

    // State flags
    bool bPushToTalk;
    bool bPttActive;
    bool bVoiceActivityDetection;
    bool bCapturing;
    bool bPlaying;

    // VAD threshold
    int vadThreshold;

private slots:
    void onAudioDataAvailable();
    void processAudioBuffer();
};

#endif // VOICEENGINE_H
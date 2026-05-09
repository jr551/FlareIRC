#include <QtTest/QtTest>
#include "voiceengine.h"

class VoiceEngineTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testConstructor();
    void testFrameSizeValidation();
    void testVoiceActivityLevel();
    void testPushToTalk();
    void testVadEnabled();
    void testConfiguration();

private:
    VoiceEngine *engine;
};

void VoiceEngineTest::initTestCase()
{
    engine = new VoiceEngine();
}

void VoiceEngineTest::cleanupTestCase()
{
    delete engine;
}

void VoiceEngineTest::testConstructor()
{
    QVERIFY(engine != nullptr);
    QCOMPARE(engine->getSampleRate(), 48000);
    QCOMPARE(engine->getFrameSizeMs(), 20);
    QCOMPARE(engine->getBitrate(), 32000);
    QCOMPARE(engine->isCapturing(), false);
    QCOMPARE(engine->isPlaying(), false);
    QCOMPARE(engine->isPushToTalk(), false);
    QCOMPARE(engine->getVoiceActivityLevel(), VoiceEngine::VAD_SILENCE);
}

void VoiceEngineTest::testFrameSizeValidation()
{
    QByteArray emptyData;
    QByteArray result = engine->encodeFrame(emptyData);
    QVERIFY(result.isEmpty());
    QCOMPARE(engine->isCapturing(), false);
}

void VoiceEngineTest::testVoiceActivityLevel()
{
    engine->setVoiceActivityDetection(false);
    QCOMPARE(engine->getVoiceActivityLevel(), VoiceEngine::VAD_SILENCE);
    
    engine->setVoiceActivityDetection(true);
    QCOMPARE(engine->isVoiceActivityDetection(), true);
}

void VoiceEngineTest::testPushToTalk()
{
    engine->setPushToTalk(true);
    QCOMPARE(engine->isPushToTalk(), true);
    
    engine->setPttActive(true);
    QCOMPARE(engine->isPushToTalk(), true);
    
    engine->setPushToTalk(false);
    QCOMPARE(engine->isPushToTalk(), false);
}

void VoiceEngineTest::testVadEnabled()
{
    engine->setVoiceActivityDetection(true);
    QCOMPARE(engine->isVoiceActivityDetection(), true);
    
    engine->setVoiceActivityDetection(false);
    QCOMPARE(engine->isVoiceActivityDetection(), false);
}

void VoiceEngineTest::testConfiguration()
{
    engine->setFrameSizeMs(40);
    QCOMPARE(engine->getFrameSizeMs(), 40);
    
    engine->setSampleRate(22050);
    QCOMPARE(engine->getSampleRate(), 22050);
    
    engine->setBitrate(64000);
    QCOMPARE(engine->getBitrate(), 64000);
}

QTEST_MAIN(VoiceEngineTest)
#include "voiceenginetest.moc"
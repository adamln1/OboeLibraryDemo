#include <jni.h>
#include <string>
#include <oboe/Oboe.h>
#include <math.h>
#include "oboe/apps/fxlab/app/src/main/cpp/logging_macros.h"


class MyCallback : public oboe::AudioStreamCallback {
public:
    MyCallback() {
        oboe::AudioStreamBuilder builder;
        // The builder set methods can be chained for convenience.
        builder.setSharingMode(oboe::SharingMode::Exclusive)
                ->setPerformanceMode(oboe::PerformanceMode::LowLatency)
                ->setChannelCount(kChannelCount)
                ->setSampleRate(kSampleRate)
                ->setFormat(oboe::AudioFormat::Float)
                ->setCallback(this)
                ->openManagedStream(outStream);
        // Typically, start the stream after querying some stream information, as well as some input from the used
    }

    oboe::DataCallbackResult onAudioReady(oboe::AudioStream *oboeStream, void *audioData, int32_t numFrames) override {
        float *floatData = (float *) audioData;
        for (int i = 0; i < numFrames; ++i) {
            float sampleValue = kAmplitude * sinf(mPhase);
            for (int j = 0; j < kChannelCount; j++) {
                floatData[i * kChannelCount + j] = sampleValue;
            }
            mPhase += mPhaseIncrement;
            if (mPhase >= kTwoPi) mPhase -= kTwoPi;
        }
        return oboe::DataCallbackResult::Continue;
    }

    void start() {
        outStream->requestStart();
    }

    void pause() {
        outStream->requestStop();
    }

private:
    oboe::ManagedStream outStream;
    // Stream params
    static int constexpr kChannelCount = 2;
    static int constexpr kSampleRate = 48000;
    // Wave params, these could be instance variables in order to modify at runtime
    static float constexpr kAmplitude = 0.5f;
    static float constexpr kFrequency = 440;
    static float constexpr kPI = M_PI;
    static float constexpr kTwoPi = kPI * 2;
    static double constexpr mPhaseIncrement = kFrequency * kTwoPi / (double) kSampleRate;
    // Keeps track of where the wave is
    float mPhase = 0.0;
};

extern "C" {
    JNIEXPORT jstring JNICALL
    Java_com_demo_tutorialnativecpp_MainActivity_stringFromJNI(
            JNIEnv* env,
            jobject /* this */) {
        std::string hello = "Hello from C++";
        return env->NewStringUTF(hello.c_str());
    }

    JNIEXPORT void JNICALL
    Java_com_demo_tutorialnativecpp_MainActivity_setDefaultStreamValues(JNIEnv *env,
                                                            jobject type,
                                                            jint sampleRate,
                                                            jint framesPerBurst) {
        oboe::DefaultStreamValues::SampleRate = (int32_t) sampleRate;
        oboe::DefaultStreamValues::FramesPerBurst = (int32_t) framesPerBurst;
    }

    MyCallback myCallback;
    JNIEXPORT void JNICALL
    Java_com_demo_tutorialnativecpp_MainActivity_startSound(
            JNIEnv* env,
            jobject jobject) {
        myCallback.start();
    }

    JNIEXPORT void JNICALL
    Java_com_demo_tutorialnativecpp_MainActivity_stopSound(
            JNIEnv* env,
            jobject jobject) {
        myCallback.pause();
    }

}
#include <jni.h>
#include <string>
#include <android/log.h>

#define LOG_TAG "hook"
#define LOGV(...)  __android_log_print(ANDROID_LOG_VERBOSE,LOG_TAG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

extern "C" JNIEXPORT jstring JNICALL
Java_com_hook_yocn_MainActivity_stringFromJNI(JNIEnv *env, jobject obj, jstring param) {
    int length = (env)->GetStringLength(param);
    const char *nativeString = (env)->GetStringUTFChars(param, 0);
    char *resultChars = new char[length + 1];
    for (int i = 0; i < length; ++i) {
        resultChars[i] = nativeString[i] + 1;
    }
    resultChars[length] = '\0';
    std::string par = resultChars;
    LOGE("输入参数->%s,长度:%d", nativeString, length);
    LOGE("输出结果->%s", resultChars);
    return env->NewStringUTF(resultChars);
}

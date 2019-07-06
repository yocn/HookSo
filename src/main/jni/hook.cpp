#include <jni.h>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <android/log.h>
#include <android/bitmap.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string>

#define LOG_TAG "hook"
#define LOGV(...)  __android_log_print(ANDROID_LOG_VERBOSE,LOG_TAG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

using namespace std;

extern "C" {

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

//动态链接库路径
#define LIB_CACULATE_PATH "/data/data/com.ahook.yocn/lib/libnative-lib-src.so"

//函数指针
typedef jstring (*CAC_FUNC)(JNIEnv *env, jobject thiz, jstring param);

jstring callFunc(JNIEnv *env, jobject thiz, jstring param) {
    void *handle;
    char *error;
    CAC_FUNC cac_func = NULL;

    //打开动态链接库
    handle = dlopen(LIB_CACULATE_PATH, RTLD_LAZY);
    if (!handle) {
        LOGV("dlopen: %s\n", dlerror());
    }

    //清除之前存在的错误
    dlerror();

    //获取一个函数
    *(void **) (&cac_func) = dlsym(handle, "Java_com_hook_yocn_MainActivity_stringFromJNI");

    if ((error = const_cast<char *>(dlerror())) != NULL) {
        LOGV("dlsym: %s\n", error);
    }
    jstring ret = (*cac_func)(env, thiz, param);
//    printfJstring(env, thiz, ret);
    //关闭动态链接库
//    dlclose(handle);
    return ret;
}

JNIEXPORT jstring JNICALL
Java_com_hook_yocn_MainActivity_stringFromJNI(JNIEnv *env, jobject thiz, jstring param) {
    LOGE("Java_com_hook_yocn_MainActivity_stringFromJNI");
    string hookPre = "Hook_Head ";
    string paramString = (env)->GetStringUTFChars(param, 0) + hookPre;
    string modifyString = hookPre + paramString;
    jstring modifyParam = env->NewStringUTF(modifyString.c_str());
    jstring ss = callFunc(env, thiz, modifyParam);
    string rawResult = (env)->GetStringUTFChars(ss, 0);
    string hookEndString = rawResult + " Hook_End";
    return env->NewStringUTF(hookEndString.c_str());
}

} //extern "C"


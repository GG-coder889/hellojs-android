#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>
#include <jsapi.h>
#include <jsbindings.h>

#define  LOG_TAG    "hellojs-main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

extern "C"
{

JNIEXPORT jstring JNICALL
Java_org_cocos2dx_hellojs_getJSVMVersion (JNIEnv* env,
                                          jclass clazz) {
    LOGD("[JNI] Java_org_cocos2dx_hellojs_getJSVMVersion");
    const char* version_c_charbuf = JS_GetImplementationVersion();
    return (env->NewStringUTF(version_c_charbuf));
}

JNIEXPORT void JNICALL
Java_org_cocos2dx_hellojs_jsvmDiagnostics (JNIEnv* env,
                                         jobject clazz) {
    LOGD("[JNI] Java_org_cocos2dx_hellojs_jsvmDiagnostics");
}

JNIEXPORT jstring JNICALL
Java_org_cocos2dx_hellojs_getBindingsVersion (JNIEnv* env,
                                              jclass clazz) {
    LOGD("[JNI] Java_org_cocos2dx_hellojs_getBindingsVersion");
    const char* version_c_charbuf = jsbindings::getBindingsVersion();
    return (env->NewStringUTF(version_c_charbuf));
}

JNIEXPORT void JNICALL
Java_org_cocos2dx_hellojs_bindingsDiagnostics (JNIEnv* env,
                                               jobject clazz) {
    LOGD("[JNI] Java_org_cocos2dx_hellojs_bindingsDiagnostics");
    jsbindings::bindingsDiagnostics();
}

JNIEXPORT jstring JNICALL
Java_org_cocos2dx_hellojs_getCocosVersion (JNIEnv* env,
                                           jclass clazz) {
    LOGD("[JNI] Java_org_cocos2dx_hellojs_getCocosVersion");
    const char* version_c_charbuf = cocos2d::cocos2dVersion();
    return (env->NewStringUTF(version_c_charbuf));
}

JNIEXPORT void JNICALL
Java_org_cocos2dx_hellojs_cocosDiagnostics (JNIEnv* env,
                                            jobject clazz) {
    LOGD("[JNI] Java_org_cocos2dx_hellojs_cocosDiagnostics");
}

static JNINativeMethod hellojs_methods[] = {
    {"getJSVMVersion",      "()Ljava/lang/String;", (void *)&Java_org_cocos2dx_hellojs_getJSVMVersion},
    {"jsvmDiagnostics",     "()V",                  (void *)&Java_org_cocos2dx_hellojs_jsvmDiagnostics},
    {"getBindingsVersion",  "()Ljava/lang/String;", (void *)&Java_org_cocos2dx_hellojs_getBindingsVersion},
    {"bindingsDiagnostics", "()V",                  (void *)&Java_org_cocos2dx_hellojs_bindingsDiagnostics},
    {"getCocosVersion",     "()Ljava/lang/String;", (void *)&Java_org_cocos2dx_hellojs_getCocosVersion},
    {"cocosDiagnostics",    "()V",                  (void *)&Java_org_cocos2dx_hellojs_cocosDiagnostics},
};
    
jint JNI_OnLoad (JavaVM *vm, void *reserved) {
    LOGD("JNI_OnLoad vm : 0x%X, reserved : 0x%X", vm, reserved);

    cocos2d::JniHelper::setJavaVM(vm);
    JNIEnv* env;
    vm->GetEnv((void**)&env, JNI_VERSION_1_4);

    // Register methods for org.cocos2dx.hellojs.HelloJS
    jclass hellojs_class = env->FindClass("org/cocos2dx/hellojs/HelloJS");
    env->RegisterNatives(hellojs_class,
                         hellojs_methods,
                         sizeof(hellojs_methods)/sizeof(hellojs_methods[0]));
    
    LOGD("return JNI_VERSION_1_4");
	return JNI_VERSION_1_4;
}

}

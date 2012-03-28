#include <jni.h>
#include <android/log.h>

#include <jsapi.h>

#include <cocos2d.h>
#include <platform/android/jni/JniHelper.h>

#include <jsbindings.h>

#include <JNI_org_cocos2dx_js_bindings.h>

namespace JNI_org_cocos2dx_js_bindings {

#define  LOG_TAG    "JNI_org_cocos2dx_js_Bindings"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

    JNIEXPORT jstring JNICALL
    Java_org_cocos2dx_js_bindings_getJSVMVersion (JNIEnv* env,
                                                  jclass clazz) {
        LOGD("Java_org_cocos2dx_js_bindings_getJSVMVersion");
        const char* version_c_charbuf = JS_GetImplementationVersion();
        return (env->NewStringUTF(version_c_charbuf));
    }

    JNIEXPORT void JNICALL
    Java_org_cocos2dx_js_bindings_jsvmDiagnostics (JNIEnv* env,
                                                   jobject clazz) {
        LOGD("Java_org_cocos2dx_js_bindings_jsvmDiagnostics");
    }

    JNIEXPORT jstring JNICALL
    Java_org_cocos2dx_js_bindings_getBindingsVersion (JNIEnv* env,
                                                      jobject clazz) {
        LOGD("Java_org_cocos2dx_js_bindings_getBindingsVersion");
        const char* version_c_charbuf = jsbindings::getBindingsVersion();
        return (env->NewStringUTF(version_c_charbuf));
    }

    JNIEXPORT void JNICALL
    Java_org_cocos2dx_js_bindings_bindingsDiagnostics (JNIEnv* env,
                                                       jobject clazz) {
        LOGD("Java_org_cocos2dx_js_bindings_bindingsDiagnostics");
        jsbindings::bindingsDiagnostics();
    }

    JNIEXPORT jstring JNICALL
    Java_org_cocos2dx_js_bindings_getCocosVersion (JNIEnv* env,
                                                   jobject clazz) {
        LOGD("Java_org_cocos2dx_js_bindings_getCocosVersion");
        const char* version_c_charbuf = cocos2d::cocos2dVersion();
        return (env->NewStringUTF(version_c_charbuf));
    }

    JNIEXPORT void JNICALL
    Java_org_cocos2dx_js_bindings_cocosDiagnostics (JNIEnv* env,
                                                    jobject clazz) {
        LOGD("Java_org_cocos2dx_js_bindings_cocosDiagnostics");
    }

    static JNINativeMethod bindings_methods[] = {
        {"getJSVMVersion",      "()Ljava/lang/String;", (void *)&Java_org_cocos2dx_js_bindings_getJSVMVersion},
        {"jsvmDiagnostics",     "()V",                  (void *)&Java_org_cocos2dx_js_bindings_jsvmDiagnostics},
        {"getBindingsVersion",  "()Ljava/lang/String;", (void *)&Java_org_cocos2dx_js_bindings_getBindingsVersion},
        {"bindingsDiagnostics", "()V",                  (void *)&Java_org_cocos2dx_js_bindings_bindingsDiagnostics},
        {"getCocosVersion",     "()Ljava/lang/String;", (void *)&Java_org_cocos2dx_js_bindings_getCocosVersion},
        {"cocosDiagnostics",    "()V",                  (void *)&Java_org_cocos2dx_js_bindings_cocosDiagnostics},
    };

    // Register methods for org.cocos2dx.js.Bindings
    void registernatives(JNIEnv* env) {
        jclass bindings_class = env->FindClass("org/cocos2dx/js/Bindings");
        env->RegisterNatives(bindings_class,
                             bindings_methods,
                             sizeof(bindings_methods)/sizeof(bindings_methods[0]));
    }

}

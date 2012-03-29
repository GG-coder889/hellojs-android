#include <stdlib.h>

#include <jni.h>
#include <android/log.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

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

    JNIEXPORT void JNICALL
    Java_org_cocos2dx_js_bindings_runJSFromAssets (JNIEnv* env,
                                                   jobject thiz,
                                                   jobject java_assetmanager,
                                                   jstring java_relativepath) {
        LOGD("Java_org_cocos2dx_js_bindings_runJSFromAssets");

        // relative path
        const char* relativepath;
        relativepath = env->GetStringUTFChars(java_relativepath, NULL);
        if (NULL == relativepath) {
            LOGD("relativepath : is NULL");
            return; // OutOfMemoryError already thrown
        }
        LOGD("relativepath : %s", relativepath);

        AAssetManager* assetmanager =
            AAssetManager_fromJava(env, java_assetmanager);
        if (NULL == assetmanager) {
            LOGD("assetmanager : is NULL");
            return;
        }

        // read asset data
        AAsset* asset =
            AAssetManager_open(assetmanager,
                               relativepath,
                               AASSET_MODE_UNKNOWN);
        if (NULL == asset) {
            LOGD("asset : is NULL");
            return;
        }

        off_t size = AAsset_getLength(asset);
        LOGD("size = %d ", size);

        char* buf = (char*) malloc(size+1);
        if (NULL == buf) {
            LOGD("asset : is NULL");
            AAsset_close(asset);
            return;
        }

        int bytesread = AAsset_read(asset, (void*)buf, size);
        LOGD("bytesread = %d ", bytesread);
        buf[size] = '\0';

        AAsset_close(asset);

        env->ReleaseStringUTFChars(java_relativepath, relativepath);
    }

    static JNINativeMethod bindings_methods[] = {
        {"getJSVMVersion",      "()Ljava/lang/String;",                                    (void *)&Java_org_cocos2dx_js_bindings_getJSVMVersion},
        {"jsvmDiagnostics",     "()V",                                                     (void *)&Java_org_cocos2dx_js_bindings_jsvmDiagnostics},
        {"getBindingsVersion",  "()Ljava/lang/String;",                                    (void *)&Java_org_cocos2dx_js_bindings_getBindingsVersion},
        {"bindingsDiagnostics", "()V",                                                     (void *)&Java_org_cocos2dx_js_bindings_bindingsDiagnostics},
        {"getCocosVersion",     "()Ljava/lang/String;",                                    (void *)&Java_org_cocos2dx_js_bindings_getCocosVersion},
        {"cocosDiagnostics",    "()V",                                                     (void *)&Java_org_cocos2dx_js_bindings_cocosDiagnostics},
        {"runJSFromAssets",     "(Landroid/content/res/AssetManager;Ljava/lang/String;)V", (void *)&Java_org_cocos2dx_js_bindings_runJSFromAssets},
    };

    // Register methods for org.cocos2dx.js.Bindings
    void registernatives(JNIEnv* env) {
        jclass bindings_class = env->FindClass("org/cocos2dx/js/Bindings");
        env->RegisterNatives(bindings_class,
                             bindings_methods,
                             sizeof(bindings_methods)/sizeof(bindings_methods[0]));
    }

}

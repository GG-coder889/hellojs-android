#include "jsbindings.h"
#include <string>

#include <android/log.h>

#include <jsapi.h>

namespace jsbindings {

#define  LOG_TAG    "jsbindings.cpp"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

    static const std::string VERSION = "Unknown Version";

    const char* getBindingsVersion (void) {
        return VERSION.c_str();
    }

/* The class of the global object. */
    static JSClass global_class =
        {"global",
         JSCLASS_GLOBAL_FLAGS,
         JS_PropertyStub,
         JS_PropertyStub,
         JS_PropertyStub,
         JS_StrictPropertyStub,
         JS_EnumerateStub,
         JS_ResolveStub,
         JS_ConvertStub,
         JS_FinalizeStub,
         JSCLASS_NO_OPTIONAL_MEMBERS};

    /* The error reporter callback. */
    void reportError(JSContext *cx, const char *message, JSErrorReport *report) {
        LOGD("%s:%u:%s\n",
             report->filename ? report->filename : "<no filename>",
             (unsigned int) report->lineno,
             message);
    }

    int runJS(char* script) {
        LOGD("runJS");
        // LOGD("script :\n%s", script);

        /* JS variables. */
        JSRuntime *rt;
        JSContext *cx;
        JSObject *global; 

        /* Create a JS runtime. */
        rt = JS_NewRuntime(8L * 1024L * 1024L);
        if (rt == NULL) {
            LOGD("(rt == NULL)");
            return 1;
        }

        /* Create a context. */
        cx = JS_NewContext(rt, 8192);
        if (cx == NULL) {
            LOGD("(cx == NULL)");
            return 1;
        }

        JS_SetOptions(cx, JSOPTION_VAROBJFIX);
        JS_SetVersion(cx, JSVERSION_LATEST);
        JS_SetErrorReporter(cx, reportError);

        /* Create the global object in a new compartment. */
        global = JS_NewCompartmentAndGlobalObject(cx, &global_class, NULL);
        if (global == NULL) {
            LOGD("(global == NULL)");
            return 1;
        }

        /* Populate the global object with the standard globals, like Object and Array. */
        if (!JS_InitStandardClasses(cx, global)) {
            LOGD("(!JS_InitStandardClasses(cx, global))");
            return 1;
        }

        // . . .
        /* Your application code here. This may include JSAPI calls to create your own custom JS objects and run scripts. */
        //. . .
        /* Cleanup. */

        JS_DestroyContext(cx);
        JS_DestroyRuntime(rt);
        JS_ShutDown();

        LOGD("runJS done with no reported errors");
        return 0;
    }

    void bindingsDiagnostics (void) {
    }
}

#ifndef __JS_BINDINGS__
#define __JS_BINDINGS__ 

namespace jsbindings {
    const char* getBindingsVersion(void);
    void bindingsDiagnostics(void);
    int runJS(char* script);
}

#endif // __JS_BINDINGS__

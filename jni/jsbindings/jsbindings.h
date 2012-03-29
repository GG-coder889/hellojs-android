#ifndef __JS_BINDINGS__
#define __JS_BINDINGS__ 

namespace jsbindings {
    const char* getBindingsVersion(void);
    void bindingsDiagnostics(void);
    void runJS(char* script);
}

#endif // __JS_BINDINGS__

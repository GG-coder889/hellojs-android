#include "jsbindings.h"
#include <string>

namespace jsbindings {

    static const std::string VERSION = "Unknown Version";

    const char* getBindingsVersion (void) {
        return VERSION.c_str();
    }

    void bindingsDiagnostics (void) {
    }
}

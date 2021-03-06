#pragma once

#include <dlfcn.h>
#include <stdio.h>

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include "LoaderError.hpp"
#include "spc/common/DLType.hpp"

namespace arc::core {

template <DLType Type, typename T>
class Loader {
 private:
    typedef T* (*LoaderFunction)();
    typedef void (*UnloaderFunction)(T*);
    typedef DLType (*GetTypeFunction)();
    typedef char* (*GetNameFunction)();
    static inline std::unordered_map<T*, void*> _loaded;

 public:
    static std::string getName(const std::string& name)
    {
        void* handle = dlopen(name.c_str(), RTLD_LAZY | RTLD_NODELETE);
        if (!handle) {
            throw LoaderError(dlerror());
        }

        GetNameFunction getName = (GetNameFunction)dlsym(handle, "getName");
        if (!getName) {
            return name.substr(name.find_last_of("/\\") + 1);
        }
        std::string libName = getName();
        dlclose(handle);
        return (libName);
    }

    static bool isLoadable(const std::string& name)
    {
        void* handle = dlopen(name.c_str(), RTLD_LAZY | RTLD_NODELETE);
        if (!handle) {
            return false;
        }

        GetTypeFunction getType = (GetTypeFunction)dlsym(handle, "getType");
        if (!getType) {
            dlclose(handle);
            return false;
        }
        int libType = getType();
        dlclose(handle);
        return (libType == Type);
    }

    static T* load(const std::string& name)
    {
        void* handle = dlopen(name.c_str(), RTLD_LAZY);
        if (!handle) {
            throw LoaderError(dlerror());
        }

        LoaderFunction load = (LoaderFunction)dlsym(handle, "expose");
        if (!load) {
            dlclose(handle);
            throw LoaderError(dlerror());
        }

        GetTypeFunction getType = (GetTypeFunction)dlsym(handle, "getType");
        if (!getType) {
            dlclose(handle);
            throw LoaderError(dlerror());
        }
        int libType = getType();
        if (libType != Type) {
            dlclose(handle);
            throw LoaderError("Trying to load a library that is"
                              " not of correct type.");
        }

        T* ret = load();
        if (!ret) {
            throw LoaderError("Returned nullptr");
        }
        _loaded.insert(std::make_pair(ret, handle));
        return ret;
    }

    static void unload(T* t)
    {
        if (t == nullptr) {
            throw LoaderError("Trying to unload nullptr");
        }
        auto it = _loaded.find(t);
        if (it == _loaded.end()) {
            throw LoaderError("Trying to unload an unexisting object");
        }
        void* handle = it->second;
        if (handle == nullptr) {
            throw LoaderError("Trying to unload an unexisting object");
        }

        GetTypeFunction getType = (GetTypeFunction)dlsym(handle, "getType");
        if (!getType) {
            throw LoaderError(dlerror());
        }
        int libType = getType();
        if (libType != Type) {
            throw LoaderError("Trying to unload a library that is"
                              " not of correct type.");
        }

        UnloaderFunction unload = (UnloaderFunction)dlsym(handle, "unexpose");
        if (!unload) {
            throw LoaderError(dlerror());
        }
        unload(t);

        if (dlclose(handle) != 0) {
            throw LoaderError(dlerror());
        }
        _loaded.erase(it);
    }
};

} // namespace arc::core

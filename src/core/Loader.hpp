#pragma once

#include <dlfcn.h>
#include <stdio.h>

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include "LoaderError.hpp"

namespace arc::core {

template <typename T>
class Loader {
 private:
    typedef T* (*LoaderFunction)();
    typedef void (*UnloaderFunction)(T*);
    static inline std::unordered_map<T*, void*> _loaded;

 public:
    static T* load(const std::string& name)
    {
        void* handle = dlopen(name.c_str(), RTLD_LAZY);
        if (!handle) {
            throw LoaderError(dlerror());
        }

        LoaderFunction func = (LoaderFunction)dlsym(handle, "expose");
        if (!func) {
            throw LoaderError(dlerror());
        }

        T* ret = func();
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
        UnloaderFunction func = (UnloaderFunction)dlsym(handle, "unexpose");
        if (!func) {
            throw LoaderError(dlerror());
        }
        func(t);

        if (dlclose(handle) != 0) {
            throw LoaderError(dlerror());
        }
        _loaded.erase(it);
    }
};

} // namespace arc::core

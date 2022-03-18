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
        void* handle = _loaded.find(t)->second;
        UnloaderFunction func = (UnloaderFunction)dlsym(handle, "unexpose");
        if (!func) {
            throw LoaderError(dlerror());
        }
        func(t);

        if (dlclose(handle) != 0) {
            throw LoaderError(dlerror());
        }
    }
};

} // namespace arc::core

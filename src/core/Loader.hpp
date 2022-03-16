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
        _loaded.insert(std::make_pair(ret, handle));
        return ret;
    }

    static void unload(T* t)
    {
        void* handle = _loaded.find(t)->second;
        if (dlclose(handle) != 0) {
            throw LoaderError(dlerror());
        }
    }
};

} // namespace arc::core

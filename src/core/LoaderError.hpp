#pragma once

#include <iostream>
#include <stdexcept>

namespace arc::core {

class LoaderError : public std::exception {
 private:
    std::string _msg;

 public:
    LoaderError(const std::string& msg)
        : _msg(msg) { }
    virtual ~LoaderError() throw() { }
    virtual const char* what() const throw() { return _msg.c_str(); }
};

} // namespace arc::core

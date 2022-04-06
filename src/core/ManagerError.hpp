#pragma once

#include <iostream>
#include <stdexcept>

namespace arc::core {

class ManagerError : public std::exception {
 private:
    std::string _msg;

 public:
    ManagerError(const std::string& msg)
        : _msg(msg)
    {
    }
    virtual ~ManagerError() throw() { }
    virtual const char* what() const throw() { return _msg.c_str(); }
};

} // namespace arc::core

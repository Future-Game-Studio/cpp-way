#pragma once
#include <exception>
#include <string>
class fileNotReady : public std::exception
{
    std::string _msg;

public:
    virtual const char* what() const throw()
    { return _msg.c_str(); }

    explicit fileNotReady(const std::string& msg) throw()
    : _msg(msg)
    {}

    virtual ~fileNotReady() throw()
    {}
};

class NullObjectException : public std::exception
{
    std::string _msg;

public:
    virtual const char* what() const throw()
    { return _msg.c_str(); }

    explicit NullObjectException(const std::string& msg) throw()
    : _msg(msg)
    {}

    virtual ~NullObjectException() throw()
    {} 
};
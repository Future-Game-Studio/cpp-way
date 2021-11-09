#pragma once
#include <exception>
#include <string>
class fileNotReady : public std::exception
{
    std::string message;

public:
    fileNotReady(std::string message) : message(message)
    {
    }
    const std::string& Message()
    {
        return message;
    }
};
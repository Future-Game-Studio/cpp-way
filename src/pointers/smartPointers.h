#pragma once
#ifndef _SMART_POINTERS
#define _SMART_POINTERS
#include <iostream>
#include <memory>

class SomeClass
{
    int nonMutableVal = 5;
    mutable int mutableVal = 7;
    std::string _name;

public:
    SomeClass(const std::string &name) : _name(name)
    {
        std::cout << "Created " << _name << std::endl;
    }

    ~SomeClass()
    {
        std::cout << "Destroyed " << _name << std::endl;
    }
};

#endif

void PassPtr(const std::weak_ptr<SomeClass> &ptr)
{
    // retreive object
    if (!ptr.expired())
    {
        std::shared_ptr<SomeClass> f = ptr.lock();
        auto obj = f.get();
        // do something with object
    }
}

void SmartSharedPtr()
{
    std::shared_ptr<SomeClass> largePtr = std::make_shared<SomeClass>("Test shared_ptr");
    // or
    // std::shared_ptr largePtr = std:shared_ptr(new SomeClass("Test shared_ptr"));

    {
        std::shared_ptr<SomeClass> ptr2 = largePtr;

        if (largePtr)
        {
            // do something with ptr
            std::shared_ptr<SomeClass> ptr3 = largePtr;

            PassPtr(largePtr); // auto cast

            std::cout << "ptr3 deleted" << std::endl;
        }
        std::cout << "ptr2 deleted" << std::endl;
    }

    largePtr.reset(); // delete manually
}

void SmartUniquePtr()
{
    std::shared_ptr<SomeClass> largePtr = std::make_shared<SomeClass>("Test unique_ptr");

    // error. ptr must be unique
    //std::unique_ptr ptr2 = largePtr;
}

void SmartWeakPtr()
{
    std::shared_ptr<SomeClass> largePtr = std::make_shared<SomeClass>("Test weak_ptr");

    {
        if (largePtr)
        {
            // do something with ptr
        }
        std::weak_ptr<SomeClass> ptr2 = largePtr;

        if (!ptr2.expired())
        {
            // do something with ptr
        }
    }

    largePtr.reset(); // delete manually
}
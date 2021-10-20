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

    void SetSomeValue(const int & value) const
    {
        mutableVal = value;
    }

    ~SomeClass()
    {
        std::cout << "Destroyed " << _name << std::endl;
    }

    std::weak_ptr<SomeClass> *Target;
};

#endif

void PassPtr(const std::weak_ptr<SomeClass> &ptr)
{
    const SomeClass *obj = new SomeClass("test");
    obj->SetSomeValue(100);

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
    auto obj1 = new SomeClass("obj1");
    auto obj2 = new SomeClass("obj1");
    auto obj1Shared = std::make_shared<SomeClass>(*obj1);
    auto obj2Shared = std::make_shared<SomeClass>(*obj2);
    std::weak_ptr<SomeClass> obj1weak = obj1Shared;
    std::weak_ptr<SomeClass> obj2weak = obj2Shared;
    obj1->Target = &obj1weak;
    obj2->Target = &obj2weak;

    std::shared_ptr<SomeClass> largePtr = std::make_shared<SomeClass>("Test shared_ptr");
    // or
    //std::shared_ptr<SomeClass> largePtr = std::shared_ptr<SomeClass>(new SomeClass("Test shared_ptr"));

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
    std::unique_ptr<int> largePtr = std::make_unique<int>();

    // error. ptr must be unique
    //std::unique_ptr<int> ptr2 = largePtr;

    if (largePtr)
    {
        auto objPtr = largePtr.get();
    }
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
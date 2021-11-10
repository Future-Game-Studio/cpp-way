#pragma once
#include <iostream>
#include "../../behavioral/abstractShapeVisitor.h"
#include "../../helpers/debug.h"
#include <functional>

class Shape
{
private:
    int _baseSize;
    std::function<void(std::string &)> cylinderDataEvent;

protected:
    std::string _name; // why it's not const &

public:
    Shape(int size, std::string name) : Shape(size)
    {
        _name = name; // copy
#ifdef DEBUG_OBJECT_LIFETIME
        std::cout << "Shape " << name << " created. Base size: " << _baseSize << std::endl;
#endif
    }

    Shape(int size)
    {
        _baseSize = size;
    }

    virtual float GetArea() const = 0; // pure virtual function

    virtual void Accept(AbstractShapeVisitor *visitor) const = 0; // pure virtual function

    // event registration for data change
    void RegisterDataChangeHandler(const std::function<void(std::string &)> &handler)
    {
        this->cylinderDataEvent = handler;
    }
    
    const std::string& GetName() const
    {
        return _name;
    }

    void SetData(std::string &data)
    {
        this->_name = data;
        if (this->cylinderDataEvent != nullptr)
        {
            // data change callback event
            this->cylinderDataEvent(data);
        }
    }

    virtual ~Shape()
    {
#ifdef DEBUG_OBJECT_LIFETIME
        std::cout << "Shape " << _name << " disposed" << std::endl;
#endif
    }
};

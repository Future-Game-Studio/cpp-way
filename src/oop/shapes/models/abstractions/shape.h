#pragma once
#include "../../behavioral/abstractShapeVisitor.h"
#include <iostream>
#include "../../helpers/debug.h"

class Shape
{
private:
    int _baseSize;

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

    virtual ~Shape()
    {
#ifdef DEBUG_OBJECT_LIFETIME
        std::cout << "Shape " << _name << " disposed" << std::endl;
#endif
    }
};

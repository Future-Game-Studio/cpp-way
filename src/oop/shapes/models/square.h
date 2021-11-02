#pragma once
#include "abstractions/shape.h"
#include <math.h>
#include <string>

class Square : public Shape
{
    float sizeX;
    float sizeY;

public:
    Square(float sx, float sy) : Shape(sx), sizeX(sx), sizeY(sy)
    {
        _name = "square(x" + std::to_string(sx) + ",y" + std::to_string(sy) + ")";
        // OR
        this->sizeY = sy;
        this->sizeX = sx;
#ifdef DEBUG_OBJECT_LIFETIME
        std::cout << "Square " << _name << " created." << std::endl;
#endif
    }

    ~Square() override
    {
        // base destructor called automatically
        // don't call Shape::~Shape();

#ifdef DEBUG_OBJECT_LIFETIME
        std::cout << "Square disposed" << std::endl
                  << std::endl;
#endif
    }

    inline float GetY() const { return sizeY; }
    inline float GetX() const { return sizeX; }

    float GetArea() const override
    {
        return sizeX * sizeY;
    }

    Square operator+(Square &obj) const
    {
        return Square(std::max(obj.sizeX, sizeX), std::max(obj.sizeY, sizeY));
    }

    void Accept(AbstractShapeVisitor *visitor) const override
    {
        visitor->Visit(this);
    }
};
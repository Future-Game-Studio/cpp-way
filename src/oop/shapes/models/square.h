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
        name = "square(x" + std::to_string(sx) + ",y" + std::to_string(sy) + ")";
        // OR
        // this->y = y;
        // this->x = x;
        std::cout << "Square " << name << " created." << std::endl;
    }

    ~Square() override
    {
        // base destructor called automatically
        // don't call Shape::~Shape();
        std::cout << "Square disposed" << std::endl
                  << std::endl;
    }

    float GetArea() const override
    {
        return sizeX * sizeY;
    }

    Square operator+(Square &obj) const
    {
        return Square(std::max(obj.sizeX, sizeX), std::max(obj.sizeY, sizeY));
    }
};
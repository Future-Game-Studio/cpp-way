#pragma once
#include <math.h>
#include "abstractions/shape.h"
#include "../math/m_pi.h"
#include <string>

class Cylinder : public Shape
{
private:
    float r, h;

public:
    Cylinder(float r, float h) : Shape(h, "cylinder"), r(r), h(h)
    {
        _name = "cylinder(r" + std::to_string(r) + ",h" + std::to_string(h) + ")";
        std::cout << "Cylinder " << _name << " created." << std::endl;
    }

    float GetArea() const override 
    {
        return 2 * pi() * r * h + 2 * pi() * std::pow(r, 2);
    }
};

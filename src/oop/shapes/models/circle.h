#pragma once
#include <math.h>
#include "../math/m_pi.h"
#include <string>
#include "../models/abstractions/shape.h"

class Circle : public Shape
{
private:
    float r;

protected:
    Circle(float r, std::string name) : Shape(r, name), r(r)
    {
    }

public:
    Circle(float r) : Shape(r, "cirle"), r(r)
    {
        _name = "circle(r" + std::to_string(r) + ")";
#ifdef DEBUG_OBJECT_LIFETIME
        std::cout << "Circle " << _name << " created." << std::endl;
#endif
    }

    float GetArea() const override
    {
        return pi() * std::pow(r, 2);
    }

    inline float GetRadius() const { return r; }

    void Accept(AbstractShapeVisitor *visitor) const override
    {
        visitor->Visit(this);
    }
};

#pragma once
#include <math.h>
#include "abstractions/shape.h"
#include "circle.h"
#include "../math/m_pi.h"
#include "../helpers/debug.h"
#include <string>

class Cylinder : public Circle
{
private:
    float _r, _h;

public:
    Cylinder(float r, float h) : Circle(r, "cylinder"), _r(r), _h(h)
    {
        _name = "cylinder(r" + std::to_string(r) + ",h" + std::to_string(h) + ")";
#ifdef DEBUG_OBJECT_LIFETIME
        std::cout << "Cylinder " << _name << " created." << std::endl;
#endif
    }

    inline float GetHeight() const { return _h; }

    float GetArea() const override
    {
        return 2 * pi() * _r * _h + 2 * pi() * std::pow(_r, 2);
    }

    void Accept(AbstractShapeVisitor *visitor) const override
    {
        visitor->Visit(this);
    }
};

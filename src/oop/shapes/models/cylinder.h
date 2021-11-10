#pragma once
#include <math.h>
#include "abstractions/shape.h"
#include "circle.h"
#include "../math/m_pi.h"
#include "../helpers/debug.h"
#include <string>
#include <functional>

class Cylinder : public Circle
{
private:
    float _r, _h;
    std::function<void(Cylinder&)> _handler;

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

    void RegisterDataChangeHandler(const std::function<void(Cylinder&)> &lam)
    {
        this->_handler = lam;
    }

    void SetData(Cylinder &other)
    {
        this->_r = other._r;
        this->_h = other._h;
        this->_name = other._name;
        _handler(other);
    }
};

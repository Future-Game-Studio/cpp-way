#pragma once
#include "abstractions/shape.h"
#include <math.h>
#include <string>

class RectShape : public Shape
{
    float sizeX;
    float sizeY;
    std::function<void(RectShape&)> _handler;

public: 
    RectShape(float sx, float sy) : Shape(sx), sizeX(sx), sizeY(sy)
    {
        _name = "rectangle(x" + std::to_string(sx) + ",y" + std::to_string(sy) + ")";
        // OR
        this->sizeY = sy;
        this->sizeX = sx;
#ifdef DEBUG_OBJECT_LIFETIME
        std::cout << "RectShape " << _name << " created." << std::endl;
#endif
    }

    ~RectShape() override
    {
        // base destructor called automatically
        // don't call Shape::~Shape();

#ifdef DEBUG_OBJECT_LIFETIME
        std::cout << "RectShape disposed" << std::endl
                  << std::endl;
#endif
    }

    inline float GetY() const { return sizeY; }
    inline float GetX() const { return sizeX; }

    float GetArea() const override
    {
        return sizeX * sizeY;
    }

    RectShape operator+(RectShape &obj) const
    {
        return RectShape(std::max(obj.sizeX, sizeX), std::max(obj.sizeY, sizeY));
    }

    void Accept(AbstractShapeVisitor *visitor) const override
    {
        visitor->Visit(this);
    }

    void RegisterDataChangeHandler(const std::function<void(RectShape&)> &lam)
    {
        this->_handler = lam;
    }

    void SetData(RectShape &other)
    {
        this->sizeX = other.sizeX;
        this->sizeY = other.sizeY;
        this->_name = other._name;
        _handler(other);
    }
};
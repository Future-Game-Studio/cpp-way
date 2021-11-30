#pragma once  
#include "../models/abstractions/shape.h"

class Shape;
class Cylinder;
class RectShape;
class Circle;

class AbstractShapeVisitor
{
public:
    virtual void Visit(const Cylinder *item) const = 0;
    virtual void Visit(const RectShape *item) const = 0;
    virtual void Visit(const Circle *item) const = 0;
};
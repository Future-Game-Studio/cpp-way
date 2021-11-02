#pragma once  
#include "../models/abstractions/shape.h"

class Shape;
class Cylinder;
class Square;
class Circle;

class AbstractShapeVisitor
{
public:
    virtual void Visit(const Cylinder *item) const = 0;
    virtual void Visit(const Square *item) const = 0;
    virtual void Visit(const Circle *item) const = 0;
};
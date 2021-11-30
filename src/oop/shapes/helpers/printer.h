#pragma once
#include <iostream>
#include <typeinfo>
#include "../models/abstractions/shape.h"
#include "../models/rectangle.h"
#include "../models/cylinder.h"

static void printArea(const RectShape &shape, std::ostream *logger)
{
    *logger << "Custom implementation of printer for RectShape" << std::endl;
    *logger << "RectShape area (custom): " << shape.GetArea() << std::endl;
}

static void printArea(const Shape &shape, std::ostream *logger)
{
    std::string objectName;
    if (typeid(shape) == typeid(RectShape))
    {
        objectName = "RectShape area: ";
    }
    else if (typeid(shape) == typeid(Cylinder))
    {
        objectName = "Cylinder area: ";
    }
    else
    {
        objectName = "Shape area: ";
    }
    *logger << objectName << shape.GetArea() << std::endl;
}
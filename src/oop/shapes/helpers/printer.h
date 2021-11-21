#pragma once
#include <iostream>
#include <typeinfo>
#include "../models/abstractions/shape.h"
#include "../models/square.h"
#include "../models/cylinder.h"

static void printArea(const Square &shape, std::ostream *logger)
{
    *logger << "Custom implementation of printer for Square" << std::endl;
    *logger << "Square area (custom): " << shape.GetArea() << std::endl;
}

static void printArea(const Shape &shape, std::ostream *logger)
{
    std::string objectName;
    if (typeid(shape) == typeid(Square))
    {
        objectName = "Square area: ";
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
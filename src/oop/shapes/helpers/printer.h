#pragma once
#include <iostream>
#include <typeinfo>
#include "../models/abstractions/shape.h"
#include "../models/square.h"
#include "../models/cylinder.h"

void printArea(const Square &shape)
{
    std::cout << "Custom implementation of printer for Square" << std::endl;
    std::cout << "Square area (custom): " << shape.GetArea() << std::endl;
}

void printArea(const Shape &shape)
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
    std::cout << objectName << shape.GetArea() << std::endl;
}
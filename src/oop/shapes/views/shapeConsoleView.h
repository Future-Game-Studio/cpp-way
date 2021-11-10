#pragma once
#include <iostream>
#include "../models/abstractions/shape.h"

class ShapeConsoleView
{
private:
    Shape *model;

public:
    ShapeConsoleView() {}
    ShapeConsoleView(Shape *model)
    {
        this->model = model;
    }
    void SetShape(Shape *model)
    {
        this->model = model;
    }

    virtual void Render()
    {
        if (model != nullptr)
        {
            std::cout << std::endl;
            std::cout << " ### ------ Preety console output ------ ###" << std::endl;
            std::cout << "     > Console Viewer Of Shapes >> (name) " << model->GetName() << std::endl;
            std::cout << "     > Console Viewer Of Shapes >> (area) " << model->GetArea() << std::endl;
            std::cout << " ### ------ < end of Shape view >  ------ ###" << std::endl;
            std::cout << std::endl;
        }
    }
};
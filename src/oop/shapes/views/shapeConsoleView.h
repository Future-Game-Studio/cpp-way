#pragma once
#include <iostream>
#include "../models/abstractions/shape.h"

class ShapeConsoleView
{
private:
    Shape *model;
    std::ostream *logger;

public:
    ShapeConsoleView() {}

    ShapeConsoleView(Shape *model, std::ostream *logger) : logger(logger), model(model)
    {
        this->model = model;
    }

    void SetShape(Shape *model)
    {
        this->model = model;
    }

    virtual void Render()
    {
        if (!model || !logger)
            return;

        *logger << std::endl;
        *logger << " ### ------ Preety console output ------ ###" << std::endl;
        *logger << "     > Console Viewer Of Shapes >> (name) " << model->GetName() << std::endl;
        *logger << "     > Console Viewer Of Shapes >> (area) " << model->GetArea() << std::endl;
        *logger << " ### ------ < end of Shape view >  ------ ###" << std::endl;
        *logger << std::endl;
    }
};
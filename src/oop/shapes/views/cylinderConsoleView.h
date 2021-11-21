#pragma once
#include <iostream>
#include <iomanip>
#include "../models/cylinder.h"
#include "../helpers/exceptions.h"

class CylinderConsoleView : public ShapeConsoleView
{
private:
    Cylinder *model;
    std::ostream *logger;

public:
    CylinderConsoleView() {}
    CylinderConsoleView(Cylinder *model, std::ostream *logger) : logger(logger), model(model)
    {
    }

    void SetShape(Cylinder *model)
    {
        if (!model)
            throw NullObjectException("Model is null");
        this->model = model;
    }

    void Render() override
    {
        if (!model)
            throw NullObjectException("Model is null");
        if (!logger)
            return;
        *logger << std::endl;
        *logger << std::setfill('#') << std::setw(50) << "" << std::endl;
        *logger << "### --------- Preety console output --------- ###" << std::endl;
        *logger << "### > Console Viewer Of Cylinder >> radius " << model->GetRadius() << "  ###" << std::endl;
        *logger << "### > Console Viewer Of Cylinder >> height " << model->GetHeight() << "  ###" << std::endl;
        *logger << "### ------- < end of Cylinder view >  ------- ###" << std::endl;
        *logger << std::setfill('#') << std::setw(50) << "" << std::endl;
        *logger << std::endl;
    }
};
#pragma once
#include <iostream>
#include <iomanip>
#include "../models/cylinder.h"

class CylinderConsoleView : public ShapeConsoleView
{
private:
    Cylinder *model;

public:
    CylinderConsoleView() {}
    CylinderConsoleView(Cylinder *model)
    {
        this->model = model;
    }
    void SetShape(Cylinder *model)
    {
        this->model = model;
    }
    void Render() override
    {
        std::cout << std::endl;
        std::cout << std::setfill('#') << std::setw(50) << "" << std::endl;
        std::cout << "### --------- Preety console output --------- ###" << std::endl;
        std::cout << "### > Console Viewer Of Cylinder >> radius " << model->GetRadius() << "  ###" << std::endl;
        std::cout << "### > Console Viewer Of Cylinder >> height " << model->GetHeight() << "  ###" << std::endl;
        std::cout << "### ------- < end of Cylinder view >  ------- ###" << std::endl;
        std::cout << std::setfill('#') << std::setw(50) << "" << std::endl;
        std::cout << std::endl;
    }
};
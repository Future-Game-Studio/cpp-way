#pragma once
#include "../models/abstractions/shape.h"
#include "../views/shapeConsoleView.h"

// Combines Shape and ConsoleView
class MainController
{
private:
    Shape *model;
    ShapeConsoleView *view;

public:
    MainController(Shape *model, ShapeConsoleView *view)
    {
        this->SetModel(model);
        this->SetView(view);
    }

    void OnLoad()
    {
        this->view->Render();
    }

    void SetModel(Shape *model)
    {
        this->model = model;
    }

    void SetView(ShapeConsoleView *view)
    {
        this->view = view;
    }
};
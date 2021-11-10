#pragma once
#include <iostream>
#include <memory>
#include <string>
#include "../shapes/models/abstractions/shape.h"
#include "../shapes/views/shapeConsoleView.h"
#include "../shapes/views/cylinderConsoleView.h"
#include "../shapes/controllers/mainController.h"

class MVCDomain
{
private:
    std::unique_ptr<MainController> _controller;
    ShapeConsoleView _view;
    std::weak_ptr<Shape> _abstractModel;

public:
    MVCDomain() {}

    void Run()
    {
        const auto cylinderModel = std::make_shared<Cylinder>(10, 23);

        _abstractModel = std::weak_ptr(cylinderModel);
        ShapeConsoleView *view;

        // shape view
        {
            const auto abstractModelPtr = _abstractModel.lock().get();
            // create a view for the model
            view = new ShapeConsoleView(abstractModelPtr);
            // register the data-change event 
            abstractModelPtr->RegisterDataChangeHandler(
                [&view](std::string &str) -> void
                {
                    std::cout << "Data Changes: " << str << std::endl;
                    view->Render();
                });
            // binds the model and the view
            _controller = std::make_unique<MainController>(abstractModelPtr, view);

            // on application loaded
            _controller->OnLoad();

            std::string modelUpdate = "New Model Name";
            abstractModelPtr->SetData(modelUpdate); //triggers render 
        }

        // cylinder view
        {
            const auto abstractModelPtr = _abstractModel.lock().get();
            // create a view for the model
            view = new CylinderConsoleView(cylinderModel.get());
            // register the data-change event
            cylinderModel->RegisterDataChangeHandler(
                [&view](Cylinder &data) -> void
                {
                    std::cout << "Data Changes on Cylinder (height): " << data.GetHeight() << std::endl;
                    std::cout << "Data Changes on Cylinder (radius): " << data.GetRadius() << std::endl;
                    view->Render();
                });

            // binds the model and the view
            _controller = std::make_unique<MainController>(abstractModelPtr, view);

            // on application loaded
            _controller->OnLoad();

            auto someNewData = Cylinder(4, 5);
            cylinderModel->SetData(someNewData); //triggers render
        }
    }
};

void runMVC()
{
    auto mvcDomain = MVCDomain();
    // mvcDomain.ConfigureServices();
    mvcDomain.Run();
}
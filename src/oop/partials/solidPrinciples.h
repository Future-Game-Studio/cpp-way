#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include "../shapes/models/abstractions/shape.h"
#include "../shapes/models/square.h"
#include "../shapes/models/cylinder.h"
#include "../shapes/helpers/printer.h"
#include "../shapes/helpers/exceptions.h"
#include "../shapes/behavioral/abstractShapeVisitor.h"
#include "../shapes/behavioral/printers.h"
#include "../shapes/factory/shapeGenerator.h"

void solidPrinciples()
{
    const auto shapeGenerator = std::make_unique<ShapeGenerator>();

    const auto consoleVisitor = std::make_unique<ConsolePrinterVisitor>();
    const auto fileVisitor = std::make_unique<FileExportVisitor>();
    const auto perimeterVisitor = std::make_unique<SumPerimeterVisitor>();
    const auto areaVisitor = std::make_unique<SumAreaVisitor>();

    const std::vector<AbstractShapeVisitor *> visitors{
        dynamic_cast<AbstractShapeVisitor *>(fileVisitor.get()),
        dynamic_cast<AbstractShapeVisitor *>(consoleVisitor.get()),
        dynamic_cast<AbstractShapeVisitor *>(perimeterVisitor.get()),
        dynamic_cast<AbstractShapeVisitor *>(areaVisitor.get())};
    {

        fileVisitor->CreateFile("./oop-test.log");

        const auto circlePerimeterSum = std::make_unique<SumPerimeterVisitor>();
        const auto circleAreaSum = std::make_unique<SumAreaVisitor>();
        const auto circles = shapeGenerator->GenerateCircles(10);
        std::cout << "Printing all circles:" << std::endl;
        for (const auto &circle : circles)
        {
            const auto circleRef = circle.get();
            try
            {
                fileVisitor->Visit(circleRef);
            }
            catch (fileNotReady &ex)
            {
                std::cout << "File is not ready" << std::endl;
                std::cout << "Error: " << ex.Message() << std::endl;
                return;
            }
            catch (...)
            {
                std::cout << "Other magic stuff" << std::endl;
            }

            circlePerimeterSum->Visit(circleRef);
            circleAreaSum->Visit(circleRef);
            for (const auto &visitor : visitors)
                visitor->Visit(circleRef);
        }
        std::cout << "Circles perimeter: " << circlePerimeterSum->GetSum() << std::endl;
        std::cout << "Circles area: " << circleAreaSum->GetSum() << std::endl;
    }
    {
        const auto cylinderPerimeterSum = std::make_unique<SumPerimeterVisitor>();
        const auto cylinderAreaSum = std::make_unique<SumAreaVisitor>();
        const auto cylinders = shapeGenerator->GenerateCylinders(10);

        std::cout << "Printing all cylinders:" << std::endl;
        for (const auto &cylinder : cylinders)
        {
            cylinderPerimeterSum->Visit(cylinder.get());
            cylinderAreaSum->Visit(cylinder.get());
            for (const auto &visitor : visitors)
                visitor->Visit(cylinder.get());
        }
        std::cout << "Cylinders area: " << cylinderAreaSum->GetSum() << std::endl;
        std::cout << "Cylinders perimeter: " << cylinderPerimeterSum->GetSum() << std::endl;
    }
    std::cout << "Shapes area: " << areaVisitor->GetSum() << std::endl;
    std::cout << "Shapes perimeter: " << perimeterVisitor->GetSum() << std::endl;
}

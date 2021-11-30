#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include "../shapes/models/abstractions/shape.h"
#include "../shapes/models/rectangle.h"
#include "../shapes/models/cylinder.h"
#include "../shapes/helpers/printer.h"
#include "../shapes/helpers/exceptions.h"
#include "../shapes/behavioral/abstractShapeVisitor.h"
#include "../shapes/behavioral/printers.h"
#include "../shapes/factory/shapeGenerator.h"

void solidPrinciples()
{
    const auto logger = &std::cout;
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
        *logger << "Printing all circles:" << std::endl;
        for (const auto &circle : circles)
        {
            const auto circleRef = circle.get();
            try
            {
                fileVisitor->Visit(circleRef);
            }
            catch (fileNotReady &ex)
            {
                *logger << "File is not ready" << std::endl;
                *logger << "Error: " << ex.what() << std::endl;
                return;
            }
            catch (...)
            {
                *logger << "Other magic stuff" << std::endl;
            }

            circlePerimeterSum->Visit(circleRef);
            circleAreaSum->Visit(circleRef);
            for (const auto &visitor : visitors)
                visitor->Visit(circleRef);
        }
        *logger << "Circles perimeter: " << circlePerimeterSum->GetSum() << std::endl;
        *logger << "Circles area: " << circleAreaSum->GetSum() << std::endl;
    }
    {
        const auto cylinderPerimeterSum = std::make_unique<SumPerimeterVisitor>();
        const auto cylinderAreaSum = std::make_unique<SumAreaVisitor>();
        const auto cylinders = shapeGenerator->GenerateCylinders(10);

        *logger << "Printing all cylinders:" << std::endl;
        for (const auto &cylinder : cylinders)
        {
            cylinderPerimeterSum->Visit(cylinder.get());
            cylinderAreaSum->Visit(cylinder.get());
            for (const auto &visitor : visitors)
                visitor->Visit(cylinder.get());
        }
        *logger << "Cylinders area: " << cylinderAreaSum->GetSum() << std::endl;
        *logger << "Cylinders perimeter: " << cylinderPerimeterSum->GetSum() << std::endl;
    }
    *logger << "Shapes area: " << areaVisitor->GetSum() << std::endl;
    *logger << "Shapes perimeter: " << perimeterVisitor->GetSum() << std::endl;
}

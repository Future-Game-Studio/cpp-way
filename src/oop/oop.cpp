#include <iostream>
#include <memory>
#include "shapes/helpers/debug.h"
#include "shapes/models/abstractions/shape.h"
#include "shapes/models/square.h"
#include "shapes/models/cylinder.h"
#include "shapes/helpers/printer.h"
#include "shapes/behavioral/abstractShapeVisitor.h"
#include "shapes/behavioral/printers.h"
#include "shapes/factory/shapeGenerator.h"
#include <exception>

void pointersRecall()
{
    {
        auto shapeDyn = (Shape *)new Square(6, 7);
        printArea(*shapeDyn);

        // clear mem first!
        delete shapeDyn;

        shapeDyn = (Shape *)new Cylinder(5, 4);
        printArea(*shapeDyn);

        delete shapeDyn;
    }

    std::cout << std::endl;

    {
        auto shape1 = std::make_unique<Cylinder>(10, 15);
        if (shape1)
        {
            printArea(*shape1);
        }

        auto shape2 = std::make_unique<Square>(7, 3);
        printArea(*shape2);
        auto shape3 = std::make_unique<Square>(4, 10);
        printArea(*shape3);

        auto shape4 = std::make_unique<Square>(*shape2 + *shape3);
        printArea(*shape4);
    }

    std::cout << std::endl;
}

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
            try
            {
                fileVisitor->Visit(circle.get());
            }
            catch (...)
            {
                std::cout << "File is not ready" << std::endl;
                return;
            }
            circlePerimeterSum->Visit(circle.get());
            circleAreaSum->Visit(circle.get());
            for (const auto &visitor : visitors)
                visitor->Visit(circle.get());
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
int main()
{
    solidPrinciples();
}
#include <iostream>
#include <memory>
#include "shapes/models/abstractions/shape.h"
#include "shapes/models/square.h"
#include "shapes/models/cylinder.h"
#include "shapes/helpers/printer.h"

int main()
{
    {
        auto shapeDyn = (Shape *)new Square(6, 7);
        printArea(*shapeDyn);

        // clear mem first!
        delete shapeDyn;

        shapeDyn = new Cylinder(5, 4);
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
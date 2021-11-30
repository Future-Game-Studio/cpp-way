#pragma once
#include <memory>
#include "../shapes/models/abstractions/shape.h"
#include "../shapes/models/rectangle.h"
#include "../shapes/models/cylinder.h"
#include "../shapes/helpers/printer.h"

void pointersRecall()
{
    auto logger = &std::cout;

    {
        auto shapeDyn = (Shape *)new RectShape(6, 7);
        printArea(*shapeDyn, logger);

        // clear mem first!
        delete shapeDyn;

        shapeDyn = (Shape *)new Cylinder(5, 4);
        printArea(*shapeDyn, logger);

        delete shapeDyn;
    }

    *logger << std::endl;

    {
        auto shape1 = std::make_unique<Cylinder>(10, 15);
        if (shape1)
        {
            printArea(*shape1, logger);
        }

        auto shape2 = std::make_unique<RectShape>(7, 3);
        printArea(*shape2, logger);
        auto shape3 = std::make_unique<RectShape>(4, 10);
        printArea(*shape3, logger);

        auto shape4 = std::make_unique<RectShape>(*shape2 + *shape3);
        printArea(*shape4, logger);
    }

    *logger << std::endl;
}

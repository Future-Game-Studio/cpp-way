#include "../models/circle.h"
#include "../models/cylinder.h"
#include <vector>
#include <random>
#include <functional>
#include <memory>

class ShapeGenerator
{

public:
    std::vector<std::unique_ptr<Circle>> const GenerateCircles(int count) const
    {
        //auto items = new Circle[count];
        std::vector<std::unique_ptr<Circle>> vec;
        vec.reserve(count);
        for (size_t i = 0; i < (size_t)count; i++)
        {
            vec.push_back(std::make_unique<Circle>(1 + rand() % 10));
        }

        return vec;
    }

    std::vector<std::unique_ptr<Cylinder>> const GenerateCylinders(int count) const
    {
        std::vector<std::unique_ptr<Cylinder>> vec;

        vec.reserve(count);

        for (size_t i = 0; i < (size_t)count; i++)
            vec.push_back(std::make_unique<Cylinder>(1 + rand() % 10, 1 + rand() % 10));

        return vec;
    }
};
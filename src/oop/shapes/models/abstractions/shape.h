#pragma once

class Shape
{
private:
    int _baseSize;

protected:
    std::string name;

public:
    Shape(int size, std::string name) : Shape(size)
    {
        name = name;
        std::cout << "Shape " << name << " created. Base size: " << _baseSize << std::endl;
    }

    Shape(int size)
    {
        _baseSize = size;
    }

    virtual float GetArea() const = 0;

    virtual ~Shape() { std::cout << "Shape " << name << " disposed" << std::endl; }
};

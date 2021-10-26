#pragma once

class Shape
{
private:
    int _baseSize;

protected:
    std::string name; // why it's not const &

public:
    Shape(int size, std::string name) : Shape(size)
    {
        name = name; // copy
        std::cout << "Shape " << name << " created. Base size: " << _baseSize << std::endl;
    }

    Shape(int size)
    {
        _baseSize = size;
    }

    virtual float GetArea() const = 0; // pure virtual function

    virtual ~Shape() { std::cout << "Shape " << name << " disposed" << std::endl; }
};

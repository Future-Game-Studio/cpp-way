#pragma once
#include <iostream>
#include "../models/abstractions/shape.h"
#include "abstractShapeVisitor.h"
#include <string>
#include <iostream>
#include <fstream>
#include "../math/m_pi.h"

class SumPerimeterVisitor : public AbstractShapeVisitor
{
    mutable float sum;

public:
    float GetSum() const { return sum; }

    void Visit(const Cylinder *item) const override
    {
        sum += item->GetRadius() * 2 * pi() * item->GetHeight();
    }

    void Visit(const Square *item) const override
    {
        sum += 2 * (item->GetX() + item->GetY());
    }

    void Visit(const Circle *item) const override
    {
        sum += item->GetRadius() * 2 * pi();
    }
};

class SumAreaVisitor : public AbstractShapeVisitor
{
    mutable float sum;

public:
    float GetSum() const { return sum; }

    void Visit(const Cylinder *item) const override
    {
        sum += item->GetArea();
    }

    void Visit(const Square *item) const override
    {
        sum += item->GetArea();
    }

    void Visit(const Circle *item) const override
    {
        sum += item->GetArea();
    }
};

class ConsolePrinterVisitor : public AbstractShapeVisitor
{
private:
    void Print(const std::string &name, const Shape *item) const
    {
        std::cout << name << " area: " << item->GetArea() << std::endl;
    }

public:
    void Visit(const Cylinder *item) const override
    {
        Print("Cylinder", static_cast<const Shape *>(item));
    }

    void Visit(const Square *item) const override
    {
        Print("Square", static_cast<const Shape *>(item));
    }

    void Visit(const Circle *item) const override
    {
        Print("Circle", static_cast<const Shape *>(item));
    }
};

class FileExportVisitor : public AbstractShapeVisitor
{
private:
    std::unique_ptr<std::ofstream> _fs;

public:
    void CreateFile(const std::string &fileName)
    {
        _fs = std::make_unique<std::ofstream>(fileName, std::ios_base::out);
    }

    void Print(const std::string &name, const Shape *item) const
    {
        if (_fs != nullptr)
            *_fs << name << " area: " << item->GetArea() << std::endl;
        else
            throw("File is not open");
    }

    void Visit(const Cylinder *item) const override
    {
        // cylider specific logic
        // abstract shape parameters printing
        *_fs << "-----" << std::endl;
        Print("Cylinder", reinterpret_cast<const Shape *>(item));
        // print cylinder height
        *_fs << "Cylinder height : " << item->GetHeight() << std::endl;
        *_fs << "Cylinder radius : " << item->GetRadius() << std::endl;
        *_fs << "-----" << std::endl;
    }

    void Visit(const Square *item) const override
    {
        *_fs << "-----" << std::endl;
        Print("Square", reinterpret_cast<const Shape *>(item));
        // print cylinder height
        *_fs << "Square X: " << item->GetX() << " Y: " << item->GetY() << std::endl;
        *_fs << "-----" << std::endl;
    }

    void Visit(const Circle *item) const override
    {
        *_fs << "-----" << std::endl;
        Print("Circle", reinterpret_cast<const Shape *>(item));
        *_fs << "Circle R: " << item->GetRadius() << std::endl;
        *_fs << "-----" << std::endl;
    }

    ~FileExportVisitor()
    {
        SaveFile();
    }

    void SaveFile()
    {
        if (_fs->is_open())
            _fs->close();
        _fs.release();
    }
};
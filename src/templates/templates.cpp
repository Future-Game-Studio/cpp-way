#include <iostream>
#include <array>
#include <functional>
#include "templates.h"
#include "matrix.h"

void templateFunctions();
void templateClass();

using namespace examples;

int main()
{
    //templateFunctions();
    templateClass();
    return 0;
}

void templateFunctions()
{
    const int n = 5;

#pragma region Initialization

    float a[n] = {100.50, 50.50, 30.80, 40.80, 20.80};
    std::cout << " Initial array 1: ";
    printArray(a, n);

    std::array<size_t, n> v{1000, 250, 30, 50, 5};
    std::cout << " Initial array 2: ";
    printArray(v.data(), v.size());

#pragma endregion Initialization

#pragma region TemplateFunctions
    // template function
    bubbleSort(a, n);
    bubbleSort(v.data(), v.size());

    std::cout << " Sorted array 1: ";
    printArray(a, n);

    std::function<size_t(size_t)> func;

    func = divByTwo<size_t>;
    std::cout << " Transformed divBy2: ";
    transform(v.data(), v.size(), func);
    printArray(v.data(), v.size());

    std::cout << " Transformed multTwo: ";
    func = multByTwo<size_t>;
    transform(v.data(), v.size(), func);
    printArray(v.data(), v.size());
#pragma endregion TemplateFunctions
}

void templateClass()
{
#pragma region Matrix_Template_Example
    const int matrixCount = 3;
    // Initialize Matrix
    // no default contructor
    auto x = (Matrix<float> *)malloc(sizeof(Matrix<float>) * matrixCount);
    // default contructor
    //auto x = new  Matrix<float>[n];

    for (size_t i = 0; i < 3; i++)
    {
        x[i] = Matrix<float>(3);
        x[i].ShowMatrix();
    }
    auto mat = x[0] * x[1];
    mat.ShowMatrix();
    // dont forget to clean

    // delete x;
    free(x);
#pragma endregion Matrix_Example
}
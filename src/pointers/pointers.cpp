#include <iostream>
#include <memory>
#include "smartPointers.h"

void MethodCallWithRefParameter(int &val1, int *val2)
{
    val1 = 0;
    *val2 = 5;
}

void MethodCallWithCopyParameter(int val1)
{
    // local copy of object
    val1 = 10000; // changes only locally
}

// swaps two references
void swap(int &x, int &y)
{
    int temp;
    temp = x;
    x = y;
    y = temp;
    return;
}

int main()
{
    auto logger = &std::cout;
    int origin = 10;

    int *a;
    a = &origin;

    *logger << "Pointer address: " << a << std::endl;
    *logger << "Pointer value: " << *a << std::endl;

    int &b = *a;

    *logger << "Reference b: " << b << std::endl;
    int &c = b;

    *logger << "Reference c: " << c << std::endl;

    origin = 7;
    *logger << "Reference c (origin changed): " << c << std::endl;
    // b = nullptr; //won't compile

    a = nullptr; // remember a and c ??
    *logger << "Pointer address a (null): " << a << std::endl;

    int **M;        // 2D matrix
    int ***pM = &M; // pointer to matrix

    a = &origin; // without this line there would be segmentation fault

    *logger << "Reference b (null ref): " << b << std::endl;

    // references can not be null. pointers can
    if (a != nullptr)
    {
        int f = 4;
        b = f;
        *logger << "Reference b (before method call): " << b << std::endl;
        *logger << "Pointer a (before method call): " << a << std::endl;
        MethodCallWithRefParameter(b, a);
        *logger << "Reference b (after method call): " << b << std::endl;
        *logger << "Pointer a (after method call): " << *a << std::endl;
        MethodCallWithCopyParameter(*a);
        *logger << "Reference b (after copy call): " << b << std::endl;
    }

    const int *pconst;
    const int constVal = 2;
    pconst = &origin;
    /// int val = pconst++; // error const pointer is not arithmetic.
    const int *const pconst2 = &b;
    // pconst2 = &origin; // pointer can not be reassigned
    *logger << "Reference const p : " << b << std::endl;

    *logger << std::endl;

    SmartUniquePtr();
    SmartSharedPtr();
    SmartWeakPtr();
}

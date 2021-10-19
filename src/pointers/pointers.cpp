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
    int origin = 10;

    int *a;
    a = &origin;

    std::cout << "Pointer address: " << a << std::endl;
    std::cout << "Pointer value: " << *a << std::endl;

    int &b = *a;

    std::cout << "Reference b: " << b << std::endl;
    int &c = b;

    std::cout << "Reference c: " << c << std::endl;

    origin = 7;
    std::cout << "Reference c (origin changed): " << c << std::endl;
    // b = nullptr; //won't compile

    a = nullptr; // remember a and c ??
    std::cout << "Pointer address a (null): " << a << std::endl;

    int **M;        // 2D matrix
    int ***pM = &M; // pointer to matrix

    a = &origin; // without this line there would be segmentation fault

    // references can not be null. pointers can
    if (a != nullptr)
    {
        int f = 4;
        b = f;
        std::cout << "Reference b (before method call): " << b << std::endl;
        std::cout << "Pointer a (before method call): " << a << std::endl;
        MethodCallWithRefParameter(b, a);
        std::cout << "Reference b (after method call): " << b << std::endl;
        std::cout << "Pointer a (after method call): " << *a << std::endl;
        MethodCallWithCopyParameter(b);
        std::cout << "Reference b (after copy call): " << b << std::endl;
    }

    const int *pconst;
    const int constVal = 2;
    pconst = &origin;
    //  int val = pconst++; // error const pointer is not arithmetic.
    const int *const pconst2 = &b;
    // pconst2 = &origin; // pointer can not be reassigned
    std::cout << "Reference const p : " << b << std::endl;

    std::cout << std::endl;

    SmartUniquePtr();
    SmartSharedPtr();
    SmartWeakPtr();
}

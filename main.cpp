#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <algorithm>
#include "main.h"
// this works only on windows
// sudo apt-get install libncurses5-dev libncursesw5-dev
//#include <conio.h>
 
/* program entry point */
int main()
{ 
    std::cout << "Input N: ";
    int n;
    std::cin >> n;

    int *arr1 = new int(n);
    int *arr2 = new int(n);

    heapType heap;
    std::list<int> list1(*arr1);
    std::list<int> list2(*arr2);
    delete arr2;
    delete arr1;

    printHeap(heap);

    fillHeap(heap, list1, list2);

    printHeap(heap);
    heap.clear();

    std::cin.clear();
    std::cin.sync();
    std::cin.ignore();
    
    // this works only on windows
    //system("pause");
}

// prints everything you have in 
// heap iterating down two levels
void printHeap(heapType &heap)
{
    // iterating over heap
    std::cout << '\n'
         << std::string(10, '-') << "<heap>" << std::string(10, '-') << '\n';

    if (heap.size() == 0)
    {
        std::cout << "Empty" << '\n';
    }
    else
    {
        for (auto &i : heap)
        {
            for (auto &j : i)
                std::cout << "(" << j << ")"
                     << " ";

            std::cout << '\n';
        }
    }
    std::cout << std::string(10, '-') << "<!heap>" << std::string(10, '-') << '\n';
}

/// Inflates heap randomizing pairs
void fillHeap(heapType &heap, listType &l1, listType &l2)
{
    for (auto &&i : l1)
    {
        std::vector<int> g;
        for (auto &&j : l2)
        {
            // randomizing pairs
            i = 1 + rand() % 9 + j;
            g.push_back(i);
        }
        heap.push_back(g);
    }
}
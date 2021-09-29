#include <iostream>
#include <vector>
#include <algorithm>

// prints out vector
void showVector(std::vector<std::vector<int>> v);

// entry point
int main()
{
    std::cout << "Iterating over a vector" << std::endl;

    std::vector<std::vector<int>> v = {
        {0, 1, 2, 3, 4, 5},
        {0, 1, 2, 3, 4, 5}};

    std::reverse(v[1].begin(), v[1].end());

    showVector(v);
    auto vInt = v[1];

    std::sort(vInt.begin(), vInt.end());
    showVector(v);
}

void showVector(std::vector<std::vector<int>> v)
{
    int i = 0, j = 0;
    std::cout << "-- printing vector --" << std::endl;
    for (auto t1 : v)
    {
        for (auto t2 : t1)
            std::cout << t2 << " (" << i << "," << j++ << ")"
                      << "   ";
        std::cout << '\n';
        i++;
    }
    std::cout << "-- end of vector --" << std::endl;
}
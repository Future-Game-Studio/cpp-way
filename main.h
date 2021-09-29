#include <vector>
#include <list>
#include <tuple>  

typedef std::list<int> listType;
typedef std::vector<std::vector<int>> heapType;

void fillHeap(heapType &heap, listType &l1, listType &l2);
void printHeap(heapType &heap);
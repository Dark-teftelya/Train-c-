#ifndef SORTING_YARD_H
#define SORTING_YARD_H

#include <vector>
#include <algorithm>

class SortingYard {
public:
    SortingYard();
    void sortWagons(const std::vector<int>& inputWagons, std::vector<int>& sortedWagons);
};

#endif
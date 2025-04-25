#include "sorting_yard.h"

SortingYard::SortingYard() {}

void SortingYard::sortWagons(const std::vector<int>& inputWagons, std::vector<int>& sortedWagons) {
    sortedWagons = inputWagons;
    std::sort(sortedWagons.begin(), sortedWagons.end());
}
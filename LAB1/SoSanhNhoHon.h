#pragma once
#include <vector>

bool SoSanhNhoHon(const std::vector<int>& a, const std::vector<int>& b) {
    int sizeA = a.size();
    int sizeB = b.size();
    while (sizeA > 1 && a[sizeA - 1] == 0) sizeA--;
    while (sizeB > 1 && b[sizeB - 1] == 0) sizeB--;

    if (sizeA != sizeB) return sizeA < sizeB;

    for (int i = sizeA - 1; i >= 0; i--) {
        if (a[i] != b[i]) return a[i] < b[i];
    }
    return false; 
}
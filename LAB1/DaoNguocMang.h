#pragma once
#include <vector>
#include <algorithm>
void DaoNguocMang(std::vector<int>& a) {
    int l = 0, r = a.size() - 1;
    while (l < r) {
        std::swap(a[l++], a[r--]);
    }
}
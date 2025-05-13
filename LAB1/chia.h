#pragma once
#include <vector>
#include <stdexcept>
// #include <algorithm>
#include "SoSanhNhoHon.h"
#include "DaoNguocMang.h"


std::vector<int> truHaiSo(const std::vector<int>& a, const std::vector<int>& b, bool& isNegativeResult) {
    std::vector<int> c;
    isNegativeResult = false;

    if (SoSanhNhoHon(a, b)) {
        throw std::invalid_argument("Số bị trừ nhỏ hơn số trừ trong phép trừ hỗ trợ chia");
    }

    int n1 = a.size(), n2 = b.size();
    int n = std::max(n1, n2);
    c.reserve(n);

    int borrow = 0;
    for (int i = 0; i < n; i++) {
        int digitA = (i < n1) ? a[i] : 0;
        int digitB = (i < n2) ? b[i] : 0;
        int diff = digitA - digitB - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        c.push_back(diff);
    }

    while (c.size() > 1 && c.back() == 0) {
        c.pop_back();
    }

    return c;
}

// Nhân một số a với một chữ số digit.
std::vector<int> nhanVoiChuSo(const std::vector<int>& a, int digit) {

    if (digit == 0) return {0}; // Nếu digit bằng 0 thì kết quả chia  là 0 và trả về kết quả.

    std::vector<int> c; // Khai báo mảng c để lưu kết quả nhân.
    c.reserve(a.size() + 1); // Kích thướt của c là kích thướt của a + 1.
    int carry = 0; // Biến lưu số nhớ.

    // Duyệt qua từng chữ số x trong a.
    for (int x : a) {
        int product = x * digit + carry; // Tính tích x*digit + carry.
        c.push_back(product % 10); // Lưu vào c chữ số cuối cùng.
        carry = product / 10; // Cập nhật carry.
    }
    if (carry > 0) { // Nếu còn số nhớ thêm vào c.
        c.push_back(carry);
    }

    return c; // Trả về kết quả nhân với một chữ số.
}


std::vector<int> ChiaHaiSo(const std::vector<int>& a, const std::vector<int>& b, bool isNegativeA, bool isNegativeB, bool& resultNegative) {
    std::vector<int> c;
    resultNegative = (isNegativeA != isNegativeB);

    for (int x : a) {
        if (x < 0 || x > 9) throw std::invalid_argument("Chữ số không hợp lệ trong a");
    }
    for (int x : b) {
        if (x < 0 || x > 9) throw std::invalid_argument("Chữ số không hợp lệ trong b");
    }

    if (a.empty()) return {0};
    if (b.empty() || (b.size() == 1 && b[0] == 0)) {
        throw std::invalid_argument("Chia cho 0!");
    }
    if (SoSanhNhoHon(a, b)) return {0};
    if (a == b) return {1};

    std::vector<int> num1 = a, num2 = b;
    std::vector<int> remainder = num1;
    c.clear();

    int n1 = num1.size(), n2 = num2.size();
    std::vector<int> current; 
    int idx = n1 - 1; 

    while (idx >= 0 || !SoSanhNhoHon(current, num2)) {
        if (idx >= 0) {
            current.insert(current.begin(), num1[idx]);
            while (current.size() > 1 && current.back() == 0) current.pop_back();
            idx--;
        }

        if (SoSanhNhoHon(current, num2)) {
            if (idx < 0) break;
            c.insert(c.begin(), 0);
            continue;
        }

        int q = 0;
        int left = 0, right = 9;
        std::vector<int> temp;
        while (left <= right) {
            int mid = (left + right) / 2;
            std::vector<int> product = nhanVoiChuSo(num2, mid);
            if (SoSanhNhoHon(current, product)) {
                right = mid - 1;
            } else {
                q = mid;
                temp = product;
                left = mid + 1;
            }
        }

        bool temp_am;
        current = truHaiSo(current, temp, temp_am);
        c.insert(c.begin(), q);
    }

    // Loại bỏ số 0 thừa
    while (c.size() > 1 && c.back() == 0) {
        c.pop_back();
    }

    return c;
}
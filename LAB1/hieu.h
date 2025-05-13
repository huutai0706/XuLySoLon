#pragma once
#include <vector>
#include <stdexcept>
// #include <algorithm>
#include "SoSanhNhoHon.h"
#include "chia.h"


// Khai báo trước cho TongHaiSo
std::vector<int> TongHaiSo(const std::vector<int>& a, const std::vector<int>& b, bool isNegativeA, bool isNegativeB, bool& resultNegative);

std::vector<int> HieuHaiSo(const std::vector<int>& a, const std::vector<int>& b, bool isNegativeA, bool isNegativeB, bool& resultNegative) {
    std::vector<int> c; // Tạo mảng c lưu kết trả phép trừ
    resultNegative = false; // Gỉa sử ban đầu dấu của kết quả là dương.
    // Kiểm tra trong mảng a và b các phần tử phải thuộc [0, 9].
    for (int x : a) {
        if (x < 0 || x > 9) throw std::invalid_argument("Chữ số không hợp lệ trong a");
    }
    for (int x : b) {
        if (x < 0 || x > 9) throw std::invalid_argument("Chữ số không hợp lệ trong b");
    }

    // Nếu a và b rỗng thì trả về mảng 0.
    if (a.empty() && b.empty()) return {0};

    // Nếu mảng a rỗng thì kết quả là b.
    if (a.empty()) {
        resultNegative = isNegativeB;
        return b;
    }
    // Nếu mảng b rỗng thì kết quả là a.
    if (b.empty()) {
        resultNegative = isNegativeA;
        return a;
    }

    // Nếu a âm và b dương thực hiện (-a) - b = -(a + b).
    if (isNegativeA && !isNegativeB) {
        bool tempNeg;
        c = TongHaiSo(a, b, false, false, tempNeg); // Gọi hàm Tổng để cộng hai số a và b.
        resultNegative = true; // Dấu kết quả sẽ là âm.
        return c; // Trả về kết quả.
    } else if (!isNegativeA && isNegativeB) { // Nếu a dương và b âm thì thực hiện a - (-b) -> a + b.
        bool tempNeg;
        c = TongHaiSo(a, b, false, false, tempNeg); // Gọi hàm tổng để cộng hai số a và b.
        resultNegative = false; // Kết quả của phép cộng hai số a và b là dương.
        return c; // Trả về kết quả phép tính.
    }

    // Trường hợp (+a) - (+b) hoặc (-a) - (-b)
    std::vector<int> num1 = a, num2 = b; // Sao chép a và b.
    bool resultNeg = false; 

    if (isNegativeA && isNegativeB) { // Nếu a âm và b âm thì thực hiện (-a) - (-b) -> -a + b -> b - a.
        // (-a) - (-b) = b - a
        if (SoSanhNhoHon(b, a)) { // Gọi hàm so sánh nhỏ hơn để biết dấu của phép tính.
            std::swap(num1, num2); // Nếu a nhỏ hơn b thì hoán đổi cho nhau.
            resultNeg = true; // Nếu a nhỏ hơn b thì kết quả sẽ là âm.
        }
    } else { // Trường hợp a - b.
        // (+a) - (+b)
        if (SoSanhNhoHon(a, b)) { // Gọi hàm so sánh nhỏ hơn để biết dấu của phép tính.
            std::swap(num1, num2); // Đổi giá trị cho nhau.
            resultNeg = true; // Kết quả nhận được sẽ âm.
        }
    }

    int n1 = num1.size(), n2 = num2.size(); // Lấy kích thướt cả hai mảng.
    int n = std::max(n1, n2); //Chọn giá trị lớn nhất của hai mảng.
    c.reserve(n); // Mảng tạo có kích thướt của max size hai mảng a và b.

    int borrow = 0; // Biến mượn.
    for (int i = 0; i < n; i++) { // Lặp qua n chữ số.
        int digitA = (i < n1) ? num1[i] : 0; // DigitA sẽ là chữ số thứ num1[i] hoặc là 0 nếu mảng num1 hết giá trị.
        int digitB = (i < n2) ? num2[i] : 0; // DigitB sẽ là chữ số thứ num2[i] hoặc là 0 nếu mảng num2 hết giá trị.
        int diff = digitA - digitB - borrow; // Tính diff.

        if (diff < 0) { // Nếu diff nhỏ hơn 0 thì mượn thêm 10. Sau đó gán borrow(mượn) = 1.
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0; // Ngược lại mượn bằng 0.
        }
        c.push_back(diff); // Thêm diff vào c.
    }
    // Loại bỏ các số 0 ở đầu kết quả giữ lại nếu còn 1 số 0.
    while (c.size() > 1 && c.back() == 0) {
        c.pop_back();
    }
     
    resultNegative = resultNeg; //Gán dấu kết quả.
    return c; // Trả về mảng c.
}
#pragma once
#include <vector>
#include <stdexcept>

std::vector<int> nhanHaiSo(const std::vector<int>& a, const std::vector<int>& b, bool isNegativeA, bool isNegativeB, bool& resultNegative) {
    // Kiểm tra từng phần tử trong a và b đảm bảo nằm trong [0, 9].
    for (int x : a) {
        if (x < 0 || x > 9) throw std::invalid_argument("Chữ số không hợp lệ trong a");
    }
    for (int x : b) {
        if (x < 0 || x > 9) throw std::invalid_argument("Chữ số không hợp lệ trong b");
    }

    // Dấu của kết quả dựa trên dấu của a và b.
    resultNegative = (isNegativeA != isNegativeB);

    if (a.empty() || b.empty()) return {0}; // Nếu a hoặc b rỗng thì trả về 0.
    if (a.size() == 1 && a[0] == 0) return {0}; // Nếu a có duy nhất nột phần tử, là 0 thì trả về 0.
    if (b.size() == 1 && b[0] == 0) return {0}; // Nếu b có duy nhất nột phần tử, là 0 thì trả về 0.

    int n1 = a.size(), n2 = b.size(); // Lấy kích thướt của hai mảng a và b.
    std::vector<int> c(n1 + n2, 0);   // Kích thướt của mảng kết quả và tổng kích thướt hai mảng ban đầu.

    // Thực hiện lặp qua n1 phần tử trong a[i].
    for (int i = 0; i < n1; i++) {
        int carry = 0; // Nhớ.
        for (int j = 0; j < n2; j++) { // Với mỗi lần lặp i thì sẽ lặp n2 j.
            int product = a[i] * b[j] + c[i + j] + carry; // Tính tích của hai giá trị a[i] và b[j] cộng với số của c[i + j] và nhớ.
            c[i + j] = product % 10; // Lưu chữ số kết quả.
            carry = product / 10; // Cập nhật lại nhớ.
        }
        if (carry > 0) {
            c[i + n2] += carry; // Cộng nhớ vào vị trí tiếp theo.
        }
    }

    // Loại bỏ các số 0 ở đầu kết quả nếu nhiều hơn 2 số 0.
    while (c.size() > 1 && c.back() == 0) {
        c.pop_back();
    }

    // Trả về kết quả nhân.
    return c;
}
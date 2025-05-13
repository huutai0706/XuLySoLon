#pragma once
#include <vector>
#include <stdexcept>
#include "SoSanhNhoHon.h"


// Khai báo trước cho HieuHaiSo
std::vector<int> HieuHaiSo(const std::vector<int> &a, const std::vector<int> &b, bool isNegativeA, bool isNegativeB, bool &resultNegative);

//
std::vector<int> TongHaiSo(const std::vector<int> &a, const std::vector<int> &b, bool isNegativeA, bool isNegativeB, bool &resultNegative){
    //  Kiểm tra chữu số trong mảng a và b phải nằm trong [0, 9]
    for (int x : a){
        if (x < 0 || x > 9)
            throw std::invalid_argument("Chữ số không hợp lệ trong a");
    }
    for (int x : b){
        if (x < 0 || x > 9)
            throw std::invalid_argument("Chữ số không hợp lệ trong b");
    }

    resultNegative = false; // Giả sử kết quả ban đầu là không âm
    std::vector<int> result;     // Mảng lưu kết quả của phép cộng

    if (a.empty() && b.empty())
        return {0}; // Trả về mảng 0 nếu hai mảng a và b đều rỗng.

    // Nếu a rỗng thì trả về kết quả là b.
    if (a.empty()){
        result = b;
        resultNegative = isNegativeB;
        return result;
    }

    // Nếu b rỗng thì trả về kết quả là a.
    if (b.empty()){
        result = a;
        resultNegative = isNegativeA;
        return result;
    }

    // Nếu cả a và b đều không âm thì thực hiện phép công.
    if (!isNegativeA && !isNegativeB){
        std::vector<int> c;                    // Mảng lưu kết quả cộng
        int carry = 0;                    // Biến nhớ
        int n1 = a.size(), n2 = b.size(); // Lấy kích thướt của mảng a và b.
        int n = std::max(n1, n2);              // Kích thướt lớn nhất của a và b.
        c.reserve(n + 1);                 // Tạo mảng c có kích thướt n + 1 vì phép cộng có thể tạo ra số có chữ số lớn hơn n nhỏ hơn n + 1.

        // Lặp qua n chữ số
        for (int i = 0; i < n; i++){
            int digitA = (i < n1) ? a[i] : 0;  // ditgitA là lấy chữ số thứ a[i] hoặc 0 nếu n vượt qua kích thướt a.
            int digitB = (i < n2) ? b[i] : 0;  // digtitB là lấy chữ số thứ b[i] hoặc 0 nếu n vượt qua kích thướt b.
            int sum = digitA + digitB + carry; // Tổng của  ditgitA và ditgitB và nhớ(carry).
            c.push_back(sum % 10);             // Lưu chữ số vào mảng c là chữ số hàng đơn vị của sum.
            carry = sum / 10;                  // Lấy nhớ carry là hàng chục của sum.
        }

        // Nếu sau rời vòng lặp vẫn còn số carry thì thêm carry vào mảng c.
        if (carry > 0)
            c.push_back(carry);

        return c; // Trả về vector c chứa kết quả cộng.
    } else if (!isNegativeA && isNegativeB){  // Nếu a không âm và b âm ( a + ( -b ) ) -> a - b.
        // Gọi hàm Tính hiệu hai số với mảng a và b đều không âm.
        return HieuHaiSo(a, b, false, false, resultNegative);
    } else if (isNegativeA && !isNegativeB){ // Nếu a âm và b không âm ( ( -a ) + b) -> b - a.
        // Gọi hàm Tính hiệu hai số với mảng a và b đều không âm.
        return HieuHaiSo(b, a, false, false, resultNegative);
    } else{ // Trường hợp nếu cả a và b đều âm (-a) + (-b) -> -(a + b).
        resultNegative = true;// Vì a và b đều âm nên kết quả sẽ âm gán result là true.
        std::vector<int> c; // Tạo mảng chứa phép tính.
        int carry = 0; // Nhớ 
        int n1 = a.size(), n2 = b.size(); /// Lấy kích thướt a và b.
        int n = std::max(n1, n2); // cho n là kích thướt lớn nhất giữa a và b.
        c.reserve(n + 1); // Tạo mảng c với kích thướt max(a, b) + 1.

        // Lặp qua n chữ số
        for (int i = 0; i < n; i++){
            int digitA = (i < n1) ? a[i] : 0;  // ditgitA là lấy chữ số thứ a[i] hoặc 0 nếu n vượt qua kích thướt a.
            int digitB = (i < n2) ? b[i] : 0;  // digtitB là lấy chữ số thứ b[i] hoặc 0 nếu n vượt qua kích thướt b.
            int sum = digitA + digitB + carry; // Tổng của  ditgitA và ditgitB và nhớ(carry).
            c.push_back(sum % 10);             // Lưu chữ số vào mảng c là chữ số hàng đơn vị của sum.
            carry = sum / 10;                  // Lấy nhớ carry là hàng chục của sum.
        }

        // Nếu sau rời vòng lặp vẫn còn số carry thì thêm carry vào mảng c.
        if (carry > 0)
            c.push_back(carry);

        return c; // Trả về vector c chứa kết quả cộng.
    }
}
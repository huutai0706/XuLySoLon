#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
#include <cctype>
#include "tong.h"
#include "hieu.h"
#include "nhan.h"
#include "chia.h"
#include "SoSanhNhoHon.h"
#include <windows.h>

using namespace std;

// Cấu trúc lưu số lớn 
struct BigInt {
    vector<int> digits; // Lưu các chữ số của số lớn
    bool isNegative;    // Lưu dấu của của số lớn 
    BigInt(const vector<int>& d = {0}, bool neg = false) : digits(d), isNegative(neg) {} // Khởi tạo mặc định với số 0 và dấu không âm.
};

// Chuyển chuỗi số thành BigInt
BigInt stringToBigInt(const string& s) {
    vector<int> result;         // Khởi tạo result 
    bool isNegative = false;    // Khởi tạo isNegative không âm.
    int start = 0;           

    if (!s.empty() && s[0] == '-') {    // Nếu chuỗi bắt đầu là - thì chuỗi âm lưu biến isNegative là true.
        isNegative = true;
        start = 1;  // Gía trị bắt đầu là 1.
    }
    // Duyệt chuỗi từ starst.
    for (int i = start; i < s.length(); i++) {
        if (!isdigit(s[i])) throw invalid_argument("Chuỗi chứa ký tự không phải số"); // Nếu ký tự không phải số ném lỗi.
        result.push_back(s[i] - '0');             // Chuyển ký tự thành số
    }
    if (result.empty()) result.push_back(0);      // Nếu result rỗng thêm 0 vào.
    reverse(result.begin(), result.end());        // Đảo ngược chuỗi lưu dưới dạng 123-> 3, 2, 1
    return BigInt(result, isNegative);            //Trả về BigInt với result và isNegative.
}

// Chuyển BigInt thành chuỗi để in ra.
string bigIntToString(const BigInt& num) {
    if (num.digits.size() == 1 && num.digits[0] == 0) return "0";   // Nếu digits = 0 trả về chuỗi 0.
    string result = num.isNegative ? "-" : "";  // Khởi tạo result với dấu âm nếu isNegative = true.
    for (int i = num.digits.size() - 1; i >= 0; i--) {  // Duyệt các chữ số từ cuối dến đầu và thêm vào result.
        result += to_string(num.digits[i]);
    }
    return result;  // Trả về result.
}

// Kiểm tra ưu tiên toán tử
int precedence(char op) {
    if (op == '+' || op == '-') return 1;   // +, - mức độ ưu tiên là 1.
    if (op == '*' || op == '/') return 2;   // *. / mức độ ưu tiên là 2.
    return 0;                               // Các ký tự khác như () mức độ ưu tiên là 0.
}

// Chuyển biểu thức infix sang postfix 1+2*3 -> 1, 2, 3, *, +.
vector<string> infixToPostfix(const string& expr) {
    vector<string> output;  // Vector lưu biểu thức postfix.
    stack<char> operators;  // Lưu các toán tử và dấu ngoặc.
    string number;          // Chuỗi tạm.

    // Duyệt qua từng lý tự trong biểu thức bỏ qua khoảng trắng.
    for (int i = 0; i < expr.length(); i++) {   // expr.length: tính độ dài chuỗi
        if (isspace(expr[i])) continue;         // isspace(exprr[i]): dùng hàm để nếu tại vị trí là khoảng trắng bỏ qua
        // Có thể dùng expr[i] == " ";

        // Xử lý số (bao gồm số âm)
        // Nếu vị trí hiện tại là số hoặc (toán tử âm và (vị trí là 0 hoặc vị trí trước là (, + - * /))
        // expr[i] được coi là số âm nếu i = 0, sau dấu ngoặc ( hoặc toán tử +-*/
        if (isdigit(expr[i]) || (expr[i] == '-' && (i == 0 || expr[i-1] == '(' || expr[i-1] == '+' || expr[i-1] == '-' || expr[i-1] == '*' || expr[i-1] == '/'))) {
            number += expr[i]; // Thêm ký tự hiện tại vào number
            while (i + 1 < expr.length() && isdigit(expr[i + 1])) {
                number += expr[++i];
            }
            output.push_back(number); // Thêm vào output
            number.clear(); // Xóa number
        } else if (expr[i] == '(') { // Xử lý dấu ngoặc mở
            operators.push(expr[i]);    // Đẩy vào stack operators
        } else if (expr[i] == ')') {    // Xử lý dấu ngoặc đóng
            while (!operators.empty() && operators.top() != '(') { // Lấy toán tử từ stack cho đến khi gặp (
                output.push_back(string(1, operators.top()));   // Thêm từng toán tử vào output
                operators.pop();    // Xóa toán tử khỏi stack
            }
            if (!operators.empty()) operators.pop(); // Bỏ '('
            else throw invalid_argument("Dấu ngoặc không khớp");
        } else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {  // Nếu stack không rỗng toán tử trên không phải là là ( toán tử trên có độ ưu tiên lớn hơn hoặc bằng toán tử hiện tại thì thêm vào output xóa khỏi stack
            while (!operators.empty() && operators.top() != '(' && precedence(operators.top()) >= precedence(expr[i])) {
                output.push_back(string(1, operators.top()));
                operators.pop();
            }
            operators.push(expr[i]);
        } else {
            throw invalid_argument("Ký tự không hợp lệ: " + string(1, expr[i]));
        }
    }

    while (!operators.empty()) {
        if (operators.top() == '(') throw invalid_argument("Dấu ngoặc không khớp");
        output.push_back(string(1, operators.top()));
        operators.pop();
    }

    return output;
}

// Đánh giá biểu thức postfix
BigInt evaluatePostfix(const vector<string>& postfix) {
    stack<BigInt> numStack;

    for (const string& token : postfix) {
        if (isdigit(token[0]) || (token[0] == '-' && token.length() > 1)) {
            BigInt num = stringToBigInt(token);
            numStack.push(num);
        } else {
            if (numStack.size() < 2) throw invalid_argument("Biểu thức không hợp lệ: Thiếu toán hạng");
            BigInt b = numStack.top(); numStack.pop();
            BigInt a = numStack.top(); numStack.pop();
            bool resultNeg;
            vector<int> result;

            if (token == "+") {
                result = TongHaiSo(a.digits, b.digits, a.isNegative, b.isNegative, resultNeg);
            } else if (token == "-") {
                result = HieuHaiSo(a.digits, b.digits, a.isNegative, b.isNegative, resultNeg);
            } else if (token == "*") {
                result = nhanHaiSo(a.digits, b.digits, a.isNegative, b.isNegative, resultNeg);
            } else if (token == "/") {
                result = ChiaHaiSo(a.digits, b.digits, a.isNegative, b.isNegative, resultNeg);
            } else {
                throw invalid_argument("Toán tử không hợp lệ: " + token);
            }

            numStack.push(BigInt(result, resultNeg));
        }
    }

    if (numStack.empty()) throw invalid_argument("Biểu thức rỗng");
    BigInt result = numStack.top();
    numStack.pop();
    if (!numStack.empty()) throw invalid_argument("Biểu thức không hợp lệ: Dư toán hạng");
    return result;
}

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    if (argc != 3) {
       cerr << "Cách dùng: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }

    ifstream inFile(argv[1]);
    ofstream outFile(argv[2]);

    if (!inFile.is_open()) {
       cerr << "Không thể mở tệp đầu vào: " << argv[1] << endl;
        return 1;
    }
    if (!outFile.is_open()) {
       cerr << "Không thể mở tệp đầu ra: " << argv[2] << endl;
        return 1;
    } else {
        cout << "\nĐã in ra console và ghi vào trong tệp " << argv[2] << endl << endl;
        cout << "----------------------Kết quả-------------------------\n";
    }

    string expr;
    while (getline(inFile, expr)) {
        try {
            vector<string> postfix = infixToPostfix(expr);
            BigInt result = evaluatePostfix(postfix);
            string resultStr = bigIntToString(result);
            outFile << resultStr << endl;
            cout << resultStr << endl;
        } catch (const exception& e) {
            string error = "Lỗi: " + string(e.what());
            outFile << error << endl;
            cout << error << endl;
        }
    }
    cout << "--------------------------------------------------------\n\n";
    inFile.close();
    outFile.close();
    return 0;
}
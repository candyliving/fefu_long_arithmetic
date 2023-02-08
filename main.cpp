#include <bits/stdc++.h>

using namespace std;

const double pi = acos(-1);

typedef complex<double> ftype;

fstream fin("in.txt", ios::in);
fstream fout("out.txt", ios::out);
fstream fin_answers("answer.txt", ios::in);

string delete_zeros(string num) {
    int counter = num.size();
    for (int i = 0; i < counter; i++) {
        if (num[0] == '0') {
            num.erase(num.begin());
        } else break;
    }

    return num;
}

vector<int> addition(vector<int> op1, vector<int> op2) {
    int lenop1 = op1.size();
    int lenop2 = op2.size();

    int dif = lenop1 - lenop2;

    for (int i = 0; i < dif; i++) {
        op2.insert(op2.begin(), 0);

    }
    for (int i = lenop1 - 1; i >= 0; i--) {
        if (op1[i] + op2[i] >= 10) {
            op1[i] = op1[i] + op2[i] - 10;
            op1[i - 1] += 1;
        } else {
            op1[i] = op1[i] + op2[i];
        }

    }
    return op1;
}

string result_addition(string num1, string num2) {
    vector<int> op1;
    vector<int> op2;
    vector<int> answer;
    op1.push_back(0);
    op2.push_back(0);
    for (int i = 0; num1.size() > i; i++) {
        op1.push_back(static_cast<int>(num1[i]) - 48);
    }
    for (int i = 0; num2.size() > i; i++) {
        op2.push_back(static_cast<int>(num2[i]) - 48);
    }
    if (num1.size() > num2.size()) answer = addition(op1, op2);
    else answer = addition(op2, op1);
    stringstream ss;
    if (answer[0] == 0) {
        for (auto it = answer.begin() + 1; it != answer.end(); it++) {
            ss << *it;
        }
    } else {
        for (auto it = answer.begin(); it != answer.end(); it++) {
            ss << *it;
        }
    }
    return ss.str();
}

vector<int> subtraction(vector<int> op1, vector<int> op2) {
    int lenop1 = op1.size();
    int lenop2 = op2.size();
    int dif = lenop1 - lenop2;
    for (int i = 0; i < dif; i++) {
        op2.insert(op2.begin(), 0);
    }
    for (int i = lenop1 - 1; i >= 0; i--) {
        if (op1[i] - op2[i] < 0) {
            op1[i] = op1[i] + 10 - op2[i];
            op1[i - 1] -= 1;
        } else {
            op1[i] = op1[i] - op2[i];
        }
    }
    return op1;
}

string result_subtraction(string str1, string str2) {

    vector<int> op1;
    vector<int> op2;
    vector<int> answer;

    for (int i = 0; str1.size() > i; i++) {
        op1.push_back(static_cast<int>(str1[i]) - 48);
    }
    for (int i = 0; str2.size() > i; i++) {
        op2.push_back(static_cast<int>(str2[i]) - 48);
    }
    answer = subtraction(op1, op2);
    str1 = "";
    int c = 0;
    for (int j = 0; j < answer.size(); j++) {
        if (answer[j] == 0) {
            continue;
        } else {
            for (int i = j; answer.size() > i; i++) {
                str1 += to_string(answer[i]);
                c++;
            }
            break;
        }
    }
    if (c == 0) str1 += "0";
    return str1;

}

vector<int> reading_big(string str, vector<int> &a) {
    for (int i = str.length() - 1; i >= 0; i -= 1) {
        a.push_back(static_cast<int>(str[i]) - 48);
    }
    return a;
}

string convert_to_string(vector<int> res) {
    stringstream ss;
    reverse(res.begin(), res.end());
    for (auto it = res.begin(); it != res.end(); it++) {
        ss << *it;
    }
    return ss.str();
}

void normalize(vector<int> &a) {
    int carry = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        a[i] += carry;
        carry = a[i] / 10;
        a[i] %= 10;
    }
}


void fft(vector<ftype> &a, bool invert) {
    int n = (int) a.size();
    if (n == 1) return;

    vector<ftype> a0(n / 2), a1(n / 2);
    for (int i = 0, j = 0; i < n; i += 2, ++j) {
        a0[j] = a[i];
        a1[j] = a[i + 1];
    }
    fft(a0, invert);
    fft(a1, invert);

    double ang = 2 * pi / n * (invert ? -1 : 1);
    ftype w(1), wn(cos(ang), sin(ang));
    for (int i = 0; i < n / 2; ++i) {
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        if (invert)
            a[i] /= 2, a[i + n / 2] /= 2;
        w *= wn;
    }
}

void multiply(const vector<int> &a, const vector<int> &b, vector<int> &res) {
    vector<ftype> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    size_t n = 1;
    while (n < max(a.size(), b.size())) n <<= 1;
    n <<= 1;
    fa.resize(n), fb.resize(n);

    fft(fa, false), fft(fb, false);
    for (size_t i = 0; i < n; ++i)
        fa[i] *= fb[i];
    fft(fa, true);

    res.resize(n);
    for (size_t i = 0; i < n; ++i)
        res[i] = int(fa[i].real() + 0.5);
}

bool is_equal(vector<int> &a, vector<int> &b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

bool is_bigger(vector<int> &a, vector<int> &b) {
    if (a.size() != b.size()) {
        return (a.size() > b.size());
    }
    for (int i = a.size() - 1; i >= 0; i--) {
        if (a[i] != b[i]) {
            return (a[i] > b[i]);
        }
    }
    return false;
}

bool compare(string num1, string num2) {
    if (num1.size() < num2.size()) return false;
    else if (num1.size() == num2.size() && num1 < num2) return false;
    return true;
}

string subForDivision(string num1, string num2) {

    bool is_negative = false;

    if (num1.size() < num2.size()) {
        string temp = num1;
        num1 = num2;
        num2 = temp;
        is_negative = true;
    } else if (num1.size() == num2.size()) {
        int len = num1.size();
        for (int i = 0; i < len; ++i) {
            if (num1[i] == num2[i])
                continue;
            if (num1[i] > num2[i])
                break;
            if (num1[i] < num2[i]) {
                string temp = num1;
                num1 = num2;
                num2 = temp;
                is_negative = true;
            }
        }
    }
    int lenNum1 = num1.size();
    int lenNum2 = num2.size();

    int *result = new int[lenNum1];
    int index = 0;

    for (int i = lenNum1 - 1; i >= 0; --i)
        result[index++] = num1[i] - '0';

    index = 0;
    for (int i = lenNum2 - 1; i >= 0; --i) {
        int num = num2[i] - '0';
        if (num > result[index]) {
            result[index + 1] -= 1;
            result[index] = 10 + result[index] - num;
        } else
            result[index] = result[index] - num;

        ++index;
    }
    index = lenNum1 - 1;
    while (result[index] == 0)
        --index;


    ostringstream osstr;
    if (is_negative == true)
        osstr << '-';
    for (int i = index; i >= 0; --i)
        osstr << result[i];
    delete result;
    return osstr.str();
}

string division(string a, string b) {
    string reminder;
    ostringstream result;
    int count;
    if ("0" == b) {
        return "null";
    }
    a = delete_zeros(a);
    b = delete_zeros(b);
    if (!compare(a, b)) {
        return "0";
    }
    int len = a.size();
    for (int i = 0; i < len; i++) {
        count = 0;
        reminder.push_back(a[i]);
        while (compare(reminder, b)) {
            reminder = subForDivision(reminder, b);
            count++;
        }
        if (count != 0) result << count;
    }
    return result.str();
}

int main() {
    string num1, num2, operation_sign, result_str, correct_result;
    int correct_tests = 0, wrong_tests = 0, tests = 0, minus_1 = 0, minus_2 = 0;

    while (tests != 30) {
        tests += 1;
        fin >> num1 >> operation_sign >> num2;
        fin_answers >> correct_result;
        if (num1[0] == '-') {
            minus_1 = 1;
            num1.erase(0, 1);
        }
        if (num2[0] == '-') {
            minus_2 = 1;
            num2.erase(0, 1);
        }
        vector<int> a, b, result;
        a = reading_big(num1, a);
        b = reading_big(num2, b);
        if (operation_sign == "+") {
            if (minus_1 == 0 && minus_2 == 0) {
                result_str = result_addition(num1, num2);
            }
            if (minus_1 == 1 && minus_2 == 1) {
                result_str = result_addition(num1, num2);
                result_str.insert(0, "-");
            }
            if (minus_1 == 1 && minus_2 == 0) {
                if (is_bigger(a, b)) {
                    result_str = result_subtraction(num1, num2);
                    result_str.insert(0, "-");
                } else {
                    result_str = result_subtraction(num2, num1);
                }
            }
            if (minus_1 == 0 && minus_2 == 1) {
                if (is_bigger(b, a)) {
                    result_str = result_subtraction(num2, num1);
                    result_str.insert(0, "-");
                } else {
                    result_str = result_subtraction(num1, num2);
                }
            }
        }
        if (operation_sign == "-") {
            if (minus_1 == 0 && minus_2 == 0) {
                if (is_bigger(a, b) || is_equal(a, b)) {
                    result_str = result_subtraction(num1, num2);
                } else {
                    result_str = result_subtraction(num2, num1);
                    result_str.insert(0, "-");
                }
            }
            if (minus_1 == 0 && minus_2 == 1) {
                result_str = result_addition(num1, num2);
            }
            if (minus_1 == 1 && minus_2 == 0) {
                result_str = result_addition(num1, num2);
                result_str.insert(0, "-");
            }
            if (minus_1 == 1 && minus_2 == 1) {
                if (is_bigger(a, b)) {
                    result_str = result_subtraction(num1, num2);
                    result_str.insert(0, "-");
                } else {
                    result_str = result_subtraction(num2, num1);
                }
            }
        }
        if (operation_sign == "*") {
            multiply(a, b, result);
            normalize(result);
            result_str = convert_to_string(result);
            result_str = delete_zeros(result_str);
            if ((minus_1 == 1 && minus_2 == 0) || (minus_1 == 0 && minus_2 == 1)) {
                result_str.insert(0, "-");
            }
            if (num1 == "0" || num2 == "0") {
                result_str = "0";
            }
        }
        if (operation_sign == "/") {
            result_str = division(num1, num2);
            if (((minus_1 == 1 && minus_2 == 0) || (minus_1 == 0 && minus_2 == 1)) && num1 != "0") {
                result_str.insert(0, "-");
            }
        }
        if (result_str == correct_result){
            fout <<"#"<< tests << " OK: " << result_str << " ANSWER: " << correct_result << endl;
            correct_tests++;
        } else{
            fout <<"#"<< tests << " NOT OK: " << result_str << " ANSWER: " << correct_result << endl;
            wrong_tests++;
        }
        minus_1 = 0;
        minus_2 = 0;
    }
    fout << "CORRECT TESTS: " << correct_tests << endl;
    fout << "WRONG TESTS: " << wrong_tests << endl;
    return 0;
}
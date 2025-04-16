#include"input_check.h"

double Stod(const std::string& s) {
    size_t i = 0;
    bool negative = false;

    while (i < s.size() && isspace(s[i])) i++;

    if (i < s.size() && s[0] == '-') {
        negative = true;
        i++;
    }

    double result = 0;
    while (i < s.size() && isdigit(s[i])) {
        result = result * 10 + (s[i] - '0');
        i++;
    }

    if (i < s.size() && s[i] == '.') {
        i++;
        double fraction = 0;
        double divisor = 1;

        while (i < s.size() && isdigit(s[i])) {
            fraction = fraction * 10 + (s[i] - '0');
            divisor *= 10;
            i++;
        }
        result += fraction / divisor;
    }

    return negative ? -result : result;
}

bool check_unsigned_input(const std::string& s) {
    if (s.empty()) return false;
    return s.length() < MAX_INT32.length() || (s.length() == MAX_INT32.length() && s <= MAX_INT32);
}
bool check_int_input(const std::string& s) {
    if (s.empty()) return false;
    bool has_point = false;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == '-') {
            if (i != 0) return false;
        }
        else if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}
bool check_onlyNegative_int_input(const std::string& s) {
    if (s.empty() || s[0] != '-') return false;
    std::string num = s.substr(1);
    return num.length() < MIN_INT32.length() || (num.length() == MIN_INT32.length() && num <= MIN_INT32);
}
bool check_onlyPositive_int_input(const std::string& s) {
    if (s.empty()) return false;
    if (s[0] == '-') return false;
    if (!(s.begin(), s.end(), ::isdigit)) return false;
    return s.length() < MAX_INT32.length() || (s.length() == MAX_INT32.length() && s <= MAX_INT32);
}
bool check_double_float_input(const std::string& s) {
    if (s.empty()) return false;
    bool has_point = false;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == '-') {
            if (i != 0) return false;
        }
        else if (s[i] == '.' && s[0] != '.') {
            if (has_point) return false;
            has_point = true;
        }
        else if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}
bool englishAlnum_imput(const std::string& s) {
    if (s.empty()) return false;
    char c = s[0];
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || (c == '-') || (c == '_') || (c == '.');
}

void filteredInput_letter_numbers(std::string& s, bool maskInput) {
    s.clear();

    while (true) {
        int c = _getch();
        std::string charAsString(1, (char)c);

        if (c == 0 || c == 0xE0) {
            _getch();
            continue;
        }

        if (englishAlnum_imput(charAsString) && s.size() < MAX_DIGITS) {
            s += (char)c;
            std::cout << (maskInput ? '*' : (char)c);
        }

        if (c == BACKSPACE && !s.empty()) {
            s.pop_back();
            std::cout << "\b \b";
        }
        else if (c == ENTER && !s.empty()) {
            std::cout << std::endl;
            return;
        }
    }
}
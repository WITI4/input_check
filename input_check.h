#pragma once
#include <iostream>
#include <string>
#include <conio.h>

constexpr const int ENTER = 13;
constexpr const int BACKSPACE = 8;
constexpr const int MAX_DIGITS = 11;
const std::string MAX_INT32 = "2147483647";
const std::string MIN_INT32 = "2147483648";

double Stod(const std::string& s);

bool check_unsigned_input(const std::string& s);
bool check_int_input(const std::string& s);
bool check_onlyNegative_int_input(const std::string& s);
bool check_onlyPositive_int_input(const std::string& s);
bool check_double_float_input(const std::string& s);
bool englishAlnum_imput(const std::string& s);

void filteredInput_letter_numbers(std::string& s, bool maskInput = false);

template <typename T>
bool is_valid_number(T& num, bool requireNegative = false, bool requirePositive = false) {
    std::string buf;

    while (true) {
        int c = _getch();

        if constexpr (std::is_same_v<T, unsigned>) {
            if (isdigit(c) && buf.size() < MAX_DIGITS - 1) {
                buf += c;
                if (check_unsigned_input(buf)) std::cout << (char)c;
                else buf.pop_back();
            }
        }
        else if constexpr (std::is_same_v<T, int>) {
            if ((isdigit(c) || (c == '-' && buf.empty())) && buf.size() < MAX_DIGITS) {
                buf += c;
                bool isValid = false;
                if (requireNegative) {
                    isValid = check_onlyNegative_int_input(buf);
                }
                else if (requirePositive) {
                    isValid = check_onlyPositive_int_input(buf);
                }
                else {
                    isValid = check_int_input(buf);
                }
                if (isValid) std::cout << (char)c;
                else buf.pop_back();
            }
        }
        else if constexpr (std::is_same_v<T, double> || std::is_same_v<T, float>) {
            if ((isdigit(c) || c == '.' || (c == '-' && buf.empty())) && buf.size() < MAX_DIGITS) {
                buf += c;
                if (check_double_float_input(buf)) std::cout << (char)c;
                else buf.pop_back();
            }
        }
        else if constexpr (std::is_same_v<T, std::string>) {
            if (isalpha(c)) {
                buf += c;
                std::cout << (char)c;
            }
        }

        if (c == BACKSPACE && !buf.empty()) {
            buf.pop_back();
            std::cout << "\b \b";
        }
        else if (c == ENTER && !buf.empty()) {
            try {
                if constexpr (std::is_same_v<T, unsigned>) {
                    num = stoul(buf);
                }
                else if constexpr (std::is_same_v<T, int>) {
                    num = stoi(buf);
                }
                else if constexpr (std::is_same_v<T, double> || std::is_same_v<T, float>) {
                    num = Stod(buf);
                }
                else if constexpr (std::is_same_v<T, std::string>) {
                    num = buf;
                }
                return true;
            }
            catch (...) {
                return false;
            }
        }
    }
}
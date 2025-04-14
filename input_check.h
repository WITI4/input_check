#pragma once
#include <iostream>
#include <string>
#include <conio.h>

const int ENTER = 13;
const int BACKSPACE = 8;
const int MAX_DIGITS = 11;
const std::string MAX_INT32 = "2147483647";
const std::string MIN_INT32 = "2147483648";

double Stod(const std::string& s);

bool check_unsigned_input(const std::string& s);
bool check_int_input(const std::string& s);
bool check_double_float_input(const std::string& s);

template <typename T>
bool is_valid_number(T& num) {
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
                if (check_int_input(buf)) std::cout << (char)c;
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
                return true;
            }
            catch (...) {
                return false;
            }
        }
    }
}
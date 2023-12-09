#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <iomanip>
#include <string>

struct Time {
    int hours{};
    int minutes{};
    int seconds{};
};


// Validation function
bool isValid(const Time& time);

// String representation
std::string toString(const Time& time, bool is24HourFormat = true);

// AM/PM check
bool isAM(const Time& time);

// Arithmetic operators
Time operator+(const Time& time, int seconds);
Time operator-(const Time& time, int seconds);
Time& operator++(Time& time); // Prefix ++
Time operator++(Time& time, int); // Postfix ++
Time& operator--(Time& time); // Prefix --
Time operator--(Time& time, int); // Postfix --

// Comparison operators
bool operator==(const Time& lhs, const Time& rhs);
bool operator!=(const Time& lhs, const Time& rhs);
bool operator<(const Time& lhs, const Time& rhs);
bool operator<=(const Time& lhs, const Time& rhs);
bool operator>(const Time& lhs, const Time& rhs);
bool operator>=(const Time& lhs, const Time& rhs);

// Stream operators
std::ostream& operator<<(std::ostream& os, const Time& time);

//Here the time input is accepting 3 numbers and 2 characters even though it is an incorrect value

std::istream& operator>>(std::istream& is, Time& time);

#endif

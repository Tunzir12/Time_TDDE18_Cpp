#include "Time.h"
#include<string>


using namespace std;


// Validation function
bool isValid(const Time& time) {
    return (time.hours >= 0 && time.hours < 24) &&
           (time.minutes >= 0 && time.minutes < 60) &&
           (time.seconds >= 0 && time.seconds < 60);
}

// String representation
string toString(const Time& time, bool is24HourFormat) {
    ostringstream oss{};
    if (is24HourFormat) {
        oss <<setfill('0') << setw(2) << time.hours << ":"
            << setw(2) << time.minutes << ":"
            << setw(2) << time.seconds;
    } else {
        string period = (time.hours < 12) ? "AM" : "PM";
        int displayHours = (time.hours == 0 || time.hours == 12) ? 12 : time.hours % 12;
        oss << setfill('0') << setw(2) << displayHours << ":"
            << setw(2) << time.minutes << ":"
            << setw(2) << time.seconds << " " << period;
    }
    return oss.str();
}

// AM/PM check
bool isAM(const Time& time) {
    return (time.hours >= 0 && time.hours < 12);
}

// Arithmetic operators
Time operator+(const Time& time, int seconds) {
    Time result = time;
    int totalSeconds = time.hours * 3600 + time.minutes * 60 + time.seconds + seconds;

    
    while (totalSeconds < 0) {
        totalSeconds += 86400; // Add 1 day's worth of seconds for negative values
    }

    if (totalSeconds < 0) {
        totalSeconds = 0;
    }

    result.hours = totalSeconds / 3600;
    totalSeconds %= 3600;
    result.minutes = totalSeconds / 60;
    result.seconds = totalSeconds % 60;

     while (result.hours >= 24) { // // Handle rollovers for days
        result.hours -= 24;
    }


    return result;
}

Time operator-(const Time& time, int seconds) {
    // Reuse the code of operator+ by negating the seconds to subtract
    return time + (-seconds);
}


// Prefix ++
Time& operator++(Time& time) {
    time = time + 1;
    return time;
}

// Postfix ++
Time operator++(Time& time, int) {
    Time oldTime = time;
    time = time + 1;
    return oldTime;
}

// Prefix --
Time& operator--(Time& time) {
    time = time - 1;
    return time;
}

// Postfix --
Time operator--(Time& time, int) {
    Time oldTime = time;
    time = time - 1;
    return oldTime;
}

// Comparison operators
bool operator==(const Time& lhs, const Time& rhs) {
    return (lhs.hours == rhs.hours) && (lhs.minutes == rhs.minutes) && (lhs.seconds == rhs.seconds);
}

bool operator!=(const Time& lhs, const Time& rhs) {
    return !(lhs == rhs);
}

bool operator<(const Time& lhs, const Time& rhs) {
    if (lhs.hours < rhs.hours) return true;
    if (lhs.hours > rhs.hours) return false;
    if (lhs.minutes < rhs.minutes) return true;
    if (lhs.minutes > rhs.minutes) return false;
    return lhs.seconds < rhs.seconds;
}

bool operator<=(const Time& lhs, const Time& rhs) {
    return (lhs < rhs) || (lhs == rhs);
}

bool operator>(const Time& lhs, const Time& rhs) {
    return !(lhs <= rhs);
}

bool operator>=(const Time& lhs, const Time& rhs) {
    return !(lhs < rhs);
}

// Stream operators
std::ostream& operator<<(std::ostream& os, const Time& time) {
    os << toString(time);
    return os;
}

std::istream& operator>>(std::istream& is, Time& time) {
    int hours, minutes, seconds;
    char colon;

    // Attempt to read the hours, minutes, and seconds from the input stream
    is >> hours >> colon >> minutes >> colon >> seconds;

    if (is.fail() || is.peek() != EOF || !isValid(Time{hours, minutes, seconds})) {
        // Set the failbit on the stream if any of the conditions fail
        is.setstate(std::ios::failbit);
    } else {
        
        time.hours = hours;
        time.minutes = minutes;
        time.seconds = seconds;
    }

    return is;
}


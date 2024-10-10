#include <iostream>
#include <ctime>

class ClockTime {
public:
    std::tm userTime;
    std::tm current_time;
    std::time_t current_time_t;
    ClockTime();
    long long readTimeFromInput();
    long long calculateTimeFromSeconds();
    std::wstring time_to_wstring(tm current_time);
    void update(int i, double x, double y);
};

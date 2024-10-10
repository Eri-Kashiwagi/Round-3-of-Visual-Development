#include <iostream>
#include <ctime>
#include "ClockTime.h"
#include <sstream> 
#include <iomanip>
#include <graphics.h>
using namespace std;
ClockTime::ClockTime() {
    userTime.tm_year = 2024 - 1900; 
    userTime.tm_mon = 5 - 1;
    userTime.tm_mday = 3;
    userTime.tm_hour = 0;
    userTime.tm_min = 0;
    userTime.tm_sec = 0;
    userTime.tm_isdst = -1;
}
long long ClockTime::readTimeFromInput() {
    std::cout << "请输入年份: ";
    std::cin >> userTime.tm_year;
    userTime.tm_year -= 1900;  
    std::cout << "请输入月份: ";
    std::cin >> userTime.tm_mon;
    userTime.tm_mon -= 1;  
    std::cout << "请输入日期: ";
    std::cin >> userTime.tm_mday;
    std::cout << "请输入小时: ";
    std::cin >> userTime.tm_hour;
    std::cout << "请输入分钟: ";
    std::cin >> userTime.tm_min;
    std::cout << "请输入秒: ";
    std::cin >> userTime.tm_sec;
    userTime.tm_isdst = -1;
    std::tm targetTime = {};
    targetTime.tm_year = 2024 - 1900;
    targetTime.tm_mon = 5 - 1;
    targetTime.tm_mday = 3;
    targetTime.tm_hour = 0;
    targetTime.tm_min = 0;
    targetTime.tm_sec = 0;
    targetTime.tm_isdst = -1;
    std::time_t targetTimeT = std::mktime(&targetTime);
    std::time_t userTimeT = std::mktime(&userTime);
    return std::difftime(userTimeT,targetTimeT);
}
long long ClockTime::calculateTimeFromSeconds() {
    long long seconds;
    std::cout << "请输入期望的秒数: ";
    std::cin >> seconds;
    std::time_t userTimeT = std::mktime(&userTime);
    std::time_t newTimeT = userTimeT + seconds;
    std::tm newTime;
    localtime_s(&newTime, &newTimeT); 
    userTime = newTime;
    return seconds;
}
wstring ClockTime::time_to_wstring(tm current_time) {
    wstringstream ss;
    ss << setfill(L'0') << std::setw(4) << (current_time.tm_year + 1900) << L"/"
        << setw(2) << (current_time.tm_mon + 1) << L"/"
        << setw(2) << current_time.tm_mday << L" "
        << setw(2) << current_time.tm_hour << L":"
        << setw(2) << current_time.tm_min << L":"
        << setw(2) << current_time.tm_sec;
    return ss.str();
}
void ClockTime::update(int i,double x,double y) {
    localtime_s(&current_time, &current_time_t);
    wstring time_str = time_to_wstring(current_time);
    settextcolor(BLACK);
    settextstyle(50, 0, L"Consolas");
    outtextxy(600, 950, time_str.c_str());
    current_time_t += i;
}
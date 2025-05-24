#include "DateUtils.h"
#include <ctime>
#include <sstream>
#include <iomanip>
#include <iostream>
using namespace std;

string getCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    stringstream ss;
    ss << setfill('0') << setw(2) << ltm->tm_mday << "-"
       << setfill('0') << setw(2) << 1 + ltm->tm_mon << "-"
       << 1900 + ltm->tm_year;
    return ss.str();
}

int daysBetween(const string& date1, const string& date2) {
    tm tm1 = {}, tm2 = {};
    istringstream(date1) >> get_time(&tm1, "%d-%m-%Y");
    istringstream(date2) >> get_time(&tm2, "%d-%m-%Y");

    time_t t1 = mktime(&tm1);
    time_t t2 = mktime(&tm2);

    if (t1 == -1 || t2 == -1) return 0;
    double seconds = difftime(t2, t1);
    return static_cast<int>(seconds / (60 * 60 * 24));
}

bool isOverdue(const string& issueDate, const string& checkDate, int allowedDays) {
    return daysBetween(issueDate, checkDate) > allowedDays;
}


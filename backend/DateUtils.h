#ifndef DATEUTILS_H
#define DATEUTILS_H

#include <string>
using namespace std;

string getCurrentDate();
int daysBetween(const string& date1, const string& date2);
bool isOverdue(const string& issueDate, const string& checkDate, int allowedDays = 14);

#endif

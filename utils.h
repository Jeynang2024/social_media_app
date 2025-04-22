// include/utils.h
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
using namespace std;

vector<string> split(const string& str, char delimiter);
bool isInteger(const string& str);
bool accountExists(const string& user_id);
void saveToCSV(const string& user_id);

#endif
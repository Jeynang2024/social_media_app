// src/utils.cpp
#include "utils.h"
#include <fstream>
#include <algorithm>
#include <cctype>
#include<iostream>
#include <sstream>
using namespace std;

vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    stringstream ss(str);
    while (getline(ss, token, delimiter)) tokens.push_back(token);
    return tokens;
}

bool isInteger(const string& str) {
    return !str.empty() && all_of(str.begin(), str.end(), ::isdigit);
}

bool accountExists(const string& user_id) {
    ifstream file("account.csv");
    string line, uid;
    while (getline(file, line)) {
        uid = split(line, ',')[0];
        if (uid == user_id) return true;
    }
    return false;
}

void saveToCSV(const string& user_id) {
    ofstream file("account.csv", ios::app);
    int po;
    cout << "Creating new account\nEnter the post count: ";
    cin >> po;
    file << user_id << ",,," << po << "\n";
    cout << "Account created.\n";
    file.close();
}
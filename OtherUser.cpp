// src/OtherUser.cpp
#include "OtherUser.h"
#include "utils.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

OtherUser::OtherUser(string uid, vector<string> followers, 
                     vector<string> following, int posts)
    : User(uid, followers, following, posts) {}

void OtherUser::displayInfo() const {
    cout << left << setw(25) << "USER ID"
         << setw(25) << "No. OF FOLLOWERS"
         << setw(25) << "No. OF ACCs FOLLOWING"
         << setw(25) << "No. OF POSTS" << endl;
    cout << left << setw(25) << user_id
         << setw(25) << followers_list.size()
         << setw(25) << following_list.size()
         << setw(25) << posts_count << endl;

    char choice;
    cout << "Do you want to see the followers list? (y/n): ";
    cin >> choice;
    if (tolower(choice) == 'y') {
        for (const auto& f : followers_list) cout << f << endl;
    }

    cout << "Do you want to see the following list? (y/n): ";
    cin >> choice;
    if (tolower(choice) == 'y') {
        for (const auto& f : following_list) cout << f << endl;
    }
}

namespace other_users {
    void getAccountInfo(string search_user_id, string current_user_id) {
        ifstream file("account.csv");
        string line;
        vector<string> updatedLines;
        bool found = false;
        bool followOperationPerformed = false;
        bool unfollowOperation = false;
    
        while (getline(file, line)) {
            if (line.empty()) continue;
            
            vector<string> tokens = split(line, ',');
            if (tokens.size() < 4) continue;
    
            string uid = tokens[0];
            if (uid == search_user_id) {
                vector<string> followersList = split(tokens[1], ';');
                vector<string> followingList = split(tokens[2], ';');
                int postsCount = isInteger(tokens[3]) ? stoi(tokens[3]) : 0;
    
                OtherUser user(uid, followersList, followingList, postsCount);
                user.displayInfo();
                found = true;
    
                bool isAlreadyFollowing = find(followersList.begin(), followersList.end(), current_user_id) != followersList.end();
    
                if (isAlreadyFollowing) {
                    cout << "You are already following " << search_user_id << ".\nDo you want to unfollow them? (yes/no): ";
                    string choice;
                    cin >> choice;
                    if (choice == "yes") {
                        followersList.erase(remove(followersList.begin(), followersList.end(), current_user_id), followersList.end());
                        unfollowOperation = true;
                        followOperationPerformed = true;
                        cout << "Successfully unfollowed.\n";
                    }
                } else {
                    cout << "Do you want to follow " << search_user_id << "? (yes/no): ";
                    string choice;
                    cin >> choice;
                    if (choice == "yes") {
                        followersList.push_back(current_user_id);
                        followOperationPerformed = true;
                        cout << "You have followed " << search_user_id << ".\n";
                    }
                }
    
                stringstream updatedLine;
                updatedLine << uid << ",";
                for (size_t i = 0; i < followersList.size(); ++i) {
                    updatedLine << followersList[i];
                    if (i != followersList.size() - 1) updatedLine << ";";
                }
                updatedLine << ",";
                for (size_t i = 0; i < followingList.size(); ++i) {
                    updatedLine << followingList[i];
                    if (i != followingList.size() - 1) updatedLine << ";";
                }
                updatedLine << "," << postsCount;
                updatedLines.push_back(updatedLine.str());
            } else {
                updatedLines.push_back(line);
            }
        }
        file.close();
    
        if (!found) {
            cout << "User with ID " << search_user_id << " not found." << endl;
            return;
        }
    
        if (followOperationPerformed) {
            vector<string> finalLines;
            for (const auto& line : updatedLines) {
                vector<string> tokens = split(line, ',');
                if (tokens.size() < 4) {
                    finalLines.push_back(line);
                    continue;
                }
    
                string uid = tokens[0];
                if (uid == current_user_id) {
                    vector<string> followersList = split(tokens[1], ';');
                    vector<string> followingList = split(tokens[2], ';');
                    int postsCount = isInteger(tokens[3]) ? stoi(tokens[3]) : 0;
    
                    if (unfollowOperation) {
                        followingList.erase(remove(followingList.begin(), followingList.end(), search_user_id), followingList.end());
                    } else if (followOperationPerformed && !unfollowOperation) {
                        followingList.push_back(search_user_id);
                    }
    
                    stringstream updatedLine;
                    updatedLine << uid << ",";
                    for (size_t i = 0; i < followersList.size(); ++i) {
                        updatedLine << followersList[i];
                        if (i != followersList.size() - 1) updatedLine << ";";
                    }
                    updatedLine << ",";
                    for (size_t i = 0; i < followingList.size(); ++i) {
                        updatedLine << followingList[i];
                        if (i != followingList.size() - 1) updatedLine << ";";
                    }
                    updatedLine << "," << postsCount;
                    finalLines.push_back(updatedLine.str());
                } else {
                    finalLines.push_back(line);
                }
            }
            updatedLines = finalLines;
        }
    
        ofstream outFile("account.csv");
        for (const auto& updatedLine : updatedLines) {
            outFile << updatedLine << endl;
        }
        outFile.close();
    }

}
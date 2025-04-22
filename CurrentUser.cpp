#include "CurrentUser.h"
#include "utils.h"
#include "OtherUser.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

CurrentUser::CurrentUser(string uid, vector<string> followers, 
                         vector<string> following, int posts)
    : User(uid, followers, following, posts) {}

void CurrentUser::displayInfo() const {
    cout << "Viewing your own profile:\n";

    ifstream file("account.csv");
    string line;
    bool found = false;

    while (getline(file, line)) {
        vector<string> tokens = split(line, ',');
        if (tokens.size() < 4) continue;

        string uid = tokens[0];
        if (uid == user_id) {
            vector<string> followersList = split(tokens[1], ';');
            vector<string> followingList = split(tokens[2], ';');
            int postsCount = isInteger(tokens[3]) ? stoi(tokens[3]) : 0;

            cout << left << setw(25) << "USER ID"
                 << setw(25) << "No. OF FOLLOWERS"
                 << setw(25) << "No. OF ACCs FOLLOWING"
                 << setw(25) << "No. OF POSTS" << endl;
            cout << left << setw(25) << uid
                 << setw(25) << followersList.size()
                 << setw(25) << followingList.size()
                 << setw(25) << postsCount << endl;

            char choice;
            cout << "Do you want to see the followers list? (y/n): ";
            cin >> choice;
            if (tolower(choice) == 'y') {
                for (const auto& f : followersList) cout << f << endl;
            }

            cout << "Do you want to see the following list? (y/n): ";
            cin >> choice;
            if (tolower(choice) == 'y') {
                for (const auto& f : followingList) cout << f << endl;
            }

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Your profile could not be found.\n";
    }

    file.close();
}

void CurrentUser::update(string user_id, int add) {
    ifstream file("account.csv");
    vector<string> lines;
    string line;
    bool updated = false;
    int postsCount = 0;

    while (getline(file, line)) {
        vector<string> tokens = split(line, ',');
        if (tokens.size() < 4) {
            lines.push_back(line);
            continue;
        }

        if (tokens[0] == user_id) {
            postsCount = stoi(tokens[3]);
            
            if (add == 1) {
                postsCount++;
            } else if (add == -1 && postsCount > 0) {
                postsCount--;
            }

            vector<string> followersList = split(tokens[1], ';');
            vector<string> followingList = split(tokens[2], ';');
            stringstream updatedLine;
            updatedLine << user_id << ",";

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

            lines.push_back(updatedLine.str());
            updated = true;
        } else {
            lines.push_back(line);
        }
    }
    file.close();

    if (updated) {
        ofstream outFile("account.csv");
        for (const auto& l : lines) outFile << l << "\n";
        outFile.close();
    } else {
        cout << "Your account could not be found.\n";
    }
}

void CurrentUser::editProfile() {
    int choice;
    do {
        cout << "\n--- Edit Profile Menu ---\n";
        cout << "1. Add Post\n2. Delete Post\n3. Unfollow Someone\n4. Exit\nEnter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                update(user_id, 1);
                cout << "Post added!\n";
                break;
            case 2:
                update(user_id, -1);
                cout << "Post deleted!\n";
                break;
            case 3: {
                string uid;
                cout << "Enter user ID to unfollow: ";
                getline(cin, uid);
                other_users::getAccountInfo(uid, user_id);
                break;
            }
            case 4:
                cout << "Exiting profile editing.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 4);
}
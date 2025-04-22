// src/main.cpp
#include "CurrentUser.h"
#include "OtherUser.h"
#include "utils.h"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    string current_user_id;
    cout << "Enter your user ID: ";
    cin >> current_user_id;
    
    if (!accountExists(current_user_id)) {
        char choice;
        cout << "Account does not exist. Do you want to create a new account? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            saveToCSV(current_user_id);
        } else {
            cout << "Exiting program.\n";
            return 0;
        }
    }

    int menu_choice;
    do {
        cout << "\n--- Main Menu ---\n";
        cout << "1. View Other User's Profile\n";
        cout << "2. View & Edit My Profile\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> menu_choice;

        switch (menu_choice) {
            case 1: {
                string search_user_id;
                cout << "Enter user ID to search: ";
                cin >> search_user_id;
                other_users::getAccountInfo(search_user_id, current_user_id);
                break;
            }
            case 2: {
                vector<string> followers, following;
                int posts_count = 0;
                CurrentUser current_user(current_user_id, followers, following, posts_count);
                current_user.displayInfo();
                current_user.editProfile();
                break;
            }
            case 3:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid option.\n";
        }
    } while (menu_choice != 3);

    return 0;
}
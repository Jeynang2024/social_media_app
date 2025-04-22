// include/CurrentUser.h
#ifndef CURRENT_USER_H
#define CURRENT_USER_H

#include "User.h"
using namespace std;


class CurrentUser : public User {
public:
    CurrentUser(string uid, vector<string> followers, 
                vector<string> following, int posts);
    void displayInfo() const override;
    void editProfile() override;
    void update(string user_id, int add);
};

#endif
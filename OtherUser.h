// include/OtherUser.h
#ifndef OTHER_USER_H
#define OTHER_USER_H

#include "User.h"
using namespace std;


class OtherUser : public User {
public:
    OtherUser(string uid, vector<string> followers, 
              vector<string> following, int posts);
    void displayInfo() const override;
};

namespace other_users {
    void getAccountInfo(string search_user_id, string current_user_id);
}

#endif
// include/User.h
#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
using namespace std;

class User {
protected:
    string user_id;
    vector<string> followers_list;
    vector<string> following_list;
    int posts_count;

public:
    User(string uid, vector<string> followers, 
         vector<string> following, int posts);
    
    virtual ~User() = default;
    virtual void displayInfo() const = 0;
    virtual void editProfile() {}

    string getId() const;
    vector<string>& getFollowers();
    vector<string>& getFollowing();
    int getPostCount() const;
    void setPostCount(int count);
};

#endif
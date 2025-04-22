// src/User.cpp
#include "User.h"
using namespace std;
User::User(string uid, vector<string> followers, 
           vector<std::string> following, int posts)
    : user_id(uid), followers_list(followers), 
      following_list(following), posts_count(posts) {}

string User::getId() const { return user_id; }
vector<string>& User::getFollowers() { return followers_list; }
vector<string>& User::getFollowing() { return following_list; }
int User::getPostCount() const { return posts_count; }
void User::setPostCount(int count) { posts_count = count; }
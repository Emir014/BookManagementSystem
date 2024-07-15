#ifndef USER_H
#define USER_H

#include <hasher.h>
#include <iostream>
#include <json.hpp>

using namespace std;
using json = nlohmann::json;

class User{
private:
    string username;
    string passwordHash;
    Hasher hash;

public:
    User(const string& username, const string& password, bool isHashed = false);

    void setPassword(const string password, bool isHashed = false);

    bool isStrong(const string& password);

    const string& getUserName() const;
    const string& getPasswordHash() const;
    const Hasher& getHash() const;

    json toJson() const;
};
#endif
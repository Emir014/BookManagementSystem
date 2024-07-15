#include <user.h>
#include <iostream>

using namespace std;

// Constructor
User::User(const string& username, const string& password, bool isHashed)
: username(username) {
  setPassword(password, isHashed);
}

void User::setPassword(const string password, bool isHashed) {
  if(isHashed) {
    passwordHash = password;
  } else {
  passwordHash = hash.customHash(password);
  }
}

bool User::isStrong(const string& password) {
  return password.size() >= 8;
}

const string& User::getUserName() const {
  return username;
}
const string& User::getPasswordHash() const {
  return passwordHash;
}
const Hasher& User::getHash() const {
  return hash;
}

json User::toJson() const{
  return json{{"username", username},
  {"password_hash", passwordHash}};
}
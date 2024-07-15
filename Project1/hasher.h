#ifndef HASHER_H
#define HASHER_H

#include <iostream>

using namespace std;

class Hasher{
private:
    int shifts[16];
    int shiftSize;

    int getToPrintableRange(int ascii);
public:
    Hasher();

    // Custom Hash function
    string customHash(const string& password) const;

    string reverseHash(string& hashedPassword);
};
#endif
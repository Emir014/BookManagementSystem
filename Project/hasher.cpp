#include <hasher.h>
#include <iostream>

using namespace std;

// Constructor
Hasher::Hasher() : shifts{23, 56, 67, 59, 93, 109, 14, 3, 34, 54, 83, 92, 20, 55, 28, 45} {
  shiftSize = sizeof(shifts) / sizeof(shifts[0]);
}

// Private method to get to printable characters' ascii range
int Hasher::getToPrintableRange(int ascii) {
  if(ascii < 32) {
while(ascii < 32) {
  ascii += 96;
}
  }
  else if(ascii > 127) {
while(ascii > 127) {
  ascii -= 96;
}
  }
  return ascii;
}

// Custom Hash function
string Hasher::customHash(const string& password) const {
  string hashedPassword = password;
  for(int i = 0; i < password.size(); i++) {
int ascii = static_cast<int>(password[i]);
ascii = (ascii + shifts[i % shiftSize]) % 96 + 32; // Printable character range[32, 127]
hashedPassword[i] = static_cast<char>(ascii);
  }
  return hashedPassword;
}

// Reverses the hash (Used for debugging)
string Hasher::reverseHash(string& hashedPassword) {
  string password = hashedPassword;
  for(int i = 0; i < hashedPassword.size(); i++) {
int ascii = static_cast<int>(hashedPassword[i]);
ascii = getToPrintableRange(ascii - 32 - shifts[i % shiftSize]);
password[i] = static_cast<char>(ascii);
  }
  return password;
}
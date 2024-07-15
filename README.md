# BookManagementSystem

## Overview
This program acts as a library system where users can create accounts, add books, delete books from the library, borrow or return books, and search by genre or author.

## Features
- **User Authentication**: Users can create accounts and log in. Passwords are hashed using a custom hash function for practice purposes (note: the hashing method is not secure and should not be used in production).
- **Book Management**: Add, remove, borrow, and return books.
- **Search Functionality**: Search for books by genre or author.
- **Data Persistence**: User data is stored in and read from a JSON file using the `json.hpp` library.

## Dependencies
- [nlohmann/json](https://github.com/nlohmann/json/blob/develop/single_include/nlohmann/json.hpp)

## Setup and Compilation
1. **Clone the Repository**:
    ```sh
    git clone <repository-url>
    cd <repository-directory>
    ```
    
2. **Compile the Program**:
    Open a terminal in the project directory and run the following command, specifying all the `.cpp` files and the path to the `json.hpp` file:
    g++ -o BookManagementSystem main.cpp user.cpp book.cpp library.cpp hasher.cpp -I path/to/json.hpp -I path/to/headerFiles

## File Structure
- `main.cpp`: The main entry point for the program.
- `hasher.cpp` / `hasher.h`: Implementation of the hash function to store password.
- `user.cpp` / `user.h`: Implementation of user authentication and management.
- `book.cpp` / `book.h`: Implementation of book management functions.
- `library.cpp` / `library.h`: Library system functionalities combining users and books.
- `json.hpp`: JSON library header file for data persistence.

## Notes
- The password hashing implemented is for practice purposes and is not secure. For production systems, use a standard and secure hashing library.
- Ensure the paths to your `.cpp` files and the `json.hpp` file are correctly specified during compilation.

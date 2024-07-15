#ifndef LIBRARY_H
#define LIBRARY_H

#include <book.h>
#include <user.h>
#include <fstream>
#include <iostream>

using namespace std;
using json = nlohmann::json;

class Library{
private:
    vector<Book> books;
    vector<User> users;
    vector<Book> defaultBooks;
public:
    // Constructor
    Library();
    // Number of books
    int size() const;

    void addBook(Book& book);
    void removeBook(Book& book);

    void setBooks(vector<Book>& books);
    vector<Book>& getBooks();

    void setUsers(vector<User>& users);
    vector<User>& getUsers();

    void addUser(User& user);

    // Search book by its title
    Book* searchBook(const string& title);

    // Search user by username
    User* searchUser(const string& username);

    //Get the index of a book object
    int getIndex(Book book);

    void addDefaultBooks();
    void clear();

    void viewAvailableBooks() const;
    void viewBorrowedBooks() const;

    bool borrowBook(const string& title);
    bool returnBook(const string& title);

    void searchByAuthor(const string& author);
    void searchByGenre(const string& genre);
    Book* searchByPages(const int& pages);
    Book* searchByYear(const int& pages);

    // Read books from JSON file
    vector<Book> readBooks(const string& path);
    // Write books to JSON file
    void writeBooks(const string& path);

    // Read users from JSON file
    vector<User> readUsers(const string& path);
    // Write users to JSON file
    void writeUsers(const string& path);

    // Used for sorting by year or pages
    void mergeSort(int arr[], int size);
};
#endif
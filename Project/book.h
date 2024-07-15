#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <json.hpp>
using namespace std;
using json = nlohmann::json;

class Book {
private:
    string title;
    string author;
    string status;
    string genre;
    int year;
    int pages;
public:
    // Constructors
    Book(const string &title, const string &author, const int &year, const int &pages, const string &genre);

    Book(const string &title, const string &author, const int &year, const int &pages, const string &genre,
         const string &status);

    Book();

    // Destructor
    ~Book();

    // Getters
    string getTitle() const;

    string getAuthor() const;

    string getStatus() const;

    string getGenre() const;

    int getYear() const;

    int getPages() const;

    // Setters
    void setTitle(const string &title);

    void setAuthor(const string &author);

    void setStatus(const string &status);

    void setYear(int year);

    void setPages(int pages);

    // Change status
    void borrowBook();

    void returnBook();

    // Overload the equality operator
    bool operator==(const Book &other) const;

    // Display the book
    void display() const;
    string toString() const;

    // JSON Serialization
    json toJson() const;
    static Book fromJson(const json &j);
};

#endif
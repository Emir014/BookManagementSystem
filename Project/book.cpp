#include <book.h>
#include <iostream>

using namespace std;

// Constructor
Book::Book(const string& title,const string& author,const int& year,const int& pages,const string& genre) :
    title(title), author(author), year(year), pages(pages), genre(genre), status("Available") {}

Book::Book(const string& title, const string& author, const int& year, const int& pages, const string& genre, const string& status) :
    title(title), author(author), year(year), pages(pages), genre(genre), status(status) {}

// Default Constructor
Book::Book() : title(""), author(""), year(0), pages(0), genre(""), status("Available") {}

// Destructor
Book::~Book() {}

// Getters
string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
string Book::getStatus() const { return status; }
string Book::getGenre() const { return genre; }
int Book::getYear() const { return year; }
int Book::getPages() const { return pages; }

// Setters
void Book::setTitle(const string &title) { this->title = title; }
void Book::setAuthor(const string &author) { this->author = author; }
void Book::setStatus(const string &status) { this->status = status; }
void Book::setYear(int year) { this->year = year; }
void Book::setPages(int pages) { this->pages = pages; }

// Change status
void Book::borrowBook() { status = "Borrowed"; }
void Book::returnBook() { status = "Available"; }

// Overload the equality operator
bool Book::operator==(const Book &other) const {
  return title == other.title && author == other.author &&
         year == other.year && pages == other.pages && genre == other.genre;
}

// Display the book
void Book::display() const {
  cout << "title: " << title << ", author: " << author << ", genre: " << genre << ", publish year: " << year;
  cout << ", pages: " << pages << ", status: " << status << endl;
}

string Book::toString() const {
  return title + "\n" + author + "\n" + genre + "\n" + to_string(year) +
         "\n" + to_string(pages) + "\n" + status + "\n\n";
}

// JSON Serialization
json Book::toJson() const {
  return json{
             {"title", title},
             {"author", author},
             {"genre", genre},
             {"year", year},
             {"pages", pages},
             {"status", status}
  };
}
Book Book::fromJson(const json& j) {
  return Book(j["title"], j["author"], j["year"], j["pages"], j["genre"], j["status"]);
}

#include <library.h>

// Constructor
Library::Library() {
  books = readBooks("Books.json");
  users = readUsers("Users.json");
  defaultBooks = vector<Book> {
          Book("1984", "George Orwell", 1949, 328, "Dystopian"),
          Book("To Kill a Mockingbird", "Harper Lee", 1960, 281, "Southern Gothic"),
          Book("Anna Karenina", "Leo Tolstoy", 1877, 864, "Realist Novel"),
          Book("Crime and Punishment", "Fyodor Dostoevsky", 1866, 671, "Psychological Fiction"),
          Book("Les Miserables", "Victor Hugo", 1862, 1463, "Historical Fiction"),
  };
}
// Number of books
int Library::size() const {
  return books.size();
}

void Library::addBook(Book& book) {
  books.emplace_back(book);
}
void Library::removeBook(Book& book) {
  int idx = getIndex(book);
  if(idx != -1) {
    books.erase(books.begin() + idx);
  }
}

void Library::setBooks(vector<Book>& books) { this->books = books; }
vector<Book>& Library::getBooks() { return books; }

void Library::setUsers(vector<User>& users) { this->users = users; }
vector<User>& Library::getUsers() { return users; }

void Library::addUser(User& user) {
  users.emplace_back(user);
}

void Library::clear() {
  books.clear();
}

// Search book by its title
Book* Library::searchBook(const string& title) {
  for(Book& book: books) {
    if(book.getTitle() == title) {
      return &book;
    }
  }
  return nullptr;
}

// Search user by username
User* Library::searchUser(const string& username) {
  for(User& user: users) {
    if(user.getUserName() == username) {
      return &user;
    }
  }
  return nullptr;
}

//Get the index of a book object
int Library::getIndex(Book book) {
  for(int i = 0; i < size(); i++) {
    if(books[i] == book) {
      return i;
    }
  }
  return -1;
}

void Library::viewAvailableBooks() const {
  cout << "Available Books: \n";
  for(const Book& book: books) {
    if(book.getStatus() == "Available") {
      book.display();
    }
  }
  cout << endl;
};
void Library::viewBorrowedBooks() const {
  cout << "Borrowed books: \n";
  for(const Book& book: books) {
    if(book.getStatus() == "Borrowed") {
      book.display();
    }
  }
  cout << endl;
}

bool Library::borrowBook(const string& title) {
  Book* searchedBook = searchBook(title);
  if(!searchedBook) {
    cout << "No books found with title " << title << " !\n";
    return false;
  }
  if(searchedBook->getStatus() == "Available") {
    cout << "You borrowed the book " << title << " .\n";
    searchedBook->borrowBook();
    return true;
  }
  else if(searchedBook->getStatus() == "Borrowed") {
    cout << "Book " << title << " is not available for borrowing";
    return false;
  }
  return false;
}

bool Library::returnBook(const string& title) {
  Book* searchedBook = searchBook(title);
  if(!searchedBook) {
    cout << "No books found with title " << title << " !\n";
    return false;
  }
  if(searchedBook->getStatus() == "Borrowed") {
    cout << "You returned the book " << title << " .\n";
    searchedBook->returnBook();
    return true;
  }
  else if(searchedBook->getStatus() == "Available") {
    return false;
  }
  return false;
}

void Library::addDefaultBooks() {
  for(Book& book: defaultBooks) {
    if(!searchBook(book.getTitle()))
    addBook(book);
  }
}

void Library::searchByAuthor(const string& author) {
  cout << "Books by " << author << ":\n";
  for(const Book& book : books) {
    if(book.getAuthor() == author) {
      book.display();
    }
  }
}

void Library::searchByGenre(const string& genre) {
  cout << "Books in genre " << genre << ":\n";
  for(const Book& book : books) {
    if(book.getGenre() == genre) {
      book.display();
    }
  }
}

Book* Library::searchByPages(const int& pages) {
  for(Book& book : books) {
    if(book.getPages() == pages) {
      return &book;
    }
  }
  return nullptr;
}

Book* Library::searchByYear(const int& year) {
  for(Book& book : books) {
    if(book.getYear() == year) {
      return &book;
    }
  }
  return nullptr;
}

// Read books from JSON file
vector<Book> Library::readBooks(const string& path) {
  vector<Book> books;
  ifstream file(path);

  if(file.is_open()) {
    try {
      json j;
      file >> j;
      for (const auto &j_book: j) {
        books.emplace_back(Book::fromJson(j_book));
      }
    } catch (const json::parse_error& e) {
      cerr << "JSON parse error: " << e.what() << endl;
    } catch(const std::exception& e) {
      cerr << "Error: " << e.what() << endl;
    }
    file.close();
  } else {
    cerr << "Unable to open file at path: " << path << endl;
  }
  return books;
}

// Write books to JSON file
void Library::writeBooks(const string& path) {
  json j_books = json::array();
  for(const auto& book : books) {
    j_books.push_back(book.toJson());
  }
  ofstream file(path);

  if(file.is_open()) {
    try {
      file << j_books.dump(2);
    } catch (const std::exception& e) {
      cerr << "Error writing to file: " << e.what() << endl;
    }
    file.close();
  } else {
    cerr << "Unable to open file at path: " << path << endl;
  }
}

// Read users from JSON file
vector<User> Library::readUsers(const string& path) {
  vector<User> users;
  ifstream file(path);

  if(file.is_open()) {
    try {
      if (file.peek() == ifstream::traits_type::eof()) { // if file is empty
        cout << "The file at path: " << path << " is empty.\n";
        return users;
      }
      json j;
      file >> j;
      for(auto& user_json: j) {
        users.emplace_back(User(user_json["username"], user_json["password_hash"], true));
      }
    } catch (const json::parse_error& e) {
      cerr << "JSON parse error: " << e.what() << endl;
    } catch(const std::exception& e) {
      cerr << "Error: " << e.what() << endl;
    }
    file.close();
  } else {
    cerr << "Unable to open file at path: " << path << endl;
  }
  return users;
}

// Write users to JSON file
void Library::writeUsers(const string& path) {
  json j_users = json::array();
  for(const auto& user : users) {
    j_users.push_back(user.toJson());
  }
  ofstream file(path);

  if(file.is_open()) {
    try {
      file << j_users.dump(2); // Indent with 2 spaces for readability
    } catch (const std::exception& e) {
      cerr << "Error writing to file: " << e.what() << endl;
    }
    file.close();
  } else {
    cerr << "Unable to open file at path: " << path << endl;
  }
}

// Used for sorting by year or pages
void Library::mergeSort(int arr[], int size) {
  if (size == 1) {
    return;
  }
  int mid = size / 2;
  int leftHalf[mid];
  int rightHalf[size-mid];

  for(int i = 0; i < mid; i++) {
    leftHalf[i] = arr[i];
  }
  for(int i = 0; i < size-mid; i++) {
    rightHalf[i] = arr[mid+i];
  }

  mergeSort(leftHalf, mid);
  mergeSort(rightHalf, size-mid);

  int i = 0;
  int j = 0;
  int k = 0;

  while(i < mid && j < size-mid) {
    if(leftHalf[i] <= rightHalf[j]) {
      arr[k] = leftHalf[i];
      i++;
    }
    else {
      arr[k] = rightHalf[j];
      j++;
    }
    k++;
  }
  while(i < mid) {
    arr[k] = leftHalf[i];
    i++;
    k++;
  }
  while(j < size-mid) {
    arr[k] = rightHalf[j];
    j++;
    k++;
  }
}
#include <library.h>
#include <iostream>

using namespace std;


int getInt() {
    int value;
    while (true) {
        cin >> value;

        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter an integer.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
    return value;
}

void menu(Library& library);

void login(Library& library) {
  string options = "1. Login\n"
                   "2. Register\n"
                   "3. Exit";
  int option = 0;

  while(option != 3) {
    cout << options << endl;
    option = getInt();

    switch(option) {
      case 1: {
        string username, password;
        cout << "Enter your username: ";
        getline(cin, username);
        User* user = library.searchUser(username);
        if(user) {
          cout << "Enter your password: ";
          getline(cin, password);
	  if(user->getPasswordHash() == user->getHash().customHash(password)) {
            cout << "Login successful!\n";
            menu(library);
            return; // Program terminates if user exits the menu function
          } else {
            cout << "Invalid password. Please try again.\n";
          }
        } else {
          cout << "User not found. Please register.\n";
        }
        break;
      }
      case 2: {
        string username, password, password1;
        cout << "Enter a new username: ";
        getline(cin, username);
        cout << "Enter a password with at least 8 characters: ";
        getline(cin, password);
        cout << "Enter your password again: ";
        getline(cin, password1);
        if(password1 != password) {
          cout << "Passwords do not match. Please try again.\n";
        } else if(password.size() >= 8) {
          User newUser(username, password);
          library.addUser(newUser);
          library.writeUsers("Users.json");
          cout << "Registration successful. You can  now login.\n";
        } else {
          cout << "Password must be at least 8 characters long. Please try again.\n";
        }
        break;
      }
      case 3: {
        cout << "Exiting the login menu.\n";
        return;  // Exit the function to stop the loop
      }
      default: {
        cout << "Invalid option. Please try again.\n";
        break;
      }
    }
  }
}

void menu(Library& library) {
  string options = "1. Add default books to the library\n"
                   "2. Add book\n"
                   "3. Remove book\n"
                   "4. View available books\n"
                   "5. View borrowed books\n"
                   "6. Borrow book\n"
                   "7. Return book\n"
                   "8. Search by author\n"
                   "9. Search by genre\n"
                   "10. Exit";
  int option = 0;

  while(option != 10) {
    cout << options << endl;
    option = getInt();

    switch (option) {
      case 1: {
        library.addDefaultBooks();
        cout << "Added default books to the library\n";
        break;
      }
      case 2: {
        string title, author, genre;
        int year, pages;
        cout << "You are adding a new book to the library.\nEnter the title of the book: ";
        getline(cin, title);
        cout << "Enter the author of the book: ";
        getline(cin, author);
        cout << "Enter the year the publication of the book: ";
        year = getInt();
        cout << "Enter the page count of the book: ";
        pages = getInt();
        cout << "Enter the genre of the book: ";
        getline(cin, genre);
        Book newBook = Book(title, author, year, pages, genre);
        library.addBook(newBook);
        break;
      }
      case 3: {
        string title;
        cout << "Enter the title of the book to be removed: ";
        getline(cin, title);
        Book *book = library.searchBook(title);
        if (book) {
          library.removeBook(*book);
        } else {
          cout << "Book " << title << " not found!\n";
        }
        break;
      }
      case 4: {
        library.viewAvailableBooks();
        break;
      }
      case 5: {
        library.viewBorrowedBooks();
        break;
      }
      case 6: {
        string title;
        cout << "Enter the title of the book to borrow: ";
        getline(cin, title);
        bool status = library.borrowBook(title);
        if (!status) {
          cout << "The book " << title << " is already borrowed or not available!\n";
        }
        break;
      }
      case 7: {
        string title;
        cout << "Enter the title of the book to return: ";
        getline(cin, title);
        bool status = library.returnBook(title);
        if(!status) {
          cout << "The book " << title << " is already in the library!\n";
        }
        break;
      }
      case 8: {
        string author;
        cout << "Enter the name of the author to be searched for: ";
        getline(cin, author);
        library.searchByAuthor(author);
        break;
      }
      case 9: {
        string genre;
        cout << "Enter a genre to be searched for: ";
        getline(cin, genre);
        library.searchByGenre(genre);
        break;
      }
      case 10: {
        cout << "Exiting the program. Goodbye!\n";
        library.writeBooks("Books.json");
        library.writeUsers("Users.json");
        break;
      }
      default: {
        cout << "Invalid option. Please try again.\n";
        break;
      }
    }
  }
}

int main() {
  Library library;
  login(library);
  return 0;
}

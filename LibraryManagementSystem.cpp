#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Class to represent a Book
class Book {
private:
    int id;
    string title;
    string author;
    bool isIssued;

public:
    Book(int id = 0, string t = "", string a = "", bool issued = false) {
        this->id = id;
        title = t;
        author = a;
        isIssued = issued;
    }

    // Getters
    int getId() const { return id; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool getIsIssued() const { return isIssued; }

    // Setters
    void setIssued(bool status) { isIssued = status; }

    // Display book details
    void display() const {
        cout << "ID: " << id << "\nTitle: " << title << "\nAuthor: " << author
             << "\nStatus: " << (isIssued ? "Issued" : "Available") << "\n\n";
    }
};

// Class to manage the Library
class Library {
private:
    vector<Book> books;
    const string filename = "books.txt";

    // Load books from file
    void loadBooks() {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "No existing book records found.\n";
            return;
        }

        int id;
        string title, author;
        bool issued;
        string line;

        while (file >> id) {
            file.ignore(); // Ignore newline after id
            getline(file, title);
            getline(file, author);
            file >> issued;
            file.ignore(); // Ignore newline after issued
            books.push_back(Book(id, title, author, issued));
        }
        file.close();
    }

    // Save books to file
    void saveBooks() {
        ofstream file(filename);
        for (const auto& book : books) {
            file << book.getId() << "\n"
                 << book.getTitle() << "\n"
                 << book.getAuthor() << "\n"
                 << book.getIsIssued() << "\n";
        }
        file.close();
    }

public:
    Library() {
        loadBooks(); // Load books when library object is created
    }

    // Add a new book
    void addBook() {
        int id;
        string title, author;
        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore(); // Clear input buffer
        cout << "Enter Book Title: ";
        getline(cin, title);
        cout << "Enter Book Author: ";
        getline(cin, author);

        // Check if ID already exists
        for (const auto& book : books) {
            if (book.getId() == id) {
                cout << "Book ID already exists!\n";
                return;
            }
        }

        books.push_back(Book(id, title, author, false));
        saveBooks();
        cout << "Book added successfully!\n";
    }

    // Display all books
    void displayBooks() {
        if (books.empty()) {
            cout << "No books in the library.\n";
            return;
        }
        for (const auto& book : books) {
            book.display();
        }
    }

    // Search book by ID
    void searchBook() {
        int id;
        cout << "Enter Book ID to search: ";
        cin >> id;

        for (const auto& book : books) {
            if (book.getId() == id) {
                book.display();
                return;
            }
        }
        cout << "Book not found!\n";
    }

    // Delete a book by ID
    void deleteBook() {
        int id;
        cout << "Enter Book ID to delete: ";
        cin >> id;

        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->getId() == id) {
                books.erase(it);
                saveBooks();
                cout << "Book deleted successfully!\n";
                return;
            }
        }
        cout << "Book not found!\n";
    }

    // Issue a book
    void issueBook() {
        int id;
        cout << "Enter Book ID to issue: ";
        cin >> id;

        for (auto& book : books) {
            if (book.getId() == id) {
                if (book.getIsIssued()) {
                    cout << "Book is already issued!\n";
                } else {
                    book.setIssued(true);
                    saveBooks();
                    cout << "Book issued successfully!\n";
                }
                return;
            }
        }
        cout << "Book not found!\n";
    }

    // Return a book
    void returnBook() {
        int id;
        cout << "Enter Book ID to return: ";
        cin >> id;

        for (auto& book : books) {
            if (book.getId() == id) {
                if (!book.getIsIssued()) {
                    cout << "Book is not issued!\n";
                } else {
                    book.setIssued(false);
                    saveBooks();
                    cout << "Book returned successfully!\n";
                }
                return;
            }
        }
        cout << "Book not found!\n";
    }
};

// Main function to run the program
int main() {
    Library lib;
    int choice;

    while (true) {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Book\n";
        cout << "4. Delete Book\n";
        cout << "5. Issue Book\n";
        cout << "6. Return Book\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: lib.addBook(); break;
            case 2: lib.displayBooks(); break;
            case 3: lib.searchBook(); break;
            case 4: lib.deleteBook(); break;
            case 5: lib.issueBook(); break;
            case 6: lib.returnBook(); break;
            case 7: cout << "Exiting...\n"; return 0;
            default: cout << "Invalid choice!\n";
        }
    }
    return 0;
}
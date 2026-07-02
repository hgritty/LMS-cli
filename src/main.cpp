#include "library.h"
#include <iostream>

using namespace std;

int main() {
    Library library;

    cout << "========================================\n";
    cout << "     Library Management System\n";
    cout << "========================================\n";

    int choice;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add a book\n";
        cout << "2. List all books\n";
        cout << "3. Borrow a book\n";
        cout << "4. Return a book\n";
        cout << "5. Delete a book\n";
        cout << "6. Exit\n";
        cout << "Enter your choice (1-6): ";

        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string title, author;
            cout << "Enter book title: ";
            getline(cin, title);
            cout << "Enter book author: ";
            getline(cin, author);
            library.addBook(title, author);

        } else if (choice == 2) {
            library.listBooks();

        } else if (choice == 3) {
            int id;
            cout << "Enter book ID to borrow: ";
            cin >> id;
            cin.ignore();
            library.borrowBook(id);

        } else if (choice == 4) {
            int id;
            cout << "Enter book ID to return: ";
            cin >> id;
            cin.ignore();
            library.returnBook(id);

        } else if (choice == 5) {
            int id;
            cout << "Enter book ID to delete: ";
            cin >> id;
            cin.ignore();
            library.deleteBook(id);

        } else if (choice == 6) {
            cout << "Goodbye!\n";
            break;

        } else {
            cout << "Invalid input! Please enter 1-6.\n";
        }
    }

    return 0;
}
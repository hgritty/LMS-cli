#include "book.h"
#include <iostream>

using namespace std;

int main() {
    loadData();
    cout << "========================================" << endl;
    cout << "     Library Management System v3.1.1" << endl;
    cout << "========================================" << endl;

    int choice;

    while(true) {
        cout << "\nMenu:" << endl;
        cout << "1. Add a book" << endl;
        cout << "2. List all books" << endl;
        cout << "3. Borrow a book" << endl;
        cout << "4. Return a book" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice(1-5): ";

        cin >> choice;

        if (choice == 1) {
            addBook();
        } else if (choice == 2) {
            listBooks();
        } else if (choice == 3) {
            borrowBook();
        } else if (choice == 4) {
            returnBook();
        } else if (choice == 5) {
            saveData();
            cout << "Goodbye!" << endl;
            break;
        } else {
            cout << "Invalid input! Please enter 1-5." << endl;
        }
    }

    return 0;
}
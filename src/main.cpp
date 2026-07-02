#include "library.h"
#include <iostream>

using namespace std;

int main() {
    Library library;
    string filename = "../books.txt";

    // 加载数据
    library.loadFromFile(filename);

    cout << "========================================" << endl;
    cout << "     Library Management System    " << endl;
    cout << "========================================" << endl;

    int choice;

    while(true) {
        cout << endl << "Menu:" << endl;
        cout << "1. Add a book" << endl;
        cout << "2. List all books" << endl;
        cout << "3. Borrow a book" << endl;
        cout << "4. Return a book" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice(1-5): ";
        
        //只读取数字1，会把\n留在缓冲区里，所以下面需要先ignore
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
            library.saveToFile(filename);
            cout << "Goodbye!" << endl;
            break;

        } else {
            cout << "Invalid input! Please enter 1-5." << endl;
        }
    }

    return 0;
}
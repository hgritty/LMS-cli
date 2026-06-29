// Library Management System
// Author : hgritty
// Date : 2026-6-29

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Book {
    int id;
    string title;
    string author;
    bool borrowed;
};


vector<Book> books;   // 存放所有书的容器
int nextId = 1;       // 下一本书的编号

void addBook();
void borrowBook();
void returnBook();
void listBooks();
void saveData();
void loadData();

int main() {
    cout << "========================================" << endl;
    cout << "     Library Management System" << endl;
    cout << "========================================" << endl;

    int choice;

    while(true) {
        cout << "\nMenu:" << endl;
        cout << " 1. Add a book" << endl;
        cout << " 2. List all books" << endl;
        cout << " 3. Borrow a book" << endl;
        cout << " 4. Return a book" << endl;
        cout << " 5. Exit" << endl;
        cout << " Enter your choice(1-5)";

        cin >> choice;

        if (choice == 1) {
            // 调用 addBook()
        } else if (choice == 2) {
            // 调用 listBooks()
        } else if (choice == 3) {
            // 调用 borrowBook()
        } else if (choice == 4) {
            // 调用 returnBook()
        } else if (choice == 5) {
            cout << "Goodbye!" << endl;
            break;
        } else {
            cout << "Invalid input! Please enter 1-5." << endl;
        }
    }

    return 0;
}


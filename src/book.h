#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>

using namespace std;

struct Book {
    int id;
    string title;
    string author;
    bool borrowed;
};

// 声明全局变量（extern 表示"定义在其他文件"）
extern vector<Book> books;
extern int nextId;

// 声明所有函数
void addBook();
void borrowBook();
void returnBook();
void listBooks();
void saveData();
void loadData();

#endif
#include "library.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

// 构造函数：初始化 nextId 为 1
Library::Library() : nextId(1) {

}

// 添加图书
void Library::addBook(const string& title, const string& author) {
     // 1. 创建新书对象
    Book newBook;
    newBook.id = nextId;
    nextId = nextId + 1;
    newBook.title = title;
    newBook.author = author;
    newBook.borrowed = false;
    
    // 2. 存入书架
    books.push_back(newBook);
    
    // 3. 提示用户（cout 在 main 里做，这里只返回信息）
    cout << "Book added successfully! ID: " << newBook.id << endl;
}

// 列出所有图书
void Library::listBooks() const {
    if (books.empty()) {
        cout << "Sorry, there is no book here." << endl;
    } else {
        // 设置对齐方式
        cout << left;  // 左对齐
        
        // 表头
        cout << "+----+---------------------+---------------------+----------+" << endl;
        cout << "| ID | Title               | Author              | Status   |" << endl;
        cout << "+----+---------------------+---------------------+----------+" << endl;
        
        // 数据行
        for (const Book& b : books) {
            string status = b.borrowed ? "Borrowed" : "Available";
            
            cout << "| ";
            cout << setw(2) << b.id << " | ";
            cout << setw(19) << b.title << " | ";
            cout << setw(19) << b.author << " | ";
            cout << setw(8) << status << " |" << endl;
        }
        
        cout << "+----+---------------------+---------------------+----------+" << endl;
    }
}

// 借阅图书
bool Library::borrowBook(int id) {
    // 边界检查
    if (id < 1 || id >= nextId) {
        cout << "Out of Index!" << endl;
        return false;
    }

    // 遍历查找
    for (Book& b : books) {
        if (b.id == id) {
            if (b.borrowed == false) {
                b.borrowed = true;
                cout << "Book borrowed successfully!" << endl;
                return true;
            } else {
                cout << "Book is already borrowed!" << endl;
                return false;
            }
        }
    }

    cout << "Book not found!" << endl;
    return false;
}

// 归还图书
bool Library::returnBook(int id) {
    //边界检查
    if (id < 1 || id >= nextId) {
        cout << "Out of Index!" << endl;
        return false;
    }

    //遍历查找
    for (Book& b : books) {
        if (b.id == id) {
            if (b.borrowed == true) {
                b.borrowed = false;
                cout << "Book returned successfully!" << endl;
                return true;
            } else {
                cout << "Book is already available (not borrowed)!" << endl;
                return false;
            }
        }
    }

    cout << "Book not found!" << endl;
    return false;
}

// 删除图书
bool Library::deleteBook(int id) {
    // 边界检查
    if (id < 1 || id >= nextId) {
        cout << "Out of Index!" << endl;
        return false;
    }

    // 遍历查找
    for (auto it = books.begin(); it != books.end(); ++it) {
        if (it->id == id) {
            // 检查是否已借出
            if (it->borrowed == true) {
                cout << "Cannot delete: book is currently borrowed!" << endl;
                return false;
            }
            
            books.erase(it);
            cout << "Book deleted successfully!" << endl;
            return true;
        }
    }

    cout << "Book not found!" << endl;
    return false;
}

// 保存数据到文件
bool Library::saveToFile(const string& filename) const {
    // 打开文件
    ofstream file(filename);
    if (!file) {
        cerr << "Error: Cannot open file for writing!" << endl;
        return false;
    }

    for (const Book& b : books) {
        string content = to_string(b.id) + "|" + b.title + "|" + b.author + "|" + to_string(b.borrowed);
        file << content << endl;
    }

    return true;
}

// 从文件加载数据
bool Library::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        // 文件不存在是正常情况（首次运行）
        return true;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, title, author, statusStr;

        getline(ss, idStr, '|');
        getline(ss, title, '|');
        getline(ss, author, '|');
        getline(ss, statusStr, '|');

        int id = stoi(idStr);
        bool borrowed = stoi(statusStr);

        Book b;
        b.id = id;
        b.title = title;
        b.author = author;
        b.borrowed = borrowed;
        books.push_back(b);

        if (id >= nextId) {
            nextId = id + 1;
        }
    }

    return true;
}

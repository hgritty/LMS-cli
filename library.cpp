// Library Management System
// Author : hgritty
// Date : 2026-6-30

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;

struct Book {
    int id;
    string title;
    string author;
    bool borrowed;
};


vector<Book> books;   // 存放所有书的容器
int nextId = 1;       // 下一本书的编号


void addBook() {
    // 1. 创建一个临时的 Book 对象，用来存放用户输入的数据
    Book newBook;
    
    // 2. 自动分配编号
    //    nextId 是全局变量，记录"下一本书应该用哪个编号"
    //    先把 nextId 赋给新书，然后 nextId 自增 1，为下一本书做准备
    newBook.id = nextId;
    nextId = nextId + 1;
    
    // 3. 提示用户输入书名
    cout << "Enter book title: ";
    // 4. 清除输入缓冲区里残留的换行符
    //    原因：在 main() 里用了 cin >> choice，用户按回车后，缓冲区里还留着 '\n'
    //    如果不清除，下面的 getline 会直接读到 '\n'，跳过书名输入
    cin.ignore();
    // 5. 读取用户输入的书名（允许包含空格，如 "The C++ Programming Language"）
    getline(cin, newBook.title);
    
    // 6. 提示用户输入作者
    cout << "Enter book author: ";
    // 7. 读取作者名（允许包含空格，如 "J. R. R. Tolkien"）
    //    注意：这里不需要再 cin.ignore()，因为上一步的 getline 已经把换行符吃掉了
    getline(cin, newBook.author);
    
    // 8. 新书默认状态：未被借出（在库）
    newBook.borrowed = false;
    
    // 9. 把这本书存入书架（books 容器）
    //    push_back 是 vector 的方法，把元素添加到末尾
    books.push_back(newBook);
    
    // 10. 提示用户添加成功，并显示自动分配的编号
    //     用户记住这个编号，后续借阅/归还时需要用到
    cout << "Book added successfully! ID: " << newBook.id << endl;
}

void borrowBook() {
    int id;
    cout << "Enter book ID to borrow: ";
    cin >> id;

    if (id < 1 || id >= nextId) {  // 检查是否在合理范围
        cout << "Out of Index!" << endl;
        return;
    }

    // 遍历查找
    for (Book& b : books) {
        if (b.id == id) {
            if (b.borrowed == false) {
                b.borrowed = true;
                cout << "Book borrowed successfully!" << endl;
            } else {
                cout << "Book is already borrowed!" << endl;
            }
            return;
        }
    }

    // 循环结束还没找到（可能编号不连续了,该号码的书已经被删除）
    cout << "Book not found!" << endl;
}

void returnBook() {
    int id;
    cout << "Enter book ID to return: ";
    cin >> id;

    // 快速边界检查（和 borrowBook 保持一致）
    if (id < 1 || id >= nextId) {
        cout << "Out of Index!" << endl;
        return;
    }

    // 遍历查找
    for (Book& b : books) {
        if (b.id == id) {
            if (b.borrowed == true) {
                b.borrowed = false;
                cout << "Book returned successfully!" << endl;
            } else {
                cout << "Book is already available (not borrowed)!" << endl;
            }
            return;
        }
    }

    // 循环结束还没找到
    cout << "Book not found!" << endl;
}

void listBooks() {
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

void saveData() {
    // 1. 打开文件（ofstream）
    ofstream file("books.txt");
    
    // 2. 遍历 books 容器，每本书写一行
    for (const Book& b : books) {
        // 把 int 转成 string，然后拼接
        string content = to_string(b.id) + "|" + b.title + "|" + b.author + "|" + to_string(b.borrowed);
        file << content << endl;
    }
    
    // 文件会在函数结束时自动关闭
}

void loadData() {
    ifstream file("books.txt");
    if (!file) return;  // 文件不存在就退出
    
    string line;
    while (getline(file, line)) {
        // 用 stringstream 分割字符串
        stringstream ss(line);
        string idStr, title, author, statusStr;
        
        getline(ss, idStr, '|');
        getline(ss, title, '|');
        getline(ss, author, '|');
        getline(ss, statusStr, '|');
        
        // 转换成对应类型
        int id = stoi(idStr);
        bool borrowed = stoi(statusStr);  // "0" → false, "1" → true
        
        // 创建 Book 对象并加入容器
        Book b;
        b.id = id;
        b.title = title;
        b.author = author;
        b.borrowed = borrowed;
        books.push_back(b);
        
        // 更新 nextId（保证编号不重复）
        if (id >= nextId) {
            nextId = id + 1;
        }
    }
}

int main() {
    loadData();
    cout << "========================================" << endl;
    cout << "     Library Management System v1.0" << endl;
    cout << "========================================" << endl;

    int choice;

    while(true) {
        cout << "\nMenu:" << endl;
        cout << "1. Add a book" << endl;
        cout << "2. List all books" << endl;
        cout << "3. Borrow a book" << endl;
        cout << "4. Return a book" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice(1-5)";

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
            saveData();  // 退出前保存数据
            cout << "Goodbye!" << endl;
            break;
        } else {
            cout << "Invalid input! Please enter 1-5." << endl;
        }
    }

    return 0;
}


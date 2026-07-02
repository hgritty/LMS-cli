#include "library.h"
#include <iostream>
#include <sqlite3.h>

using namespace std;

// 构造函数：打开数据库，初始化表
Library::Library() : db(nullptr), nextId(1) {
    // 打开数据库文件（如果不存在会自动创建）
    int rc = sqlite3_open("../library.db", &db);
    if (rc != SQLITE_OK) {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        return;
    }
    initializeDatabase();
}

// 析构函数：关闭数据库
Library::~Library() {
    if (db) {
        sqlite3_close(db);
    }
}

// 初始化数据库：创建表
bool Library::initializeDatabase() {
    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS books (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            title TEXT NOT NULL,
            author TEXT NOT NULL,
            borrowed INTEGER DEFAULT 0
        );
    )";

    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
        return false;
    }
    
    // 获取当前最大 id，用于 nextId
    sqlite3_stmt* stmt;
    const char* maxSql = "SELECT MAX(id) FROM books;";
    rc = sqlite3_prepare_v2(db, maxSql, -1, &stmt, nullptr);
    if (rc == SQLITE_OK && sqlite3_step(stmt) == SQLITE_ROW) {
        nextId = sqlite3_column_int(stmt, 0) + 1;
    }
    sqlite3_finalize(stmt);
    
    return true;
}

// 添加图书
void Library::addBook(const string& title, const string& author) {
    const char* sql = "INSERT INTO books (title, author, borrowed) VALUES (?, ?, 0);";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Prepare failed: " << sqlite3_errmsg(db) << endl;
        return;
    }
    
    sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, author.c_str(), -1, SQLITE_STATIC);
    
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_DONE) {
        int id = sqlite3_last_insert_rowid(db);
        cout << "Book added successfully! ID: " << id << endl;
        if (id >= nextId) nextId = id + 1;
    } else {
        cerr << "Insert failed: " << sqlite3_errmsg(db) << endl;
    }
    sqlite3_finalize(stmt);
}

// 列出所有图书
void Library::listBooks() const {
    const char* sql = "SELECT id, title, author, borrowed FROM books ORDER BY id;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Prepare failed: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // 表头
    // printf("+----+---------------------------+---------------------------+----------+\n");
    printf("| ID | Title                     | Author                    | Status     |\n");
    // printf("+----+---------------------------+---------------------------+----------+\n");

    bool hasData = false;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        hasData = true;
        int id = sqlite3_column_int(stmt, 0);
        const char* title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* author = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        int borrowed = sqlite3_column_int(stmt, 3);

        const char* status = borrowed ? "Borrowed" : "Available";
        
        // 用 printf 控制宽度（左对齐）
        printf("| %2d | %-25s | %-25s | %-10s |\n", id, title, author, status);
    }

    if (!hasData) {
        printf("| (empty)                                                 |\n");
    }
    // printf("+----+---------------------------+---------------------------+----------+\n");
    sqlite3_finalize(stmt);
}

// 借阅图书
bool Library::borrowBook(int id) {
    // 先检查是否存在及状态
    const char* checkSql = "SELECT borrowed FROM books WHERE id = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, checkSql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Prepare failed: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    sqlite3_bind_int(stmt, 1, id);
    
    if (sqlite3_step(stmt) != SQLITE_ROW) {
        cout << "Book not found!" << endl;
        sqlite3_finalize(stmt);
        return false;
    }
    
    int borrowed = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    
    if (borrowed) {
        cout << "Book is already borrowed!" << endl;
        return false;
    }
    
    // 更新状态
    const char* updateSql = "UPDATE books SET borrowed = 1 WHERE id = ?;";
    rc = sqlite3_prepare_v2(db, updateSql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Prepare failed: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    sqlite3_bind_int(stmt, 1, id);
    
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    if (rc == SQLITE_DONE) {
        cout << "Book borrowed successfully!" << endl;
        return true;
    }
    
    cout << "Borrow failed!" << endl;
    return false;
}

// 归还图书
bool Library::returnBook(int id) {
    const char* checkSql = "SELECT borrowed FROM books WHERE id = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, checkSql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Prepare failed: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    sqlite3_bind_int(stmt, 1, id);
    
    if (sqlite3_step(stmt) != SQLITE_ROW) {
        cout << "Book not found!" << endl;
        sqlite3_finalize(stmt);
        return false;
    }
    
    int borrowed = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    
    if (!borrowed) {
        cout << "Book is already available (not borrowed)!" << endl;
        return false;
    }
    
    const char* updateSql = "UPDATE books SET borrowed = 0 WHERE id = ?;";
    rc = sqlite3_prepare_v2(db, updateSql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Prepare failed: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    sqlite3_bind_int(stmt, 1, id);
    
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    if (rc == SQLITE_DONE) {
        cout << "Book returned successfully!" << endl;
        return true;
    }
    
    cout << "Return failed!" << endl;
    return false;
}

// 删除图书
bool Library::deleteBook(int id) {
    const char* checkSql = "SELECT borrowed FROM books WHERE id = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, checkSql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Prepare failed: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    sqlite3_bind_int(stmt, 1, id);
    
    if (sqlite3_step(stmt) != SQLITE_ROW) {
        cout << "Book not found!" << endl;
        sqlite3_finalize(stmt);
        return false;
    }
    
    int borrowed = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    
    if (borrowed) {
        cout << "Cannot delete: book is currently borrowed!" << endl;
        return false;
    }
    
    const char* deleteSql = "DELETE FROM books WHERE id = ?;";
    rc = sqlite3_prepare_v2(db, deleteSql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Prepare failed: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    sqlite3_bind_int(stmt, 1, id);
    
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    if (rc == SQLITE_DONE) {
        cout << "Book deleted successfully!" << endl;
        return true;
    }
    
    cout << "Delete failed!" << endl;
    return false;
}
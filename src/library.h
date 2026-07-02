#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <sqlite3.h>

class Library {
private:
    int nextId;
    sqlite3* db;

public:
    Library();
    ~Library();

    void addBook(const std::string& title, const std::string& author);
    void listBooks() const;
    bool borrowBook(int id);
    bool returnBook(int id);
    bool deleteBook(int id);

    bool initializeDatabase();
};

#endif
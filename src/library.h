#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include "book.h"

class Library {
private:
    std::vector<Book> books;
    int nextId;

public:
    Library();

    void addBook(const std::string& title, const std::string& author);
    void listBooks() const;
    bool borrowBook(int id);
    bool returnBook(int id);
    bool saveToFile(const std::string& filename)  const;
    bool loadFromFile(const std::string& filename);
    bool deleteBook(int id);
};

#endif
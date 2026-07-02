#include <gtest/gtest.h>
#include "../src/library.h"
#include <sqlite3.h>
#include <iostream>
#include <fstream>

// ============================================
// 测试辅助函数
// ============================================

// 删除测试数据库文件（保证每个测试独立）
void removeTestDatabase() {
    std::remove("../library.db");
}

// ============================================
// 测试 1：添加一本正常的书
// ============================================
TEST(LibraryTest, AddBook) {
    removeTestDatabase();  // 清理旧数据
    
    Library lib;
    lib.addBook("C++ Primer", "Lippman");
    
    // 直接测试：添加后应该有数据
    // 这里我们无法直接验证 listBooks，但可以通过 SQL 查询确认
    sqlite3* db;
    sqlite3_open("../library.db", &db);
    
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, "SELECT COUNT(*) FROM books;", -1, &stmt, nullptr);
    sqlite3_step(stmt);
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    
    EXPECT_EQ(count, 1);  // 应该有 1 本书
}

// ============================================
// 测试 2：借阅一本存在的书
// ============================================
TEST(LibraryTest, BorrowExistingBook) {
    removeTestDatabase();
    
    Library lib;
    lib.addBook("C++ Primer", "Lippman");
    
    bool result = lib.borrowBook(1);
    EXPECT_TRUE(result);  // 借阅成功，返回 true
    
    // 验证数据库状态
    sqlite3* db;
    sqlite3_open("../library.db", &db);
    
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, "SELECT borrowed FROM books WHERE id = 1;", -1, &stmt, nullptr);
    sqlite3_step(stmt);
    int borrowed = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    
    EXPECT_EQ(borrowed, 1);  // 状态变为 1（已借出）
}

// ============================================
// 测试 3：借阅一本不存在的书
// ============================================
TEST(LibraryTest, BorrowNonExistingBook) {
    removeTestDatabase();
    
    Library lib;
    
    bool result = lib.borrowBook(999);
    EXPECT_FALSE(result);  // 借阅失败，返回 false
}

// ============================================
// 测试 4：删除一本已借出的书（应该失败）
// ============================================
TEST(LibraryTest, DeleteBorrowedBook) {
    removeTestDatabase();
    
    Library lib;
    lib.addBook("C++ Primer", "Lippman");
    lib.borrowBook(1);
    
    bool result = lib.deleteBook(1);
    EXPECT_FALSE(result);  // 不能删除已借出的书，返回 false
}

// ============================================
// 测试 5：删除一本存在的书（应该成功）
// ============================================
TEST(LibraryTest, DeleteExistingBook) {
    removeTestDatabase();
    
    Library lib;
    lib.addBook("C++ Primer", "Lippman");
    
    bool result = lib.deleteBook(1);
    EXPECT_TRUE(result);  // 删除成功，返回 true
    
    // 验证数据库
    sqlite3* db;
    sqlite3_open("../library.db", &db);
    
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, "SELECT COUNT(*) FROM books;", -1, &stmt, nullptr);
    sqlite3_step(stmt);
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    
    EXPECT_EQ(count, 0);  // 应该没有书了
}

// ============================================
// 测试 6：归还一本已借出的书
// ============================================
TEST(LibraryTest, ReturnBorrowedBook) {
    removeTestDatabase();
    
    Library lib;
    lib.addBook("C++ Primer", "Lippman");
    lib.borrowBook(1);
    
    bool result = lib.returnBook(1);
    EXPECT_TRUE(result);  // 归还成功，返回 true
    
    // 验证数据库状态
    sqlite3* db;
    sqlite3_open("../library.db", &db);
    
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, "SELECT borrowed FROM books WHERE id = 1;", -1, &stmt, nullptr);
    sqlite3_step(stmt);
    int borrowed = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    
    EXPECT_EQ(borrowed, 0);  // 状态变为 0（在库）
}

// ============================================
// 主函数
// ============================================
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
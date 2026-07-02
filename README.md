# LMS-cli

**LMS-cli**（Library Management System in CLI）是一个基于 C++ 的命令行图书管理系统，提供图书的增删改查、借阅归还和数据持久化功能。

---

## ✨ 功能列表

### 已实现
- [x] 添加图书（自动分配编号）
- [x] 查看所有图书（表格对齐）
- [x] 借阅图书（按 ID 操作）
- [x] 归还图书（按 ID 操作）
- [x] 删除图书
- [x] 数据持久化（SQLite 数据库）

### 待开发
- [ ] 按书名搜索
- [ ] 按作者搜索
- [ ] 统计功能（总书数、已借数量）
- [ ] 修改图书信息
- [ ] 同一本书多副本支持

---

## 🛠️ 开发环境

| 工具 | 版本 |
|------|------|
| C++ 标准 | C++11 |
| 构建工具 | CMake 3.10+ |
| 编译器 | GCC / Clang |
| 数据库 | SQLite3 |
| 操作系统 | Ubuntu 24.04 / WSL2 |

---

## 📁 项目结构

```
LMS-cli/
├── src/
│   ├── library.h       # Library 类声明
│   ├── library.cpp     # Library 类实现（含 SQLite 操作）
│   └── main.cpp        # 程序入口（菜单 + main）
├── build/              # 编译产物（自动生成）
├── CMakeLists.txt      # CMake 构建配置
├── README.md
├── library.db          # 书籍信息的数据库
├── LICENSE
└── .gitignore
```

---

## 🔧 编译与运行


### 方式一：使用 CMake（推荐）

```bash
# 1. 进入项目目录
cd ~/code/LMS-cli

# 2. 创建构建目录并编译
mkdir build && cd build
cmake ..
make

# 3. 运行
./lms
```

### 方式二：直接编译

```bash
g++ -std=c++11 src/library.cpp src/main.cpp -o lms -lsqlite3
./lms
```

---

## 📖 使用说明

运行程序后，通过菜单选择操作：

```
Menu:
1. Add a book      # 添加图书
2. List all books  # 查看所有图书
3. Borrow a book   # 借阅图书（输入 ID）
4. Return a book   # 归还图书（输入 ID）
5. Delete a book   # 删除图书（输入 ID）
6. Exit            # 退出程序
```

---

## 📂 数据存储

数据存储在 SQLite 数据库文件 `library.db` 中，位于项目根目录。

表结构：

```sql
CREATE TABLE books (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    title TEXT NOT NULL,
    author TEXT NOT NULL,
    borrowed INTEGER DEFAULT 0
);
```

| 字段 | 类型 | 说明 |
|------|------|------|
| `id` | INTEGER | 自动递增编号 |
| `title` | TEXT | 书名 |
| `author` | TEXT | 作者 |
| `borrowed` | INTEGER | 0=在库，1=已借出 |

---

## 🧹 清理编译产物

```bash
cd build
make clean
```

或彻底清理：

```bash
rm -rf build
```

---

## 📌 注意事项

- 程序启动时会自动创建 `library.db` 数据库文件
- 数据自动持久化，无需手动保存
- 删除图书时，如果该书已借出，会提示无法删除

---

## 🏷️ 版本标签

本项目使用 Git Tag 管理版本：

| 版本 | 说明 |
|------|------|
| `v1.0.0` | 初始版本：文件存储 + 面向过程 |
| `v1.1.0` | OOP 重构：引入 Library 类 |
| `v1.2.0` | SQLite 数据库集成 |

### 查看所有标签

```bash
git tag -l
```

### 打标签

```bash
# 给当前 commit 打标签
git tag v1.2.0

# 给指定 commit 打标签
git tag v1.1.0 c0ba576

# 推送标签到远程仓库
git push origin --tags
```

---

## 🔗 远程仓库

| 项目信息 | 说明 |
|---------|------|
| 远程仓库地址 | `git@github.com:hgritty/LMS-cli.git` |
| 克隆命令 | `git clone git@github.com:hgritty/LMS-cli.git` |
| HTTPS 地址 | `https://github.com/hgritty/LMS-cli.git` |

### 提交规范

本项目遵循 [Conventional Commits](https://www.conventionalcommits.org/) 规范：

```bash
feat: 添加新功能
fix: 修复 Bug
docs: 文档/注释更新
style: 代码格式调整
refactor: 重构（不改变功能）
chore: 构建/工具配置
```

---
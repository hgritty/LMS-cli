# LMS-cli

**LMS-cli**（Library Management System in CLI）是一个基于 C++ 的命令行图书管理系统，提供图书的增删改查、借阅归还和数据持久化功能。

---

## ✨ 功能列表

### 已实现
- [x] 添加图书（自动分配编号）
- [x] 查看所有图书（表格对齐）
- [x] 借阅图书（按 ID 操作）
- [x] 归还图书（按 ID 操作）
- [x] 数据持久化（自动保存/加载）

### 待开发
- [ ] 删除图书
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
| 构建工具 | CMake 3.28.3 |
| 编译器 | GCC / Clang |
| 操作系统 | Ubuntu 24.04 / WSL2 |

---

## 📁 项目结构

```
library/
├── src/
│   ├── book.h          # Book 结构体 + 函数声明
│   ├── book.cpp        # 函数实现
│   └── main.cpp        # 程序入口（菜单 + main）
├── build/              # 编译产物（自动生成）
├── CMakeLists.txt      # CMake 构建配置
├── README.md
└── .gitignore
```

---

## 🔧 编译与运行

### 方式一：使用 CMake（推荐）

```bash
# 1. 进入项目目录
cd ~/code/library

# 2. 创建构建目录并编译
mkdir build && cd build
cmake ..
make

# 3. 运行
./lib
```

### 方式二：直接编译

```bash
g++ -std=c++11 src/book.cpp src/main.cpp -o lib
./lib
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
5. Exit            # 退出并保存数据
```

---

## 📂 数据存储

数据保存在项目根目录的 `books.txt` 中，格式为：

```text
编号|书名|作者|状态
1|C++ Primer|Lippman|0
2|The C Programming Language|Kernighan|1
```

| 状态 | 含义 |
|------|------|
| `0` | 在库（Available） |
| `1` | 已借出（Borrowed） |

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

- 程序启动时会自动加载 `books.txt` 中的数据
- 退出时会自动保存数据到 `books.txt`
- 请勿手动修改 `books.txt` 格式，否则可能导致读取失败

---

## 🚀 后续计划

- [ ] 删除图书
- [ ] 按书名/作者搜索
- [ ] 统计功能
- [ ] 同一本书多副本支持



---

## ✅ 更新后的 README 特点

| 对比 | 旧版 | 新版 |
|------|------|------|
| 项目结构 | ❌ 没有说明 | ✅ 清晰列出 |
| 编译方式 | ❌ 只有手动编译 | ✅ CMake + 手动两种方式 |
| 目录说明 | ❌ 没有 | ✅ 说明每个文件的作用 |
| 数据格式 | ✅ 有 | ✅ 保留并优化 |
| 使用说明 | ❌ 没有 | ✅ 菜单说明 |
| 清理命令 | ❌ 没有 | ✅ 添加 |

---

提交更新：

```bash
git add README.md
git commit -m "docs: 更新 README，适配新的项目结构"
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


---

## 📄 许可证

MIT License
```

---

## 🔨 替换你的 README

```bash
cd ~/code/library
nano README.md
```

把上面的内容复制进去，保存退出。
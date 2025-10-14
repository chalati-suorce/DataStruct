# 数据结构课程代码仓库

这是一个数据结构课程的代码仓库，包含使用C和C++语言实现的各种数据结构算法和练习。

## 仓库结构

```
.
├── C/                    # C语言实现
│   └── Unit2/           # 第二单元练习
│       ├── Book.c               # 图书信息管理系统
│       ├── book.txt             # 图书数据文件
│       ├── example.c            # 示例程序
│       ├── ShopInformation.c    # 商店信息管理系统
│       ├── StudentInformation.c # 学生信息管理系统
│       ├── test_compile.c       # 编译测试程序
│       ├── test_example.c       # 示例测试程序
│       ├── Unit2 problem1.c     # 第二单元问题1
│       ├── Unit2 problem2.c     # 第二单元问题2
│       └── output/              # 编译输出目录
│           ├── Book.exe
│           ├── example.exe
│           ├── ShopInformation.exe
│           ├── StudentInformation.exe
│           ├── test_compile.exe
│           ├── test_example.exe
│           └── Unit2 problem2.exe
└── C++/                  # C++语言实现
    └── Unit2/           # 第二单元练习
        ├── example.cpp           # 示例程序
        ├── Studentlnformation.cpp # 学生信息管理系统
        └── output/              # 编译输出目录
```

## 主要功能模块

### C语言实现
- **Book.c**: 图书信息管理系统，实现图书数据的增删改查功能
- **ShopInformation.c**: 商店信息管理系统，管理商店商品信息
- **StudentInformation.c**: 学生信息管理系统，处理学生基本信息
- **Unit2 problem1.c**: 第二单元的第一个问题解决方案
- **Unit2 problem2.c**: 第二单元的第二个问题解决方案

### C++语言实现
- **Studentlnformation.cpp**: 使用C++实现的学生信息管理系统
- **example.cpp**: C++示例程序

## 编译和运行

### 使用GCC编译C程序
```bash
# 编译单个C文件
gcc -o output/filename.exe C/Unit2/filename.c

# 编译所有C文件
cd C/Unit2
gcc -o output/Book.exe Book.c
gcc -o output/ShopInformation.exe ShopInformation.c
gcc -o output/StudentInformation.exe StudentInformation.c
```

### 使用G++编译C++程序
```bash
# 编译单个C++文件
g++ -o output/filename.exe C++/Unit2/filename.cpp

# 编译C++文件
cd C++/Unit2
g++ -o output/Studentlnformation.exe Studentlnformation.cpp
g++ -o output/example.exe example.cpp
```

### 运行程序
```bash
# 运行编译后的可执行文件
./output/filename.exe
```

## 开发环境配置

### 必需工具
- GCC (MinGW) - C语言编译器
- G++ - C++语言编译器
- Git - 版本控制

### VSCode配置
此仓库已配置VSCode调试环境，支持：
- C/C++程序调试
- 断点设置和变量监视
- 自动编译任务

详细配置请参考 `.vscode/` 目录下的配置文件。

## 学习目标

通过本仓库的代码，可以学习到：

1. **数据结构基础**
   - 数组、链表、栈、队列的实现
   - 基本数据操作（增删改查）

2. **C/C++编程**
   - 文件I/O操作
   - 内存管理
   - 结构体和类的使用

3. **系统设计**
   - 信息管理系统的架构设计
   - 用户交互界面设计
   - 数据持久化存储

## 贡献指南

1. Fork本仓库
2. 创建功能分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 创建Pull Request

## 许可证

本项目采用MIT许可证 - 查看 [LICENSE](LICENSE) 文件了解详情

## 联系方式

如有问题或建议，请通过以下方式联系：
- 邮箱：[1841220662@qq.com]

---

*最后更新: 2025年10月*

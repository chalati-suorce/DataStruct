# 数据结构课程代码仓库

这是一个数据结构课程的完整代码仓库，包含使用C语言实现的各种数据结构算法和练习，涵盖从基础到高级的所有章节内容。

## 仓库结构

```
.
├── Chapter 1Introduction/              # 第一章：绪论
│   ├── Complex quadruple opration.c    # 复数四则运算
│   ├── Four-rule Operation of rational number.c  # 有理数四则运算
│   └── Turtle mapping.c                # 海龟绘图
├── Chapter 2 Linear Lists/             # 第二章：线性表
│   ├── Colorful rain falls on the pond at night.c    # 彩色雨夜池塘
│   ├── Joseph ring.c                   # 约瑟夫环问题
│   ├── Long interger four-rule operation.c          # 长整数四则运算
│   ├── Sports score statiscs.c         # 体育成绩统计
│   ├── StudentInformationManageSystem.c # 学生信息管理系统
│   ├── The of union ,intersection and difference of sets.c  # 集合的并、交、差运算
│   └── Unary sparse  polynomial calculator.c        # 一元稀疏多项式计算器
├── Chapter 3 Stacks andd Queues/       # 第三章：栈和队列
│   ├── Air passenger booking system.c  # 航空客运订票系统
│   ├── Banking simulation.c            # 银行模拟
│   ├── Car dispaching.c                # 汽车调度
│   ├── Demonstration of evaluation of airthmetic expressions.c  # 算术表达式求值演示
│   ├── Elevator simulation.c           # 电梯模拟
│   ├── Horse stepping chessborad.c     # 马踏棋盘
│   ├── Interpretation of the Devil's Lauguage.c     # 魔王语言解释
│   ├── Maze problem.c                  # 迷宫问题
│   └── Parking lot management.c        # 停车场管理
├── Chapter 4 Strings,Arrays and Generalized Lists/  # 第四章：串、数组和广义表
│   ├── A demonstration that identifies the head or tail of a generalized table.c  # 广义表头尾识别演示
│   ├── Literary Research Assistant.c   # 文学研究助手
│   ├── Multidimensional array.c        # 多维数组
│   ├── Program analysis.c              # 程序分析
│   ├── Simple line editor.c            # 简单行编辑器
│   ├── Simple LISP arithmetic Expression Calculator.c  # 简单LISP算术表达式计算器
│   ├── Sparse matrix operator.c        # 稀疏矩阵运算
│   ├── String operating commamd system.c  # 字符串操作命令系统
│   └── Text formatting.c               # 文本格式化
├── Chapter 5 Trees and Binary Trees/   # 第五章：树和二叉树
│   ├── Huffman compiler.c              # 哈夫曼编译器
│   ├── Implementation of expression types.c  # 表达式类型实现
│   ├── Minimum spanning tree problem.c # 最小生成树问题
│   ├── Tautology discrimination.c      # 重言式判别
│   └── The problem of compiling teaching plan.c  # 教学计划编制问题
├── Chapter 6 Graphs/                   # 第六章：图
│   ├── Campus tour guide consultation.c  # 校园导游咨询
│   ├── Demonstration of graph traversal.c  # 图的遍历演示
│   └── National Traffic Consultation Simulation.c  # 全国交通咨询模拟
├── Chapter 7 Searching/                # 第七章：查找
│   ├── Book management.c               # 图书管理
│   ├── Demonstration of Balanced Binary Tree Operations.C  # 平衡二叉树操作演示
│   ├── Hash table design.c             # 哈希表设计
│   ├── Maintenance and Identification of English Dictionary.C  # 英文词典维护与识别
│   └── Partner Storage Management System Demo.c  # 伙伴存储管理系统演示
└── Chapter 8 Sorting/                  # 第八章：排序
    ├── Comparison of Internal Sorting Algorithms.C  # 内部排序算法比较
    ├── Demonstration of Balanced Binary Tree Operations.C  # 平衡二叉树操作演示
    └── Multi-keyword sort.C            # 多关键字排序
```

## 主要功能模块

### 第一章：绪论
- **复数四则运算**: 实现复数的加减乘除运算
- **有理数四则运算**: 实现有理数的基本运算
- **海龟绘图**: 图形化绘图程序

### 第二章：线性表
- **约瑟夫环问题**: 经典的约瑟夫环算法实现
- **长整数四则运算**: 处理大整数的数学运算
- **学生信息管理系统**: 完整的学籍管理系统
- **一元稀疏多项式计算器**: 多项式运算工具

### 第三章：栈和队列
- **算术表达式求值**: 使用栈实现表达式计算
- **迷宫问题**: 使用栈解决迷宫路径问题
- **停车场管理**: 队列在停车场管理中的应用
- **银行模拟**: 队列在银行服务系统中的应用

### 第四章：串、数组和广义表
- **简单行编辑器**: 文本编辑器的基本功能
- **稀疏矩阵运算**: 高效处理稀疏矩阵
- **文学研究助手**: 文本分析和处理工具
- **LISP表达式计算器**: 函数式编程语言解释器

### 第五章：树和二叉树
- **哈夫曼编译器**: 数据压缩算法实现
- **最小生成树**: 图论算法应用
- **表达式树**: 树结构在表达式处理中的应用

### 第六章：图
- **图的遍历**: 深度优先和广度优先搜索
- **最短路径**: Dijkstra算法实现
- **校园导游系统**: 图在路径规划中的应用

### 第七章：查找
- **平衡二叉树**: AVL树或红黑树实现
- **哈希表**: 散列查找技术
- **词典维护**: 字典数据结构的应用

### 第八章：排序
- **内部排序算法比较**: 多种排序算法性能分析
- **多关键字排序**: 复杂排序需求处理

## 编译和运行

### 使用GCC编译C程序
```bash
# 编译单个C文件（Windows环境）
gcc -o output/program.exe "Chapter X ChapterName/program.c"

# 示例：编译第一章的复数四则运算程序
gcc -o output/complex.exe "Chapter 1Introduction/Complex quadruple opration.c"

# 示例：编译第二章的约瑟夫环程序
gcc -o output/joseph.exe "Chapter 2 Linear Lists/Joseph ring.c"

# 编译所有章节的程序（批量编译）
for /r %%i in (*.c) do (
    gcc -o "output/%%~ni.exe" "%%i"
)
```

### 使用G++编译C++程序
```bash
# 编译C++文件（Windows环境）
g++ -o output/program.exe "C++/Unit2/program.cpp"

# 示例：编译C++学生信息管理系统
g++ -o output/student_cpp.exe "C++/Unit2/Studentlnformation.cpp"
```

### 运行程序
```bash
# 运行编译后的可执行文件（Windows环境）
output\program.exe

# 示例：运行复数四则运算程序
output\complex.exe

# 示例：运行约瑟夫环程序
output\joseph.exe
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

通过本仓库的代码，可以系统学习数据结构与算法的完整知识体系：

1. **基础数据结构**
   - 线性表：顺序表、链表及其应用
   - 栈和队列：表达式求值、迷宫求解、系统模拟
   - 串：模式匹配、文本编辑、字符串处理

2. **高级数据结构**
   - 树结构：二叉树、哈夫曼树、表达式树
   - 图结构：图的遍历、最短路径、最小生成树
   - 查找结构：平衡二叉树、哈希表、字典树

3. **算法设计与分析**
   - 排序算法：内部排序算法比较与分析
   - 图算法：深度优先搜索、广度优先搜索
   - 压缩算法：哈夫曼编码实现

4. **实际应用场景**
   - 信息管理系统：学生管理、图书管理
   - 系统模拟：银行排队、停车场管理、电梯调度
   - 数学计算：复数运算、多项式计算、矩阵运算

5. **编程技能提升**
   - C语言高级特性：指针、结构体、文件操作
   - 算法实现技巧：递归、动态规划、贪心算法
   - 系统设计能力：模块化设计、接口设计

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

# C语言项目开发配置说明

## 配置概述

本项目已配置了完整的C语言开发环境，支持编译后自动运行，并集成了多种有用的插件和工具。

## 快速开始

### 1. 安装推荐插件
打开VSCode，按 `Ctrl+Shift+X` 打开扩展面板，搜索并安装 `.vscode/extensions.json` 中推荐的插件。

### 2. 编译和运行方式

#### 方式一：使用快捷键（推荐）
- **F5**: 使用Code Runner快速编译并运行当前文件
- **Ctrl+F7**: 使用任务系统自动编译并运行
- **Ctrl+Shift+B**: 编译当前文件
- **Ctrl+F5**: 启动调试

#### 方式二：使用命令面板
1. 按 `Ctrl+Shift+P`
2. 输入以下命令：
   - `Tasks: Run Task` → 选择"自动编译并运行"
   - `Run Code` → 使用Code Runner运行

#### 方式三：使用终端
```bash
# 编译当前文件
gcc -g filename.c -o filename.exe

# 运行程序
./filename.exe
```

## 配置特性

### 自动编译和运行
- 文件保存后自动格式化
- 支持一键编译并运行
- 编译错误实时显示

### 调试支持
- 集成GDB调试器
- 支持断点调试
- 变量监视和调用堆栈

### 代码质量
- 自动代码格式化
- 语法高亮和智能提示
- 错误检查和警告

## 项目结构

```
DataStruct/
├── .vscode/                 # VSCode配置目录
│   ├── tasks.json          # 任务配置
│   ├── launch.json         # 调试配置
│   ├── settings.json       # 工作区设置
│   ├── keybindings.json    # 快捷键配置
│   └── extensions.json     # 插件推荐
├── All test/               # 测试文件目录
├── Chapter 1Introduction/  # 第一章示例
├── Chapter 2 Linear Lists/ # 第二章示例
└── ...                     # 其他章节
```

## 常用命令

### 编译特定文件
```bash
# 编译当前打开的文件
Ctrl+Shift+B

# 编译并立即运行
Ctrl+F7 或 F5
```

### 批量编译
```bash
# 编译All test目录下的所有C文件
Ctrl+Shift+F5
```

### 调试
```bash
# 启动调试会话
Ctrl+F5

# 设置断点：在行号左侧点击
# 单步执行：F10
# 进入函数：F11
# 跳出函数：Shift+F11
```

## 插件功能说明

### 核心插件
- **C/C++**: Microsoft官方C/C++扩展，提供智能提示、调试等功能
- **Code Runner**: 快速运行代码片段
- **GitLens**: Git版本控制增强
- **Material Icon Theme**: 文件图标主题

### 辅助插件
- **Clang-Format**: 代码格式化
- **Doxygen**: 文档生成
- **Makefile Tools**: Makefile支持

## 故障排除

### 编译错误
1. 检查GCC路径是否正确配置
2. 确认文件编码为UTF-8
3. 检查头文件包含路径

### 运行问题
1. 确认可执行文件生成成功
2. 检查终端权限
3. 验证输入数据格式

### 调试问题
1. 确认编译时包含调试信息 (`-g` 参数)
2. 检查GDB路径配置
3. 验证断点设置位置

## 注意事项

1. 确保GCC编译器已正确安装并添加到PATH
2. 建议使用UTF-8编码保存文件
3. 定期更新插件以获得最新功能
4. 备份重要代码文件

## 联系方式

如有配置问题，请参考VSCode官方文档或联系项目维护者。

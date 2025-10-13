# Visual Studio Code C/C++ 调试配置

此配置已针对您的 MinGW 环境（位于 `D:\MSYS\mingw64\bin`）进行了优化，支持 C 和 C++ 程序的编译、运行和调试。

## 配置说明

### 1. 调试配置 (launch.json)
- **Debug C Program**: 调试 C 程序
- **Debug C++ Program**: 调试 C++ 程序

### 2. 编译任务 (tasks.json)
- **build-c-program**: 编译当前 C 文件
- **build-cpp-program**: 编译当前 C++ 文件
- **build-c-program-debug**: 编译 C 文件（带调试信息）
- **build-cpp-program-debug**: 编译 C++ 文件（带调试信息）

### 3. 使用方式

#### 方法一：使用调试功能
1. 打开一个 C 或 C++ 文件
2. 按 `F5` 或点击运行和调试
3. 选择相应的调试配置（C 或 C++）
4. 程序将自动编译并启动调试

#### 方法二：使用任务编译
1. 按 `Ctrl+Shift+P`
2. 输入 "Tasks: Run Task"
3. 选择相应的编译任务

#### 方法三：使用 Code Runner 扩展
1. 安装 Code Runner 扩展
2. 右键点击文件选择 "Run Code" 或按 `Ctrl+Alt+N`

### 4. 输出目录
- C 程序输出到：`C/output/`
- C++ 程序输出到：`C++/output/`

### 5. 调试功能
- 支持断点调试
- 变量监视
- 调用堆栈查看
- GDB 集成

### 6. 必需扩展
建议安装以下扩展以获得最佳体验：
- C/C++ (Microsoft)
- Code Runner

## 注意事项
- 确保 MinGW 路径 `D:\MSYS\mingw64\bin` 已在系统 PATH 中
- 编译时会自动生成调试信息（-g 标志）
- 输出文件会自动保存到相应的输出目录

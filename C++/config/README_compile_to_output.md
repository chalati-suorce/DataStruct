# 编译到Output目录配置

此配置确保所有C/C++编译的exe文件默认保存到`output`目录。

## 配置说明

### 1. VSCode配置
- 已配置VSCode的Code Runner扩展，自动将编译输出重定向到output目录
- 支持C和C++文件
- 编译时会显示"Compiled to output/文件名.exe"的提示

### 2. 编译脚本

#### Windows批处理文件 (compile_to_output.bat)
```cmd
# 编译单个文件
compile_to_output.bat example.c

# 编译多个文件
for %f in (*.c) do compile_to_output.bat "%f"
```

#### PowerShell脚本 (compile_to_output.ps1)
```powershell
# 编译单个文件
.\compile_to_output.ps1 -SourceFile "example.c"

# 编译所有C文件
Get-ChildItem *.c | ForEach-Object { .\compile_to_output.ps1 -SourceFile $_.Name }

# 编译所有C++文件
Get-ChildItem *.cpp | ForEach-Object { .\compile_to_output.ps1 -SourceFile $_.Name }
```

### 3. VSCode快捷方式
- 安装Code Runner扩展后，可以使用快捷键：
  - `Ctrl+Alt+N` - 运行当前文件
  - `Ctrl+Alt+M` - 停止运行
  - 右键点击文件选择"Run Code"

### 4. 手动编译命令
如果使用手动编译，可以使用以下命令：

```cmd
# C文件
gcc filename.c -o output/filename.exe

# C++文件
g++ filename.cpp -o output/filename.exe
```

## 目录结构
```
C++/
├── U2/
│   ├── *.c, *.cpp          # 源代码文件
│   └── output/             # 编译输出目录
│       └── *.exe           # 可执行文件
├── compile_to_output.bat   # 批处理编译脚本
├── compile_to_output.ps1   # PowerShell编译脚本
└── README_compile_to_output.md # 本说明文档
```

## 注意事项
1. 确保已安装GCC/G++编译器
2. output目录会自动创建（如果不存在）
3. 编译失败时会显示错误信息
4. 成功编译后会显示输出路径

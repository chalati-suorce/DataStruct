# 文件编码和终端中文乱码解决方案

## 问题描述
- 项目中存在.exe文件需要被Git忽略
- 终端显示中文乱码
- 文件编码可能不一致

## 解决方案

### 1. Git忽略设置
已创建`.gitignore`文件，忽略以下内容：
- 所有`.exe`可执行文件
- `.vscode/`目录
- 其他构建文件和IDE文件

### 2. 终端编码设置

#### 方法一：使用批处理文件
运行 `fix_encoding.bat` 来设置终端编码为UTF-8：
```cmd
fix_encoding.bat
```

#### 方法二：手动设置
在PowerShell中运行：
```powershell
chcp 65001
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
```

### 3. 文件编码转换

#### 批量转换所有C/C++文件为UTF-8
运行PowerShell脚本：
```powershell
.\convert_to_utf8.ps1
```

#### 手动转换单个文件
```powershell
Get-Content "文件名.c" | Out-File -Encoding UTF8 "文件名.c"
```

### 4. VSCode配置
已创建`.vscode/settings.json`文件，自动设置：
- 文件编码为UTF-8
- 终端默认使用UTF-8编码
- 自动猜测文件编码

## 验证解决方案

1. **检查终端编码**：
   ```cmd
   chcp
   ```
   应该显示 `65001` (UTF-8)

2. **测试中文显示**：
   ```cmd
   echo 中文测试
   ```

3. **检查文件编码**：
   在VSCode中查看文件右下角的编码显示

## 注意事项

- 脚本文件 (`fix_encoding.bat`, `convert_to_utf8.ps1`) 已保留在版本控制中
- `.vscode/settings.json` 配置了VSCode的编码设置
- 所有新创建的文件将使用UTF-8编码

## 常见问题

**Q: 为什么终端还是显示乱码？**
A: 确保运行了编码设置脚本，或者重启终端。

**Q: 如何检查文件当前编码？**
A: 在VSCode中查看文件右下角的状态栏，或者使用PowerShell命令检测。

**Q: 转换编码会影响代码功能吗？**
A: 不会，只是改变了字符的编码方式，不影响代码逻辑。

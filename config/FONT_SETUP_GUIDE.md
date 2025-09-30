# 中文乱码解决方案 - 字体设置指南

## 问题分析
中文乱码通常由以下原因导致：
1. **终端编码不是UTF-8**
2. **终端字体不支持中文**
3. **文件编码不是UTF-8**

我们已经解决了编码问题，现在需要解决字体问题。

## 解决方案

### 方法1：VSCode终端字体设置（推荐）
VSCode已自动配置，如果仍然乱码，请手动设置：

1. 打开VSCode设置（Ctrl+,）
2. 搜索 `terminal font`
3. 设置 `Terminal › Integrated: Font Family` 为：
   ```
   Consolas, 'Microsoft YaHei Mono', 'SimSun-ExtB', 'NSimSun', monospace
   ```
4. 重启VSCode终端

### 方法2：Windows终端字体设置
如果使用Windows Terminal：

1. 打开Windows Terminal设置
2. 选择"默认值"或具体配置文件
3. 在"外观"选项卡中设置字体为：
   - `Microsoft YaHei Mono`
   - `SimSun-ExtB` 
   - `NSimSun`
   - `等距更纱黑体 SC` (如果安装了)

### 方法3：系统字体安装
如果上述字体不可用，请安装支持中文的等宽字体：

1. **下载字体**：
   - 微软雅黑 Mono
   - 等距更纱黑体
   - Source Han Code JP

2. **安装字体**：
   - 右键字体文件 → "为所有用户安装"
   - 重启VSCode

## 验证解决方案

运行以下命令测试中文显示：
```powershell
config\fix_chinese_encoding_final.ps1
```

如果显示 `中文测试` 而不是乱码，说明问题已解决。

## 备用方案

如果上述方法都不起作用，可以：

1. **使用外部终端**：
   - 在VSCode中设置 `"terminal.integrated.external.windowsExec": "wt"`
   - 使用Windows Terminal代替内置终端

2. **使用CMD终端**：
   - 在VSCode中切换终端为CMD
   - CMD对中文支持更好

## 最终检查清单

- [ ] 终端编码设置为65001 (UTF-8)
- [ ] 所有C/C++文件编码为UTF-8
- [ ] 终端字体设置为支持中文的字体
- [ ] 重启终端后中文显示正常

如果完成所有步骤后中文仍然乱码，可能是系统级别的字体问题，建议重新安装支持中文的字体包。

# QT贪吃蛇游戏

基于 Qt Widgets 的经典贪吃蛇桌面游戏，支持多种皮肤、难度切换、音效、障碍物模式及游戏进度保存/加载。

## 功能特色

- 经典贪吃蛇玩法，键盘方向控制
- 多种皮肤（经典、暗黑、霓虹、自然）一键切换
- 简单/中等/困难三档难度调节
- 随机障碍物模式，提升挑战性
- 游戏音效支持，可开关
- 实时分数与最高分统计，自动保存
- 支持游戏进度保存与读取，断点续玩
- 采用面向对象设计，代码结构清晰，易于扩展

## 截图

> 可在此处插入游戏运行截图（如 snake-demo.png）

## 编译与运行

### 环境要求

- 推荐 Qt 6.5 及以上
- CMake 3.16+
- C++17 编译器（如 MinGW、MSVC、Clang）

### 构建步骤

1. 克隆仓库
   ```sh
   git clone https://github.com/H1600/snake-qt.git
   cd snake-qt
   ```

2. 使用 CMake 构建
   ```sh
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```

3. 运行
   - Windows 下可直接双击 `snake.exe`
   - 或在终端运行：
     ```sh
     ./snake
     ```

### Qt Creator 用户

- 直接用 Qt Creator 打开 `CMakeLists.txt`，配置好 Qt Kit，点击构建并运行即可。

## 操作说明

- 方向键：控制蛇移动
- 空格键：暂停/继续
- R 键：暂停时重开
- 菜单栏可切换皮肤、难度、障碍物、音效等

## 主要文件结构

- `main.cpp`         程序入口
- `gamewindow.*`     主窗口与游戏逻辑
- `snake.*`          蛇对象
- `food.*`           食物对象
- `scoremanager.*`   分数与进度管理
- `soundmanager.*`   音效管理
- `skinmanager.*`    皮肤管理
- `resources.qrc`    资源文件（音效）

## 许可协议

本项目采用 MIT License，欢迎学习和二次开发。

---

如有建议或问题，欢迎 issue 或 PR！

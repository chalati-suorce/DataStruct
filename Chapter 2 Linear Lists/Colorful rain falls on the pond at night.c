/*
池塘夜降彩色雨
问题描述：设计程序演示 “池塘夜雨” 景色，雨点从天而降，溅起水圈。
基本要求：雨点的出现位置、降落可见度、入水位置、颜色、水圈等随机确定；多个雨点同时演示。
测试数据：调整雨点密度、水圈大小和状态变化时间间隔等参数。
实现提示：
雨点存在周期分三个阶段，需记录参数和状态。
编程实现雨点下降和水圈扩散的视觉效果。
管理当前存在的雨点，及时删除消失的雨点。
选作内容：
增加电闪雷鸣景象。
增加风的效果。
实现雨点密度变化。
将池塘改为荷塘，模拟雨点滴荷叶的效果。
*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>

#define MAX_RAINDROPS 50
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define POND_LEVEL 20

// 雨点状态枚举
typedef enum {
    FALLING,    // 下降阶段
    SPLASHING,  // 入水阶段
    RIPPLE      // 水圈扩散阶段
} RaindropState;

// 雨点结构体
typedef struct {
    int x;              // 水平位置
    int y;              // 垂直位置
    int color;          // 颜色
    int speed;          // 下降速度
    int ripple_radius;  // 水圈半径
    int ripple_max;     // 水圈最大半径
    RaindropState state; // 当前状态
    int lifetime;       // 生命周期计数器
} Raindrop;

// 全局变量
Raindrop raindrops[MAX_RAINDROPS];
int raindrop_count = 0;
int rain_density = 5;   // 雨点密度
int wind_strength = 0;  // 风力强度

// 函数声明
void initRaindrop(Raindrop *rd);
void updateRaindrops();
void drawScene();
void drawRaindrop(Raindrop *rd);
void drawPond();
void clearScreen();
void setCursorPosition(int x, int y);
void setColor(int color);
void resetColor();
void simulateLightning();
void applyWindEffect(Raindrop *rd);

// 初始化雨点
void initRaindrop(Raindrop *rd) {
    rd->x = rand() % SCREEN_WIDTH;
    rd->y = 0;
    rd->color = rand() % 7 + 9;  // 9-15为亮色
    rd->speed = rand() % 3 + 1;
    rd->ripple_radius = 0;
    rd->ripple_max = rand() % 5 + 3;
    rd->state = FALLING;
    rd->lifetime = 0;
}

// 更新所有雨点状态
void updateRaindrops() {
    // 随机生成新雨点
    if (raindrop_count < MAX_RAINDROPS && rand() % (20 - rain_density) == 0) {
        initRaindrop(&raindrops[raindrop_count]);
        raindrop_count++;
    }
    
    // 更新现有雨点
    for (int i = 0; i < raindrop_count; i++) {
        Raindrop *rd = &raindrops[i];
        rd->lifetime++;
        
        switch (rd->state) {
            case FALLING:
                // 应用风力效果
                applyWindEffect(rd);
                
                // 下降
                rd->y += rd->speed;
                
                // 检查是否到达水面
                if (rd->y >= POND_LEVEL) {
                    rd->state = SPLASHING;
                    rd->lifetime = 0;
                }
                break;
                
            case SPLASHING:
                // 入水效果，短暂停留
                if (rd->lifetime > 2) {
                    rd->state = RIPPLE;
                    rd->lifetime = 0;
                }
                break;
                
            case RIPPLE:
                // 水圈扩散
                rd->ripple_radius++;
                if (rd->ripple_radius > rd->ripple_max) {
                    // 删除这个雨点
                    for (int j = i; j < raindrop_count - 1; j++) {
                        raindrops[j] = raindrops[j + 1];
                    }
                    raindrop_count--;
                    i--;
                }
                break;
        }
    }
    
    // 随机闪电效果
    if (rand() % 500 == 0) {
        simulateLightning();
    }
}

// 绘制雨点
void drawRaindrop(Raindrop *rd) {
    setCursorPosition(rd->x, rd->y);
    setColor(rd->color);
    
    switch (rd->state) {
        case FALLING:
            printf("|");
            break;
        case SPLASHING:
            printf("*");
            break;
        case RIPPLE:
            // 绘制水圈
            for (int r = 1; r <= rd->ripple_radius; r++) {
                if (rd->x - r >= 0) {
                    setCursorPosition(rd->x - r, POND_LEVEL);
                    printf("-");
                }
                if (rd->x + r < SCREEN_WIDTH) {
                    setCursorPosition(rd->x + r, POND_LEVEL);
                    printf("-");
                }
            }
            break;
    }
    
    resetColor();
}

// 绘制池塘
void drawPond() {
    setCursorPosition(0, POND_LEVEL);
    setColor(11); // 青色
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        printf("~");
    }
    resetColor();
}

// 绘制荷叶（选作内容）
void drawLotusLeaves() {
    // 随机位置绘制荷叶
    setColor(10); // 绿色
    setCursorPosition(15, POND_LEVEL - 1);
    printf("( )");
    setCursorPosition(45, POND_LEVEL - 1);
    printf("( )");
    setCursorPosition(65, POND_LEVEL - 1);
    printf("( )");
    resetColor();
}

// 模拟闪电效果
void simulateLightning() {
    setColor(15); // 亮白色
    for (int i = 0; i < 3; i++) {
        clearScreen();
        // 绘制闪电图案
        for (int y = 0; y < 5; y++) {
            setCursorPosition(40 + rand() % 5, y);
            printf("!");
        }
        drawPond();
        drawLotusLeaves();
        Sleep(50);
    }
    resetColor();
}

// 应用风力效果
void applyWindEffect(Raindrop *rd) {
    if (wind_strength != 0 && rd->state == FALLING) {
        rd->x += wind_strength;
        // 边界检查
        if (rd->x < 0) rd->x = 0;
        if (rd->x >= SCREEN_WIDTH) rd->x = SCREEN_WIDTH - 1;
    }
}

// 设置控制台颜色
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// 重置颜色
void resetColor() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

// 设置光标位置
void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// 清屏
void clearScreen() {
    system("cls");
}

// 绘制整个场景
void drawScene() {
    clearScreen();
    
    // 绘制夜空背景
    setColor(1); // 蓝色
    for (int y = 0; y < POND_LEVEL; y++) {
        setCursorPosition(0, y);
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            printf(" ");
        }
    }
    
    // 绘制星星
    setColor(15);
    for (int i = 0; i < 10; i++) {
        setCursorPosition(rand() % SCREEN_WIDTH, rand() % (POND_LEVEL / 2));
        printf(".");
    }
    
    // 绘制池塘
    drawPond();
    
    // 绘制荷叶（选作内容）
    drawLotusLeaves();
    
    // 绘制所有雨点
    for (int i = 0; i < raindrop_count; i++) {
        drawRaindrop(&raindrops[i]);
    }
    
    // 显示状态信息
    setCursorPosition(0, SCREEN_HEIGHT - 2);
    setColor(7);
    printf("雨点密度: %d | 风力: %d | 雨点数量: %d", rain_density, wind_strength, raindrop_count);
    printf(" | 按+/-调整密度, ←/→调整风力, Q退出");
    
    resetColor();
}

// 主函数
int main() {
    // 初始化随机数种子
    srand((unsigned int)time(NULL));
    
    // 隐藏光标
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    
    printf("池塘夜降彩色雨模拟程序\n");
    printf("按任意键开始...");
    getchar();
    
    // 主循环
    while (1) {
        // 检查键盘输入
        if (GetAsyncKeyState('Q') & 0x8000) {
            break;
        }
        if (GetAsyncKeyState(VK_ADD) & 0x8000) {
            rain_density = (rain_density < 15) ? rain_density + 1 : 15;
            Sleep(100);
        }
        if (GetAsyncKeyState(VK_SUBTRACT) & 0x8000) {
            rain_density = (rain_density > 1) ? rain_density - 1 : 1;
            Sleep(100);
        }
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            wind_strength = (wind_strength > -3) ? wind_strength - 1 : -3;
            Sleep(100);
        }
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            wind_strength = (wind_strength < 3) ? wind_strength + 1 : 3;
            Sleep(100);
        }
        
        updateRaindrops();
        drawScene();
        Sleep(50); // 控制动画速度
    }
    
    // 恢复光标
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    
    clearScreen();
    printf("程序结束！\n");
    
    return 0;
}

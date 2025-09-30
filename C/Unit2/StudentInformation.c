#include <stdio.h>

#define MAX 100

typedef struct {
    int id;
    int studentID;
    char name[20];
    char gender[20];
    char className[20];
    char phonenumber[11];
} Student;

typedef Student elemtype;

typedef struct {
    elemtype students[MAX];
    int length;
} StudentList;

// 初始化学生列表
void init(StudentList *list) {
    list->length = 0;
    printf("初始化完成！\n");
}

// 添加学生
void addStudent(StudentList *list) {
    if (list->length >= MAX) {
        printf("学生数量已达上限！\n");
        return;
    }
    Student s;
    printf("请输入学号: ");
    scanf_s("%d", &s.studentID);
    printf("请输入姓名: ");
    scanf_s("%s", s.name, sizeof(s.name));
    printf("请输入性别: ");
    scanf_s("%s", s.gender, sizeof(s.gender));
    printf("请输入班级: ");
    scanf_s("%s", s.className, sizeof(s.className));
    printf("请输入手机号: ");
    scanf_s("%s", s.phonenumber, sizeof(s.phonenumber));
    s.id = list->length + 1;
    list->students[list->length++] = s;
    printf("添加成功！\n");
}

// 显示所有学生
void showAll(StudentList *list) {
    printf("%-6s %-10s %-10s %-8s %-10s %-12s\n", "编号", "学号", "姓名", "性别", "班级", "手机号");
    for (int i = 0; i < list->length; i++) {
        Student s = list->students[i];
        printf("%-6d %-10d %-10s %-8s %-10s %-12s\n", s.id, s.studentID, s.name, s.gender, s.className, s.phonenumber);
    }
}

// 按学号查找学生
void findStudent(StudentList *list) {
    int sid;
    printf("请输入要查找的学号: ");
    scanf_s("%d", &sid);
    for (int i = 0; i < list->length; i++) {
        if (list->students[i].studentID == sid) {
            Student s = list->students[i];
            printf("找到学生: %d\t%d\t%s\t%s\t%s\t%s\n", s.id, s.studentID, s.name, s.gender, s.className, s.phonenumber);
            return;
        }
    }
    printf("未找到该学生！\n");
}

// 删除学生
void deleteStudent(StudentList *list) {
    int sid, found = 0;
    printf("请输入要删除的学号: ");
    scanf_s("%d", &sid);
    for (int i = 0; i < list->length; i++) {
        if (list->students[i].studentID == sid) {
            for (int j = i; j < list->length - 1; j++) {
                list->students[j] = list->students[j + 1];
            }
            list->length--;
            found = 1;
            printf("删除成功！\n");
            break;
        }
    }
    if (!found) {
        printf("未找到该学生！\n");
    }
}

// 修改学生信息
void modifyStudent(StudentList *list) {
    int sid;
    printf("请输入要修改的学号: ");
    scanf_s("%d", &sid);
    for (int i = 0; i < list->length; i++) {
        if (list->students[i].studentID == sid) {
            printf("请输入新姓名: ");
            scanf_s("%s", list->students[i].name, sizeof(list->students[i].name));
            printf("请输入新性别: ");
            scanf_s("%s", list->students[i].gender, sizeof(list->students[i].gender));
            printf("请输入新班级: ");
            scanf_s("%s", list->students[i].className, sizeof(list->students[i].className));
            printf("请输入新手机号: ");
            scanf_s("%s", list->students[i].phonenumber, sizeof(list->students[i].phonenumber));
            printf("修改成功！\n");
            return;
        }
    }
    printf("未找到该学生！\n");
}

// 清空学生列表
void clearList(StudentList *list) {
    list->length = 0;
    printf("已清空所有学生信息！\n");
}

// 保存到文件
void saveToFile(StudentList *list, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("文件保存失败！\n");
        return;
    }
    for (int i = 0; i < list->length; i++) {
        Student s = list->students[i];
        fprintf(fp, "%d %d %s %s %s %s\n", s.id, s.studentID, s.name, s.gender, s.className, s.phonenumber);
    }
    fclose(fp);
    printf("保存到文件成功！\n");
}

// 从文件读取
void loadFromFile(StudentList *list, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("文件读取失败！\n");
        return;
    }
    list->length = 0;
    Student s;
    while (fscanf(fp, "%d %d %s %s %s %s", &s.id, &s.studentID, s.name, s.gender, s.className, s.phonenumber) == 6) {
        list->students[list->length++] = s;
    }
    fclose(fp);
    printf("读取文件成功！\n");
}

// 清屏
void clearScreen() {
    for (int i = 0; i < 50; i++) {
        printf("\n");
    }
}

void modifyID(StudentList *list) {
    int oldID, newID, found = 0;
    printf("请输入要修改编号的学号: ");
    scanf_s("%d", &oldID);
    for (int i = 0; i < list->length; i++) {
        if (list->students[i].studentID == oldID) {
            printf("当前编号为: %d\n", list->students[i].id);
            printf("请输入新编号: ");
            scanf_s("%d", &newID);
            list->students[i].id = newID;
            printf("编号修改成功！\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("未找到该学生！\n");
    }
}

// ...existing code...

int main() {
    StudentList list;
    int choice;
    char filename[100] = "students.txt";
    while (1) {
        printf("\n小型学生信息管理系统\n");
        printf("1. 初始化\n");
        printf("2. 输出\n");
        printf("3. 插入\n");
        printf("4. 删除\n");
        printf("5. 修改\n");
        printf("6. 查找\n");
        printf("7. 清空\n");
        printf("8. 读文件\n");
        printf("9. 写文件\n");
        printf("10. 修改编号\n"); // 新增菜单项
        printf("0. 清屏\n");
        printf("886. 退出\n");
        printf("请选择: ");
        scanf_s("%d", &choice);
        switch (choice) {
            case 1: init(&list); break;
            case 2: showAll(&list); break;
            case 3: addStudent(&list); break;
            case 4: deleteStudent(&list); break;
            case 5: modifyStudent(&list); break;
            case 6: findStudent(&list); break;
            case 7: clearList(&list); break;
            case 8: loadFromFile(&list, filename); break;
            case 9: saveToFile(&list, filename); break;
            case 10: modifyID(&list); break; // 新增功能
            case 0: clearScreen(); break;
            case 886: return 0;
            default: printf("无效选择！\n");
        }
    }
    return 0;
}



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 学生信息结构体
typedef struct Student
{
    char id[20];          // 学号
    char name[50];        // 姓名
    char gender[10];      // 性别
    int age;              // 年龄
    char major[50];       // 专业
    float score;          // 成绩
    struct Student *next; // 指向下一个节点的指针
} Student;

// 链表结构体
typedef struct
{
    Student *head; // 头指针
    int length;    // 链表长度
} StudentList;

// 1. 初始化链表
void InitList(StudentList *L)
{
    L->head = NULL;
    L->length = 0;
    printf("链表初始化成功！\n");
}

// 2. 创建新节点
Student *CreateNode(char *id, char *name, char *gender, int age, char *major, float score)
{
    Student *newNode = (Student *)malloc(sizeof(Student));
    if (newNode == NULL)
    {
        printf("内存分配失败！\n");
        return NULL;
    }

    strcpy(newNode->id, id);
    strcpy(newNode->name, name);
    strcpy(newNode->gender, gender);
    newNode->age = age;
    strcpy(newNode->major, major);
    newNode->score = score;
    newNode->next = NULL;

    return newNode;
}

// 3. 在链表尾部插入学生
int InsertAtEnd(StudentList *L, Student *newNode)
{
    if (newNode == NULL)
    {
        return 0;
    }

    // 检查学号是否重复
    Student *current = L->head;
    while (current != NULL)
    {
        if (strcmp(current->id, newNode->id) == 0)
        {
            printf("学号 %s 已存在，无法插入！\n", newNode->id);
            free(newNode);
            return 0;
        }
        current = current->next;
    }

    if (L->head == NULL)
    {
        L->head = newNode;
    }
    else
    {
        current = L->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }

    L->length++;
    printf("学生信息插入成功！\n");
    return 1;
}

// 4. 在指定位置插入学生
int InsertAtPosition(StudentList *L, Student *newNode, int position)
{
    if (newNode == NULL)
    {
        return 0;
    }

    if (position < 1 || position > L->length + 1)
    {
        printf("插入位置 %d 无效！有效范围: 1-%d\n", position, L->length + 1);
        free(newNode);
        return 0;
    }

    // 检查学号是否重复
    Student *current = L->head;
    while (current != NULL)
    {
        if (strcmp(current->id, newNode->id) == 0)
        {
            printf("学号 %s 已存在，无法插入！\n", newNode->id);
            free(newNode);
            return 0;
        }
        current = current->next;
    }

    if (position == 1)
    {
        newNode->next = L->head;
        L->head = newNode;
    }
    else
    {
        current = L->head;
        for (int i = 1; i < position - 1; i++)
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    L->length++;
    printf("学生信息插入成功！位置: %d\n", position);
    return 1;
}

// 5. 删除指定位置的学生
int DeleteAtPosition(StudentList *L, int position)
{
    if (position < 1 || position > L->length)
    {
        printf("删除位置 %d 无效！有效范围: 1-%d\n", position, L->length);
        return 0;
    }

    Student *temp, *prev;

    if (position == 1)
    {
        temp = L->head;
        L->head = L->head->next;
    }
    else
    {
        prev = L->head;
        for (int i = 1; i < position - 1; i++)
        {
            prev = prev->next;
        }
        temp = prev->next;
        prev->next = temp->next;
    }

    printf("删除的学生信息:\n");
    printf("学号: %s, 姓名: %s, 性别: %s, 年龄: %d, 专业: %s, 成绩: %.2f\n",
           temp->id, temp->name, temp->gender, temp->age, temp->major, temp->score);

    free(temp);
    L->length--;
    printf("学生信息删除成功！\n");
    return 1;
}

// 6. 按学号删除学生
int DeleteById(StudentList *L, char *id)
{
    Student *current = L->head;
    Student *prev = NULL;

    while (current != NULL)
    {
        if (strcmp(current->id, id) == 0)
        {
            if (prev == NULL)
            {
                L->head = current->next;
            }
            else
            {
                prev->next = current->next;
            }

            printf("删除的学生信息:\n");
            printf("学号: %s, 姓名: %s, 性别: %s, 年龄: %d, 专业: %s, 成绩: %.2f\n",
                   current->id, current->name, current->gender, current->age, current->major, current->score);

            free(current);
            L->length--;
            printf("学生信息删除成功！\n");
            return 1;
        }
        prev = current;
        current = current->next;
    }

    printf("未找到学号为 %s 的学生！\n", id);
    return 0;
}

// 7. 查找指定位置的学生
Student *GetElem(StudentList *L, int position)
{
    if (position < 1 || position > L->length)
    {
        printf("位置 %d 无效！有效范围: 1-%d\n", position, L->length);
        return NULL;
    }

    Student *current = L->head;
    for (int i = 1; i < position; i++)
    {
        current = current->next;
    }

    return current;
}

// 8. 按学号查找学生
Student *LocateById(StudentList *L, char *id)
{
    Student *current = L->head;

    while (current != NULL)
    {
        if (strcmp(current->id, id) == 0)
        {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

// 9. 按姓名查找学生
void SearchByName(StudentList *L, char *name)
{
    Student *current = L->head;
    int found = 0;

    printf("\n按姓名查找结果\n");
    while (current != NULL)
    {
        if (strstr(current->name, name) != NULL)
        {
            printf("学号: %s, 姓名: %s, 性别: %s, 年龄: %d, 专业: %s, 成绩: %.2f\n",
                   current->id, current->name, current->gender, current->age, current->major, current->score);
            found = 1;
        }
        current = current->next;
    }

    if (!found)
    {
        printf("未找到姓名为 \"%s\" 的学生！\n", name);
    }
}

// 10. 修改学生信息
int ModifyStudent(StudentList *L, char *id, Student *newData)
{
    Student *student = LocateById(L, id);
    if (student == NULL)
    {
        printf("未找到学号为 %s 的学生！\n", id);
        return 0;
    }

    // 检查新学号是否与其他学生冲突（除了当前学生）
    if (strcmp(id, newData->id) != 0)
    {
        Student *current = L->head;
        while (current != NULL)
        {
            if (current != student && strcmp(current->id, newData->id) == 0)
            {
                printf("学号 %s 已存在，无法修改！\n", newData->id);
                return 0;
            }
            current = current->next;
        }
    }

    printf("原学生信息:\n");
    printf("学号: %s, 姓名: %s, 性别: %s, 年龄: %d, 专业: %s, 成绩: %.2f\n",
           student->id, student->name, student->gender, student->age, student->major, student->score);

    strcpy(student->id, newData->id);
    strcpy(student->name, newData->name);
    strcpy(student->gender, newData->gender);
    student->age = newData->age;
    strcpy(student->major, newData->major);
    student->score = newData->score;

    printf("学生信息修改成功！\n");
    return 1;
}

// 11. 输出所有学生信息
void PrintList(StudentList *L)
{
    if (L->length == 0)
    {
        printf("链表为空！\n");
        return;
    }

    Student *current = L->head;
    int count = 1;

    printf("\n学生信息列表\n");
    printf("序号\t学号\t\t姓名\t\t性别\t年龄\t专业\t\t成绩\n");

    while (current != NULL)
    {
        printf("%d\t%s\t%s\t%s\t%d\t%s\t%.2f\n",
               count,
               current->id,
               current->name,
               current->gender,
               current->age,
               current->major,
               current->score);
        current = current->next;
        count++;
    }
    printf("总记录数: %d\n", L->length);
}

// 12. 清空链表
void ClearList(StudentList *L)
{
    Student *current = L->head;
    Student *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    L->head = NULL;
    L->length = 0;
    printf("链表已清空！\n");
}

// 13. 获取链表长度
int GetLength(StudentList *L)
{
    return L->length;
}

// 14. 判断链表是否为空
int IsEmpty(StudentList *L)
{
    return L->length == 0;
}

// 15. 输入学生信息
Student *InputStudent()
{
    Student *student = (Student *)malloc(sizeof(Student));
    if (student == NULL)
    {
        printf("内存分配失败！\n");
        return NULL;
    }

    printf("请输入学生信息:\n");

    printf("学号: ");
    scanf("%s", student->id);

    printf("姓名: ");
    scanf("%s", student->name);

    printf("性别: ");
    scanf("%s", student->gender);

    printf("年龄: ");
    scanf("%d", &student->age);

    printf("专业: ");
    scanf("%s", student->major);

    printf("成绩: ");
    scanf("%f", &student->score);

    student->next = NULL;

    return student;
}

// 16. 显示菜单
void ShowMenu()
{
    printf("\n学生信息管理系统\n");
    printf("1. 初始化链表\n");
    printf("2. 输出所有学生\n");
    printf("3. 在尾部插入学生\n");
    printf("4. 在指定位置插入学生\n");
    printf("5. 删除指定位置的学生\n");
    printf("6. 按学号删除学生\n");
    printf("7. 查找指定位置的学生\n");
    printf("8. 按学号查找学生\n");
    printf("9. 按姓名查找学生\n");
    printf("10. 修改学生信息\n");
    printf("11. 清空链表\n");
    printf("12. 获取链表长度\n");
    printf("13. 判断链表是否为空\n");
    printf("0. 退出系统\n");
    printf("请选择操作: ");
}

int main()
{
    StudentList studentList;
    int choice, position;
    char id[20], name[50];
    Student *student, *foundStudent;

    // 初始化链表
    InitList(&studentList);

    while (1)
    {
        ShowMenu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 0:
            // 释放所有内存
            ClearList(&studentList);
            printf("感谢使用学生信息管理系统！\n");
            return 0;

        case 1:
            ClearList(&studentList);
            InitList(&studentList);
            break;

        case 2:
            PrintList(&studentList);
            break;

        case 3:
            student = InputStudent();
            if (student != NULL)
            {
                InsertAtEnd(&studentList, student);
            }
            break;

        case 4:
            student = InputStudent();
            if (student != NULL)
            {
                printf("请输入插入位置: ");
                scanf("%d", &position);
                InsertAtPosition(&studentList, student, position);
            }
            break;

        case 5:
            printf("请输入要删除的位置: ");
            scanf("%d", &position);
            DeleteAtPosition(&studentList, position);
            break;

        case 6:
            printf("请输入要删除的学号: ");
            scanf("%s", id);
            DeleteById(&studentList, id);
            break;

        case 7:
            printf("请输入要查找的位置: ");
            scanf("%d", &position);
            foundStudent = GetElem(&studentList, position);
            if (foundStudent != NULL)
            {
                printf("第%d个位置的学生信息:\n", position);
                printf("学号: %s, 姓名: %s, 性别: %s, 年龄: %d, 专业: %s, 成绩: %.2f\n",
                       foundStudent->id, foundStudent->name, foundStudent->gender,
                       foundStudent->age, foundStudent->major, foundStudent->score);
            }
            break;

        case 8:
            printf("请输入要查找的学号: ");
            scanf("%s", id);
            foundStudent = LocateById(&studentList, id);
            if (foundStudent != NULL)
            {
                printf("学号 %s 的学生信息:\n", id);
                printf("学号: %s, 姓名: %s, 性别: %s, 年龄: %d, 专业: %s, 成绩: %.2f\n",
                       foundStudent->id, foundStudent->name, foundStudent->gender,
                       foundStudent->age, foundStudent->major, foundStudent->score);
            }
            else
            {
                printf("未找到学号为 %s 的学生\n", id);
            }
            break;

        case 9:
            printf("请输入要查找的姓名: ");
            scanf("%s", name);
            SearchByName(&studentList, name);
            break;

        case 10:
            printf("请输入要修改的学号: ");
            scanf("%s", id);
            student = InputStudent();
            if (student != NULL)
            {
                ModifyStudent(&studentList, id, student);
                free(student);
            }
            break;

        case 11:
            ClearList(&studentList);
            break;

        case 12:
            printf("链表当前长度: %d\n", GetLength(&studentList));
            break;

        case 13:
            if (IsEmpty(&studentList))
            {
                printf("链表为空\n");
            }
            else
            {
                printf("链表不为空\n");
            }
            break;

        default:
            printf("无效的选择，请重新输入！\n");
            break;
        }
    }

    return 0;
}

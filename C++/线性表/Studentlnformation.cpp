#include <iostream>
#include <cstdio>
#include <cstring> 
using namespace std;

#define MAX 100

struct Student {
    int id;
    int studentID;
    char name[32];
    char gender[8];
    char className[32];
    char phonenumber[20];
};

class StudentList {
public:
    Student students[MAX];
    int length = 0;

    void init() {
        length = 0;
        cout << "初始化完成！" << endl;
    }

    void addStudent() {
        if (length >= MAX) {
            cout << "学生数量已达上限！" << endl;
            return;
        }
        Student s;
        cout << "请输入学号: ";
        cin >> s.studentID;
        cout << "请输入姓名: ";
        cin >> s.name;
        cout << "请输入性别: ";
        cin >> s.gender;
        cout << "请输入班级: ";
        cin >> s.className;
        cout << "请输入手机号: ";
        cin >> s.phonenumber;
        s.id = length + 1;
        students[length++] = s;
        cout << "添加成功！" << endl;
    }

void showAll() {
    cout << "编号    学号        姓名        性别    班级        手机号" << endl;
    for (int i = 0; i < length; i++) {
        cout << students[i].id << "    "
             << students[i].studentID << "    ";

        // 姓名补足宽度
        cout << students[i].name;
        int nameLen = strlen(students[i].name);
        for (int k = 0; k < 10 - nameLen * 2; k++) cout << " ";

        cout << students[i].gender;
        int genderLen = strlen(students[i].gender);
        for (int k = 0; k < 8 - genderLen * 2; k++) cout << " ";

        cout << students[i].className;
        int classLen = strlen(students[i].className);
        for (int k = 0; k < 10 - classLen * 2; k++) cout << " ";

        cout << students[i].phonenumber << endl;
    }
}

    void findStudent() {
        int sid;
        cout << "请输入要查找的学号: ";
        cin >> sid;
        for (int i = 0; i < length; i++) {
            if (students[i].studentID == sid) {
                printf("找到学生: %d  %d  %s  %s  %s  %s\n",
                    students[i].id,
                    students[i].studentID,
                    students[i].name,
                    students[i].gender,
                    students[i].className,
                    students[i].phonenumber);
                return;
            }
        }
        cout << "未找到该学生！" << endl;
    }

    void deleteStudent() {
        int sid;
        cout << "请输入要删除的学号: ";
        cin >> sid;
        for (int i = 0; i < length; i++) {
            if (students[i].studentID == sid) {
                for (int j = i; j < length - 1; j++) {
                    students[j] = students[j + 1];
                }
                length--;
                cout << "删除成功！" << endl;
                return;
            }
        }
        cout << "未找到该学生！" << endl;
    }

    void modifyStudent() {
        int sid;
        cout << "请输入要修改的学号: ";
        cin >> sid;
        for (int i = 0; i < length; i++) {
            if (students[i].studentID == sid) {
                cout << "请输入新姓名: ";
                cin >> students[i].name;
                cout << "请输入新性别: ";
                cin >> students[i].gender;
                cout << "请输入新班级: ";
                cin >> students[i].className;
                cout << "请输入新手机号: ";
                cin >> students[i].phonenumber;
                cout << "修改成功！" << endl;
                return;
            }
        }
        cout << "未找到该学生！" << endl;
    }

    void clearList() {
        length = 0;
        cout << "已清空所有学生信息！" << endl;
    }

    void saveToFile(const char* filename) {
        FILE* fp = fopen(filename, "w");
        if (!fp) {
            cout << "文件保存失败！" << endl;
            return;
        }
        for (int i = 0; i < length; i++) {
            fprintf(fp, "%d %d %s %s %s %s\n",
                students[i].id,
                students[i].studentID,
                students[i].name,
                students[i].gender,
                students[i].className,
                students[i].phonenumber);
        }
        fclose(fp);
        cout << "保存到文件成功！" << endl;
    }

    void loadFromFile(const char* filename) {
        FILE* fp = fopen(filename, "r");
        if (!fp) {
            cout << "文件读取失败！" << endl;
            return;
        }
        length = 0;
        Student s;
        while (fscanf(fp, "%d %d %s %s %s %s",
            &s.id, &s.studentID, s.name, s.gender, s.className, s.phonenumber) == 6) {
            students[length++] = s;
        }
        fclose(fp);
        cout << "读取文件成功！" << endl;
    }

    void clearScreen() {
        for (int i = 0; i < 50; i++) cout << endl;
    }

    void modifyID() {
        int sid, newID;
        cout << "请输入要修改编号的学号: ";
        cin >> sid;
        for (int i = 0; i < length; i++) {
            if (students[i].studentID == sid) {
                cout << "当前编号为: " << students[i].id << endl;
                cout << "请输入新编号: ";
                cin >> newID;
                students[i].id = newID;
                cout << "编号修改成功！" << endl;
                return;
            }
        }
        cout << "未找到该学生！" << endl;
    }
};

int main() {
    StudentList list;
    int choice;
    const char* filename = "students.txt";
    while (true) {
        cout << "\n学生信息管理系统" << endl;
        cout << "1. 初始化" << endl;
        cout << "2. 输出" << endl;
        cout << "3. 插入" << endl;
        cout << "4. 删除" << endl;
        cout << "5. 修改" << endl;
        cout << "6. 查找" << endl;
        cout << "7. 清空" << endl;
        cout << "8. 读文件" << endl;
        cout << "9. 写文件" << endl;
        cout << "10. 修改编号" << endl;
        cout << "0. 清屏" << endl;
        cout << "886. 退出" << endl;
        cout << "请选择: ";
        cin >> choice;
        switch (choice) {
            case 1: list.init(); break;
            case 2: list.showAll(); break;
            case 3: list.addStudent(); break;
            case 4: list.deleteStudent(); break;
            case 5: list.modifyStudent(); break;
            case 6: list.findStudent(); break;
            case 7: list.clearList(); break;
            case 8: list.loadFromFile(filename); break;
            case 9: list.saveToFile(filename); break;
            case 10: list.modifyID(); break;
            case 0: list.clearScreen(); break;
            case 886: return 0;
            default: cout << "无效选择！" << endl;
        }
    }
    return 0;
}
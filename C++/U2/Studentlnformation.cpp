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
        cout << "��ʼ����ɣ�" << endl;
    }

    void addStudent() {
        if (length >= MAX) {
            cout << "ѧ�������Ѵ����ޣ�" << endl;
            return;
        }
        Student s;
        cout << "������ѧ��: ";
        cin >> s.studentID;
        cout << "����������: ";
        cin >> s.name;
        cout << "�������Ա�: ";
        cin >> s.gender;
        cout << "������༶: ";
        cin >> s.className;
        cout << "�������ֻ���: ";
        cin >> s.phonenumber;
        s.id = length + 1;
        students[length++] = s;
        cout << "��ӳɹ���" << endl;
    }

void showAll() {
    cout << "���    ѧ��        ����        �Ա�    �༶        �ֻ���" << endl;
    for (int i = 0; i < length; i++) {
        cout << students[i].id << "    "
             << students[i].studentID << "    ";

        // ����������
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
        cout << "������Ҫ���ҵ�ѧ��: ";
        cin >> sid;
        for (int i = 0; i < length; i++) {
            if (students[i].studentID == sid) {
                printf("�ҵ�ѧ��: %d  %d  %s  %s  %s  %s\n",
                    students[i].id,
                    students[i].studentID,
                    students[i].name,
                    students[i].gender,
                    students[i].className,
                    students[i].phonenumber);
                return;
            }
        }
        cout << "δ�ҵ���ѧ����" << endl;
    }

    void deleteStudent() {
        int sid;
        cout << "������Ҫɾ����ѧ��: ";
        cin >> sid;
        for (int i = 0; i < length; i++) {
            if (students[i].studentID == sid) {
                for (int j = i; j < length - 1; j++) {
                    students[j] = students[j + 1];
                }
                length--;
                cout << "ɾ���ɹ���" << endl;
                return;
            }
        }
        cout << "δ�ҵ���ѧ����" << endl;
    }

    void modifyStudent() {
        int sid;
        cout << "������Ҫ�޸ĵ�ѧ��: ";
        cin >> sid;
        for (int i = 0; i < length; i++) {
            if (students[i].studentID == sid) {
                cout << "������������: ";
                cin >> students[i].name;
                cout << "���������Ա�: ";
                cin >> students[i].gender;
                cout << "�������°༶: ";
                cin >> students[i].className;
                cout << "���������ֻ���: ";
                cin >> students[i].phonenumber;
                cout << "�޸ĳɹ���" << endl;
                return;
            }
        }
        cout << "δ�ҵ���ѧ����" << endl;
    }

    void clearList() {
        length = 0;
        cout << "���������ѧ����Ϣ��" << endl;
    }

    void saveToFile(const char* filename) {
        FILE* fp = fopen(filename, "w");
        if (!fp) {
            cout << "�ļ�����ʧ�ܣ�" << endl;
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
        cout << "���浽�ļ��ɹ���" << endl;
    }

    void loadFromFile(const char* filename) {
        FILE* fp = fopen(filename, "r");
        if (!fp) {
            cout << "�ļ���ȡʧ�ܣ�" << endl;
            return;
        }
        length = 0;
        Student s;
        while (fscanf(fp, "%d %d %s %s %s %s",
            &s.id, &s.studentID, s.name, s.gender, s.className, s.phonenumber) == 6) {
            students[length++] = s;
        }
        fclose(fp);
        cout << "��ȡ�ļ��ɹ���" << endl;
    }

    void clearScreen() {
        for (int i = 0; i < 50; i++) cout << endl;
    }

    void modifyID() {
        int sid, newID;
        cout << "������Ҫ�޸ı�ŵ�ѧ��: ";
        cin >> sid;
        for (int i = 0; i < length; i++) {
            if (students[i].studentID == sid) {
                cout << "��ǰ���Ϊ: " << students[i].id << endl;
                cout << "�������±��: ";
                cin >> newID;
                students[i].id = newID;
                cout << "����޸ĳɹ���" << endl;
                return;
            }
        }
        cout << "δ�ҵ���ѧ����" << endl;
    }
};

int main() {
    StudentList list;
    int choice;
    const char* filename = "students.txt";
    while (true) {
        cout << "\nѧ����Ϣ����ϵͳ" << endl;
        cout << "1. ��ʼ��" << endl;
        cout << "2. ���" << endl;
        cout << "3. ����" << endl;
        cout << "4. ɾ��" << endl;
        cout << "5. �޸�" << endl;
        cout << "6. ����" << endl;
        cout << "7. ���" << endl;
        cout << "8. ���ļ�" << endl;
        cout << "9. д�ļ�" << endl;
        cout << "10. �޸ı��" << endl;
        cout << "0. ����" << endl;
        cout << "886. �˳�" << endl;
        cout << "��ѡ��: ";
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
            default: cout << "��Чѡ��" << endl;
        }
    }
    return 0;
}
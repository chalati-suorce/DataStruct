#include <stdio.h>

#define MAX 100

typedef struct {
    int id;
    int studentID;
    char name[20];
    char gender[20];
    char className[20];
    char phonenumber[12];
} Student;

typedef struct {
    Student students[MAX];
    int length;
} StudentList;

// ��ʼ��ѧ���б�
void init(StudentList *list) {
    list->length = 0;
    printf("��ʼ����ɣ�\n");
}

// ���ѧ��
void addStudent(StudentList *list) {
    if (list->length >= MAX) {
        printf("ѧ�������Ѵ����ޣ�\n");
        return;
    }
    Student s;
    printf("������ѧ��: ");
    scanf("%d", &s.studentID);
    printf("����������: ");
    scanf("%s", s.name);
    printf("�������Ա�: ");
    scanf("%s", s.gender);
    printf("������༶: ");
    scanf("%s", s.className);
    printf("�������ֻ���: ");
    scanf("%s", s.phonenumber);
    s.id = list->length + 1;
    list->students[list->length++] = s;
    printf("��ӳɹ���\n");
}

// ��ʾ����ѧ��
void showAll(StudentList *list) {
    printf("%-6s %-10s %-10s %-8s %-10s %-12s\n", "���", "ѧ��", "����", "�Ա�", "�༶", "�ֻ���");
    for (int i = 0; i < list->length; i++) {
        Student s = list->students[i];
        printf("%-6d %-10d %-10s %-8s %-10s %-12s\n", s.id, s.studentID, s.name, s.gender, s.className, s.phonenumber);
    }
}

// ��ѧ�Ų���ѧ��
void findStudent(StudentList *list) {
    int sid;
    printf("������Ҫ���ҵ�ѧ��: ");
    scanf("%d", &sid);
    for (int i = 0; i < list->length; i++) {
        if (list->students[i].studentID == sid) {
            Student s = list->students[i];
            printf("�ҵ�ѧ��: %d\t%d\t%s\t%s\t%s\t%s\n", s.id, s.studentID, s.name, s.gender, s.className, s.phonenumber);
            return;
        }
    }
    printf("δ�ҵ���ѧ����\n");
}

// ɾ��ѧ��
void deleteStudent(StudentList *list) {
    int sid, found = 0;
    printf("������Ҫɾ����ѧ��: ");
    scanf("%d", &sid);
    for (int i = 0; i < list->length; i++) {
        if (list->students[i].studentID == sid) {
            for (int j = i; j < list->length - 1; j++) {
                list->students[j] = list->students[j + 1];
            }
            list->length--;
            found = 1;
            printf("ɾ���ɹ���\n");
            break;
        }
    }
    if (!found) {
        printf("δ�ҵ���ѧ����\n");
    }
}

// �޸�ѧ����Ϣ
void modifyStudent(StudentList *list) {
    int sid;
    printf("������Ҫ�޸ĵ�ѧ��: ");
    scanf("%d", &sid);
    for (int i = 0; i < list->length; i++) {
        if (list->students[i].studentID == sid) {
            printf("������������: ");
            scanf("%s", list->students[i].name);
            printf("���������Ա�: ");
            scanf("%s", list->students[i].gender);
            printf("�������°༶: ");
            scanf("%s", list->students[i].className);
            printf("���������ֻ���: ");
            scanf("%s", list->students[i].phonenumber);
            printf("�޸ĳɹ���\n");
            return;
        }
    }
    printf("δ�ҵ���ѧ����\n");
}

// ���ѧ���б�
void clearList(StudentList *list) {
    list->length = 0;
    printf("���������ѧ����Ϣ��\n");
}

// ���浽�ļ�
void saveToFile(StudentList *list, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("�ļ�����ʧ�ܣ�\n");
        return;
    }
    for (int i = 0; i < list->length; i++) {
        Student s = list->students[i];
        fprintf(fp, "%d %d %s %s %s %s\n", s.id, s.studentID, s.name, s.gender, s.className, s.phonenumber);
    }
    fclose(fp);
    printf("���浽�ļ��ɹ���\n");
}

// ���ļ���ȡ
void loadFromFile(StudentList *list, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("�ļ���ȡʧ�ܣ�\n");
        return;
    }
    list->length = 0;
    Student s;
    while (fscanf(fp, "%d %d %s %s %s %s", &s.id, &s.studentID, s.name, s.gender, s.className, s.phonenumber) == 6) {
        list->students[list->length++] = s;
    }
    fclose(fp);
    printf("��ȡ�ļ��ɹ���\n");
}

// ����
void clearScreen() {
    for (int i = 0; i < 50; i++) {
        printf("\n");
    }
}

void modifyID(StudentList *list) {
    int oldID, newID, found = 0;
    printf("������Ҫ�޸ı�ŵ�ѧ��: ");
    scanf("%d", &oldID);
    for (int i = 0; i < list->length; i++) {
        if (list->students[i].studentID == oldID) {
            printf("��ǰ���Ϊ: %d\n", list->students[i].id);
            printf("�������±��: ");
            scanf("%d", &newID);
            list->students[i].id = newID;
            printf("����޸ĳɹ���\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("δ�ҵ���ѧ����\n");
    }
}

// ...existing code...

int main() {
    StudentList list;
    int choice;
    char filename[100] = "students.txt";
    while (1) {
        printf("\nС��ѧ����Ϣ����ϵͳ\n");
        printf("1. ��ʼ��\n");
        printf("2. ���\n");
        printf("3. ����\n");
        printf("4. ɾ��\n");
        printf("5. �޸�\n");
        printf("6. ����\n");
        printf("7. ���\n");
        printf("8. ���ļ�\n");
        printf("9. д�ļ�\n");
        printf("10. �޸ı��\n"); // �����˵���
        printf("0. ����\n");
        printf("886. �˳�\n");
        printf("��ѡ��: ");
        scanf("%d", &choice);
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
            case 10: modifyID(&list); break; // ��������
            case 0: clearScreen(); break;
            case 886: return 0;
            default: printf("��Чѡ��\n");
        }
    }
    return 0;
}
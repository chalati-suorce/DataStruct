#include<stdio.h>

typedef int elemtype;

#define MAX 1000

typedef struct{
    char studentid[10];
    char name[20];
    char gendar;
    float GPA;
    char class[10];
    int phone[11];
}student;

typedef struct{
    elemtype student[MAX];
    int length;
}studentlist;

 void init(studentlist*List){
    List->length=0;
 }

 //增加学生
int add(studentlist *L,student stu){
    if(L->length>=MAX){
    printf("学生数量已达上限");
}
for(int i=0;i<L->length;i++){
    if(L->student[i].studentid==){

    }
}

}

int main(){
    return 0;
}
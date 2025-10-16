#include<stdio.h>
#include<stdlib.h>

#define n 1000//n个数据元素

typedef int elemtype;

struct studentinformartion{
    char id[6];
    char name[20];
    char sex;
    int age;
    char class[20];
    char phone[12];
};

struct student{
    struct studentinformartion data[n];//1、建立一个顺序表，利用一维数组来存储，含有n个数据元素；
    int length;
}s;

//顺序表初始化
void initlist(struct student *list){
    list->length = 0;
}

//顺序表插入
int insertlist(struct student *list,struct studentinformartion data,int i){
    if(list->length==n){
        printf("顺序表已满，无法插入新数据！\n");
        return 0;
    }
    if(i<1||i>list->length+1){
        printf("插入位置无效");
    }
     
printf("请输入要插入的位置(1~%d):",list->length+1);
}

int main(){

    return 0;
}
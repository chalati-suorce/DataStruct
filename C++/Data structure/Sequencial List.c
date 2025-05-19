#include<stdio.h>
#define INIT_SIZE 100

typedef int Elemptype;//元素类型

typedef struct{
    Elemptype *List;
    int length;
    int capacity;//顺序表初始容量
}Seqlist;

//顺序表初始化
void init(Seqlist *L){
    L->List=(Seqlist*)malloc(INIT_SIZE*sizeof(Elemptype));
    if(L->List==NULL)//“!L->List等价于L->List==NULL”
    {
        printf("内存分配失败。\n");
        exit(1);//结束程序运行
    }
    L->length=0;
    L->capacity=INIT_SIZE;
}

void add(){

}

int main(){

    return 0;
}
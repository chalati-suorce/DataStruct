#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 病人结构体
typedef struct Patient {
    int id;             // 病人编号
    char name[50];      // 病人姓名
    int age;            // 病人年龄
    char symptom[100];  // 症状描述
    time_t arrivalTime; // 到达时间
    struct Patient* next; // 指向下一个病人的指针
} Patient;

// 队列结构体
typedef struct Queue {
    Patient* front;     // 队首指针
    Patient* rear;      // 队尾指针
    int size;           // 队列大小
} Queue;

// 初始化队列
void initQueue(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}

// 判断队列是否为空
int isEmpty(Queue* queue) {
    return queue->front == NULL;
}

// 入队操作 - 病人排队
void enqueue(Queue* queue, Patient* patient) {
    if (queue->rear == NULL) {
        // 队列为空
        queue->front = patient;
        queue->rear = patient;
    } else {
        // 队列不为空，添加到队尾
        queue->rear->next = patient;
        queue->rear = patient;
    }
    patient->next = NULL;
    queue->size++;
    printf("病人 %s (编号: %d) 已成功排队，当前排队人数: %d\n", 
           patient->name, patient->id, queue->size);
}

// 出队操作 - 病人就诊
Patient* dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("队列为空，没有病人等待就诊\n");
        return NULL;
    }
    
    Patient* patient = queue->front;
    queue->front = queue->front->next;
    
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    
    queue->size--;
    return patient;
}

// 查看队首病人
Patient* peek(Queue* queue) {
    if (isEmpty(queue)) {
        return NULL;
    }
    return queue->front;
}

// 显示当前排队情况
void displayQueue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("当前没有病人排队\n");
        return;
    }
    
    printf("\n=== 当前排队情况 ===\n");
    printf("总排队人数: %d\n", queue->size);
    printf("排队顺序:\n");
    
    Patient* current = queue->front;
    int position = 1;
    
    while (current != NULL) {
        struct tm* timeinfo = localtime(&current->arrivalTime);
        char timeStr[20];
        strftime(timeStr, sizeof(timeStr), "%H:%M:%S", timeinfo);
        
        printf("%d. 编号: %d, 姓名: %s, 年龄: %d, 症状: %s, 到达时间: %s\n",
               position, current->id, current->name, current->age, 
               current->symptom, timeStr);
        current = current->next;
        position++;
    }
    printf("===================\n");
}

// 创建新病人
Patient* createPatient(int id, const char* name, int age, const char* symptom) {
    Patient* patient = (Patient*)malloc(sizeof(Patient));
    if (patient == NULL) {
        printf("内存分配失败\n");
        return NULL;
    }
    
    patient->id = id;
    strcpy(patient->name, name);
    patient->age = age;
    strcpy(patient->symptom, symptom);
    patient->arrivalTime = time(NULL);
    patient->next = NULL;
    
    return patient;
}

// 释放病人内存
void freePatient(Patient* patient) {
    if (patient != NULL) {
        free(patient);
    }
}

int main() {
    Queue queue;
    initQueue(&queue);
    
    int patientId = 1;
    int choice;
    
    printf("=== 医院挂号系统 ===\n");
    
    while (1) {
        printf("\n请选择操作:\n");
        printf("1. 病人排队挂号\n");
        printf("2. 医生叫号就诊\n");
        printf("3. 查看当前排队情况\n");
        printf("4. 查看下一个就诊病人\n");
        printf("5. 退出系统\n");
        printf("请选择 (1-5): ");
        
        if (scanf("%d", &choice) != 1) {
            printf("输入无效，请重新输入\n");
            while (getchar() != '\n'); // 清空输入缓冲区
            continue;
        }
        
        switch (choice) {
            case 1: {
                // 病人排队
                char name[50];
                int age;
                char symptom[100];
                
                printf("\n请输入病人信息:\n");
                printf("姓名: ");
                scanf("%s", name);
                printf("年龄: ");
                scanf("%d", &age);
                printf("症状描述: ");
                scanf("%s", symptom);
                
                Patient* patient = createPatient(patientId++, name, age, symptom);
                if (patient != NULL) {
                    enqueue(&queue, patient);
                }
                break;
            }
            
            case 2: {
                // 医生叫号就诊
                Patient* patient = dequeue(&queue);
                if (patient != NULL) {
                    struct tm* timeinfo = localtime(&patient->arrivalTime);
                    char timeStr[20];
                    strftime(timeStr, sizeof(timeStr), "%H:%M:%S", timeinfo);
                    
                    printf("\n=== 就诊通知 ===\n");
                    printf("请病人 %s (编号: %d) 到诊室就诊\n", patient->name, patient->id);
                    printf("年龄: %d, 症状: %s\n", patient->age, patient->symptom);
                    printf("到达时间: %s\n", timeStr);
                    printf("================\n");
                    
                    freePatient(patient);
                }
                break;
            }
            
            case 3: {
                // 查看排队情况
                displayQueue(&queue);
                break;
            }
            
            case 4: {
                // 查看下一个就诊病人
                Patient* patient = peek(&queue);
                if (patient != NULL) {
                    struct tm* timeinfo = localtime(&patient->arrivalTime);
                    char timeStr[20];
                    strftime(timeStr, sizeof(timeStr), "%H:%M:%S", timeinfo);
                    
                    printf("\n=== 下一个就诊病人 ===\n");
                    printf("编号: %d, 姓名: %s, 年龄: %d\n", 
                           patient->id, patient->name, patient->age);
                    printf("症状: %s, 到达时间: %s\n", patient->symptom, timeStr);
                    printf("预计等待时间: 约 %d 分钟\n", queue.size * 5);
                    printf("====================\n");
                } else {
                    printf("当前没有病人等待就诊\n");
                }
                break;
            }
            
            case 5: {
                // 退出系统，释放所有内存
                printf("系统退出中...\n");
                while (!isEmpty(&queue)) {
                    Patient* patient = dequeue(&queue);
                    freePatient(patient);
                }
                printf("系统已退出，感谢使用！\n");
                return 0;
            }
            
            default:
                printf("无效选择，请重新输入 (1-5)\n");
                break;
        }
    }
    
    return 0;
}

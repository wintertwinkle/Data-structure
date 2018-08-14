/**
 * 该文件定义单链表的数据结构和对单链表的基本操作
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "common.h"

struct LinkList {
    ElemType data; // 数据域
    LinkList *next; //　指针域
};

// 函数声明
Status ListInsert(struct LinkList *head, int i, ElemType data){
    struct LinkList *newNode;
    struct LinkList *currentPointer;
    int index = 1;

    currentPointer = head;

    while(currentPointer && index < i){
        currentPointer = currentPointer->next;
        ++index;
    }

    // 创建新节点
    newNode = (struct LinkList *)malloc(sizeof (struct LinkList));
    newNode->data = data;

    newNode->next = currentPointer->next;
    currentPointer->next = newNode;

    return OK;
}
Status ListDelete(struct LinkList *head, int i){
    struct LinkList *currentPointer;
    int index = 1;

    while(currentPointer && index < i){
        currentPointer = currentPointer->next;
        ++index;
    }

    currentPointer->next = currentPointer->next->next;
    
}
ElemType GetElem(struct LinkList *head, int i){
    // p为头指针
    struct LinkList *currentPointer;
    int index = 1;

    currentPointer = head->next;
    // 从单链表头部出发，直到currentPointer指向要找寻的节点
    while(currentPointer && index < i){
        currentPointer = currentPointer->next;
        ++index;
    }

    if(index + 1 != i){
        printf("要找选的节点不存在\n");
        exit(ERROR);
    }

    return currentPointer->data;
}



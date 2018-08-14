/**
 * 该文件定义顺序表的数据结构和对顺序表的基本操作
 */

#include <stdio.h>
#include <stdlib.h> // 为malloc，free提供函数原型
#include <time.h> // 为time()提供函数原型
#include "common.h"

#define LIST_INIT_SIZE 100  // 线性表存储空间的初始分配量
#define LISTINCREMENT 10    // 线性表存储空间的分配增量

struct SqList {
	ElemType *elem; // 存储空间基址
	int length;		// 线性表当前长度
	int listsize;	// 线性表当前分配的存储容量(以sizeof(ElemType)为单位)
};

// 函数声明
Status InitList(struct SqList *l);
Status DestroyList(struct SqList *l);
Status ClearList(struct SqList *l);
Status ListInsert(struct SqList *l, int i, ElemType e);
ElemType ListDelete(struct SqList *l, int i);
int ListLength(struct SqList *l);
Status ListEmpty(struct SqList *l);
ElemType GetElem(struct SqList *l, int i);
// 返回L中第一个与e满足关系compare()的数据元素的位序
int LocateElem(struct SqList *l, ElemType e, int type, Status (*compare)(ElemType e1, ElemType e2, int type));
ElemType PriorElem(struct SqList *l, ElemType e);
ElemType NextElem(struct SqList *l, ElemType e);
void Print(struct SqList *l);
Status compare(ElemType e1, ElemType e2, int type);
void Init(struct SqList *l);




// 函数定义

Status InitList(struct SqList *l){
	l->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!l->elem) {
		printf("线性表初始化失败！\n\n");
		exit(OVERFLOW);
	}
	l->length = 0;
	l->listsize = LIST_INIT_SIZE;
	printf("线性表初始化成功!\n\n");

	return OK;
}

Status DestroyList(struct SqList *l){
	free(l->elem);
	l->length = 0;
	l->listsize = 0;

	printf("线性表已销毁!\n");
	return OK;
}

Status ClearList(struct SqList *l){
	l->length = 0;
	printf("线性表已清空!\n");

	return OK;
}

//插入，这里的i从1开始
Status ListInsert(struct SqList *l, int i, ElemType e){
	// 判断插入位置是否合法
	if (i < 1 || i > l->length + 1) {
		printf("插入位置非法！\n\n");
		exit(ERROR);
	}
	// 判断线性表是否内存空间已满,如果已满，动态增加空间
	if (l->length >= l->listsize) {
		ElemType *newbase;
		newbase = (ElemType *)realloc(l->elem, (l->listsize + LISTINCREMENT) * sizeof(ElemType));
		if (!newbase) {
			printf("内存分配失败！\n\n");
			exit(OVERFLOW);
		}
		l->elem = newbase;
		l->listsize += LISTINCREMENT;
	}
	// 插入算法
	for (int j = l->length; j >= i - 1; j--) {
		l->elem[j + 1] = l->elem[j];
	}
	l->elem[i - 1] = e;
	l->length++;
	// printf("插入%d到第%d位成功！\n\n", e, i);

	return OK;
}

ElemType ListDelete(struct SqList *l, int i){
	int RetVal;

	if(i < 1 || i > l->length){
		printf("删除位置非法！\n\n");
		exit(ERROR);
	}

	RetVal = l->elem[i - 1];
	for(i; i < l->length; i++){
		l->elem[i - 1] = l->elem[i];
	}
	l->length--;

	printf("删除%d成功!\n\n", RetVal);

	return RetVal;
}

int ListLength(struct SqList *l){
	// printf("该表长度为:%d\n\n", l->length);
	return l->length;
}

Status ListEmpty(struct SqList *l){
	if(l->length == 0)
		printf("该表是空表！\n\n");
	else
		printf("该表不为空!\n\n");

	return l->length == 0 ? TRUE : FALSE;
}

ElemType GetElem(struct SqList *l, int i){
	// printf("第%d个元素是%d\n\n", i, l->elem[i - 1]);

	return l->elem[i - 1];
}

int LocateElem(struct SqList *l, ElemType e, int type, Status (*compare)(ElemType e1, ElemType e2, int type)){
	int i = 1;

	while(i <= l->length && !compare(e, l->elem[i - 1], type))
		i++;
	if(i <= l->length){
		printf("满足关系的第一个元素的位置为%d\n\n", i);
		return i;
	}else{
		printf("在该表中没有找到符合条件的元素!\n\n");
		return 0;
	}
}

ElemType PriorElem(struct SqList *l, ElemType e){
	ElemType RetVal = 0;
	int index;

	for(index = 0; index < l->length; index++){
		if(e == l->elem[index] && index != 0){
			printf("%d的前驱元素是%d\n\n", e, l->elem[index - 1]);
			RetVal =  l->elem[index - 1];
		}
	}

	return RetVal;
}

ElemType NextElem(struct SqList *l, ElemType e){
	ElemType RetVal = 0;
	int index;

	for(index = 0; index < l->length; index++){
		if(e == l->elem[index] && index != l->length - 1){
			printf("%d的前驱元素是%d\n\n", e, l->elem[index + 1]);
			RetVal =  l->elem[index + 1];
		}
	}

	return RetVal;
}

// 打印线性表
void Print(struct SqList *l){
	printf("开始打印线性表：\n");
	for(int i = 0; i < l->length; i++){
		printf("%d ", l->elem[i]);
	}
	printf("\n打印结束!\n\n");
}
// compare函数
Status compare(ElemType e1, ElemType e2, int type){
	switch(type){
		//e1 > e2
		case 0:
			return e1 > e2 ? TRUE : FALSE;
		// e1 = e2
		case 1:
			return e1 == e2 ? TRUE : FALSE;
		// e1 < e2
		case 2:
			return e1 < e2 ? TRUE : FALSE;
		default:
			return ERROR;
	}
}
// 初始化一个线性表并随机插入5~10个随机数到数组中
void Init(struct SqList *l){
	int insertLength;
	ElemType insertNumber;

	InitList(l);

	// 插入数量
	insertLength = rand() % 5 + 5;
	// 插入随机元素
	for(int i = 1; i <= insertLength; i++){
		insertNumber = rand() % 100;
		ListInsert(l, i, insertNumber);
	}
}
//　初始化一个按从小到大顺序排列的顺序表
void InitSeq(struct SqList *l){
	int insertNumber = rand() % 5 + 5;

	InitList(l);

	for(int i = 1; i <= insertNumber; i++)
		ListInsert(l, i, i);
}

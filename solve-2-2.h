#include "SqList.h"

// 函数声明
void Union(struct SqList *l1, struct SqList *l2);
void MergeList(struct SqList *l1, struct SqList *l2, struct SqList *l3);
ElemType DeleteMin(struct SqList *l);
void Reverse(struct SqList *l);
void DeleteX(struct SqList *l, ElemType x);
void DeleteX_2(struct SqList *l, ElemType x);
void DeleteX_s_t(struct SqList*l, ElemType s, ElemType t);

// 函数定义
void Union(struct SqList *l1, struct SqList *l2){
	int l1_len = ListLength(l1);
	int l2_len = ListLength(l2);
	ElemType elem;

	// Union的时间复杂度为O(l2_len*l1_len)
	for(int i = 1; i <= l2_len; i++){
		elem = GetElem(l2, i);
		if(!LocateElem(l1, elem, 1, compare))
			ListInsert(l1, ++l1_len, elem);
	}
}
void MergeList(struct SqList *l1, struct SqList *l2, struct SqList *l3){
	int index1 = 1;
	int index2 = 1;
	int index3 = 1;
	int l1_len = ListLength(l1);
	int l2_len = ListLength(l2);
	ElemType l1_elem;
	ElemType l2_elem;

	InitList(l3);

	// MergeList的时间复杂度为O(l1_len+l2_len)
	while(index1 <= l1_len && index2 <= l2_len){
		l1_elem = GetElem(l1, index1);
		l2_elem = GetElem(l2, index2);

		if(l1_elem <= l2_elem){
			ListInsert(l3, index3++, l1_elem);
			index1++;
		}else{
			ListInsert(l3, index3++, l2_elem);
			index2++;
		}
	}

	//插入剩余元素
	while(index1 <= l1_len){
		l1_elem = GetElem(l1, index1++);
		ListInsert(l3, index3++, l1_elem);
	}
	while(index2 <= l2_len){
		l2_elem = GetElem(l2, index2++);
		ListInsert(l3, index3++, l2_elem);
	}
}

//************************* 王道数据结构算法题 *************************//

/**
 * 1.
 * 从顺序表中删除具有最小值的元素(假设唯一)并由函数返回被删元素的值。
 * 空出的位置由最后一个元素填补，若顺序表为空则显示出错信息并退出运行
 */
ElemType DeleteMin(struct SqList *l){
	ElemType RetVal = GetElem(l, 1);
	ElemType TmpElem;
	int index = 0;
	int locate = 0;
	int length = ListLength(l);

	if(!length){
		printf("表为空！\n");
		exit(ERROR);
	}

	// 遍历整个表找到最小值，同时记录最小值坐标
	for(index; index < length; index++){
		TmpElem = GetElem(l, index + 1);
		if(RetVal > TmpElem){
			RetVal = TmpElem;
			locate = index;
		}
	}

	// 删除最小值
	l->elem[locate] = l->elem[length - 1];
	l->length--;
	
	return RetVal;
}
/**
 * 2.
 * 设计一个高效的算法，将顺序表的所有元素逆转，要求算法的空间复杂度为O(1)
 */
void Reverse(struct SqList *l){
	int head = 0;
	int tail = ListLength(l) - 1;
	ElemType TmpElem;

	if(tail == -1){
		printf("表为空！\n");
		exit(ERROR);
	}

	while(head < tail){
		TmpElem = l->elem[head];
		l->elem[head] = l->elem[tail];
		l->elem[tail] = TmpElem;
		head++;
		tail--;
	}
}
/**
 * 3.
 * 长度为n的顺序表L,编写一个时间复杂度为O(n)，空间复杂度为O(1)的算法，
 * 该算法删除线性表中所有值为x的数据元素
 */
void DeleteX(struct SqList *l, ElemType x){
	int length = ListLength(l);
	int record = 0;

	for(int i = 0; i < length; i++){
		if(l->elem[i] != x){
			l->elem[record] = l->elem[i];
			record++;
		}
	}
	l->length = record;
}
void DeleteX_2(struct SqList *l, ElemType x){
	int length = ListLength(l);
	int record = 0;
	int i = 0;

	while(i < length){
		if(l->elem[i] == x)
			record++;
		else
			l->elem[i - record] = l->elem[i];

		i++;
	}
	l->length = length - record; 
}
/**
 * 4.
 * 从有序顺序表中删除其值在给定值s和t之间(要求s<t)的所有元素，如果s或t不合理或者顺序表为空则显示出错信息并退出运行。
 */
void DeleteX_st1(struct SqList *l, ElemType s, ElemType t){
	int i = 0;
	int length = ListLength(l);

	if(s >= t){
		printf("所给参数不合理:s>=t!\n");
		exit(ERROR);
	}

	if(l->length == 0){
		printf("该表为空表！\n");
		exit(ERROR);
	}

	while(i < length){
		if(l->elem[i] > s && l->elem[i] < t){
			ListDelete(l, i + 1);
			length--;
		}else{
			i++;
		}
	}
}
//　有bug
void DeleteX_st2(struct SqList *l, ElemType s, ElemType t){
	int head = 0;
	int tail = ListLength(l) - 1;
	int minus = 0;

	if(s >= t){
		printf("所给参数不合理:s>=t!\n");
		exit(ERROR);
	}

	if(l->length == 0){
		printf("该表为空表！\n");
		exit(ERROR);
	}
	
	while(l->elem[head] < s)
		head++;
	while(l->elem[tail] > t)
		tail--;
	
	printf("head=%d  ", head);
	printf("tail=%d\n", tail);
	

	minus = tail - head - 1;

	while(tail < ListLength(l)){
		printf("tail=%d  : ", tail);
		printf("%d=%d\n", l->elem[head], l->elem[tail]);
		l->elem[++head] = l->elem[tail++];
	}
	
	l->length -= minus;
}
void DeleteX_st3(struct SqList *l, ElemType s, ElemType t){
	int i, j;
	
	if(s >= t || l->length == 0)
		exit(ERROR);

	for(i = 0; i < ListLength(l) && l->elem[i] < s; i++);

	if(i >= ListLength(l))
		exit(OK);

	for(j = i; j < ListLength(l) && l->elem[j] > t; j++);

	for(; j < ListLength(l); i++, j++)
		l->elem[i] = l->elem[j];

	l->length = i + 1;
}
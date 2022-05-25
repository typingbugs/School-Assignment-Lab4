//存放与排序功能相关的功能函数

#include"Lab4_data.h"


/**
 * 函数功能：为给二维数组使用qsort编写的cmp函数
 * 输入参数：比较的两个长度为3的一维数组的地址const void* a、const void* b
 * 返回值：<0（不进行置换） / >0（进行置换） / 0（不进行置换）
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月18日
*/
int cmp_for_2d_array_qsort(const void* a, const void* b)
{
	return ((int*)a)[2] - ((int*)b)[2];
}


/**
 * 函数功能：为给二维数组使用qsort编写的cmp函数（逆序）
 * 输入参数：比较的两个长度为3的一维数组的地址const void* a、const void* b
 * 返回值：<0(不进行置换) / >0(进行置换) / 0(不进行置换)
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月18日
*/
int cmp_reverse_for_2d_array_qsort(const void* a, const void* b)
{
	return ((int*)b)[2] - ((int*)a)[2];
}


/**
 * 函数功能：为给结构体数组使用qsort编写的cmp函数
 * 输入参数：比较的两个一维数组的地址const void* a、const void* b
 * 返回值：<0（不进行置换） / >0（进行置换） / 0（不进行置换）
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月20日
*/
int cmp_for_struct_array_qsort(const void* a, const void* b)
{
	return ((DATAITEM*)a)->item3 - ((DATAITEM*)b)->item3;
}


/**
 * 函数功能：为给结构体数组使用qsort编写的cmp函数（逆序）
 * 输入参数：比较的两个一维数组的地址const void* a、const void* b
 * 返回值：<0（不进行置换） / >0（进行置换） / 0（不进行置换）
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月20日
*/
int cmp_reverse_for_struct_array_qsort(const void* a, const void* b)
{
	return ((DATAITEM*)b)->item3 - ((DATAITEM*)a)->item3;
}


/**
 * 函数功能：为给指针数组使用qsort编写的cmp函数
 * 输入参数：比较的两个二维数组的地址const void** a、const void** b
 * 返回值：<0（不进行置换） / >0（进行置换） / 0（不进行置换）
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月20日
*/
int cmp_for_point_array_qsort(const void** a, const void** b)
{
	return (*(DATAITEM**)a)->item3 - (*(DATAITEM**)b)->item3;
}


/**
 * 函数功能：为给指针数组使用qsort编写的cmp函数（逆序）
 * 输入参数：比较的两个二维数组的地址const void** a、const void** b
 * 返回值：<0（不进行置换） / >0（进行置换） / 0（不进行置换）
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月20日
*/
int cmp_reverse_for_point_array_qsort(const void** a, const void** b)
{
	return (*(DATAITEM**)b)->item3 - (*(DATAITEM**)a)->item3;
}


/**
 * 函数功能：对单链表使用冒泡排序
 * 输入参数：单链表头节点（value为空）NODE* head，链表长度dataNum，是否逆序reverse
 * 返回值：无
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月20日
*/
void bubble_for_link_list(NODE* head, int dataNum, int reverse)
{
	NODE* p, * q, * r;
	for (int count1 = 0; count1 < dataNum - 1; count1++)
	{
		p = head;
		q = head->next;
		r = q->next;
		int count2 = dataNum - 1 - count1;
		while (count2--)
		{
			if ((q->value3 > r->value3 && reverse == 0) || (q->value3 < r->value3 && reverse == 1))
			{
				q->next = r->next;
				r->next = q;
				p->next = r;
			}
			p = p->next;
			q = p->next;
			r = q->next;
		}

	}
}
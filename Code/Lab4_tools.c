//存储模块常用的而主函数不调用的工具函数

#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"Lab4_data.h"


/**
 * 函数功能：将numArr中的存储数据记录条数检查是否合法，合法转化为数字
 * 输入参数：存储数字信息的字符串numArr
 * 返回值：合法转化数字结果num，有非数字字符返回-2，超出范围返回-1
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年4月11日
*/
int str_to_int(char* numArr)
{
	int dataNum = 0;
	for (int i = 0; i < strlen(numArr); i++)
	{
		if (numArr[i] > '9' || numArr[i] < '0')
		{
			return -2;
		}
		else if (i == 9 && dataNum > 214748364)
		{
			return -1;
		}
		else if (i == 9 && dataNum == 214748364 && numArr[i] - '0' > 7)
		{
			return -1;
		}
		else
		{
			dataNum *= 10;
			dataNum += numArr[i] - '0';
		}	//按位读取数据行数
	}
	return dataNum;
}


/**
 * 函数功能：释放指针数组的每个元素指向的空间
 * 输入参数：结构体数组地址DATAITEM** data，数据记录条数dataNum
 * 返回值：无
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月20日
*/
void free_data_in_point_array(DATAITEM** data, int dataNum)
{
	for (int i = 0; i < dataNum; i++)
	{
		free(data[i]);
	}
}


/**
 * 函数功能：释放单链表的空间
 * 输入参数：单链表头节点（value为空）NODE* head
 * 返回值：无
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月20日
*/
void free_data_in_link_list(NODE* head)
{
	NODE* p = head, * q = head->next;
	while (q != NULL)
	{
		free(p);
		p = q;
		q = q->next;
	}
}


/**
 * 函数功能：获取当前时间，输出格式：xx月xx日xx时xx分xx秒-xxxx年
 * 输入参数：存储当前时间的字符串
 * 返回值：无
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月18日
*/
void get_time(char* buffer)
{
	time_t timep;
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);
	int t[6] = { 0 };
	t[0] = 1 + p->tm_mon;	//月
	t[1] = p->tm_mday;	//日
	t[2] = (8 + p->tm_hour) % 24;	//时
	t[3] = p->tm_min;	//分
	t[4] = p->tm_sec;	//秒
	t[5] = 1900 + p->tm_year;	//年
	char numStr[6][6] = { 0 };
	numStr[2][0] = '0';
	numStr[3][0] = '0';
	numStr[4][0] = '0';
	char add[6][4] = { "月", "日","时", "分", "秒-" , "年" };
	for (int i = 0; i < 6; i++)
	{
		int temp1 = t[i], temp2 = t[i], j = 0, max = 0;
		for (; temp1; j++, temp1 /= 10)
			max++;
		max--;
		for (j = 0; temp2; j++, temp2 /= 10)
			numStr[i][max - j] = '0' + temp2 % 10;
		strcat(buffer, numStr[i]);
		strcat(buffer, add[i]);
	}
}
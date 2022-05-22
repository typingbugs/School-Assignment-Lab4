//�洢ģ�鳣�õĶ������������õĹ��ߺ���

#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"Lab4_data.h"


/**
 * �������ܣ���numArr�еĴ洢���ݼ�¼��������Ƿ�Ϸ����Ϸ�ת��Ϊ����
 * ����������洢������Ϣ���ַ���numArr
 * ����ֵ���Ϸ�ת�����ֽ��num���з������ַ�����-2��������Χ����-1
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��4��11��
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
		}	//��λ��ȡ��������
	}
	return dataNum;
}


/**
 * �������ܣ��ͷ�ָ�������ÿ��Ԫ��ָ��Ŀռ�
 * ����������ṹ�������ַDATAITEM** data�����ݼ�¼����dataNum
 * ����ֵ����
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��20��
*/
void free_data_in_point_array(DATAITEM** data, int dataNum)
{
	for (int i = 0; i < dataNum; i++)
	{
		free(data[i]);
	}
}


/**
 * �������ܣ��ͷŵ�����Ŀռ�
 * ���������������ͷ�ڵ㣨valueΪ�գ�NODE* head
 * ����ֵ����
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��20��
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
 * �������ܣ���ȡ��ǰʱ�䣬�����ʽ��xx��xx��xxʱxx��xx��-xxxx��
 * ����������洢��ǰʱ����ַ���
 * ����ֵ����
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��18��
*/
void get_time(char* buffer)
{
	time_t timep;
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);
	int t[6] = { 0 };
	t[0] = 1 + p->tm_mon;	//��
	t[1] = p->tm_mday;	//��
	t[2] = (8 + p->tm_hour) % 24;	//ʱ
	t[3] = p->tm_min;	//��
	t[4] = p->tm_sec;	//��
	t[5] = 1900 + p->tm_year;	//��
	char numStr[6][6] = { 0 };
	numStr[2][0] = '0';
	numStr[3][0] = '0';
	numStr[4][0] = '0';
	char add[6][4] = { "��", "��","ʱ", "��", "��-" , "��" };
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
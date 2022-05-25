//�������������صĹ��ܺ���

#include"Lab4_data.h"


/**
 * �������ܣ�Ϊ����ά����ʹ��qsort��д��cmp����
 * ����������Ƚϵ���������Ϊ3��һά����ĵ�ַconst void* a��const void* b
 * ����ֵ��<0���������û��� / >0�������û��� / 0���������û���
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��18��
*/
int cmp_for_2d_array_qsort(const void* a, const void* b)
{
	return ((int*)a)[2] - ((int*)b)[2];
}


/**
 * �������ܣ�Ϊ����ά����ʹ��qsort��д��cmp����������
 * ����������Ƚϵ���������Ϊ3��һά����ĵ�ַconst void* a��const void* b
 * ����ֵ��<0(�������û�) / >0(�����û�) / 0(�������û�)
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��18��
*/
int cmp_reverse_for_2d_array_qsort(const void* a, const void* b)
{
	return ((int*)b)[2] - ((int*)a)[2];
}


/**
 * �������ܣ�Ϊ���ṹ������ʹ��qsort��д��cmp����
 * ����������Ƚϵ�����һά����ĵ�ַconst void* a��const void* b
 * ����ֵ��<0���������û��� / >0�������û��� / 0���������û���
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��20��
*/
int cmp_for_struct_array_qsort(const void* a, const void* b)
{
	return ((DATAITEM*)a)->item3 - ((DATAITEM*)b)->item3;
}


/**
 * �������ܣ�Ϊ���ṹ������ʹ��qsort��д��cmp����������
 * ����������Ƚϵ�����һά����ĵ�ַconst void* a��const void* b
 * ����ֵ��<0���������û��� / >0�������û��� / 0���������û���
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��20��
*/
int cmp_reverse_for_struct_array_qsort(const void* a, const void* b)
{
	return ((DATAITEM*)b)->item3 - ((DATAITEM*)a)->item3;
}


/**
 * �������ܣ�Ϊ��ָ������ʹ��qsort��д��cmp����
 * ����������Ƚϵ�������ά����ĵ�ַconst void** a��const void** b
 * ����ֵ��<0���������û��� / >0�������û��� / 0���������û���
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��20��
*/
int cmp_for_point_array_qsort(const void** a, const void** b)
{
	return (*(DATAITEM**)a)->item3 - (*(DATAITEM**)b)->item3;
}


/**
 * �������ܣ�Ϊ��ָ������ʹ��qsort��д��cmp����������
 * ����������Ƚϵ�������ά����ĵ�ַconst void** a��const void** b
 * ����ֵ��<0���������û��� / >0�������û��� / 0���������û���
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��20��
*/
int cmp_reverse_for_point_array_qsort(const void** a, const void** b)
{
	return (*(DATAITEM**)b)->item3 - (*(DATAITEM**)a)->item3;
}


/**
 * �������ܣ��Ե�����ʹ��ð������
 * ���������������ͷ�ڵ㣨valueΪ�գ�NODE* head��������dataNum���Ƿ�����reverse
 * ����ֵ����
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��20��
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
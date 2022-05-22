//��Ž��洢���ڴ������е����ݼ�¼��ʾ�������Ļ�Ϲ��ܵ���غ���

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include"Lab4_tools.h"
#include"Lab4_sort.h"
#include"Lab4_data.h"
#include"Lab4_loadfile.h"


/**
 * �������ܣ���ʾѡ���û�/������ģʽ�Ĳ˵�����ȡ����
 * �����������
 * ����ֵ���û��������ݣ�int��
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��10��
*/
int show_menu_root()
{
	printf("+ ---- + ---------- +\n");
	printf("| ��� | ģʽ       |\n");
	printf("+ ---- + ---------- +\n");
	printf("|  1   | �û�ģʽ   |\n");
	printf("|  2   | ������ģʽ |\n");
	printf("+ ---- + ---------- +\n");
	char input[2];
	int ans = 1;
	do {
		do {
			if (ans > 2 || ans <= 0)
				printf("�����������\n���������빦�ܶ�Ӧ����ţ�");
			else
				printf("�����빦�ܶ�Ӧ����ţ�");
			fgets(input, 2, stdin);
			int c;
			while ((c = getchar()) != '\n' && c != EOF)
				;
		} while (input[0] == '\n');	//���û����س���������������������
		ans = str_to_int(input);
	} while (ans > 2 || ans <= 0);
	return ans;
}


/**
 * �������ܣ���ʾ�û�ģʽ�Ĳ˵�����ȡ����
 * �����������
 * ����ֵ���û��������ݣ�int��
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��10��
*/
int show_menu_user()
{
	printf("+ ---- + ---------------- +\n");
	printf("| ��� | ģʽ             |\n");
	printf("+ ---- + ---------------- +\n");
	printf("|  1   | �Զ�ģʽ         |\n");
	printf("|  2   | ����ģʽ         |\n");
	printf("|  3   | �鿴�������ݼ�¼ |\n");
	printf("|  0   | �˳�             |\n");
	printf("+ ---- + ---------------- +\n");
	char input[2];
	int ans = 1;
	do {
		do {
			if (ans > 3 || ans < 0)
				printf("�����������\n���������빦�ܶ�Ӧ����ţ�");
			else
				printf("�����빦�ܶ�Ӧ����ţ�");
			fgets(input, 2, stdin);
			int c;
			while ((c = getchar()) != '\n' && c != EOF)
				;
		} while (input[0] == '\n');	//���û����س���������������������
		ans = str_to_int(input);
	} while (ans > 3 || ans < 0);
	return ans;
}


/**
 * �������ܣ���ʾ������ģʽ�Ĳ˵�����ȡ����
 * �����������
 * ����ֵ���û��������ݣ�int��
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��10��
*/
int show_menu_developer()
{
	printf("+ ---- + ------------ +\n");
	printf("| ��� | ����         |\n");
	printf("+ ---- + ------------ +\n");
	printf("|  1   | �޸������ļ� |\n");
	printf("|  2   | ���г���     |\n");
	printf("|  0   | �˳�         |\n");
	printf("+ ---- + ------------ +\n");
	char input[2];
	int ans = 1;
	do {
		do {
			if (ans > 2 || ans < 0)
				printf("�����������\n���������빦�ܶ�Ӧ����ţ�");
			else
				printf("�����빦�ܶ�Ӧ����ţ�");
			fgets(input, 2, stdin);
			int c;
			while ((c = getchar()) != '\n' && c != EOF)
				;
		} while (input[0] == '\n');	//���û����س���������������������
		ans = str_to_int(input);
	} while (ans > 2 || ans < 0);
	return ans;
}


/**
 * �������ܣ�ѯ���û��Ƿ�鿴���ɵ����ݼ�¼�ļ�
 * �����������
 * ����ֵ���û��������ݣ�1-Y��0-N��
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��17��
*/
int show_menu_ask_if_read_file()
{
	char input[2] = "Y";
	do {
		if (input[0] != 'Y' && input[0] != 'N')
			printf("�����������������롣\n�Ƿ�鿴���ɵ����ݼ�¼�ļ�����Y\\N����");
		else
			printf("�Ƿ�鿴���ɵ����ݼ�¼�ļ�����Y\\N����");
		fgets(input, 2, stdin);
		int c;
		while ((c = getchar()) != '\n' && c != EOF)
			;
	} while (input[0] != 'Y' && input[0] != 'N');	//���û����س���������������������
	if (input[0] == 'Y')
		return 1;
	else
		return 0;
}


/**
 * �������ܣ�ѯ���û�ѡ���ά����/�ṹ������/ָ������/����洢
 * �����������
 * ����ֵ���û��������ݣ�int��
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��17��
*/
int show_menu_ask_how_to_store()
{
	printf("+ ---- + ---------- +\n");
	printf("| ��� | �洢��ʽ   |\n");
	printf("+ ---- + ---------- +\n");
	printf("|  1   | ��ά����   |\n");
	printf("|  2   | �ṹ������ |\n");
	printf("|  3   | ָ������   |\n");
	printf("|  4   | ����       |\n");
	printf("+ ---- + ---------- +\n");
	char input[2];
	int ans = 1;
	do {
		do {
			if (ans > 4 || ans <= 0)
				printf("�����������\n���������빦�ܶ�Ӧ����ţ�");
			else
				printf("�����빦�ܶ�Ӧ����ţ�");
			fgets(input, 2, stdin);
			int c;
			while ((c = getchar()) != '\n' && c != EOF)
				;
		} while (input[0] == '\n');	//���û����س���������������������
		ans = str_to_int(input);
	} while (ans > 4 || ans <= 0);
	return ans;
}


/**
 * �������ܣ�������ģʽѯ���û����г���ʱ�Ƿ��ʱ
 * �����������
 * ����ֵ���û��������ݣ�1-Y��0-N��
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��10��
*/
static int show_menu_timeCount()
{
	char input[2] = "Y";
	do {
		if (input[0] != 'Y' && input[0] != 'N')
			printf("�����������������롣\n�Ƿ��ʱ���У���Y\\N����");
		else
			printf("�Ƿ��ʱ���У���Y\\N����");
		fgets(input, 2, stdin);
		int c;
		while ((c = getchar()) != '\n' && c != EOF)
			;
	} while (input[0] != 'Y' && input[0] != 'N');	//���û����س���������������������
	if (input[0] == 'Y')
		return 1;
	else
		return 0;
}


/**
 * �������ܣ�ѯ���û�ѡ���ʱ����ǰ����Ԥ����ʽ
 * �����������
 * ����ֵ���û��������ݣ�int��
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��18��
*/
static int show_menu_ask_data_status_before_sort()
{
	printf("+ ---- + ---------- +\n");
	printf("| ��� | ���ݼ����� |\n");
	printf("+ ---- + ---------- +\n");
	printf("|  1   | ����       |\n");
	printf("|  2   | ����       |\n");
	printf("|  3   | �����     |\n");
	printf("+ ---- + ---------- +\n");
	char input[2];
	int ans = 1;
	do {
		do {
			if (ans > 3 || ans <= 0)
				printf("�����������\n���������빦�ܶ�Ӧ����ţ�");
			else
				printf("�����빦�ܶ�Ӧ����ţ�");
			fgets(input, 2, stdin);
			int c;
			while ((c = getchar()) != '\n' && c != EOF)
				;
		} while (input[0] == '\n');	//���û����س���������������������
		ans = str_to_int(input);
	} while (ans > 3 || ans <= 0);
	return ans;
}


/**
 * �������ܣ�ѯ���û�ѡ������ʽ
 * �����������
 * ����ֵ���û��������ݣ�int��
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��18��
*/
static int show_menu_ask_sort_method()
{
	printf("+ ---- + -------- +\n");
	printf("| ��� | ����ʽ |\n");
	printf("+ ---- + -------- +\n");
	printf("|  1   | �������� |\n");
	printf("|  2   | ð������ |\n");
	printf("+ ---- + -------- +\n");
	char input[2];
	int ans = 1;
	do {
		do {
			if (ans > 2 || ans <= 0)
				printf("�����������\n���������빦�ܶ�Ӧ����ţ�");
			else
				printf("�����빦�ܶ�Ӧ����ţ�");
			fgets(input, 2, stdin);
			int c;
			while ((c = getchar()) != '\n' && c != EOF)
				;
		} while (input[0] == '\n');	//���û����س���������������������
		ans = str_to_int(input);
	} while (ans > 2 || ans <= 0);
	return ans;
}


/**
 * �������ܣ���ӡ��ά��������
 * �����������ά�����ַint(*data)[3]�����ݼ�¼����dataNum
 * ����ֵ����
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��18��
*/
static void print_data_in_2d_array(int(*data)[3], int dataNum)
{
	for (int i = 0; i < dataNum; i++)
	{
		printf("%5d ", data[i][0]);
		printf("%5d ", data[i][1]);
		printf("%5d\n", data[i][2]);
	}
}


/**
 * �������ܣ���ӡ�ṹ����������
 * ����������ṹ�������ַDATAITEM* data�����ݼ�¼����dataNum
 * ����ֵ����
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��20��
*/
static void print_data_in_struct_array(DATAITEM* data, int dataNum)
{
	for (int i = 0; i < dataNum; i++)
	{
		printf("%5d ", data[i].item1);
		printf("%5d ", data[i].item2);
		printf("%5d\n", data[i].item3);
	}
}


/**
 * �������ܣ���ӡָ����������
 * ����������ṹ�������ַDATAITEM** data�����ݼ�¼����dataNum
 * ����ֵ����
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��20��
*/
static void print_data_in_point_array(DATAITEM** data, int dataNum)
{
	for (int i = 0; i < dataNum; i++)
	{
		printf("%5d ", data[i]->item1);
		printf("%5d ", data[i]->item2);
		printf("%5d\n", data[i]->item3);
	}
}


/**
 * �������ܣ���ӡ��������
 * ���������������ͷ�ڵ㣨valueΪ�գ�NODE* head
 * ����ֵ����
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��20��
*/
static void print_data_in_link_list(NODE* head)
{
	NODE* p = head;
	while (p->next != NULL)
	{
		p = p->next;
		printf("%5d ", p->value1);
		printf("%5d ", p->value2);
		printf("%5d\n", p->value3);
	}
}


/**
 * �������ܣ�����չʾ���ݼ�¼����ά���飩
 * ������������ݼ�¼�ļ�·�����ļ���filename���ļ�ָ��fp���û�/������ģʽrootMode
 * ����ֵ����
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��18��
*/
void show_data_in_2d_array(char* filename, FILE* fp, int rootMode)
{
	int dataNum;
	char numArr[MAX_INT_LEN + 1];
	if (fgets(numArr, MAX_INT_LEN + 1, fp) == NULL)
	{
		printf("���ݼ�¼�����������ݼ�¼�ļ���\n");
		exit(0);
	}
	int len = strlen(numArr);
	if (numArr[len - 1] == '\n')
		numArr[len - 1] = '\0';	//ɾȥ����Ļس�
	dataNum = str_to_int(numArr);
	if (dataNum < 0)
	{
		printf("���ݼ�¼�����������ݼ�¼�ļ���\n");
		exit(0);
	}
	int(*data)[3] = (int(*)[3])malloc(sizeof(int) * 3 * dataNum);
	if (data == NULL)
	{
		printf("���ִ��󣺶�̬�����ڴ�ʧ�ܡ�\n");
		exit(0);
	}
	store_data_in_2d_array(data, fp, dataNum);
	if (rootMode == 2)
	{
		if (show_menu_timeCount())
		{
			int ans = show_menu_ask_data_status_before_sort();
			if (ans == 1)
				qsort(data, dataNum, 3 * sizeof(int), cmp_for_2d_array_qsort);
			else if (ans == 2)
				qsort(data, dataNum, 3 * sizeof(int), cmp_reverse_for_2d_array_qsort);
			char dataStatus[3][5] = { "����","����","����" };
			if (show_menu_ask_sort_method() == 1)
			{
				clock_t startTime, finishTime;
				double totalTime = 0;
				startTime = clock();
				qsort(data, dataNum, sizeof(data[0]), cmp_for_2d_array_qsort);
				finishTime = clock();
				totalTime = (double)(finishTime - startTime) / CLOCKS_PER_SEC;
				char timeBuffer[30] = { 0 };
				get_time(timeBuffer);
				print_data_in_2d_array(data, dataNum);
				printf("��������%d�����ݣ���ʱ%lf�롣", dataNum, totalTime);
				FILE* log;
				log = fopen("Log.csv", "a+");
				if (log == NULL)
				{
					printf("��־�ļ���ʧ�ܣ��޷���������ʱ������־��\n");
					exit(0);
				}
				fprintf(log, "��ά����,%d��,%s,��������,%lf��,%s\n", dataNum, dataStatus[ans - 1], totalTime, timeBuffer);
				fclose(log);
			}
			else
			{
				clock_t startTime, finishTime;
				double totalTime = 0;
				startTime = clock();
				for (int i = 0; i < dataNum - 1; i++)
				{
					for (int j = 0; j < dataNum - i - 1; j++)
					{
						if (data[j][2] > data[j + 1][2])
						{
							int temp = data[j + 1][2];
							data[j + 1][2] = data[j][2];
							data[j][2] = temp;
						}
					}
				}
				finishTime = clock();
				totalTime = (double)(finishTime - startTime) / CLOCKS_PER_SEC;
				char timeBuffer[30] = { 0 };
				get_time(timeBuffer);
				print_data_in_2d_array(data, dataNum);
				printf("ð������%d�����ݣ���ʱ%lf�롣", dataNum, totalTime);
				FILE* log;
				log = fopen("Log.csv", "a+");
				if (log == NULL)
				{
					printf("��־�ļ���ʧ�ܣ��޷���������ʱ������־��\n");
					exit(0);
				}
				fprintf(log, "��ά����,%d��,%s,ð������,%lf��,%s\n", dataNum, dataStatus[ans - 1], totalTime, timeBuffer);
				fclose(log);
			}
		}
		else
		{
			qsort(data, dataNum, 3 * sizeof(int), cmp_for_2d_array_qsort);
			print_data_in_2d_array(data, dataNum);
		}
	}
	else
	{
		qsort(data, dataNum, 3 * sizeof(int), cmp_for_2d_array_qsort);
		print_data_in_2d_array(data, dataNum);
	}
	free(data);
}


/**
 * �������ܣ�����չʾ���ݼ�¼���ṹ�����飩
 * ������������ݼ�¼�ļ�·�����ļ���filename���ļ�ָ��fp���û�/������ģʽrootMode
 * ����ֵ����
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��20��
*/
void show_data_in_struct_array(char* filename, FILE* fp, int rootMode)
{
	int dataNum;
	char numArr[MAX_INT_LEN + 1];
	if (fgets(numArr, MAX_INT_LEN + 1, fp) == NULL)
	{
		printf("���ݼ�¼�����������ݼ�¼�ļ���\n");
		exit(0);
	}
	int len = strlen(numArr);
	if (numArr[len - 1] == '\n')
		numArr[len - 1] = '\0';	//ɾȥ����Ļس�
	dataNum = str_to_int(numArr);
	if (dataNum < 0)
	{
		printf("���ݼ�¼�����������ݼ�¼�ļ���\n");
		exit(0);
	}
	DATAITEM* data = (DATAITEM*)malloc(sizeof(DATAITEM) * dataNum);
	if (data == NULL)
	{
		printf("���ִ��󣺶�̬�����ڴ�ʧ�ܡ�\n");
		exit(0);
	}
	store_data_in_struct_array(data, fp, dataNum);
	if (rootMode == 2)
	{
		if (show_menu_timeCount())
		{
			int ans = show_menu_ask_data_status_before_sort();
			if (ans == 1)
				qsort(data, dataNum, sizeof(data[0]), cmp_for_struct_array_qsort);
			else if (ans == 2)
				qsort(data, dataNum, sizeof(data[0]), cmp_reverse_for_struct_array_qsort);
			char dataStatus[3][5] = { "����","����","����" };
			if (show_menu_ask_sort_method() == 1)
			{
				clock_t startTime, finishTime;
				double totalTime = 0;
				startTime = clock();
				qsort(data, dataNum, sizeof(data[0]), cmp_for_struct_array_qsort);
				finishTime = clock();
				totalTime = (double)(finishTime - startTime) / CLOCKS_PER_SEC;
				char timeBuffer[30] = { 0 };
				get_time(timeBuffer);
				print_data_in_struct_array(data, dataNum);
				printf("��������%d�����ݣ���ʱ%lf�롣", dataNum, totalTime);
				FILE* log;
				log = fopen("Log.csv", "a+");
				if (log == NULL)
				{
					printf("��־�ļ���ʧ�ܣ��޷���������ʱ������־��\n");
					exit(0);
				}
				fprintf(log, "�ṹ������,%d��,%s,��������,%lf��,%s\n", dataNum, dataStatus[ans - 1], totalTime, timeBuffer);
				fclose(log);
			}
			else
			{
				clock_t startTime, finishTime;
				double totalTime = 0;
				startTime = clock();
				for (int i = 0; i < dataNum - 1; i++)
				{
					for (int j = 0; j < dataNum - i - 1; j++)
					{
						if (data[j].item3 > data[j + 1].item3)
						{
							int temp = data[j + 1].item3;
							data[j + 1].item3 = data[j].item3;
							data[j].item3 = temp;
						}
					}
				}
				finishTime = clock();
				totalTime = (double)(finishTime - startTime) / CLOCKS_PER_SEC;
				char timeBuffer[30] = { 0 };
				get_time(timeBuffer);
				print_data_in_struct_array(data, dataNum);
				printf("ð������%d�����ݣ���ʱ%lf�롣", dataNum, totalTime);
				FILE* log;
				log = fopen("Log.csv", "a+");
				if (log == NULL)
				{
					printf("��־�ļ���ʧ�ܣ��޷���������ʱ������־��\n");
					exit(0);
				}
				fprintf(log, "�ṹ������,%d��,%s,ð������,%lf��,%s\n", dataNum, dataStatus[ans - 1], totalTime, timeBuffer);
				fclose(log);
			}
		}
		else
		{
			qsort(data, dataNum, sizeof(data[0]), cmp_for_struct_array_qsort);
			print_data_in_struct_array(data, dataNum);
		}
	}
	else
	{
		qsort(data, dataNum, sizeof(data[0]), cmp_for_struct_array_qsort);
		print_data_in_struct_array(data, dataNum);
	}
	free(data);
}


/**
 * �������ܣ�����չʾ���ݼ�¼��ָ�����飩
 * ������������ݼ�¼�ļ�·�����ļ���filename���ļ�ָ��fp���û�/������ģʽrootMode
 * ����ֵ����
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��20��
*/
void show_data_in_point_array(char* filename, FILE* fp, int rootMode)
{
	int dataNum;
	char numArr[MAX_INT_LEN + 1];
	if (fgets(numArr, MAX_INT_LEN + 1, fp) == NULL)
	{
		printf("���ݼ�¼�����������ݼ�¼�ļ���\n");
		exit(0);
	}
	int len = strlen(numArr);
	if (numArr[len - 1] == '\n')
		numArr[len - 1] = '\0';	//ɾȥ����Ļس�
	dataNum = str_to_int(numArr);
	if (dataNum < 0)
	{
		printf("���ݼ�¼�����������ݼ�¼�ļ���\n");
		exit(0);
	}
	DATAITEM** data = (DATAITEM**)malloc(sizeof(DATAITEM*) * dataNum);
	if (data == NULL)
	{
		printf("���ִ��󣺶�̬�����ڴ�ʧ�ܡ�\n");
		exit(0);
	}
	store_data_in_point_array(data, fp, dataNum);
	if (rootMode == 2)
	{
		if (show_menu_timeCount())
		{
			int ans = show_menu_ask_data_status_before_sort();
			if (ans == 1)
				qsort(data, dataNum, sizeof(data[0]), cmp_for_point_array_qsort);
			else if (ans == 2)
				qsort(data, dataNum, sizeof(data[0]), cmp_reverse_for_point_array_qsort);
			char dataStatus[3][5] = { "����","����","����" };
			if (show_menu_ask_sort_method() == 1)
			{
				clock_t startTime, finishTime;
				double totalTime = 0;
				startTime = clock();
				qsort(data, dataNum, sizeof(data[0]), cmp_for_point_array_qsort);
				finishTime = clock();
				totalTime = (double)(finishTime - startTime) / CLOCKS_PER_SEC;
				char timeBuffer[30] = { 0 };
				get_time(timeBuffer);
				print_data_in_point_array(data, dataNum);
				printf("��������%d�����ݣ���ʱ%lf�롣", dataNum, totalTime);
				FILE* log;
				log = fopen("Log.csv", "a+");
				if (log == NULL)
				{
					printf("��־�ļ���ʧ�ܣ��޷���������ʱ������־��\n");
					exit(0);
				}
				fprintf(log, "ָ������,%d��,%s,��������,%lf��,%s\n", dataNum, dataStatus[ans - 1], totalTime, timeBuffer);
				fclose(log);
			}
			else
			{
				clock_t startTime, finishTime;
				double totalTime = 0;
				startTime = clock();
				for (int i = 0; i < dataNum - 1; i++)
				{
					for (int j = 0; j < dataNum - i - 1; j++)
					{
						if (data[j]->item3 > data[j + 1]->item3)
						{
							int temp = data[j + 1]->item3;
							data[j + 1]->item3 = data[j]->item3;
							data[j]->item3 = temp;
						}
					}
				}
				finishTime = clock();
				totalTime = (double)(finishTime - startTime) / CLOCKS_PER_SEC;
				char timeBuffer[30] = { 0 };
				get_time(timeBuffer);
				print_data_in_point_array(data, dataNum);
				printf("ð������%d�����ݣ���ʱ%lf�롣", dataNum, totalTime);
				FILE* log;
				log = fopen("Log.csv", "a+");
				if (log == NULL)
				{
					printf("��־�ļ���ʧ�ܣ��޷���������ʱ������־��\n");
					exit(0);
				}
				fprintf(log, "ָ������,%d��,%s,ð������,%lf��,%s\n", dataNum, dataStatus[ans - 1], totalTime, timeBuffer);
				fclose(log);
			}
		}
		else
		{
			qsort(data, dataNum, sizeof(data[0]), cmp_for_point_array_qsort);
			print_data_in_point_array(data, dataNum);
		}
	}
	else
	{
		qsort(data, dataNum, sizeof(data[0]), cmp_for_point_array_qsort);
		print_data_in_point_array(data, dataNum);
	}
	free_data_in_point_array(data, dataNum);
	free(data);
}


/**
 * �������ܣ�����չʾ���ݼ�¼������
 * ������������ݼ�¼�ļ�·�����ļ���filename���ļ�ָ��fp���û�/������ģʽrootMode
 * ����ֵ����
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��20��
*/
void show_data_in_link_list(char* filename, FILE* fp, int rootMode)
{
	int dataNum;
	char numArr[MAX_INT_LEN + 1];
	if (fgets(numArr, MAX_INT_LEN + 1, fp) == NULL)
	{
		printf("���ݼ�¼�����������ݼ�¼�ļ���\n");
		exit(0);
	}
	int len = strlen(numArr);
	if (numArr[len - 1] == '\n')
		numArr[len - 1] = '\0';	//ɾȥ����Ļس�
	dataNum = str_to_int(numArr);
	if (dataNum < 0)
	{
		printf("���ݼ�¼�����������ݼ�¼�ļ���\n");
		exit(0);
	}
	NODE* head = (NODE*)malloc(sizeof(NODE));
	head->next = NULL;
	if (head == NULL)
	{
		printf("���ִ��󣺶�̬�����ڴ�ʧ�ܡ�\n");
		exit(0);
	}
	store_data_in_link_list(head, fp, dataNum);
	if (rootMode == 2)
	{
		if (show_menu_timeCount())
		{
			int ans = show_menu_ask_data_status_before_sort();
			if (ans != 3)
			{
				bubble_for_link_list(head, dataNum, ans - 1);
			}
			printf("���ݼ�������ϣ����������������");
			getchar();
			char dataStatus[3][5] = { "����","����","����" };
			clock_t startTime, finishTime;
			double totalTime = 0;
			startTime = clock();
			bubble_for_link_list(head, dataNum, 0);
			finishTime = clock();
			totalTime = (double)(finishTime - startTime) / CLOCKS_PER_SEC;
			char timeBuffer[30] = { 0 };
			get_time(timeBuffer);
			print_data_in_link_list(head);
			printf("ð������%d�����ݣ���ʱ%lf�롣", dataNum, totalTime);
			FILE* log;
			log = fopen("Log.csv", "a+");
			if (log == NULL)
			{
				printf("��־�ļ���ʧ�ܣ��޷���������ʱ������־��\n");
				exit(0);
			}
			fprintf(log, "����,%d��,%s,ð������,%lf��,%s\n", dataNum, dataStatus[ans - 1], totalTime, timeBuffer);
			fclose(log);

		}
		else
		{
			bubble_for_link_list(head, dataNum, 0);
			print_data_in_link_list(head);
		}
	}
	else
	{
		bubble_for_link_list(head, dataNum, 0);
		print_data_in_link_list(head);
	}
	free_data_in_link_list(head);
}
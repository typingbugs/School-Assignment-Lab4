//�����ݶ�ȡ�����ݼ�����ع�������ĺ���

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>	//getcwd()/mkdir()
#include <sys/types.h>	//mkdir()
#include <sys/stat.h>	//mkdir()
#include <io.h>	//access()
#include "Lab4_data.h"
#include "Lab4_tools.h"

static void fget_file_path_and_name(char* s, FILE* fp);
static int fget_num(FILE* fp);
int check_filename(char* filename);
void create_path(char* filename);


/**
 * �������ܣ����Lab3.exe�Ƿ���ã�����conf.ini�ж�ȡ�������ݼ�¼�ļ������Ʋ���
 * ����������������ݼ�¼�ļ������Ʋ���ָ��CONF* pIni�����ݼ�¼�ļ�·�����ļ���filename
 * ����ֵ����
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��9��
*/
void self_check_and_get_configinfo(CONF* pIni, char* filename)
{
	printf("�ȴ������Լ�...");
	FILE* conf;

	if (access("Lab3.exe", 0))
	{
		printf("��������Lab3.exe�ļ���ʧ��\n");
		exit(0);
	}	//�ж��ܷ�ִ��Lab3.exe

	conf = fopen("conf.ini", "r");
	if (!conf)
	{
		printf("�������󣺴����ò����ļ�ʧ�ܣ�����ϵ����Ա�����\n");
		exit(0);
	}	//���ļ����ж��Ƿ�ɹ�

	fget_file_path_and_name(pIni->filesavepath, conf);
	fget_file_path_and_name(pIni->filename, conf);
	pIni->maxvalue1 = fget_num(conf);
	pIni->minvalue1 = fget_num(conf);
	pIni->maxvalue2 = fget_num(conf);
	pIni->minvalue2 = fget_num(conf);
	pIni->recordcount1 = fget_num(conf);
	pIni->recordcount2 = fget_num(conf);
	srand((unsigned)time(NULL));
	pIni->number = rand() % (pIni->recordcount1 - pIni->recordcount2 + 1) + pIni->recordcount2;
	fclose(conf);

	strncpy(filename, pIni->filesavepath, MAX_STR_LEN);
	strcpy(filename, "/");
	strncpy(filename, pIni->filename, MAX_STR_LEN);
	if (!check_filename(filename))
	{
		printf("�����������ò�����������ϵ����Ա�����\n");
		exit(0);
	}
	create_path(filename);
	int len = strlen(filename);
	FILE* fp;
	if (filename[len - 1] == 't')
	{
		fp = fopen(filename, "w+");
		if (!fp)
		{
			printf("�����������ò�����������ϵ����Ա�����\n");
			exit(0);
		}
	}
	else
	{
		fp = fopen(filename, "wb+");
		if (!fp)
		{
			printf("�����������ò�����������ϵ����Ա�����\n");
			exit(0);
		}
	}
	fclose(fp);

	printf("�Լ���ɡ�\n");
}


/**
 * �������ܣ����ļ�·��ת��Ϊ����·��
 * �����������¼�ļ����ĵ�ַfilename
 * ����ֵ��ִ�����error��1-·������0-·������
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��9��
*/
int change_Filename_to_absolute(char* filename)
{
	char tempFilename[2 * MAX_STR_LEN];
	strncpy(tempFilename, filename, 2 * MAX_STR_LEN);

	if (tempFilename[1] == ':')	//ԭ�����Ǿ���·��
		strcpy(filename, tempFilename);
	else
	{
		char* path = getcwd(NULL, 0);
		if (!path)
		{
			printf("�������󣡻�ȡ��ǰ·��ʧ�ܣ�\n");
			exit(0);
		}
		if (tempFilename[0] == '.' && tempFilename[1] == '.' && tempFilename[2] == '/')
		{
			int noError = 1;
			int i = 0;
			while (tempFilename[0 + i] == '.' && tempFilename[1 + i] == '.' && tempFilename[2 + i] == '/')
			{
				int j = strlen(path) - 1;
				while (path[j] != '\\')
				{
					if (path[j] == ':')	//������Ŀ¼�޷��ٽ�����һ��
					{
						printf("����������Ч·����\n");
						noError = 0;
						break;
					}
					j--;
				}
				if (!noError)	//�ļ�·����Ч
				{
					return 0;
				}
				path[j] = 0;
				i += 3;
			}
			if (noError)
			{
				i--;	//Ҫ����ǰ���һ��'/'
				strncpy(filename, path, MAX_STR_LEN);
				filename[MAX_STR_LEN - 1] = 0;
				strncat(filename, tempFilename + i, MAX_STR_LEN);
			}
		}
		else
		{
			strncpy(filename, path, MAX_STR_LEN);
			filename[MAX_STR_LEN - 1] = 0;
			strcat(filename, "/");
			filename[MAX_STR_LEN - 1] = 0;
			strncat(filename, tempFilename, MAX_STR_LEN);
		}

		free(path);
		return 1;
	}
}


/**
 * �������ܣ����·��δ�������򴴽�·��
 * �����������¼�ļ����ĵ�ַfilename
 * ����ֵ����
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��4��11��
*/
void create_path(char* filename)
{
	int len = strlen(filename);

	for (int i = 0; i < len; i++)
	{
		if (filename[i] == '\\' || filename[i] == '/')
		{
			char temp = filename[i];
			filename[i] = '\0';
			if (access(filename, 0) != 0)
				mkdir(filename);
			filename[i] = temp;
		}
	}
}


/**
 * �������ܣ�����ļ����Ƿ�Ϸ�
 * �����������¼�ļ����ĵ�ַfilename
 * ����ֵ���ļ�·���Ƿ�����error��1-·������0-·������
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��9��
*/
int check_filename(char* filename)
{
	int noError = 1;
	int len = strlen(filename);

	if (len <= 4)
		noError = 0;
	else if (strcmp(filename + len - 4, ".txt") != 0 && strcmp(filename + len - 4, ".bin") != 0)
		noError = 0;	//�жϺ�׺�Ƿ�Ϸ�
	else
	{
		for (int i = 0; i < len - 4; i++)
		{
			if (filename[i] == '<')
				noError = 0;
			else if (filename[i] == '>')
				noError = 0;
			else if (filename[i] == '|')
				noError = 0;
			else if (filename[i] == '*')
				noError = 0;
			else if (filename[i] == '?')
				noError = 0;
		}
	}	//�ж��ļ����Ƿ�Ϸ�
	if (!noError)
		return 0;
	else
		return 1;
}


/**
 * �������ܣ����ļ��ж�ȡ���ڴ�����ݼ�¼�ļ��Ĵ洢Ŀ¼���ļ������ַ���
 * ������������ڴ�����ݼ�¼�ļ��Ĵ洢Ŀ¼���ļ������ַ���s����ȡĿ���ļ�fp
 * ����ֵ����
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��4��11��
*/
static void fget_file_path_and_name(char* s, FILE* fp)
{
	int len;

	fgets(s, MAX_STR_LEN, fp);
	len = strlen(s);
	if (s[len - 1] == '\n')
		s[len - 1] = 0;	//ɾȥ����Ļس�
}


/**
 * �������ܣ����ļ��ж�ȡ�������ݼ�¼�ļ������Ʋ�����ת��Ϊ����
 * �����������ȡĿ���ļ�fp
 * ����ֵ���������ݼ�¼�ļ������Ʋ���num
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��4��11��
*/
static int fget_num(FILE* fp)
{
	int len, num = 0;
	char numArr[11];

	fgets(numArr, MAX_INT_LEN + 1, fp);
	len = strlen(numArr);
	if (numArr[len - 1] == '\n')
	{
		numArr[len - 1] = 0;	//ɾȥ����Ļس�
		len--;
	}

	num = str_to_int(numArr);
	if (num < 0)
	{
		printf("�ܱ�Ǹ���������ݳ��ִ�������ϵ����Ա�����\n");
		//��ʾconf.ini�����ݳ��ִ������ͷ�Χ�Ĵ���
		exit(0);
	}

	return num;
}


/**
 * �������ܣ���ȡ���ݼ�¼����
 * ������������ݼ�¼������Ϣ��״̬��ָ��pDataNumStatus���������ݼ�¼�ļ������Ʋ���ָ��CONF* pIni
 * ����ֵ�����ݼ�¼������int��
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��10��
*/
void get_dataNum(int* pDataNumStatus, CONF* pIni)
{
	int tempDataNum = pIni->number;
	char dataNumArr[MAX_INT_LEN + 1];
	do {
		do {
			if (tempDataNum == 0)
				printf("�����������������0���������������롣\n");
			else if (tempDataNum == -2)
				printf("����������ݼ�¼���������벻Ҫ������������ݡ�\n");
			else if (tempDataNum == -1)
				printf("����������ݼ�¼���������벻Ҫ�������2147483647�����ݡ�\n");

			if (*pDataNumStatus == 0)
				printf("ԭ���ݼ�¼����Ϊ��%d\n�޸�Ϊ��", pIni->number);
			else
				printf("���������ݼ�¼������");
			fgets(dataNumArr, MAX_INT_LEN + 1, stdin);
		} while (dataNumArr[0] == '\n');	//���û����س���������������������
		int len = strlen(dataNumArr);
		if (dataNumArr[len - 1] == '\n')
			dataNumArr[len - 1] = '\0';	//ɾȥ����Ļس�
		tempDataNum = str_to_int(dataNumArr);
	} while (tempDataNum <= 0);
	*pDataNumStatus = 1;
	pIni->number = tempDataNum;
}


/**
 * �������ܣ���ȡ�ļ�·��
 * ������������ݼ�¼�ļ�·����Ϣ��״̬��ָ��pFilenameStatus�����ݼ�¼�ļ�·�����ļ���filename
 * ����ֵ����
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��11��
*/
void get_filename(int* pFilenameStatus, char* filename)
{
	char tempFilename[MAX_STR_LEN * 2 + 1];
	strcpy(tempFilename, filename);
	int error = 0;
	do {
		do {
			if (error == 1)
			{
				if (*pFilenameStatus == 2)
					printf("�Ҳ�����������ļ������������롣\n");
				else
					printf("��������ļ�·�����ļ����������������롣\n");
			}

			if (*pFilenameStatus == 0)
				printf("ԭ���ݼ�¼�ļ�·��Ϊ��%s\n�޸�Ϊ��", filename);
			else
				printf("���������ݼ�¼�ļ�·����");
			fgets(tempFilename, MAX_STR_LEN * 2 + 1, stdin);
		} while (tempFilename[0] == '\n');	//���û����س���������������������
		error = 0;
		int len = strlen(tempFilename);
		if (tempFilename[len - 1] == '\n')
			tempFilename[len - 1] = '\0';	//ɾȥ����Ļس�
		if (check_filename(tempFilename) == 0)
		{
			error = 1;
			continue;
		}
		if (change_Filename_to_absolute(tempFilename) == 0)
		{
			error = 1;
			continue;
		}
		create_path(tempFilename);
		len = strlen(tempFilename);
		FILE* fp;
		if (tempFilename[len - 1] == 't')
		{
			if (*pFilenameStatus == 2)
				fp = fopen(tempFilename, "r+");
			else
				fp = fopen(tempFilename, "w+");
			if (!fp)
			{
				error = 1;
				continue;
			}
		}
		else
		{
			if (*pFilenameStatus == 2)
				fp = fopen(tempFilename, "rb+");
			else
				fp = fopen(tempFilename, "wb+");
			if (!fp)
			{
				error = 1;
				continue;
			}
		}
		fclose(fp);
	} while (error == 1);
	*pFilenameStatus = 1;
	strcpy(filename, tempFilename);
}


/**
 * �������ܣ����ļ���ȡ���ݽ���ά����
 * �����������ά�����ַint(*data)[3]���ļ�ָ��fp�����ݼ�¼����dataNum
 * ����ֵ����
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��18��
*/
void store_data_in_2d_array(int(*data)[3], FILE* fp, int dataNum)
{

	for (int i = 0; i < dataNum; i++)
	{
		char numArr[20];
		char* p = numArr;
		if (fgets(numArr, 20, fp) == NULL)
		{
			printf("���ݼ�¼�����������ݼ�¼�ļ���\n");
			exit(0);
		}
		for (int j = 0; j < 3; j++)
		{
			int k = 0;
			while (k < 6)
			{
				if (p[k] < '0' || p[k] > '9')
				{
					p[k] = '\0';
					break;
				}
				k++;
			}
			data[i][j] = str_to_int(p);
			if (data[i][j] < 0)
			{
				printf("���ݼ�¼�����������ݼ�¼�ļ���\n");
				exit(0);
			}
			p += k + 1;
		}
	}
}


/**
 * �������ܣ����ļ���ȡ���ݽ��ṹ������
 * ����������ṹ�������ַDATAITEM* data���ļ�ָ��fp�����ݼ�¼����dataNum
 * ����ֵ����
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��20��
*/
void store_data_in_struct_array(DATAITEM* data, FILE* fp, int dataNum)
{
	for (int i = 0; i < dataNum; i++)
	{
		char numArr[20];
		char* p = numArr;
		if (fgets(numArr, 20, fp) == NULL)
		{
			printf("���ݼ�¼�����������ݼ�¼�ļ���\n");
			exit(0);
		}
		for (int j = 0; j < 3; j++)
		{
			int k = 0;
			while (k < 6)
			{
				if (p[k] < '0' || p[k] > '9')
				{
					p[k] = '\0';
					break;
				}
				k++;
			}
			int a = str_to_int(p);
			if (a < 0)
			{
				printf("���ݼ�¼�����������ݼ�¼�ļ���\n");
				exit(0);
			}
			if (j == 0)
				data[i].item1 = a;
			else if (j == 1)
				data[i].item2 = a;
			else if (j == 2)
				data[i].item3 = a;
			p += k + 1;
		}
	}
}


/**
 * �������ܣ����ļ���ȡ���ݽ�ָ������
 * ����������ṹ�������ַDATAITEM** data���ļ�ָ��fp�����ݼ�¼����dataNum
 * ����ֵ����
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��20��
*/
void store_data_in_point_array(DATAITEM** data, FILE* fp, int dataNum)
{
	for (int i = 0; i < dataNum; i++)
	{
		data[i] = (DATAITEM*)malloc(sizeof(DATAITEM));
		if (data[i] == NULL)
		{
			printf("���ִ��󣺶�̬�����ڴ�ʧ�ܡ�\n");
			exit(0);
		}
		char numArr[20];
		char* p = numArr;
		if (fgets(numArr, 20, fp) == NULL)
		{
			printf("���ݼ�¼�����������ݼ�¼�ļ���\n");
			exit(0);
		}
		for (int j = 0; j < 3; j++)
		{
			int k = 0;
			while (k < 6)
			{
				if (p[k] < '0' || p[k] > '9')
				{
					p[k] = '\0';
					break;
				}
				k++;
			}
			int a = str_to_int(p);
			if (a < 0)
			{
				printf("���ݼ�¼�����������ݼ�¼�ļ���\n");
				exit(0);
			}
			if (j == 0)
				data[i]->item1 = a;
			else if (j == 1)
				data[i]->item2 = a;
			else if (j == 2)
				data[i]->item3 = a;
			p += k + 1;
		}
	}
}


/**
 * �������ܣ����ļ���ȡ���ݽ�������
 * ���������������ͷ�ڵ㣨valueΪ�գ�NODE* head���ļ�ָ��fp�����ݼ�¼����dataNum
 * ����ֵ����
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��20��
*/
void store_data_in_link_list(NODE* head, FILE* fp, int dataNum)
{
	NODE* q = head;
	for (int i = 0; i < dataNum; i++)
	{
		q->next = (NODE*)malloc(sizeof(NODE));
		if (q->next == NULL)
		{
			printf("���ִ��󣺶�̬�����ڴ�ʧ�ܡ�\n");
			exit(0);
		}
		q = q->next;
		q->next = NULL;
		char numArr[20];
		char* p = numArr;
		if (fgets(numArr, 20, fp) == NULL)
		{
			printf("���ݼ�¼�����������ݼ�¼�ļ���\n");
			exit(0);
		}
		for (int j = 0; j < 3; j++)
		{
			int k = 0;
			while (k < 6)
			{
				if (p[k] < '0' || p[k] > '9')
				{
					p[k] = '\0';
					break;
				}
				k++;
			}
			int a = str_to_int(p);
			if (a < 0)
			{
				printf("���ݼ�¼�����������ݼ�¼�ļ���\n");
				exit(0);
			}
			if (j == 0)
				q->value1 = a;
			else if (j == 1)
				q->value2 = a;
			else if (j == 2)
				q->value3 = a;
			p += k + 1;
		}
	}
}
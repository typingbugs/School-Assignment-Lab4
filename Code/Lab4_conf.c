//������޸������ļ���صĹ��ܺ���

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"Lab4_data.h"
#include"Lab4_loadfile.h"
#include"Lab4_tools.h"


/**
 * �������ܣ��޸������ļ�
 * ����������������ݼ�¼�ļ������Ʋ���ָ��CONF* pIni
 * ����ֵ����
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��13��
*/
void modify_configinfo(CONF* pIni)
{
	int ans = 0;
	do {
		int max = 0;
		FILE* fp;
		fp = fopen("conf.ini", "r");
		if (!fp)
		{
			printf("�������󣺴����ò����ļ�ʧ�ܡ�\n");
			exit(0);
		}	//���ļ�
		char arr[MAX_STR_LEN * 2 + 2];
		int len[8];
		for (int i = 0; i < 8; i++)
		{
			fgets(arr, MAX_STR_LEN * 2 + 2, fp);
			len[i] = strlen(arr) - 1;
			if (len[i] > max)
				max = len[i];
		}
		fclose(fp);
		printf("+ ---- + -------------------------------------- + ");
		for (int i = 0; i < max; i++)
			printf("-");
		printf(" +\n");
		printf("| ��� | ����                                   | ����");
		for (int i = 0; i < max - 4; i++)
			printf(" ");
		printf(" |\n");
		printf("+ ---- + -------------------------------------- + ");
		for (int i = 0; i < max; i++)
			printf("-");
		printf(" +\n");
		printf("|  1   | ���ݼ�¼�ļ��Ĵ洢Ŀ¼                 | ");
		printf("%s", pIni->filesavepath);
		for (int i = 0; i < max - len[0]; i++)
			printf(" ");
		printf(" |\n");
		printf("|  2   | ���ݼ�¼�ļ����ļ�����Ϣ               | ");
		printf("%s", pIni->filename);
		for (int i = 0; i < max - len[1]; i++)
			printf(" ");
		printf(" |\n");
		printf("|  3   | ���ݼ�¼��Ԫ���е�1��2��Ԫ��ȡֵ������ | ");
		printf("%d", pIni->maxvalue1);
		for (int i = 0; i < max - len[2]; i++)
			printf(" ");
		printf(" |\n");
		printf("|  4   | ���ݼ�¼��Ԫ���е�1��2��Ԫ��ȡֵ������ | ");
		printf("%d", pIni->minvalue1);
		for (int i = 0; i < max - len[3]; i++)
			printf(" ");
		printf(" |\n");
		printf("|  5   | ���ݼ�¼��Ԫ���е�3��Ԫ��ȡֵ������    | ");
		printf("%d", pIni->maxvalue2);
		for (int i = 0; i < max - len[4]; i++)
			printf(" ");
		printf(" |\n");
		printf("|  6   | ���ݼ�¼��Ԫ���е�3��Ԫ��ȡֵ������    | ");
		printf("%d", pIni->minvalue2);
		for (int i = 0; i < max - len[5]; i++)
			printf(" ");
		printf(" |\n");
		printf("|  7   | ��Ҫ������ɼ�¼����ʱ����ֵ������     | ");
		printf("%d", pIni->recordcount1);
		for (int i = 0; i < max - len[6]; i++)
			printf(" ");
		printf(" |\n");
		printf("|  8   | ��Ҫ������ɼ�¼����ʱ����ֵ������     | ");
		printf("%d", pIni->recordcount2);
		for (int i = 0; i < max - len[7] - 1; i++)
			printf(" ");
		printf(" |\n");
		printf("|  0   | �޸����                               | ");
		for (int i = 0; i < max; i++)
			printf(" ");
		printf(" |\n");
		printf("+ ---- + -------------------------------------- + ");
		for (int i = 0; i < max; i++)
			printf("-");
		printf(" +\n");

		char input[2];
		do {
			do {
				if (ans > 8 || ans < 0)
					printf("����ָ������\n������������ţ�");
				else
					printf("��������Ҫ��������ţ�");
				fgets(input, 2, stdin);
				int c;
				while ((c = getchar()) != '\n' && c != EOF)
					;
			} while (input[0] == '\n');	//���û����س���������������������
			ans = str_to_int(input);
		} while (ans > 8 || ans < 0);

		if (ans == 1 || ans == 2)
		{
			char tempFilesavepath[MAX_STR_LEN];
			char tempFilename[MAX_STR_LEN];
			char filename[MAX_STR_LEN * 2 + 1];
			if (ans == 1)
			{
				fgets(tempFilesavepath, MAX_STR_LEN, stdin);
				strcpy(tempFilename, pIni->filename);
			}
			else
			{
				fgets(tempFilename, MAX_STR_LEN, stdin);
				strcpy(tempFilesavepath, pIni->filesavepath);
			}
			strncpy(filename, tempFilesavepath, MAX_STR_LEN);
			strcpy(filename, "/");
			strncpy(filename, tempFilename, MAX_STR_LEN);
			if (!check_filename(filename))
			{
				if (ans == 1)
					printf("�޸�ʧ�ܣ���������ݼ�¼�ļ�·�����������²�����\n");
				else
					printf("�޸�ʧ�ܣ���������ݼ�¼�ļ������������²�����\n");
				continue;
			}
			create_path(filename);
			int len = strlen(filename);
			FILE* fp;
			if (filename[len - 1] == 't')
			{
				fp = fopen(filename, "w+");
				if (!fp)
				{
					if (ans == 1)
						printf("�޸�ʧ�ܣ���������ݼ�¼�ļ�·�����������²�����\n");
					else
						printf("�޸�ʧ�ܣ���������ݼ�¼�ļ������������²�����\n");
					continue;
				}
			}
			else
			{
				fp = fopen(filename, "wb+");
				if (!fp)
				{
					if (ans == 1)
						printf("�޸�ʧ�ܣ���������ݼ�¼�ļ�·�����������²�����\n");
					else
						printf("�޸�ʧ�ܣ���������ݼ�¼�ļ������������²�����\n");
					continue;
				}
			}
			fclose(fp);
			if (ans == 1)
				strcpy(pIni->filesavepath, tempFilesavepath);
			else
				strcpy(pIni->filename, tempFilename);
		}
		else if (ans == 3 || ans == 4 || ans == 5 || ans == 6 || ans == 7 || ans == 8)
		{
			int tempDataNum;
			char dataNumArr[MAX_INT_LEN + 1];
			do {
				printf("��������Ҫ�޸ĵ����ݣ�");
				fgets(dataNumArr, MAX_INT_LEN + 1, stdin);
			} while (dataNumArr[0] == '\n');	//���û����س���������������������
			int len = strlen(dataNumArr);
			if (dataNumArr[len - 1] == '\n')
				dataNumArr[len - 1] = '\0';	//ɾȥ����Ļس�
			tempDataNum = str_to_int(dataNumArr);
			if (tempDataNum == 0)
			{
				printf("�޸�ʧ�ܣ������������������0���������������롣\n");
				continue;
			}
			else if (tempDataNum == -2)
			{
				printf("�޸�ʧ�ܣ�����������������벻Ҫ������������ݡ�\n");
				continue;
			}
			else if (tempDataNum == -1)
			{
				printf("�޸�ʧ�ܣ�����������ݹ����벻Ҫ�������2147483647�����ݡ�\n");
				continue;
			}
			else
			{
				if (ans == 3 && tempDataNum < pIni->minvalue1)
				{
					printf("�޸�ʧ�ܣ���������С�����ޣ����������롣\n");
					continue;
				}
				else if (ans == 4 && tempDataNum > pIni->maxvalue1)
				{
					printf("�޸�ʧ�ܣ��������ݴ������ޣ����������롣\n");
					continue;
				}
				else if (ans == 5 && tempDataNum < pIni->minvalue2)
				{
					printf("�޸�ʧ�ܣ���������С�����ޣ����������롣\n");
					continue;
				}
				else if (ans == 6 && tempDataNum < pIni->maxvalue2)
				{
					printf("�޸�ʧ�ܣ��������ݴ������ޣ����������롣\n");
					continue;
				}
				else if (ans == 7 && tempDataNum < pIni->recordcount2)
				{
					printf("�޸�ʧ�ܣ���������С�����ޣ����������롣\n");
					continue;
				}
				else if (ans == 8 && tempDataNum > pIni->recordcount1)
				{
					printf("�޸�ʧ�ܣ��������ݴ������ޣ����������롣\n");
					continue;
				}
			}

			if (ans == 3)
				pIni->maxvalue1 = tempDataNum;
			else if (ans == 4)
				pIni->minvalue1 = tempDataNum;
			else if (ans == 5)
				pIni->maxvalue2 = tempDataNum;
			else if (ans == 6)
				pIni->minvalue2 = tempDataNum;
			else if (ans == 7)
				pIni->recordcount1 = tempDataNum;
			else if (ans == 8)
				pIni->recordcount2 = tempDataNum;

			FILE* fp;
			fp = fopen("conf.ini", "w");
			if (!fp)
			{
				printf("�������󣺴����ò����ļ�ʧ�ܡ�\n");
				exit(0);
			}	//���ļ�
			fprintf(fp, "%s\n", pIni->filesavepath);
			fprintf(fp, "%s\n", pIni->filename);
			fprintf(fp, "%d\n", pIni->maxvalue1);
			fprintf(fp, "%d\n", pIni->minvalue1);
			fprintf(fp, "%d\n", pIni->maxvalue2);
			fprintf(fp, "%d\n", pIni->minvalue2);
			fprintf(fp, "%d\n", pIni->recordcount1);
			fprintf(fp, "%d\n", pIni->recordcount2);
			fclose(fp);
		}
	} while (ans != 0);
}
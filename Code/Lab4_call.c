//��ŵ���ʵ��4�����������ݼ�¼�ļ�����������

#include<stdio.h>
#include<Windows.h>
#include"Lab4_data.h"
#include"Lab4_tools.h"
#include"Lab4_loadfile.h"


/**
 * �������ܣ������û�ȷ�������Ƿ����󲢵����ⲿ����
 * ����������Ƿ����Զ�ģʽautoMode���������ݼ�¼�ļ������Ʋ���ָ��CONF* pIni�����ݼ�¼�ļ�·�����ļ���filename��
			 ���ݼ�¼�ļ�·����Ϣ��״̬��ָ��pFilenameStatus�����ݼ�¼������Ϣ��״̬��ָ��pDataNumStatus
 * ����ֵ����
 * ���ߣ��¾��� 21281280@bjtu.edu.cn
 * ���ڣ�2022��5��17��
*/
void call_program(int autoMode, CONF* pIni, char* filename, int* pDataNumStatus, char* pFilenameStatus)
{
	if (autoMode != 1)
	{
		int ans = 0;
		do {
			printf("��ȷ��������������Ƿ�����\n");
			printf("���ݼ�¼������%d\n", pIni->number);
			printf("���ݼ�¼�ļ�·�����ļ�����%s\n", filename);
			printf("+ ---- + ---------------------------- +\n");
			printf("| ָ�� | ����                         |\n");
			printf("+ ---- + ---------------------------- +\n");
			printf("|  0   | ȷ������                     |\n");
			printf("|  1   | �޸����ݼ�¼����             |\n");
			printf("|  2   | �޸����ݼ�¼�ļ�·�����ļ��� |\n");
			printf("|  3   | ȫ���޸�                     |\n");
			printf("+ ---- + ---------------------------- +\n");
			char input[2];
			do {
				do {
					if (ans > 3 || ans < 0)
						printf("����ָ������\n�����������Ӧָ�");
					else
						printf("�������Ӧָ�");
					fgets(input, 2, stdin);
					int c;
					while ((c = getchar()) != '\n' && c != EOF)
						;
				} while (input[0] == '\n');	//���û����س���������������������
				ans = str_to_int(input);
			} while (ans > 3 || ans < 0);
			if (ans == 0)
				break;
			else if (ans == 1)
			{
				*pDataNumStatus = 0;
				get_dataNum(pDataNumStatus, pIni);
				continue;
			}
			else if (ans == 2)
			{
				*pFilenameStatus = 0;
				get_filename(pFilenameStatus, filename);
				continue;
			}
			else if (ans == 3)
			{
				*pDataNumStatus = 0;
				*pFilenameStatus = 0;
				get_dataNum(pDataNumStatus, pIni);
				get_filename(pFilenameStatus, filename);
				continue;
			}
		} while (ans != 0);
	}

	char numberArr[12];
	int temp1 = pIni->number, temp2 = pIni->number, i = 0, max = 0;
	for (; temp1; i++, temp1 /= 10)
		max++;
	max--;
	for (i = 0; temp2; i++, temp2 /= 10)
		numberArr[max - i] = '0' + temp2 % 10;
	numberArr[i] = ' ';
	numberArr[i + 1] = 0;

	char command[MAX_STR_LEN * 2 + MAX_INT_LEN + 3] = "Lab3.exe ";
	strcat(command, numberArr);
	strcat(command, filename);
	system(command);
}
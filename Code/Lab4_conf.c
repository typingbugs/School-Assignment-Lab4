//存放与修改配置文件相关的功能函数

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"Lab4_data.h"
#include"Lab4_loadfile.h"
#include"Lab4_tools.h"


/**
 * 函数功能：修改配置文件
 * 输入参数：生成数据记录文件的限制参数指针CONF* pIni
 * 返回值：无
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月13日
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
			printf("发生错误：打开配置参数文件失败。\n");
			exit(0);
		}	//打开文件
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
		printf("| 序号 | 变量                                   | 内容");
		for (int i = 0; i < max - 4; i++)
			printf(" ");
		printf(" |\n");
		printf("+ ---- + -------------------------------------- + ");
		for (int i = 0; i < max; i++)
			printf("-");
		printf(" +\n");
		printf("|  1   | 数据记录文件的存储目录                 | ");
		printf("%s", pIni->filesavepath);
		for (int i = 0; i < max - len[0]; i++)
			printf(" ");
		printf(" |\n");
		printf("|  2   | 数据记录文件的文件名信息               | ");
		printf("%s", pIni->filename);
		for (int i = 0; i < max - len[1]; i++)
			printf(" ");
		printf(" |\n");
		printf("|  3   | 数据记录三元组中第1、2个元素取值的上限 | ");
		printf("%d", pIni->maxvalue1);
		for (int i = 0; i < max - len[2]; i++)
			printf(" ");
		printf(" |\n");
		printf("|  4   | 数据记录三元组中第1、2个元素取值的下限 | ");
		printf("%d", pIni->minvalue1);
		for (int i = 0; i < max - len[3]; i++)
			printf(" ");
		printf(" |\n");
		printf("|  5   | 数据记录三元组中第3个元素取值的上限    | ");
		printf("%d", pIni->maxvalue2);
		for (int i = 0; i < max - len[4]; i++)
			printf(" ");
		printf(" |\n");
		printf("|  6   | 数据记录三元组中第3个元素取值的下限    | ");
		printf("%d", pIni->minvalue2);
		for (int i = 0; i < max - len[5]; i++)
			printf(" ");
		printf(" |\n");
		printf("|  7   | 需要随机生成记录条数时条数值的上限     | ");
		printf("%d", pIni->recordcount1);
		for (int i = 0; i < max - len[6]; i++)
			printf(" ");
		printf(" |\n");
		printf("|  8   | 需要随机生成记录条数时条数值的下限     | ");
		printf("%d", pIni->recordcount2);
		for (int i = 0; i < max - len[7] - 1; i++)
			printf(" ");
		printf(" |\n");
		printf("|  0   | 修改完成                               | ");
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
					printf("输入指令有误。\n请重新输入序号：");
				else
					printf("请输入需要操作的序号：");
				fgets(input, 2, stdin);
				int c;
				while ((c = getchar()) != '\n' && c != EOF)
					;
			} while (input[0] == '\n');	//若用户按回车不输入则请求重新输入
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
					printf("修改失败：输入的数据记录文件路径有误，请重新操作。\n");
				else
					printf("修改失败：输入的数据记录文件名有误，请重新操作。\n");
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
						printf("修改失败：输入的数据记录文件路径有误，请重新操作。\n");
					else
						printf("修改失败：输入的数据记录文件名有误，请重新操作。\n");
					continue;
				}
			}
			else
			{
				fp = fopen(filename, "wb+");
				if (!fp)
				{
					if (ans == 1)
						printf("修改失败：输入的数据记录文件路径有误，请重新操作。\n");
					else
						printf("修改失败：输入的数据记录文件名有误，请重新操作。\n");
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
				printf("请输入需要修改的数据：");
				fgets(dataNumArr, MAX_INT_LEN + 1, stdin);
			} while (dataNumArr[0] == '\n');	//若用户按回车不输入则请求重新输入
			int len = strlen(dataNumArr);
			if (dataNumArr[len - 1] == '\n')
				dataNumArr[len - 1] = '\0';	//删去读入的回车
			tempDataNum = str_to_int(dataNumArr);
			if (tempDataNum == 0)
			{
				printf("修改失败：输入有误，请输入大于0的数，请重新输入。\n");
				continue;
			}
			else if (tempDataNum == -2)
			{
				printf("修改失败：您输入的数据有误，请不要输入非数字数据。\n");
				continue;
			}
			else if (tempDataNum == -1)
			{
				printf("修改失败：您输入的数据过大，请不要输入大于2147483647的数据。\n");
				continue;
			}
			else
			{
				if (ans == 3 && tempDataNum < pIni->minvalue1)
				{
					printf("修改失败：输入数据小于下限，请重新输入。\n");
					continue;
				}
				else if (ans == 4 && tempDataNum > pIni->maxvalue1)
				{
					printf("修改失败：输入数据大于上限，请重新输入。\n");
					continue;
				}
				else if (ans == 5 && tempDataNum < pIni->minvalue2)
				{
					printf("修改失败：输入数据小于下限，请重新输入。\n");
					continue;
				}
				else if (ans == 6 && tempDataNum < pIni->maxvalue2)
				{
					printf("修改失败：输入数据大于上限，请重新输入。\n");
					continue;
				}
				else if (ans == 7 && tempDataNum < pIni->recordcount2)
				{
					printf("修改失败：输入数据小于下限，请重新输入。\n");
					continue;
				}
				else if (ans == 8 && tempDataNum > pIni->recordcount1)
				{
					printf("修改失败：输入数据大于上限，请重新输入。\n");
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
				printf("发生错误：打开配置参数文件失败。\n");
				exit(0);
			}	//打开文件
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
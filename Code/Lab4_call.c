//存放调用实验4程序生成数据记录文件函数的声明

#include<stdio.h>
#include<Windows.h>
#include"Lab4_data.h"
#include"Lab4_tools.h"
#include"Lab4_loadfile.h"


/**
 * 函数功能：请求用户确认数据是否无误并调用外部程序
 * 输入参数：是否是自动模式autoMode，生成数据记录文件的限制参数指针CONF* pIni，数据记录文件路径和文件名filename，
			 数据记录文件路径信息的状态的指针pFilenameStatus，数据记录条数信息的状态的指针pDataNumStatus
 * 返回值：无
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月17日
*/
void call_program(int autoMode, CONF* pIni, char* filename, int* pDataNumStatus, char* pFilenameStatus)
{
	if (autoMode != 1)
	{
		int ans = 0;
		do {
			printf("请确认您输入的数据是否无误：\n");
			printf("数据记录条数：%d\n", pIni->number);
			printf("数据记录文件路径和文件名：%s\n", filename);
			printf("+ ---- + ---------------------------- +\n");
			printf("| 指令 | 功能                         |\n");
			printf("+ ---- + ---------------------------- +\n");
			printf("|  0   | 确认无误                     |\n");
			printf("|  1   | 修改数据记录条数             |\n");
			printf("|  2   | 修改数据记录文件路径和文件名 |\n");
			printf("|  3   | 全部修改                     |\n");
			printf("+ ---- + ---------------------------- +\n");
			char input[2];
			do {
				do {
					if (ans > 3 || ans < 0)
						printf("输入指令有误。\n请重新输入对应指令：");
					else
						printf("请输入对应指令：");
					fgets(input, 2, stdin);
					int c;
					while ((c = getchar()) != '\n' && c != EOF)
						;
				} while (input[0] == '\n');	//若用户按回车不输入则请求重新输入
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
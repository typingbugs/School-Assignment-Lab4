//存储run函数需要调用的各个子函数

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include <direct.h>	//getcwd()/mkdir()
#include <sys/types.h>	//mkdir()
#include <sys/stat.h>	//mkdir()
#include <io.h>	//access()
#include "Lab4_data.h"

static int str_to_int(char* numArr);
static void fget_file_path_and_name(char* s, FILE* fp);
static int fget_num(FILE* fp);
int change_Filename_to_absolute(char* filename);
void create_path(char* filename);


/**
 * 函数功能：检查Lab3.exe是否可用，并从conf.ini中读取生成数据记录文件的限制参数
 * 输入参数：生成数据记录文件的限制参数指针CONF* pIni，数据记录文件路径和文件名filename
 * 返回值：无
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月9日
*/
void self_check_and_get_configinfo(CONF* pIni, char* filename)
{
	printf("等待程序自检...");
	FILE* conf;

	if (access("Lab3.exe", 0))
	{
		printf("发生错误：Lab3.exe文件丢失。\n");
		exit(0);
	}	//判断能否执行Lab3.exe

	conf = fopen("conf.ini", "r");
	if (!conf)
	{
		printf("发生错误：打开配置参数文件失败，请联系管理员解决。\n");
		exit(0);
	}	//打开文件并判断是否成功

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
	if(!check_filename(filename))
	{
		printf("发生错误：配置参数有误，请联系管理员解决。\n");
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
			printf("发生错误：配置参数有误，请联系管理员解决。\n");
			exit(0);
		}
	}
	else
	{
		fp = fopen(filename, "wb+");
		if (!fp)
		{
			printf("发生错误：配置参数有误，请联系管理员解决。\n");
			exit(0);
		}
	}
	fclose(fp);

	printf("自检完成。\n");
}


/**
 * 函数功能：将文件路径转化为绝对路径
 * 输入参数：记录文件名的地址filename
 * 返回值：执行情况error（1-路径无误，0-路径有误）
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月9日
*/
int change_Filename_to_absolute(char* filename)
{
	char tempFilename[2 * MAX_STR_LEN];
	strncpy(tempFilename, filename, 2 * MAX_STR_LEN);

	if (tempFilename[1] == ':')	//原本就是绝对路径
		strcpy(filename, tempFilename);
	else
	{
		char* path = getcwd(NULL, 0);
		if (!path)
		{
			printf("发生错误！获取当前路径失败！\n");
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
					if (path[j] == ':')	//读到根目录无法再进入上一级
					{
						printf("发生错误！无效路径！\n");
						noError = 0;
						break;
					}
					j--;
				}
				if (!noError)	//文件路径无效
				{
					return 0;
				}
				path[j] = 0;
				i += 3;
			}
			if (noError)
			{
				i--;	//要读入前面的一个'/'
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
 * 函数功能：如果路径未被创建则创建路径
 * 输入参数：记录文件名的地址filename
 * 返回值：无
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年4月11日
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
 * 函数功能：检查文件名是否合法
 * 输入参数：记录文件名的地址filename
 * 返回值：文件路径是否有误error（1-路径无误，0-路径有误）
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月9日
*/
int check_filename(char* filename)
{
	int noError = 1;
	int len = strlen(filename);

	if (len <= 4)
		noError = 0;
	else if (strcmp(filename+len - 4, ".txt") != 0 && strcmp(filename+len - 4, ".bin") != 0)
		noError = 0;	//判断后缀是否合法
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
	}	//判断文件名是否合法
	if (!noError)
		return 0;
	else
		return 1;
}


/**
 * 函数功能：显示选择用户/开发者模式的菜单并读取输入
 * 输入参数：无
 * 返回值：用户输入内容（int）
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月10日
*/
int show_menu_root()
{
	printf("+ ---- + ---------- +\n");
	printf("| 序号 | 模式       |\n");
	printf("+ ---- + ---------- +\n");
	printf("|  1   | 用户模式   |\n");
	printf("|  2   | 开发者模式 |\n");
	printf("+ ---- + ---------- +\n");
	char input[2];
	int ans = 1;
	do {
		do {
			if(ans > 2 || ans <= 0)
				printf("输入序号有误。\n请重新输入功能对应的序号：");
			else
				printf("请输入功能对应的序号：");
			fgets(input, 2, stdin);
			int c;
			while ((c = getchar()) != '\n' && c != EOF)
				;
		} while (input[0] == '\n');	//若用户按回车不输入则请求重新输入
		ans = str_to_int(input);
	} while (ans > 2 || ans <= 0);
	return ans;
}


/**
 * 函数功能：显示用户模式的菜单并读取输入
 * 输入参数：无
 * 返回值：用户输入内容（int）
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月10日
*/
int show_menu_user()
{
	printf("+ ---- + ---------------- +\n");
	printf("| 序号 | 模式             |\n");
	printf("+ ---- + ---------------- +\n");
	printf("|  1   | 自动模式         |\n");
	printf("|  2   | 交互模式         |\n"); 
	printf("|  3   | 查看已有数据记录 |\n");
	printf("|  0   | 退出             |\n");
	printf("+ ---- + ---------------- +\n");
	char input[2];
	int ans = 1;
	do {
		do {
			if (ans > 3 || ans < 0)
				printf("输入序号有误。\n请重新输入功能对应的序号：");
			else
				printf("请输入功能对应的序号：");
			fgets(input, 2, stdin);
			int c;
			while ((c = getchar()) != '\n' && c != EOF)
				;
		} while (input[0] == '\n');	//若用户按回车不输入则请求重新输入
		ans = str_to_int(input);
	} while (ans > 3 || ans < 0);
	return ans;
}


/**
 * 函数功能：显示开发者模式的菜单并读取输入
 * 输入参数：无
 * 返回值：用户输入内容（int）
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月10日
*/
int show_menu_developer()
{
	printf("+ ---- + ------------ +\n");
	printf("| 序号 | 功能         |\n");
	printf("+ ---- + ------------ +\n");
	printf("|  1   | 修改配置文件 |\n");
	printf("|  2   | 运行程序     |\n");
	printf("|  0   | 退出         |\n");
	printf("+ ---- + ------------ +\n");
	char input[2];
	int ans = 1;
	do {
		do {
			if (ans > 2 || ans < 0)
				printf("输入序号有误。\n请重新输入功能对应的序号：");
			else
				printf("请输入功能对应的序号：");
			fgets(input, 2, stdin);
			int c;
			while ((c = getchar()) != '\n' && c != EOF)
				;
		} while (input[0] == '\n');	//若用户按回车不输入则请求重新输入
		ans = str_to_int(input);
	} while (ans > 2 || ans < 0);
	return ans;
}


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

		if (ans == 1||ans == 2)
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


/**
 * 函数功能：获取数据记录条数
 * 输入参数：数据记录条数信息的状态的指针pDataNumStatus，生成数据记录文件的限制参数指针CONF* pIni
 * 返回值：数据记录条数（int）
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月10日
*/
void get_dataNum(int* pDataNumStatus, CONF* pIni)
{
	int tempDataNum = pIni->number;
	char dataNumArr[MAX_INT_LEN + 1];
	do {
		do {
			if (tempDataNum == 0)
				printf("输入有误，请输入大于0的数。请重新输入。\n");
			else if(tempDataNum == -2)
				printf("您输入的数据记录条数有误，请不要输入非数字数据。\n");
			else if(tempDataNum == -1)
				printf("您输入的数据记录条数过大，请不要输入大于2147483647的数据。\n");

			if (*pDataNumStatus == 0)
				printf("原数据记录条数为：%d\n修改为：", pIni->number);
			else
				printf("请输入数据记录条数：");
			fgets(dataNumArr, MAX_INT_LEN + 1, stdin);
		} while (dataNumArr[0] == '\n');	//若用户按回车不输入则请求重新输入
		int len = strlen(dataNumArr);
		if (dataNumArr[len - 1] == '\n')
			dataNumArr[len - 1] = '\0';	//删去读入的回车
		tempDataNum = str_to_int(dataNumArr);
	} while (tempDataNum <= 0);
	*pDataNumStatus = 1;
	pIni->number = tempDataNum;
}


/**
 * 函数功能：获取文件路径
 * 输入参数：数据记录文件路径信息的状态的指针pFilenameStatus，数据记录文件路径和文件名filename
 * 返回值：无
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月11日
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
				if(*pFilenameStatus == 2)
					printf("找不到您输入的文件。请重新输入。\n");
				else
					printf("您输入的文件路径和文件名有误。请重新输入。\n");
			}

			if (*pFilenameStatus == 0)
				printf("原数据记录文件路径为：%s\n修改为：", filename);
			else
				printf("请输入数据记录文件路径：");
			fgets(tempFilename, MAX_STR_LEN * 2 + 1, stdin);
		} while (tempFilename[0] == '\n');	//若用户按回车不输入则请求重新输入
		error = 0;
		int len = strlen(tempFilename);
		if (tempFilename[len - 1] == '\n')
			tempFilename[len - 1] = '\0';	//删去读入的回车
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


/**
 * 函数功能：询问用户是否查看生成的数据记录文件
 * 输入参数：无
 * 返回值：用户输入内容（1-Y；0-N）
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月17日
*/
int show_menu_ask_if_read_file()
{
	char input[2] = "Y";
	do {
		if (input[0] != 'Y' && input[0] != 'N')
			printf("输入有误，请重新输入。\n是否查看生成的数据记录文件？（Y\\N）：");
		else
			printf("是否查看生成的数据记录文件？（Y\\N）：");
		fgets(input, 2, stdin);
		int c;
		while ((c = getchar()) != '\n' && c != EOF)
			;
	} while (input[0] != 'Y' && input[0] != 'N');	//若用户按回车不输入则请求重新输入
	if (input[0] == 'Y')
		return 1;
	else
		return 0;
}


/**
 * 函数功能：询问用户选择二维数组/结构体数组/指针数组/链表存储
 * 输入参数：无
 * 返回值：用户输入内容（int）
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月17日
*/
int show_menu_ask_how_to_store()
{
	printf("+ ---- + ---------- +\n");
	printf("| 序号 | 存储方式   |\n");
	printf("+ ---- + ---------- +\n");
	printf("|  1   | 二维数组   |\n");
	printf("|  2   | 结构体数组 |\n");
	printf("|  3   | 指针数组   |\n");
	printf("|  4   | 链表       |\n");
	printf("+ ---- + ---------- +\n");
	char input[2];
	int ans = 1;
	do {
		do {
			if (ans > 4 || ans <= 0)
				printf("输入序号有误。\n请重新输入功能对应的序号：");
			else
				printf("请输入功能对应的序号：");
			fgets(input, 2, stdin);
			int c;
			while ((c = getchar()) != '\n' && c != EOF)
				;
		} while (input[0] == '\n');	//若用户按回车不输入则请求重新输入
		ans = str_to_int(input);
	} while (ans > 4 || ans <= 0);
	return ans;
}


/**
 * 函数功能：从文件读取内容进二维数组
 * 输入参数：二维数组地址int(*data)[3]，文件指针fp，数据记录条数dataNum
 * 返回值：无
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月18日
*/
static void store_data_in_2d_array(int(*data)[3], FILE* fp, int dataNum)
{

	for (int i = 0; i < dataNum; i++)
	{
		char numArr[20];
		char* p = numArr;
		if (fgets(numArr, 20, fp) == NULL)
		{
			printf("数据记录有误！请检查数据记录文件。\n");
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
				printf("数据记录有误！请检查数据记录文件。\n");
				exit(0);
			}
			p +=  k + 1;
		}
	}
}


/**
 * 函数功能：从文件读取内容进结构体数组
 * 输入参数：结构体数组地址DATAITEM* data，文件指针fp，数据记录条数dataNum
 * 返回值：无
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月20日
*/
static void store_data_in_struct_array(DATAITEM* data, FILE* fp, int dataNum)
{
	for (int i = 0; i < dataNum; i++)
	{
		char numArr[20];
		char* p = numArr;
		if (fgets(numArr, 20, fp) == NULL)
		{
			printf("数据记录有误！请检查数据记录文件。\n");
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
				printf("数据记录有误！请检查数据记录文件。\n");
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
 * 函数功能：从文件读取内容进指针数组
 * 输入参数：结构体数组地址DATAITEM** data，文件指针fp，数据记录条数dataNum
 * 返回值：无
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月20日
*/
static void store_data_in_point_array(DATAITEM** data, FILE* fp, int dataNum)
{
	for (int i = 0; i < dataNum; i++)
	{
		data[i] = (DATAITEM*)malloc(sizeof(DATAITEM));
		if (data[i] == NULL)
		{
			printf("出现错误：动态分配内存失败。\n");
			exit(0);
		}
		char numArr[20];
		char* p = numArr;
		if (fgets(numArr, 20, fp) == NULL)
		{
			printf("数据记录有误！请检查数据记录文件。\n");
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
				printf("数据记录有误！请检查数据记录文件。\n");
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
 * 函数功能：释放指针数组的每个元素指向的空间
 * 输入参数：结构体数组地址DATAITEM** data，数据记录条数dataNum
 * 返回值：无
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月20日
*/
static void free_data_in_point_array(DATAITEM** data, int dataNum)
{
	for (int i = 0; i < dataNum; i++)
	{
		free(data[i]);
	}
}



/**
 * 函数功能：开发者模式询问用户运行程序时是否计时
 * 输入参数：无
 * 返回值：用户输入内容（1-Y；0-N）
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月10日
*/
static int show_menu_timeCount()
{
	char input[2] = "Y";
	do {
		if (input[0] != 'Y' && input[0] != 'N')
			printf("输入有误，请重新输入。\n是否计时运行？（Y\\N）：");
		else
			printf("是否计时运行？（Y\\N）：");
		fgets(input, 2, stdin);
		int c;
		while ((c = getchar()) != '\n' && c != EOF)
			;
	} while (input[0] != 'Y' && input[0] != 'N');	//若用户按回车不输入则请求重新输入
	if (input[0] == 'Y')
		return 1;
	else
		return 0;
}


/**
 * 函数功能：询问用户选择计时排序前数据预处理方式
 * 输入参数：无
 * 返回值：用户输入内容（int）
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月18日
*/
static int show_menu_ask_data_status_before_sort()
{
	printf("+ ---- + ---------- +\n");
	printf("| 序号 | 数据集处理 |\n");
	printf("+ ---- + ---------- +\n");
	printf("|  1   | 正序       |\n");
	printf("|  2   | 逆序       |\n");
	printf("|  3   | 随机序     |\n");
	printf("+ ---- + ---------- +\n");
	char input[2];
	int ans = 1;
	do {
		do {
			if (ans > 3 || ans <= 0)
				printf("输入序号有误。\n请重新输入功能对应的序号：");
			else
				printf("请输入功能对应的序号：");
			fgets(input, 2, stdin);
			int c;
			while ((c = getchar()) != '\n' && c != EOF)
				;
		} while (input[0] == '\n');	//若用户按回车不输入则请求重新输入
		ans = str_to_int(input);
	} while (ans > 3 || ans <= 0);
	return ans;
}


/**
 * 函数功能：为给二维数组使用qsort编写的cmp函数
 * 输入参数：比较的两个二维数组的地址const void** a、const void** b
 * 返回值：<0（不进行置换） / >0（进行置换） / 0（不进行置换）
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月18日
*/
static int cmp_for_2d_array_qsort(const void* a, const void* b)
{
		return ((int*)a)[2] - ((int*)b)[2];
}


/**
 * 函数功能：为给二维数组使用qsort编写的cmp函数（逆序）
 * 输入参数：比较的两个二维数组的地址const void** a、const void** b
 * 返回值：<0(不进行置换) / >0(进行置换) / 0(不进行置换)
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月18日
*/
static int cmp_reverse_for_2d_array_qsort(const void* a[3], const void* b[3])
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
static int cmp_for_struct_array_qsort(const void* a, const void* b)
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
static int cmp_reverse_for_struct_array_qsort(const void* a, const void* b)
{
	return ((DATAITEM*)b)->item3 - ((DATAITEM*)a)->item3;
}


/**
 * 函数功能：为给指针数组使用qsort编写的cmp函数
 * 输入参数：比较的两个一维数组的地址const void** a、const void** b
 * 返回值：<0（不进行置换） / >0（进行置换） / 0（不进行置换）
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月20日
*/
static int cmp_for_point_array_qsort(const void** a, const void** b)
{
	return (*(DATAITEM**)a)->item3 - (*(DATAITEM**)b)->item3;
}


/**
 * 函数功能：为给指针数组使用qsort编写的cmp函数（逆序）
 * 输入参数：比较的两个一维数组的地址const void** a、const void** b
 * 返回值：<0（不进行置换） / >0（进行置换） / 0（不进行置换）
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月20日
*/
static int cmp_reverse_for_point_array_qsort(const void** a, const void** b)
{
	return (*(DATAITEM**)b)->item3 - (*(DATAITEM**)a)->item3;
}


/**
 * 函数功能：询问用户选择排序方式
 * 输入参数：无
 * 返回值：用户输入内容（int）
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月18日
*/
static int show_menu_ask_sort_method()
{
	printf("+ ---- + -------- +\n");
	printf("| 序号 | 排序方式 |\n");
	printf("+ ---- + -------- +\n");
	printf("|  1   | 快速排序 |\n");
	printf("|  2   | 冒泡排序 |\n");
	printf("+ ---- + -------- +\n");
	char input[2];
	int ans = 1;
	do {
		do {
			if (ans > 2 || ans <= 0)
				printf("输入序号有误。\n请重新输入功能对应的序号：");
			else
				printf("请输入功能对应的序号：");
			fgets(input, 2, stdin);
			int c;
			while ((c = getchar()) != '\n' && c != EOF)
				;
		} while (input[0] == '\n');	//若用户按回车不输入则请求重新输入
		ans = str_to_int(input);
	} while (ans > 2 || ans <= 0);
	return ans;
}


/**
 * 函数功能：打印二维数组内容
 * 输入参数：二维数组地址int(*data)[3]，数据记录条数dataNum
 * 返回值：无
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月18日
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
 * 函数功能：打印结构体数组内容
 * 输入参数：结构体数组地址DATAITEM* data，数据记录条数dataNum
 * 返回值：无
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月20日
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
 * 函数功能：打印指针数组内容
 * 输入参数：结构体数组地址DATAITEM** data，数据记录条数dataNum
 * 返回值：无
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月20日
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
 * 函数功能：获取当前时间，输出格式：xx月xx日xx时xx分xx秒-xxxx年
 * 输入参数：存储当前时间的字符串
 * 返回值：无
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月18日
*/
static void get_time(char* buffer)
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


/**
 * 函数功能：排序并展示数据记录（二维数组）
 * 输入参数：数据记录文件路径和文件名filename，文件指针fp，用户/开发者模式rootMode
 * 返回值：无
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月18日
*/
void show_data_in_2d_array(char* filename, FILE* fp, int rootMode)
{
	int dataNum;
	char numArr[MAX_INT_LEN + 1];
	if (fgets(numArr, MAX_INT_LEN + 1, fp) == NULL)
	{
		printf("数据记录有误！请检查数据记录文件。\n");
		exit(0);
	}
	int len = strlen(numArr);
	if (numArr[len - 1] == '\n')
		numArr[len - 1] = '\0';	//删去读入的回车
	dataNum = str_to_int(numArr);
	if (dataNum < 0)
	{
		printf("数据记录有误！请检查数据记录文件。\n");
		exit(0);
	}
	int(*data)[3] = (int(*)[3])malloc(sizeof(int) * 3 * dataNum);
	if (data == NULL)
	{
		printf("出现错误：动态分配内存失败。\n");
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
			char dataStatus[3][5] = { "正序","逆序","乱序" };
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
				printf("快速排序%d条数据，用时%lf秒。", dataNum, totalTime);
				FILE* log;
				log = fopen("Log.csv", "a+");
				if (log == NULL)
				{
					printf("日志文件打开失败，无法将排序用时记入日志。\n");
					exit(0);
				}
				fprintf(log, "二维数组,%d条,%s,快速排序,%lf秒,%s\n", dataNum, dataStatus[ans - 1], totalTime, timeBuffer);
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
				printf("冒泡排序%d条数据，用时%lf秒。", dataNum, totalTime);
				FILE* log;
				log = fopen("Log.csv", "a+");
				if (log == NULL)
				{
					printf("日志文件打开失败，无法将排序用时记入日志。\n");
					exit(0);
				}
				fprintf(log, "二维数组,%d条,%s,冒泡排序,%lf秒,%s\n", dataNum, dataStatus[ans - 1], totalTime, timeBuffer);
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
 * 函数功能：排序并展示数据记录（结构体数组）
 * 输入参数：数据记录文件路径和文件名filename，文件指针fp，用户/开发者模式rootMode
 * 返回值：无
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月20日
*/
void show_data_in_struct_array(char* filename, FILE* fp, int rootMode)
{
	int dataNum;
	char numArr[MAX_INT_LEN + 1];
	if (fgets(numArr, MAX_INT_LEN + 1, fp) == NULL)
	{
		printf("数据记录有误！请检查数据记录文件。\n");
		exit(0);
	}
	int len = strlen(numArr);
	if (numArr[len - 1] == '\n')
		numArr[len - 1] = '\0';	//删去读入的回车
	dataNum = str_to_int(numArr);
	if (dataNum < 0)
	{
		printf("数据记录有误！请检查数据记录文件。\n");
		exit(0);
	}
	DATAITEM* data = (DATAITEM*)malloc(sizeof(DATAITEM) * dataNum);
	if (data == NULL)
	{
		printf("出现错误：动态分配内存失败。\n");
		exit(0);
	}
	store_data_in_struct_array(data, fp, dataNum);
	if (rootMode == 2)
	{
		if (show_menu_timeCount())
		{
			int ans = show_menu_ask_data_status_before_sort();
			if (ans == 1)
				qsort(data, dataNum, 3 * sizeof(int), cmp_for_struct_array_qsort);
			else if (ans == 2)
				qsort(data, dataNum, 3 * sizeof(int), cmp_reverse_for_struct_array_qsort);
			char dataStatus[3][5] = { "正序","逆序","乱序" };
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
				printf("快速排序%d条数据，用时%lf秒。", dataNum, totalTime);
				FILE* log;
				log = fopen("Log.csv", "a+");
				if (log == NULL)
				{
					printf("日志文件打开失败，无法将排序用时记入日志。\n");
					exit(0);
				}
				fprintf(log, "结构体数组,%d条,%s,快速排序,%lf秒,%s\n", dataNum, dataStatus[ans - 1], totalTime, timeBuffer);
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
				printf("冒泡排序%d条数据，用时%lf秒。", dataNum, totalTime);
				FILE* log;
				log = fopen("Log.csv", "a+");
				if (log == NULL)
				{
					printf("日志文件打开失败，无法将排序用时记入日志。\n");
					exit(0);
				}
				fprintf(log, "结构体数组,%d条,%s,冒泡排序,%lf秒,%s\n", dataNum, dataStatus[ans - 1], totalTime, timeBuffer);
				fclose(log);
			}
		}
		else
		{
			qsort(data, dataNum, 3 * sizeof(int), cmp_for_struct_array_qsort);
			print_data_in_struct_array(data, dataNum);
		}
	}
	else
	{
		qsort(data, dataNum, 3 * sizeof(int), cmp_for_struct_array_qsort);
		print_data_in_struct_array(data, dataNum);
	}
	free(data);
}


/**
 * 函数功能：排序并展示数据记录（指针数组）
 * 输入参数：数据记录文件路径和文件名filename，文件指针fp，用户/开发者模式rootMode
 * 返回值：无
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月20日
*/
void show_data_in_point_array(char* filename, FILE* fp, int rootMode)
{
	int dataNum;
	char numArr[MAX_INT_LEN + 1];
	if (fgets(numArr, MAX_INT_LEN + 1, fp) == NULL)
	{
		printf("数据记录有误！请检查数据记录文件。\n");
		exit(0);
	}
	int len = strlen(numArr);
	if (numArr[len - 1] == '\n')
		numArr[len - 1] = '\0';	//删去读入的回车
	dataNum = str_to_int(numArr);
	if (dataNum < 0)
	{
		printf("数据记录有误！请检查数据记录文件。\n");
		exit(0);
	}
	DATAITEM** data = (DATAITEM**)malloc(sizeof(DATAITEM*) * dataNum);
	if (data == NULL)
	{
		printf("出现错误：动态分配内存失败。\n");
		exit(0);
	}
	store_data_in_point_array(data, fp, dataNum);
	if (rootMode == 2)
	{
		if (show_menu_timeCount())
		{
			int ans = show_menu_ask_data_status_before_sort();
			if (ans == 1)
				qsort(data, dataNum, 3 * sizeof(int), cmp_for_point_array_qsort);
			else if (ans == 2)
				qsort(data, dataNum, 3 * sizeof(int), cmp_reverse_for_point_array_qsort);
			char dataStatus[3][5] = { "正序","逆序","乱序" };
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
				printf("快速排序%d条数据，用时%lf秒。", dataNum, totalTime);
				FILE* log;
				log = fopen("Log.csv", "a+");
				if (log == NULL)
				{
					printf("日志文件打开失败，无法将排序用时记入日志。\n");
					exit(0);
				}
				fprintf(log, "指针数组,%d条,%s,快速排序,%lf秒,%s\n", dataNum, dataStatus[ans - 1], totalTime, timeBuffer);
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
				printf("冒泡排序%d条数据，用时%lf秒。", dataNum, totalTime);
				FILE* log;
				log = fopen("Log.csv", "a+");
				if (log == NULL)
				{
					printf("日志文件打开失败，无法将排序用时记入日志。\n");
					exit(0);
				}
				fprintf(log, "指针数组,%d条,%s,冒泡排序,%lf秒,%s\n", dataNum, dataStatus[ans - 1], totalTime, timeBuffer);
				fclose(log);
			}
		}
		else
		{
			qsort(data, dataNum, 3 * sizeof(int), cmp_for_point_array_qsort);
			print_data_in_point_array(data, dataNum);
		}
	}
	else
	{
		qsort(data, dataNum, 3 * sizeof(int), cmp_for_point_array_qsort);
		print_data_in_point_array(data, dataNum);
	}
	free_data_in_point_array(data, dataNum);
	free(data);
}


/**
 * 函数功能：将numArr中的存储数据记录条数检查是否合法，合法转化为数字
 * 输入参数：存储数字信息的字符串numArr
 * 返回值：合法转化数字结果num，有非数字字符返回-2，超出范围返回-1
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年4月11日
*/
static int str_to_int(char* numArr)
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
 * 函数功能：从文件中读取用于存放数据记录文件的存储目录或文件名的字符串
 * 输入参数：用于存放数据记录文件的存储目录或文件名的字符串s，读取目标文件fp
 * 返回值：无
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年4月11日
*/
static void fget_file_path_and_name(char* s, FILE* fp)
{
	int len;

	fgets(s, MAX_STR_LEN, fp);
	len = strlen(s);
	if (s[len - 1] == '\n')
		s[len - 1] = 0;	//删去读入的回车
}


/**
 * 函数功能：从文件中读取生成数据记录文件的限制参数并转化为整型
 * 输入参数：读取目标文件fp
 * 返回值：生成数据记录文件的限制参数num
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年4月11日
*/
static int fget_num(FILE* fp)
{
	int len, num = 0;
	char numArr[11];

	fgets(numArr, MAX_INT_LEN + 1, fp);
	len = strlen(numArr);
	if (numArr[len - 1] == '\n')
	{
		numArr[len - 1] = 0;	//删去读入的回车
		len--;
	}

	num = str_to_int(numArr);
	if (num < 0)
	{
		printf("很抱歉！配置数据出现错误，请联系管理员解决。\n");
		//提示conf.ini中数据出现大于整型范围的错误
		exit(0);
	}

	return num;
}
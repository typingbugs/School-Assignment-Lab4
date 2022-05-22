//放数据读取、数据加载相关功能所需的函数

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
	if (!check_filename(filename))
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
	else if (strcmp(filename + len - 4, ".txt") != 0 && strcmp(filename + len - 4, ".bin") != 0)
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
			else if (tempDataNum == -2)
				printf("您输入的数据记录条数有误，请不要输入非数字数据。\n");
			else if (tempDataNum == -1)
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
				if (*pFilenameStatus == 2)
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
 * 函数功能：从文件读取内容进二维数组
 * 输入参数：二维数组地址int(*data)[3]，文件指针fp，数据记录条数dataNum
 * 返回值：无
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月18日
*/
void store_data_in_2d_array(int(*data)[3], FILE* fp, int dataNum)
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
			p += k + 1;
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
void store_data_in_struct_array(DATAITEM* data, FILE* fp, int dataNum)
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
void store_data_in_point_array(DATAITEM** data, FILE* fp, int dataNum)
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
 * 函数功能：从文件读取内容进单链表
 * 输入参数：单链表头节点（value为空）NODE* head，文件指针fp，数据记录条数dataNum
 * 返回值：无
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月20日
*/
void store_data_in_link_list(NODE* head, FILE* fp, int dataNum)
{
	NODE* q = head;
	for (int i = 0; i < dataNum; i++)
	{
		q->next = (NODE*)malloc(sizeof(NODE));
		if (q->next == NULL)
		{
			printf("出现错误：动态分配内存失败。\n");
			exit(0);
		}
		q = q->next;
		q->next = NULL;
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
				q->value1 = a;
			else if (j == 1)
				q->value2 = a;
			else if (j == 2)
				q->value3 = a;
			p += k + 1;
		}
	}
}
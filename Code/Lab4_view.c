//存放将存储在内存容器中的数据记录显示输出到屏幕上功能的相关函数

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include"Lab4_tools.h"
#include"Lab4_sort.h"
#include"Lab4_data.h"
#include"Lab4_loadfile.h"


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
 * 函数功能：打印链表内容
 * 输入参数：单链表头节点（value为空）NODE* head
 * 返回值：无
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月20日
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
				qsort(data, dataNum, sizeof(data[0]), cmp_for_struct_array_qsort);
			else if (ans == 2)
				qsort(data, dataNum, sizeof(data[0]), cmp_reverse_for_struct_array_qsort);
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
				qsort(data, dataNum, sizeof(data[0]), cmp_for_point_array_qsort);
			else if (ans == 2)
				qsort(data, dataNum, sizeof(data[0]), cmp_reverse_for_point_array_qsort);
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
 * 函数功能：排序并展示数据记录（链表）
 * 输入参数：数据记录文件路径和文件名filename，文件指针fp，用户/开发者模式rootMode
 * 返回值：无
 * 作者：柯劲帆 21281280@bjtu.edu.cn
 * 日期：2022年5月20日
*/
void show_data_in_link_list(char* filename, FILE* fp, int rootMode)
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
	NODE* head = (NODE*)malloc(sizeof(NODE));
	head->next = NULL;
	if (head == NULL)
	{
		printf("出现错误：动态分配内存失败。\n");
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
			printf("数据集处理完毕，按任意键进行排序。");
			getchar();
			char dataStatus[3][5] = { "正序","逆序","乱序" };
			clock_t startTime, finishTime;
			double totalTime = 0;
			startTime = clock();
			bubble_for_link_list(head, dataNum, 0);
			finishTime = clock();
			totalTime = (double)(finishTime - startTime) / CLOCKS_PER_SEC;
			char timeBuffer[30] = { 0 };
			get_time(timeBuffer);
			print_data_in_link_list(head);
			printf("冒泡排序%d条数据，用时%lf秒。", dataNum, totalTime);
			FILE* log;
			log = fopen("Log.csv", "a+");
			if (log == NULL)
			{
				printf("日志文件打开失败，无法将排序用时记入日志。\n");
				exit(0);
			}
			fprintf(log, "链表,%d条,%s,冒泡排序,%lf秒,%s\n", dataNum, dataStatus[ans - 1], totalTime, timeBuffer);
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
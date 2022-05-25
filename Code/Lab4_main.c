//存储run函数的函数实现

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"Lab4_conf.h"
#include"Lab4_call.h"
#include"Lab4_loadfile.h"
#include"Lab4_view.h"
#include"Lab4_data.h"


/**
 * 程序所有的功能实现
*/
void run(int argc, char* argv[])
{
	CONF ini;	//创建结构体变量存储生成数据记录文件的限制参数
	CONF* pIni = &ini;
	char filename[MAX_STR_LEN * 2];

	self_check_and_get_configinfo(pIni, filename);
	int rootMode, userMode;
	rootMode = show_menu_root();
	if (rootMode == 1)
		userMode = show_menu_user();
	else
	{
		userMode = show_menu_developer();
		while (userMode == 1)
		{
			modify_configinfo(pIni);
			userMode = show_menu_developer();
			self_check_and_get_configinfo(pIni, filename);
		}
	}

	if (userMode == 0)
		return 0;
	if (rootMode == 2 && userMode == 2)
		userMode = show_menu_user();

	int dataNumStatus = 1;
	int* pDataNumStatus = &dataNumStatus;
	int filenameStatus = 1;
	int* pFilenameStatus = &filenameStatus;
	if (userMode != 3)
	{
		if (userMode == 1)
		{
			call_program(userMode, pIni, filename, pDataNumStatus, pFilenameStatus);

		}
		if (userMode == 2)
		{
			get_dataNum(pDataNumStatus, pIni);
			get_filename(pFilenameStatus, filename);
			call_program(userMode, pIni, filename, pDataNumStatus, pFilenameStatus);
		}
		if (show_menu_ask_if_read_file() == 0)
			return 0;
	}
	if (userMode == 3)
	{
		filenameStatus = 2;
		get_filename(pFilenameStatus, filename);
	}

	FILE* fp;
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("打开数据记录文件失败，请重试。\n");
		return 0;
	}
	int storeMethod = show_menu_ask_how_to_store();
	if (storeMethod == 1)
	{
		show_data_in_2d_array(filename, fp, rootMode, get_dataNum_from_file(fp));
	}
	else if (storeMethod == 2)
	{
		show_data_in_struct_array(filename, fp, rootMode, get_dataNum_from_file(fp));
	}
	else if (storeMethod == 3)
	{
		show_data_in_point_array(filename, fp, rootMode, get_dataNum_from_file(fp));
	}
	else if (storeMethod == 4)
	{
		show_data_in_link_list(filename, fp, rootMode, get_dataNum_from_file(fp));
	}
	fclose(fp);
	return 0;
}
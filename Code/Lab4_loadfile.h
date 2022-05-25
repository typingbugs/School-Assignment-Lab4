//存放数据加载相关函数的函数声明
#pragma once

#include "Lab4_data.h"


void self_check_and_get_configinfo(CONF* pIni, char* filename);
int change_Filename_to_absolute(char* filename);
void create_path(char* filename);
int check_filename(char* filename);
void get_dataNum(int* pDataNumStatus, CONF* pIni);
void get_filename(int* pFilenameStatus, char* filename);
void store_data_in_2d_array(int(*data)[3], FILE* fp, int dataNum);
void store_data_in_struct_array(DATAITEM* data, FILE* fp, int dataNum);
void store_data_in_point_array(DATAITEM** data, FILE* fp, int dataNum);
void store_data_in_link_list(NODE* head, FILE* fp, int dataNum);
int get_dataNum_from_file(FILE* fp);
//存储模块常用的而主函数不调用的工具函数声明
#pragma once

#include"Lab4_data.h"


int str_to_int(char* numArr);
void free_data_in_point_array(DATAITEM** data, int dataNum);
void free_data_in_link_list(NODE* head);
void get_time(char* buffer);
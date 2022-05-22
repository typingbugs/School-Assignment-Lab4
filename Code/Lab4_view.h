//存放数据显示模块相关函数的函数声明
#pragma once


int show_menu_root();
int show_menu_user();
int show_menu_developer();
int show_menu_ask_if_read_file();
int show_menu_ask_how_to_store();
void show_data_in_2d_array(char* filename, FILE* fp, int rootMode);
void show_data_in_struct_array(char* filename, FILE* fp, int rootMode);
void show_data_in_point_array(char* filename, FILE* fp, int rootMode);
void show_data_in_link_list(char* filename, FILE* fp, int rootMode);
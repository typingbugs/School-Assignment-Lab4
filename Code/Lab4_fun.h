#pragma once
//存储各个子函数声明

#include<stdio.h>
#include "Lab4_data.h"


void self_check_and_get_configinfo(CONF* pIni, char* filename);
int change_Filename_to_absolute(char* filename);
void create_path(char* filename);
int check_filename(char* filename);
int show_menu_root();
int show_menu_user();
int show_menu_developer();
void modify_configinfo(CONF* pIni);
void get_dataNum(int* pDataNumStatus, CONF* pIni);
void get_filename(int* pFilenameStatus, char* filename);
void call_program(int autoMode, CONF* pIni, char* filename, int* pDataNumStatus, char* pFilenameStatus);
int show_menu_ask_if_read_file();
int show_menu_ask_how_to_store();
void show_data_in_2d_array(char* filename, FILE* fp, int rootMode);
void show_data_in_struct_array(char* filename, FILE* fp, int rootMode);
void show_data_in_point_array(char* filename, FILE* fp, int rootMode);
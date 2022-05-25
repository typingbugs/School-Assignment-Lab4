//存放与排序功能相关功能函数的函数声明
#pragma once

int cmp_for_2d_array_qsort(const void* a, const void* b);
int cmp_reverse_for_2d_array_qsort(const void* a, const void* b);
int cmp_for_struct_array_qsort(const void* a, const void* b);
int cmp_reverse_for_struct_array_qsort(const void* a, const void* b);
int cmp_for_point_array_qsort(const void** a, const void** b);
int cmp_reverse_for_point_array_qsort(const void** a, const void** b);
void bubble_for_link_list(NODE* head, int dataNum, int reverse);
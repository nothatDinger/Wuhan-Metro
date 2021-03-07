#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <stdio.h>
#include <stdlib.h>
#define HASHSIZE 1007 //定义散列表长为数组的长度
#define NUM_NULL -1


extern void InitHashTable();
extern void Insert_Hash(char* data,int id);
extern int Search(char*data);
// #ifdef __cplusplus
// extern "C" {
// #endif

// void InitHashTable();
// void Insert_Hash(char* data,int id);
// int Search(char*data);
// #ifdef __cplusplus
// }
// #endif
#endif // HASHTABLE_H

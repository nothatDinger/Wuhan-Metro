#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <stdio.h>
#include <stdlib.h>
#define HASHSIZE 1007 //定义散列表长为数组的长度
#define NUM_NULL -1


void InitHashTable();
void Insert_Hash(char* data,int id);
int Search(char*data);

#endif // HASHTABLE_H

#include"hashtable.h"
#include<string.h>
int HashTable[HASHSIZE];
int hashvalue[HASHSIZE];

// @description 初始化哈希表
// @params None
// @return None
void InitHashTable(){
    memset(HashTable,-1,sizeof(HashTable));
    memset(HashTable,-1,sizeof(HashTable));
}
// @description ELF哈希函数
// @params char* 待hash的字符串
// @return int 得到的哈希值
unsigned int ELFHash(char *str){
    unsigned int hash = 0;
    unsigned int x = 0;
     while (*str){
        hash = (hash << 4) + (*str++);//hash左移4位，当前字符ASCII存入hash低四位。
        if ((x = hash & 0xF0000000L) != 0){//如果最高的四位不为0，则说明字符多余7个，如果不处理，再加第九个字符时，第一个字符会被移出，因此要有如下处理。
                                            //该处理，如果对于字符串(a-z 或者A-Z)就会仅仅影响5-8位，否则会影响5-31位，因为C语言使用的算数移位
        hash ^= (x >> 24);//清空28-31位。
        hash &= ~x;
        }
    }
    //返回一个符号位为0的数，即丢弃最高位，以免函数外产生影响。(我们可以考虑，如果只有字符，符号位不可能为负)
    return (hash & 0x7FFFFFFF);
}

// @description 向哈希表插入一个元素
// @params char* 待插入字符串 ，id 站点id（哈希表存的值）
// @return None
//哈希表的插入函数，可用于构造哈希表
void Insert_Hash(char* data,int id){
    int hash=ELFHash(data);
    int hashAddress = hash % HASHSIZE;//求哈希地址
    while( HashTable[hashAddress] != NUM_NULL  )//处理冲突
        hashAddress = ( hashAddress + 1 ) % HASHSIZE;
    hashvalue[hashAddress] = hash;
    HashTable[hashAddress] = id;
}
// @description 在哈希表中查找一个一个字符串对应的值
// @params char* 待查找的字符串
// @return id 站点id or NUM_NULL(未找到)
int Search(char* data){
    int hash=ELFHash(data);
    int hashAddress=hash % HASHSIZE;//求哈希地址
    int i;
    for( i = 0 ; i < HASHSIZE; i++){
        if( hashvalue[hashAddress] != hash)
            hashAddress = ( hashAddress + 1 ) % HASHSIZE;
        else
            return HashTable[hashAddress];
    }
    return NUM_NULL;
}


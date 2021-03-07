#include"HashTable.h"
#include"line_station.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
Stations TotalStaions[STATIONSIZE];
Lines TotalLines[LINESIZE];
int MaxLineNum;
Edges edge[1000];
int hea[400];
int edgeNum;
int StationNum;
int LineNum;
extern int HashTable[HASHSIZE];
extern int hashvalue[HASHSIZE];
int HashTable[HASHSIZE];
int hashvalue[HASHSIZE];
//哈希函数(除留余数法)
void InitHashTable(){
    memset(HashTable,-1,sizeof(HashTable));
    memset(HashTable,-1,sizeof(HashTable));
}

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

//哈希表的插入函数，可用于构造哈希表
void Insert_Hash(char* data,int id){
    int hash=ELFHash(data);
    int hashAddress = hash % HASHSIZE;//求哈希地址
    while( HashTable[hashAddress] != NUM_NULL  )//处理冲突
        hashAddress = ( hashAddress + 1 ) % HASHSIZE;
    HashTable[hashAddress] = id;
    hashvalue[hashAddress] = hash;
}

int Search(char* data){
    int hash=ELFHash(data);
    int hashAddress=hash % HASHSIZE;//求哈希地址
    while( hashvalue[hashAddress] != hash)
        hashAddress = ( hashAddress + 1 ) % HASHSIZE;
    return HashTable[hashAddress];
}
int readFile(){

    FILE *fp;
    fp = fopen("C:/Users/13476726334/Desktop/DIR/WorkDirForVSC/C/SubwaySystem/SubwayTransferSystem/SubwayTransferSystem/data/subway.CSV","rb");
    if (!fp) {
        fprintf(stderr, "failed to open file for reading\n");
        return 0;
    }

    char line[100];
    char *result = NULL;
    char *linename = NULL;
    char *lontitude = NULL;
    char *latitude = NULL;
    char *linenum = NULL;
    int num=0,i;
    InitHashTable();
    while(fgets(line, 100, fp) != NULL) {

        result = strtok(line, ",");     
        while( result != NULL ) {
            result = strtok(line, ",");  
            linename = strtok(NULL, ",");
            latitude = strtok(NULL, ",");
            lontitude = strtok(NULL, ",");
            linenum = strtok(NULL, ",");
            
            // for(i = 0 ; linenum[i];i++)
            //     if(linename[i]=='\n'){
            //         linename[i] = 0;
            //         break;
            //     }
            
            int num_in_hash = Search(result);
            if( num_in_hash == NUM_NULL){
                TotalStaions[num].name = (char*)malloc(sizeof(char)*strlen(result));
                strcpy(TotalStaions[num].name,result);
                TotalStaions[num].stationID=num;
                Insert_Hash(result,num);

                TotalStaions[num].lontitude = strtod(lontitude,NULL);
                TotalStaions[num].latitude = strtod(latitude,NULL);

            }
            int linenumber = atoi(linenum);
            if(MaxLineNum < linenumber){
                int tmp = (num_in_hash == NUM_NULL)? num:num_in_hash;
                MaxLineNum = linenumber;
                TotalLines[linenumber].startStationID=tmp;
                TotalLines[linenumber].stat[++TotalLines[linenumber].statLength] = tmp;
            }
            num++;
            printf("%s",result);
            result = strtok(NULL, ",");
        }
        //printf("\n");
    }
    StationNum = num;
    LineNum = LINESIZE - 1;
    for(i=0;i<MaxLineNum;i++){
        TotalLines[i].finalStationID = TotalLines[i].stat[TotalLines[i].statLength-1];
    }
    fclose(fp);
    //qDebug() << QString("hello");
    printf("%s","hello");
    return 1;
}
int main(){
    int flag = readFile();
}

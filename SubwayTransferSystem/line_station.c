#include"line_station.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include <unistd.h>
//#include<QDebug>
#define PI 3.1415926
#define EARTH_RADIUS 6378.137
Stations TotalStaions[STATIONSIZE];
Lines TotalLines[LINESIZE];
int MaxLineNum;
Edges edge[1000];
int hea[400];
int edgeNum;
int StationNum;


// @description 根据简化约定设置线路各个时间点的拥挤度
// @params None
// @return None
void crowd_simulation_init(){
    int i ;
    for(i = 0 ; i <= 24*60; i++){
        TotalLines[1].crowd.value[i] = 40;
        TotalLines[2].crowd.value[i] = 50;
        TotalLines[3].crowd.value[i] = 40;
        TotalLines[4].crowd.value[i] = 50;
        TotalLines[6].crowd.value[i] = 15;
        TotalLines[7].crowd.value[i] = 15;
        TotalLines[8].crowd.value[i] = 20;
        TotalLines[9].crowd.value[i] = 10;
        TotalLines[11].crowd.value[i] = 10;
    }
    for( i = 7*60+30;i<=9*60;i ++){
        TotalLines[1].crowd.value[i] = 80;
        TotalLines[3].crowd.value[i] = 80;
    }
    for( i = 16*60+30;i<=18*60+30;i ++){
        TotalLines[1].crowd.value[i] = 80;
        TotalLines[3].crowd.value[i] = 80;
    }
    for( i = 9*60+30;i<=15*60;i ++){
        TotalLines[8].crowd.value[i] = 65;
    }
    for( i = 19*60;i<=20*60;i ++){
        TotalLines[6].crowd.value[i] = 65;
        TotalLines[7].crowd.value[i] = 65;
    }

}
// @description 读入文件中的站点数据并进行全局初始化
// @params None
// @return Mone
int readFile_txt(){

    FILE *fp;
    char buff[300];
    getcwd(buff,sizeof(buff));
    strcat(buff,".\\data\\subway.txt");
    fp = fopen(buff,"r");
    if (!fp) {
        fprintf(stderr, "failed to open file for reading\n");
        return 0;
    }

    char stationname[50];
    char linename[50];
    double longtitude,latitude;
    int linenum,num=0,i;
    InitHashTable();
    while(fscanf(fp,"%s %s %lf %lf %d",stationname,linename,&latitude,&longtitude,&linenum)!=EOF) {
        int num_in_hash = Search(stationname);
        int tmp = (num_in_hash == NUM_NULL)? num:num_in_hash;
        if( num_in_hash == NUM_NULL){//                                     对站点名hash处理
            strcpy(TotalStaions[num].name,stationname);
            TotalStaions[num].stationID=num;
            Insert_Hash(stationname,num);
            TotalStaions[num].lontitude = longtitude;
            TotalStaions[num].latitude = latitude;
            num++;
        }
        if( MaxLineNum < linenum ){//                                       将各种线路站点信息存入全局变量数组里
            TotalStaions[tmp].linesInfo[TotalStaions[tmp].linesLength++] = linenum;
            strcpy(TotalLines[linenum].name,linename);
            MaxLineNum = linenum;
            TotalLines[linenum].startStationID=tmp;
            TotalLines[linenum].lineID = linenum;
            TotalLines[linenum].stat[TotalLines[linenum].statLength++] = tmp;
            TotalLines[linenum].bus_gap = 3;
        }
        else if(MaxLineNum == linenum){
            TotalLines[linenum].stat[TotalLines[linenum].statLength++] = tmp;
            TotalStaions[tmp].linesInfo[TotalStaions[tmp].linesLength++] = linenum;
        }
    }
    StationNum = num;
    for(i=0;i<MaxLineNum;i++){
        TotalLines[i].finalStationID = TotalLines[i].stat[TotalLines[i].statLength-1];
        TotalLines[i].startStationID = TotalLines[i].stat[0];
    }
    crowd_simulation_init();
    fclose(fp);
    return 1;
}


// @description 转换角度为弧度
// @params double 角度
// @return double 弧度
double radian(double d)
{
    return d * PI / 180.0;   //角度1˚ = π / 180
}

// @description 根据两个地点的敬畏度计算距离（单位为km）
// @params double * 4 纬度 经度 纬度 经度
// @return double 距离
double get_distance(double lat1, double lng1, double lat2, double lng2)
{
    double radLat1 = radian(lat1);
    double radLat2 = radian(lat2);
    double a = radLat1 - radLat2;
    double b = radian(lng1) - radian(lng2);

    double dst = 2 * asin((sqrt(pow(sin(a / 2), 2) + cos(radLat1) * cos(radLat2) * pow(sin(b / 2), 2) )));

    dst = dst * EARTH_RADIUS;
    dst= round(dst * 10000) / 10000;
    return dst;
}

// @description 根据存储的线路和站点信息构建图的邻接表
// @params None
// @return None
void constructGraph(){
    int i,j,edgeNum=0;
    for(i=0;i<=MaxLineNum;i++){
        for(j=0;j<TotalLines[i].statLength-1;j++){
            int u = TotalStaions[TotalLines[i].stat[j]].stationID, v = TotalStaions[TotalLines[i].stat[j+1]].stationID;
            double dst = get_distance(TotalStaions[u].latitude,TotalStaions[u].lontitude,TotalStaions[v].latitude,TotalStaions[v].lontitude);
            edge[++edgeNum] = (Edges){dst,v,hea[u],i,6*60+3*j};
            hea[u]= edgeNum;
            edge[++edgeNum] = (Edges){dst,u,hea[v],i,6*60+3*(TotalLines[i].statLength-2-j)};
            hea[v]= edgeNum;
        }
    }
}

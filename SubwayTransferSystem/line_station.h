#ifndef LINE_STATION_H
#define LINE_STATION_H

#include"hashtable.h"
#include<stdio.h>
#define STATIONSIZE 400
#define LINESIZE 12
typedef struct Stations{
    double lontitude;//经度
    double latitude;//纬度
    int stationID;//站点的ID
    char name[50];//站点的名字
    int linesInfo[4];//存储该站点经过的地铁线的ID
    int linesLength;//上个数组的长度
}Stations;

typedef struct Crowd{
    int value[1441];//一天一共1440min
}Crowd;
typedef struct Lines{
    int lineID;// the ID identifies different line
    char name[50];// the name of a LINE such as "3号线"
    int stat[40];// the array that stores the stationId which belongs to the line
    int statLength;// the length of the array above
    int startStationID;// the ID of first station in this line which identifies the direction
    int finalStationID;//
    int bus_gap;// the gap between each bus of the line which is set 2min
    Crowd crowd;// the extend of crowd across the whole day
}Lines;
typedef struct Edges
{
    double len; //the length of the edge which is calculated by the longtitude and latitude
    int to;// the destination of the edge (there's a departure station hidden in the struct)
    int nex;//the pointer pointing next Edge struct
    int LineID;// the ID of the line
    int first_bus_arrival_time;// the first bus arives the departure station of the edge
}Edges;

#ifdef __cplusplus
extern "C" {
#endif
int readFile_txt();
void constructGraph();

#ifdef __cplusplus
}
#endif






#endif // LINE_STATION_H

#ifndef LINE_STATION_H
#define LINE_STATION_H

#include"HashTable.h"
#include<stdio.h>
#define STATIONSIZE 400
#define LINESIZE 12
typedef struct Stations{
    double lontitude;
    double latitude;
    int stationID;
    char name[100];
    int linesInfo[10];
    int linesLength;
}Stations;

typedef struct Crowd{
    int value[1441];
}Crowd;
typedef struct Lines{
    int lineID;
    char name[100];
    int stat[40];
    int statLength;
    int startStationID;
    int finalStationID;
    int bus_gap;
    Crowd crowd;
}Lines;

#ifdef __cplusplus
extern "C" {
#endif
int readFile_txt();
void constructGraph();

#ifdef __cplusplus
}
#endif



typedef struct Edges
{
    double len;
    int to;
    int nex;
    int LineID;
    int first_bus_arrival_time;
}Edges;



#endif // LINE_STATION_H

#ifndef TRANSFER_H
#define TRANSFER_H
//#include"HashTable.h"
#include"line_station.h"
#define inf 2147483647

typedef struct
{
    int station;
    int line;
}st;

typedef struct{
    int status;
    st stationlist[200];
    int len;
    double price;
    int transfer_times;
    double time;
    int next_bus_arrival;
    int av_crowd;
}Solution;

typedef struct{
    int starttime;
    int startID;
    int endID;
    int tolerance;
    int mode;
}Request;


#ifdef __cplusplus
extern "C" {
#endif
Solution time_min_spfa(Request a);

Solution transfer_min_spfa(Request a);

Solution transfer_min_dfs(Request a);

Solution price_min_spfa(Request a);

Solution sum_time_min_spfa(Request a);
#ifdef __cplusplus
}

#endif


#endif // TRANSFER_H

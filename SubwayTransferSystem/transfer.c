#include"transfer.h"
#include"line_station.h"
#include<string.h>
#include<stdio.h>
#define CMSPT_BTW_STA 2
#define QUEUESIZE 400
extern Stations TotalStaions[STATIONSIZE];
extern Lines TotalLines[LINESIZE];
extern int MaxLineNum;
extern Edges edge[1000];
extern int hea[400];
extern int edgeNum;
extern int StationNum;

int queue[QUEUESIZE],front,tail;
int book[STATIONSIZE];
int dis[STATIONSIZE];
int path[STATIONSIZE];
int transfer[STATIONSIZE];
double time[STATIONSIZE];
int crowd[STATIONSIZE];

// @description 转换不同线路不同时间的拥挤读为拥挤系数
// @params id int 线路id， time int 当前时间
// @return double 拥挤系数
double crowd_index_convert(int id,int time){
    int crowd = TotalLines[id].crowd.value[time];
    if(crowd <= 20)
        return 0.6;
    if(crowd >= 75)
        return 1.5;
    return 1.0;
}

// @description 转换乘车距离为对应的票价
// @params distance int 乘车距离
// @return double 对应的价格
double get_price(int dis){
    if( dis <= 4.0 )
        return 2.0;
    if( dis > 4.0 && dis <= 12.0 )
        return dis/4;
    if( dis > 12.0 && dis <= 24.0 )
        return dis/6;
    if( dis > 24.0 && dis <= 40.0 )
        return dis/8;
    if( dis > 40.0 && dis <= 50.0 )
        return dis/10;
    return dis/20;
}
// @description 获取站点在对应线路的数组索引
// @params u int 站点id， line int 线路id
// @return i int 对应的索引
int  get_index_from_line(int u,int line){
    int i;
    for(i = 0 ; i< TotalLines[line].statLength;i++)
        if( TotalLines[line].stat[i] == u)
            return i;
    return -1;
}
// @description 为三种策略的最短路算法进行初始化
// @params None
// @return None
void dij_init(){
    memset(queue,0,sizeof(queue));
    memset(book,0,sizeof(book));
    memset(path,-1,sizeof(path));
    memset(crowd,0,sizeof (crowd));
    memset(transfer,0,sizeof(transfer));
    for(front = 0 ; front < STATIONSIZE ; front ++ )
        dis[front] = time[front] = inf;
    front = tail=0;
}
// @description 以拥挤度加权时间最优进行spfa算法
// @params struct Request 完成一次路径规划服务的必要参数
// @return strcut Solution  路径规划的结果
Solution time_min_spfa(Request a ){
    dij_init();
    Solution b;
    dis[a.startID] = 0;
    time[a.startID] = 0;
    queue[tail++] = a.startID;
    book[a.startID] = 1;
    crowd[a.startID]=0;
    int i;
    while(front!=tail){
        int u = queue[front];

        for(i = hea[u]; i ; i = edge[i].nex){
            int v = edge[i].to,w = CMSPT_BTW_STA;

            if(TotalLines[edge[i].LineID].crowd.value[a.starttime]>a.tolerance)//针对拥挤度超过容忍度的剪枝
                continue;
            if( u == a.startID ){//这个if分支做特殊判断，方便确认出发时采取的线路的id，并处理出发时间没有车在站点的特殊情况
                time[u]=0;
                transfer[u] = edge[i].LineID;
                if( a.starttime < edge[i].first_bus_arrival_time )
                       time[u]+= edge[i].first_bus_arrival_time - a.starttime ;
                else{
                    int j;
                    for( j = 0 ; a.starttime >= edge[i].first_bus_arrival_time+3*j-1; j ++ );
                    if( a.starttime < edge[i].first_bus_arrival_time+3*j )
                        time[u] +=(edge[i].first_bus_arrival_time+3*j)-a.starttime;
                }

            }

            int time_start = time[u] + a.starttime,j;
            double value = 0;
            for(j=0;j<w;j++)//这个for循环用来处理加权时间
                value += crowd_index_convert(edge[i].LineID,j+time_start);

            if(edge[i].LineID!=transfer[u]){//这个if分支用来处理换线时消耗的额外代价
                value+=3;
                int j;
                for( j = 0 ; a.starttime+time[u]+value >= edge[i].first_bus_arrival_time+3*j-1; j ++ );
                if( a.starttime+time[u]+value < edge[i].first_bus_arrival_time+3*j )
                    value += (edge[i].first_bus_arrival_time+3*j) - a.starttime+value;
            }
            if(time[v]>time[u]+value){//进行松弛
                crowd[v] += crowd[u]+ TotalLines[edge[i].LineID].crowd.value[time_start];
                path[v] = u ;
                time[v] = time[u] + value;
                dis[v] = dis[u] + edge[i].len;
                transfer[v]= edge[i].LineID;

                if( !book[v]){
                    queue[tail++] = v;
                    book[v] = 1 ;
                }
            }
        }
        front++;
        book[u] = 0;
    }
    a.starttime = a.starttime+time[a.startID];

    int tmp = a.endID;
    while( tmp != -1){
        b.stationlist[b.len++] = (st){tmp,transfer[tmp]};
        tmp = path[tmp];
    }
    b.stationlist[b.len-1].line = b.stationlist[b.len-2].line;

    tmp = b.stationlist[0].line;
    b.transfer_times = 0;
    b.av_crowd = 0;
    for(i=1;i<b.len;i++){
        int j;
        for(j=0;j<TotalStaions[b.stationlist[i].station].linesLength;j++)
            if( TotalStaions[b.stationlist[i].station].linesInfo[j] == tmp)
                b.stationlist[i].line = tmp;

        if(tmp != b.stationlist[i].line){
            b.transfer_times++;
            tmp = b.stationlist[i].line;
        }
        b.av_crowd += TotalLines[b.stationlist[i].line].crowd.value[a.starttime+i*2];
    }
    if(b.len>1){
        b.av_crowd += TotalLines[b.stationlist[0].line].crowd.value[a.starttime];
        b.av_crowd /= b.len;
    }
    int index = get_index_from_line(a.startID,transfer[a.startID]),stat_len=0;
    if( index == 0 || index == TotalLines[transfer[a.startID]].statLength - 1)
        stat_len = 0;
    else if( b.stationlist[b.len-2].station == TotalLines[transfer[a.startID]].stat[index-1])
        stat_len = index;
    else if( b.stationlist[b.len-2].station == TotalLines[transfer[a.startID]].stat[index+1])
        stat_len = TotalLines[transfer[a.startID]].statLength - 1 - index;
    b.next_bus_arrival = stat_len *(2+1) + 6 * 60 ;
    while(b.next_bus_arrival < a.starttime )
        b.next_bus_arrival +=3;

    b.time = time[a.endID] + b.next_bus_arrival - a.starttime ;
    //b.transfer_times = transfer[a.endID];
    b.price = get_price(dis[a.endID]);
    b.status = 1;
    if( a.starttime <6*60|| a.starttime + b.time > 23*60 )
        b.status = 2;
    if(time[a.endID] == inf)
        b.status= 0 ;
    return b;
}
// @description 以总时间最优进行spfa算法
// @params struct Request 完成一次路径规划服务的必要参数
// @return strcut Solution  路径规划的结果
Solution sum_time_min_spfa(Request a ){
    dij_init();
    Solution b;
    dis[a.startID] = 0;
    time[a.startID] = 0;
    queue[tail++] = a.startID;
    book[a.startID] = 1;
    crowd[a.startID]=0;
    int i;
    while(front!=tail){
        int u = queue[front];

        for(i = hea[u]; i ; i = edge[i].nex){
            int v = edge[i].to,w = CMSPT_BTW_STA;

            if(TotalLines[edge[i].LineID].crowd.value[a.starttime]>a.tolerance)
                continue;
            if( u == a.startID ){
                time[u]=0;
                transfer[u] = edge[i].LineID;
                if( a.starttime < edge[i].first_bus_arrival_time )
                       time[u]+= edge[i].first_bus_arrival_time - a.starttime ;
                else{
                    int j;
                    for( j = 0 ; a.starttime >= edge[i].first_bus_arrival_time+3*j-1; j ++ );
                    if( a.starttime < edge[i].first_bus_arrival_time+3*j )
                        time[u] +=(edge[i].first_bus_arrival_time+3*j)-a.starttime;
                }

            }

            int time_start = time[u] + a.starttime,j;
            double value = 0;
            for(j=0;j<w;j++)
                value += crowd_index_convert(edge[i].LineID,j+time_start);
            if(edge[i].LineID!=transfer[u]){
                value+=3;
                int j;
                for( j = 0 ; a.starttime+time[u]+value >= edge[i].first_bus_arrival_time+3*j-1; j ++ );
                if( a.starttime+time[u]+value < edge[i].first_bus_arrival_time+3*j )
                    value += (edge[i].first_bus_arrival_time+3*j) - a.starttime+value;
            }
            if(time[v]>time[u]+w){
                crowd[v] += crowd[u]+ TotalLines[edge[i].LineID].crowd.value[time_start];
                path[v] = u ;
                time[v] = time[u] + value;
                dis[v] = dis[u] + edge[i].len;
                transfer[v]= edge[i].LineID;


                if( !book[v]){
                    queue[tail++] = v;
                    book[v] = 1 ;
                }
            }
        }
        front++;
        book[u] = 0;
    }
    a.starttime = a.starttime+time[a.startID];

    int tmp = a.endID;
    while( tmp != -1){
        b.stationlist[b.len++] = (st){tmp,transfer[tmp]};
        tmp = path[tmp];
    }
    b.stationlist[b.len-1].line = b.stationlist[b.len-2].line;

    tmp = b.stationlist[0].line;
    b.transfer_times = 0;
    b.av_crowd = 0;
    for(i=1;i<b.len;i++){
        int j;
        for(j=0;j<TotalStaions[b.stationlist[i].station].linesLength;j++)//���������·����·ʱ��bug
            if( TotalStaions[b.stationlist[i].station].linesInfo[j] == tmp)
                b.stationlist[i].line = tmp;

        if(tmp != b.stationlist[i].line){
            b.transfer_times++;
            tmp = b.stationlist[i].line;
        }
        b.av_crowd += TotalLines[b.stationlist[i].line].crowd.value[a.starttime+i*2];
    }
    if(b.len>1){
        b.av_crowd += TotalLines[b.stationlist[0].line].crowd.value[a.starttime];
        b.av_crowd /= b.len;
    }
    int index = get_index_from_line(a.startID,transfer[a.startID]),stat_len=0;
    if( index == 0 || index == TotalLines[transfer[a.startID]].statLength - 1)
        stat_len = 0;
    else if( b.stationlist[b.len-2].station == TotalLines[transfer[a.startID]].stat[index-1])
        stat_len = index;
    else if( b.stationlist[b.len-2].station == TotalLines[transfer[a.startID]].stat[index+1])
        stat_len = TotalLines[transfer[a.startID]].statLength - 1 - index;
    b.next_bus_arrival = stat_len *(2+1) + 6 * 60 ;
    while(b.next_bus_arrival < a.starttime )
        b.next_bus_arrival +=3;

    b.time = time[a.endID] + b.next_bus_arrival - a.starttime ;
    //b.transfer_times = transfer[a.endID];
    b.price = get_price(dis[a.endID]);

    b.status = 1;
    if( a.starttime <6*60|| a.starttime + b.time > 23*60 )
        b.status = 2;
    if(time[a.endID] == inf)
        b.status= 0 ;
    return b;
}

// @description 以换乘次数最少为指标进行spfa算法
// @params struct Request 完成一次路径规划服务的必要参数
// @return strcut Solution  路径规划的结果
Solution transfer_min_spfa(Request a){
    double tran[STATIONSIZE];
    int i;
    for(i = 0 ; i < STATIONSIZE ; i ++ )
        tran[i] = inf;
    dij_init();
    Solution b;
    dis[a.startID] = 0;
    time[a.startID] = 0;
    tran[a.startID] = 0;
    queue[tail++] = a.startID;
    book[a.startID] = 1;
    crowd[a.startID] = 0;
    while(front!=tail){
        int u = queue[front];
        for(i = hea[u]; i ; i = edge[i].nex){
            int v = edge[i].to,w = CMSPT_BTW_STA;

            if(TotalLines[edge[i].LineID].crowd.value[a.starttime]>a.tolerance)
                continue;

            if( u == a.startID ){
                transfer[u] = edge[i].LineID;
                if( a.starttime < edge[i].first_bus_arrival_time )
                       time[u]+= edge[i].first_bus_arrival_time - a.starttime;
                else{
                    int j;
                    for( j = 0 ; a.starttime >= edge[i].first_bus_arrival_time+3*j-1; j ++ );
                    if( a.starttime < edge[i].first_bus_arrival_time+3*j )
                        time[u] +=(edge[i].first_bus_arrival_time+3*j)-a.starttime;
                }
            }

            int time_start = time[u] + a.starttime,j;
            double value = 0;
            for(j=0;j<w;j++)
                value += crowd_index_convert(edge[i].LineID,j+time_start);
            if(edge[i].LineID!=transfer[u]){
                value+=3;
                int j;
                for( j = 0 ; a.starttime+time[u]+value >= edge[i].first_bus_arrival_time+3*j-1; j ++ );
                if( a.starttime+time[u]+value < edge[i].first_bus_arrival_time+3*j )
                    value += (edge[i].first_bus_arrival_time+3*j) - a.starttime+value;
            }
            double value4tran = value;
            if(transfer[u]!=edge[i].LineID)
                value4tran = 1e8;
            if(tran[v]>tran[u]+value4tran){
                crowd[v] += crowd[u] + TotalLines[edge[i].LineID].crowd.value[time_start];
                path[v] = u ;
                time[v] = time[u] + value;
                tran[v] = tran[u] + value4tran;
                dis[v] = dis[u] + edge[i].len;
                transfer[v]= edge[i].LineID;

                if( !book[v]){
                    queue[tail++] = v;
                    book[v] = 1 ;
                }
            }
        }
        front++;
        book[u] = 0;
    }
    a.starttime = a.starttime+time[a.startID];
    int tmp = a.endID;
    while( tmp != -1){
        b.stationlist[b.len++] = (st){tmp,transfer[tmp]};
        tmp = path[tmp];
    }
    b.stationlist[b.len-1].line = b.stationlist[b.len-2].line;

    int index = get_index_from_line(a.startID,transfer[a.startID]),stat_len=0;
    if( index == 0 || index == TotalLines[transfer[a.startID]].statLength - 1)
        stat_len = 0;
    else if( b.stationlist[b.len-2].station == TotalLines[transfer[a.startID]].stat[index-1])
        stat_len = index;
    else if( b.stationlist[b.len-2].station == TotalLines[transfer[a.startID]].stat[index+1])
        stat_len = TotalLines[transfer[a.startID]].statLength - 1 - index;
    b.next_bus_arrival = stat_len *(2+1) + 6 * 60 ;
    while(b.next_bus_arrival < a.starttime )
        b.next_bus_arrival +=3;

    tmp = b.stationlist[0].line;
    b.transfer_times = 0;
    b.av_crowd = 0;
    for(i=1;i<b.len;i++){
        int j;
        for(j=0;j<TotalStaions[b.stationlist[i].station].linesLength;j++)//���������·����·ʱ��bug
            if( TotalStaions[b.stationlist[i].station].linesInfo[j] == tmp)
                b.stationlist[i].line = tmp;

        if(tmp != b.stationlist[i].line){
            b.transfer_times++;
            tmp = b.stationlist[i].line;
        }
        b.av_crowd += TotalLines[b.stationlist[i].line].crowd.value[a.starttime+i*2];
    }
    if(b.len>1){
        b.av_crowd += TotalLines[b.stationlist[0].line].crowd.value[a.starttime];
        b.av_crowd /= b.len;
    }

    b.time = time[a.endID] + b.next_bus_arrival - a.starttime ;
    b.price = get_price(dis[a.endID]);
    b.status = 1;
    if( a.starttime <6*60|| a.starttime + b.time > 23*60 )
        b.status = 2;
    if(time[a.endID] == inf)
        b.status= 0 ;
    return b;
}

// @description 以票价最少（路途最短）为指标进行spfa算法
// @params struct Request 完成一次路径规划服务的必要参数
// @return strcut Solution  路径规划的结果
Solution price_min_spfa(Request a){
    dij_init();
    Solution b;
    dis[a.startID] = 0;
    time[a.startID] = 0;
    queue[tail++] = a.startID;
    book[a.startID] = 1;
    crowd[a.startID]=0;
    int i;
    while(front!=tail){
        int u = queue[front];

        for(i = hea[u]; i ; i = edge[i].nex){
            int v = edge[i].to,w = CMSPT_BTW_STA;

            if(TotalLines[edge[i].LineID].crowd.value[a.starttime]>a.tolerance)
                continue;
            if( u == a.startID ){
                time[u]=0;
                transfer[u] = edge[i].LineID;
                if( a.starttime < edge[i].first_bus_arrival_time )
                       time[u]+= edge[i].first_bus_arrival_time - a.starttime ;
                else{
                    int j;
                    for( j = 0 ; a.starttime >= edge[i].first_bus_arrival_time+3*j-1; j ++ );
                    if( a.starttime < edge[i].first_bus_arrival_time+3*j )
                        time[u] +=(edge[i].first_bus_arrival_time+3*j)-a.starttime;
                }

            }

            int time_start = time[u] + a.starttime,j;
            double value = 0;
            for(j=0;j<w;j++)
                value += crowd_index_convert(edge[i].LineID,j+time_start);
            if(edge[i].LineID!=transfer[u]){
                value+=3;
                int j;
                for( j = 0 ; a.starttime+time[u]+value >= edge[i].first_bus_arrival_time+3*j-1; j ++ );
                if( a.starttime+time[u]+value < edge[i].first_bus_arrival_time+3*j )
                    value += (edge[i].first_bus_arrival_time+3*j) - a.starttime+value;
            }
            if(dis[v]>dis[u]+edge[i].len){
                crowd[v] += crowd[u]+ TotalLines[edge[i].LineID].crowd.value[time_start];
                path[v] = u ;
                time[v] = time[u] + value;
                dis[v] = dis[u] + edge[i].len;
                transfer[v]= edge[i].LineID;

                if( !book[v]){
                    queue[tail++] = v;
                    book[v] = 1 ;
                }
            }
        }
        front++;
        book[u] = 0;
    }
    a.starttime = a.starttime+time[a.startID];

    int tmp = a.endID;
    while( tmp != -1){
        b.stationlist[b.len++] = (st){tmp,transfer[tmp]};
        tmp = path[tmp];
    }
    b.stationlist[b.len-1].line = b.stationlist[b.len-2].line;

    tmp = b.stationlist[0].line;
    b.transfer_times = 0;
    b.av_crowd = 0;
    for(i=1;i<b.len;i++){
        int j;
        for(j=0;j<TotalStaions[b.stationlist[i].station].linesLength;j++)
            if( TotalStaions[b.stationlist[i].station].linesInfo[j] == tmp)
                b.stationlist[i].line = tmp;

        if(tmp != b.stationlist[i].line){
            b.transfer_times++;
            tmp = b.stationlist[i].line;
        }
        b.av_crowd += TotalLines[b.stationlist[i].line].crowd.value[a.starttime+i*2];
    }
    if(b.len>1){
        b.av_crowd += TotalLines[b.stationlist[0].line].crowd.value[a.starttime];
        b.av_crowd /= b.len;
    }

    int index = get_index_from_line(a.startID,transfer[a.startID]),stat_len=0;
    if( index == 0 || index == TotalLines[transfer[a.startID]].statLength - 1)
        stat_len = 0;
    else if( b.stationlist[b.len-2].station == TotalLines[transfer[a.startID]].stat[index-1])
        stat_len = index;
    else if( b.stationlist[b.len-2].station == TotalLines[transfer[a.startID]].stat[index+1])
        stat_len = TotalLines[transfer[a.startID]].statLength - 1 - index;
    b.next_bus_arrival = stat_len *(2+1) + 6 * 60 ;
    while(b.next_bus_arrival < a.starttime )
        b.next_bus_arrival +=3;

    b.time = time[a.endID] + b.next_bus_arrival - a.starttime ;
    b.price = get_price(dis[a.endID]);
    b.status = 1;
    if( a.starttime <6*60|| a.starttime + b.time > 23*60 )
        b.status = 2;
    if(time[a.endID] == inf)
        b.status= 0 ;
    return b;
}

void dfs(int u,int line,int ditina,int starttime,int tolerance){
    int i;
    for( i = hea[u]; i ; i = edge[i].nex){
        int v = edge[i].to, w = CMSPT_BTW_STA;
        if(TotalLines[edge[i].LineID].crowd.value[starttime]>tolerance)
                continue;
        if(edge[i].LineID != line)
            continue;
        if(!book[v]){
            path[v]=u;
            book[v]=1;
            transfer[v] = line;
            int time_start = time[u] + starttime,value = 0,j;
            for(j=0;j<w;j++)
                value += crowd_index_convert(edge[i].LineID,j+time_start);
            time[v] = time[u] + value;
            dis[v] = dis[u] + edge[i].len;
            queue[tail++] = v;
            if(v == ditina)
                return ;
            dfs(v,line,ditina,starttime,tolerance);
        }
    }
}
Solution transfer_min_dfs(Request a){
    dij_init();
    Solution b;
    queue[tail++] = a.startID;
    int current_line = TotalStaions[a.startID].linesInfo[0];
    int linevisited[LINESIZE];
    dis[a.startID] = 0;
    time[a.startID] = 0;
    queue[tail++] = a.startID;

    memset(linevisited,0,sizeof(linevisited));
    path[a.startID] = -1;
    while(front!=tail){
        int u = queue[front++],i;
        for( i = 0;i < TotalStaions[u].linesLength; i++){
            if(!linevisited[TotalStaions[u].linesInfo[i]]){
                memset(book,0,sizeof(book));
                book[u] = 1;
                if( current_line != linevisited[TotalStaions[u].linesInfo[i]]){//处理换乘
                    current_line = linevisited[TotalStaions[u].linesInfo[i]];
                    time[u]+=3;
                    int j;
                    for( j = 0 ; a.starttime+time[u] >= edge[i].first_bus_arrival_time+3*j-1; j ++ );
                    if( a.starttime+time[u] < edge[i].first_bus_arrival_time+3*j )
                        time[u] +=(edge[i].first_bus_arrival_time+3*j)-a.starttime+time[u] ;
                }
                linevisited[TotalStaions[u].linesInfo[i]] = 1 ;
                dfs(u,TotalStaions[u].linesInfo[i],a.endID,a.starttime,a.tolerance);
                if( time[a.endID] != inf){
                  int tmp = a.endID;
                    while( tmp != a.startID){
                        b.stationlist[b.len++] = (st){tmp,transfer[tmp]};
                        tmp = path[tmp];
                    }
                    b.stationlist[b.len++] = (st){tmp,b.stationlist[b.len-2].line};

                    tmp = b.stationlist[0].line;
                    b.transfer_times = 0;
                    for(i=1;i<b.len;i++){
                        int j;
                        for(j=0;j<TotalStaions[b.stationlist[i].station].linesLength;j++)//���������·����·ʱ��bug
                            if( TotalStaions[b.stationlist[i].station].linesInfo[j] == tmp)
                                b.stationlist[i].line = tmp;

                        if(tmp != b.stationlist[i].line){
                            b.transfer_times++;
                            tmp = b.stationlist[i].line;
                        }
                    }
                    int index = get_index_from_line(a.startID,transfer[a.startID]),stat_len=0;
                    if( index == 0 || index == TotalLines[transfer[a.startID]].statLength - 1)
                        stat_len = 0;
                    else if( b.stationlist[b.len-2].station == TotalLines[transfer[a.startID]].stat[index-1])
                        stat_len = TotalLines[transfer[a.startID]].statLength - 1 - index;
                    else if( b.stationlist[b.len-2].station == TotalLines[transfer[a.startID]].stat[index+1])
                        stat_len = index;
                    b.next_bus_arrival = stat_len *(2+1) + 6 * 60 ;
                    while(b.next_bus_arrival < a.starttime )
                        b.next_bus_arrival +=3;

                    b.time = time[a.endID] +b.next_bus_arrival - a.starttime;
                    b.price = get_price(dis[a.endID]);
                    b.status = 1;
                    if( a.starttime <6*60|| a.starttime > 23*60 )
                        b.status = 2;
                    return b;
                }

            }
        }
    }
    b.status = 0;
    return b;

}


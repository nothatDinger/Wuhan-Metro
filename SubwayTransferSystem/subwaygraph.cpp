#include "subwaygraph.h"
#include "transfer.h"
#include "line_station.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <queue>
extern Stations TotalStaions[STATIONSIZE];
extern Lines TotalLines[LINESIZE];
extern int MaxLineNum;
extern Edges edge[1000];
extern int hea[400];
extern int StationNum;
//构造函数
SubwayGraph::SubwayGraph()
{

}
void constructGraph();
Solution price_min_dij(Request a);
Solution transfer_min_dij(Request a);
Solution time_min_dij(Request a);
void SubwayGraph::init(){
    constructGraph();
    for(int i=0;i<StationNum;i++){
        stations.push_back(TotalStaions[i]);
        stationsHash[QString::fromUtf8(TotalStaions[i].name)] = i;
        for(int j = hea[i];j;j = edge[j].nex)
            insertEdge(i,edge[j].to);
    }
    for(int i=0;i<MaxLineNum;i++)
         if( TotalLines[i].lineID!=0){
               lines.push_back(TotalLines[i]);
               linesHash[QString::fromUtf8(TotalLines[i].name)] = i;
         }

    color.push_back(QColor(0xE7,0,0x12));
    color.push_back(QColor(0,0x80,0));
    color.push_back(QColor(0xFF,0xd1,0));
    color.push_back(QColor(0x47,0x1e,0x86));
    color.push_back(QColor(0x92,0x53,0xb2));
    color.push_back(QColor(0xd7,0x00,0x6c));
    color.push_back(QColor(0xff,0x7F,0));
    color.push_back(QColor(0,0x00,0xff));
    color.push_back(QColor(0x7a,0xc8,0xee));
    color.push_back(QColor(0xc7,0xaf,0xd3));
    color.push_back(QColor(0x84,0x1c,0x21));
    color.push_back(QColor(0x05,0x7b,69));
    color.push_back(QColor(0x05,0x7b,69));
    color.push_back(QColor(0,0xFF,0));
    updateMinMaxLongiLati();
}

void SubwayGraph::set_crowd(int line, int starttime,int endtime,int tole){
    for(int i = starttime ; i <= endtime ; i++ )
           TotalLines[line].crowd.value[i]=tole;
}

QString SubwayGraph::timetableGet(int line, int station, int currenttime){
    int forwardtime=0,backwardtime=0;
    bool flag1=false,flag2 = false;
    QString forwardfinalstation,backwardfinalstation;
    for(int i = hea[station] ; i ; i = edge[i].nex ){
        if( edge[i].LineID == line){
            if( i & 1 ){
                flag1 = true;
                forwardtime = edge[i].first_bus_arrival_time;
                forwardfinalstation = QString::fromUtf8(TotalStaions[TotalLines[line].finalStationID].name);
            }
            else{
                flag2 = true;
                backwardtime = edge[i].first_bus_arrival_time;
                backwardfinalstation = QString::fromUtf8(TotalStaions[TotalLines[line].startStationID].name);
            }
        }
    }
    while( forwardtime + 1 < currenttime )
        forwardtime += 3;
    while( backwardtime + 1 < currenttime )
        backwardtime += 3;
    QString text;
    if( flag1 )
        text+=QString("前往"+forwardfinalstation+"方向的下一辆地铁将于"+QString::number(forwardtime/60)+":"+QString("%1").arg(forwardtime%60,2,10,QChar('0'))+"到达\n");
    if( flag2 )
        text+=QString("前往"+backwardfinalstation+"方向的下一辆地铁将于"+QString::number(backwardtime/60)+":"+QString("%1").arg(backwardtime%60,2,10,QChar('0'))+"到达\n");
    return text;
}
//清空数据
void SubwayGraph::clearData()
{
    stations.clear();
    lines.clear();
    stationsHash.clear();
    linesHash.clear();
    edges.clear();
    //graph.clear();
}

//插入一条边
bool SubwayGraph::insertEdge(int n1, int n2)
{
    if (edges.contains(Edge(n1, n2)) || edges.contains(Edge(n2, n1)))
    {
        return false;
    }
    edges.insert(Edge(n1, n2));
    return true;
}



//获取线路颜色
QColor SubwayGraph::getLineColor(int l)
{
    return color[l];
}

//获取线路名
QString SubwayGraph::getLineName(int l)
{
    //return lines[l].name;
    //return QString(QLatin1String(TotalLines[l].name));
    return QString::fromUtf8(TotalLines[l].name);

}

//获取线路hash值
int SubwayGraph::getLineHash(QString lineName)
{
    if(linesHash.contains(lineName))
    {
        return linesHash[lineName];
    }
    return -1;
}

//获取线路集合hash值
QList<int> SubwayGraph::getLinesHash(QList<QString> linesList)
{
    QList<int> hashList;
    for (auto &a:linesList)
    {
        hashList.push_back(getLineHash(a));
    }
    return hashList;
}

//获取线路名集合
QList<QString> SubwayGraph::getLinesNameList()
{
    QList<QString> linesNameList;
    for (auto a:lines)
    {
        linesNameList.push_back(QString::fromUtf8(a.name));
    }
    return linesNameList;
}

//获取线路的所有包含站点
QList<QString> SubwayGraph::getLineStationsList(int l)
{
    QList<QString> stationsList;
    for(int i = 0 ; i < TotalLines[l].statLength; i ++ ){
        int a = TotalLines[l].stat[i];
        stationsList.push_back(QString::fromUtf8(stations[a].name));
    }
    return stationsList;
}

//更新边界经纬度
void SubwayGraph::updateMinMaxLongiLati()
{
    double minLongitude=200, minLatitude=200;
    double maxLongitude=0, maxLatitude=0;

    for (auto &s : stations)
    {
        minLongitude = qMin(minLongitude, s.lontitude);
        minLatitude = qMin(minLatitude, s.latitude);
        maxLongitude = qMax(maxLongitude, s.lontitude);
        maxLatitude = qMax(maxLatitude, s.latitude);
    }
    SubwayGraph::minLongitude = minLongitude;
    SubwayGraph::minLatitude = minLatitude;
    SubwayGraph::maxLongitude = maxLongitude;
    SubwayGraph::maxLatitude = maxLatitude;

}

 //获取站点最小坐标
QPointF SubwayGraph::getMinCoord()
{
    return QPointF(SubwayGraph::minLongitude, SubwayGraph::minLatitude);
}

//获取站点最大坐标
QPointF SubwayGraph::getMaxCoord()
{
    return QPointF(SubwayGraph::maxLongitude, SubwayGraph::maxLatitude);
}

//获取两个站点的公共所属线路
QList<int> SubwayGraph::getCommonLines(int s1, int s2)
{
    QList<int> linesList;
    for(int i=0;i<TotalStaions[s1].linesLength;i++){
        for(int j=0;j<TotalStaions[s2].linesLength;j++)
              if(TotalStaions[s1].linesInfo[i] == TotalStaions[s2].linesInfo[j])
                  linesList.push_back(TotalStaions[s1].linesInfo[i]);
    }
    return linesList;
}

//获取站点名
QString SubwayGraph::getStationName(int s)
{

    return QString::fromUtf8(stations[s].name);
}

//获取站点地理坐标
QPointF SubwayGraph::getStationCoord(int s)
{
    return QPointF(TotalStaions[s].lontitude, TotalStaions[s].latitude);
}

//获取站点所属线路信息
QList<int> SubwayGraph::getStationLinesInfo(int s)
{
    //return stations[s].linesInfo.toList();
    QList<int> linesList;
    for(int i = 0 ; i < stations[s].linesLength; i++)
        linesList.push_back(stations[s].linesInfo[i]);
    return linesList;
}

//获取站点hash值
int SubwayGraph::getStationHash(QString stationName)
{
    if(stationsHash.contains(stationName))
    {
        return stationsHash[stationName];
    }
    return -1;
}

//获取站点集合hash值
QList<QString> SubwayGraph::getStationsNameList()
{
    QList<QString> list;
    for (auto &a: stations)
    {
        list.push_back(QString(QLatin1String(a.name)));
    }
    return list;
}

QList<QPair<QString,QString>> SubwayGraph::traverseSimulate(QString stationName){
    int s = getStationHash(stationName);
    QList<QPair<QString,QString>> list;
    for(int i = hea[s]; i ; i = edge[i].nex){
        //list.push_back(QString(QLatin1String(TotalStaions[s].name)+"("+QLatin1String(TotalLines[edge[i].LineID].name)+")"));
        list.push_back(qMakePair(QString::fromUtf8(TotalStaions[edge[i].to].name),QString::fromUtf8(TotalLines[edge[i].LineID].name)));
    }
    return list;
}





//获取网络结构，用于前端显示
void SubwayGraph::getGraph(QList<int>&stationsList, QList<Edge>&edgesList)
{
    stationsList.clear();
    for (int i=0; i<stations.size(); ++i)
    {
        stationsList.push_back(i);
    }
    edgesList=edges.toList();
    return ;
}

//获取最少时间的线路

Solution SubwayGraph::queryTransferMinTime(int s1, int s2, QList<int>&stationsList, QList<Edge>&edgesList, int tolerance, int starttime)
{
    Request a={starttime,s1,s2,tolerance,1};
    Solution b;
    b=time_min_spfa(a);
    for(int i=b.len-1;i>=1;i--){
        stationsList.push_back(b.stationlist[i].station);
        edgesList.push_back((Edge){b.stationlist[i].station,b.stationlist[i-1].station});
    }
    stationsList.push_back(b.stationlist[0].station);
    return b;
}
Solution SubwayGraph::queryTransferSumTime(int s1, int s2, QList<int>&stationsList, QList<Edge>&edgesList, int tolerance, int starttime)
{
    Request a={starttime,s1,s2,tolerance,4};
    Solution b;
    b=sum_time_min_spfa(a);
    for(int i=b.len-1;i>=1;i--){
        stationsList.push_back(b.stationlist[i].station);
        edgesList.push_back((Edge){b.stationlist[i].station,b.stationlist[i-1].station});
    }
    stationsList.push_back(b.stationlist[0].station);
    return b;
}

//获取最少换乘的线路
Solution SubwayGraph::queryTransferMinTransfer(int s1, int s2, QList<int>&stationsList, QList<Edge>&edgesList, int tolerance, int starttime)
{
    Request a={starttime,s1,s2,tolerance,2};
    Solution b;
    b=transfer_min_spfa(a);
    for(int i=b.len-1;i>=1;i--){
        stationsList.push_back(b.stationlist[i].station);
        edgesList.push_back((Edge){b.stationlist[i].station,b.stationlist[i-1].station});
    }
    stationsList.push_back(b.stationlist[0].station);
    return b;
}

Solution SubwayGraph::queryTransferMinDis(int s1, int s2, QList<int>&stationsList, QList<Edge>&edgesList, int tolerance, int starttime)
{
    Request a={starttime,s1,s2,tolerance,2};
    Solution b;
    b=transfer_min_spfa(a);
    for(int i=b.len-1;i>=1;i--){
        stationsList.push_back(b.stationlist[i].station);
        edgesList.push_back((Edge){b.stationlist[i].station,b.stationlist[i-1].station});
    }
    stationsList.push_back(b.stationlist[0].station);
    return b;
}

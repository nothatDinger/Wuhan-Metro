#include "ui_mainwindow.h"

//#include "extrafunc.h"
#include "ui_ExtraFunc.h"
#include "ExtraFunc.h"
#include "mainwindow.h"
#include <QGraphicsItem>
#include <QMessageBox>
#include <QColorDialog>
#include <QTimer>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDebug>

//int readFile_txt();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myView = new Graphics_view_zoom(ui->graphicsView);
    myView->set_modifiers(Qt::NoModifier);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    scene=new QGraphicsScene;
    scene->setSceneRect(-LINE_INFO_WIDTH,0,SCENE_WIDTH,SCENE_HEIGHT);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);

    initStatusBar();
    //extrafunc =new extrafunc;
    extrafunc =new ExtraFunc(this);
    subwayGraph=new SubwayGraph;
    appHelp=new AppHelp();
    //qDebug() << QString("中文");
    bool flag = readFile_txt();
    //qDebug() << QString("DFA");
    subwayGraph->init();
    if (!flag)
    {
        QMessageBox box;
        box.setWindowTitle(tr("error information"));
        box.setIcon(QMessageBox::Warning);
        box.setText("读取数据错误!\n将无法展示内置线路！");
        box.addButton(tr("确定"), QMessageBox::AcceptRole);
        if (box.exec() == QMessageBox::Accepted)
        {
            box.close();
        }
    }

    myConnect();

    updateTranserQueryInfo();

    on_actionLineMap_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete myView;
    delete scene;
    delete subwayGraph;
    delete appHelp;
    //delete extrafunc;
}

//连接信号和槽函数
void MainWindow::myConnect()
{
    connect(extrafunc->ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(tabWidgetCurrentChanged(int)));

    connect(extrafunc->ui->POK,SIGNAL(clicked()),this,SLOT(set_crowd()));
    connect(extrafunc->ui->pushButtontimetable,SIGNAL(clicked()),this,SLOT(timetableQuery()));

    connect(extrafunc->ui->comboBoxtimetableline, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(timetableLineChanged(QString)));
    connect(ui->comboBoxStartLine, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(transferStartLineChanged(QString)));
    connect(ui->comboBoxDstLine, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(transferDstLineChanged(QString)));
    connect(extrafunc->ui->comboBoxtraverseline, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(traverseLineChanged(QString)));
    connect(ui->pushButtonTransfer, SIGNAL(clicked()), this, SLOT(transferQuery()));
    connect(extrafunc->ui->pushButton, SIGNAL(clicked()), this, SLOT(traverseStart()));

    connect(extrafunc->ui->pushButton_1, SIGNAL(clicked()), this, SLOT(traverseButton1()));
    connect(extrafunc->ui->pushButton_2, SIGNAL(clicked()), this, SLOT(traverseButton2()));
    connect(extrafunc->ui->pushButton_3, SIGNAL(clicked()), this, SLOT(traverseButton3()));
    connect(extrafunc->ui->pushButton_4, SIGNAL(clicked()), this, SLOT(traverseButton4()));
    connect(extrafunc->ui->pushButton_5, SIGNAL(clicked()), this, SLOT(traverseButton5()));
    connect(extrafunc->ui->pushButton_6, SIGNAL(clicked()), this, SLOT(traverseButton6()));

    QTimer *timer = new QTimer(this);//新建定时器
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));//关联定时器计满信号和相应的槽函数
    timer->start(1000);//定时器开始计时，其中1000表示1000ms即1秒
}

//时间更新槽函数
void MainWindow::timerUpdate()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    statusLabel2->setText(str);
}
void MainWindow::set_crowd()
{
    int line=subwayGraph->getLineHash(extrafunc->ui->comboBoxcrowd->currentText());
    int starttime = extrafunc->ui->starttime->time().hour()*60+extrafunc->ui->starttime->time().minute();
    int endtime = extrafunc->ui->endtime->time().hour()*60+extrafunc->ui->endtime->time().minute();
    int tole = extrafunc->ui->crowd->value();
    subwayGraph->set_crowd(line,starttime,endtime,tole);
    QMessageBox box;

    box.setWindowIcon(QIcon(":/icon/icon/add.png"));
    box.setText("设置成功");
    box.addButton(tr("确定"),QMessageBox::AcceptRole);
    if(box.exec()==QMessageBox::Accepted)
    {
        box.close();
    }
}

//初始状态栏
void MainWindow::initStatusBar()
{
    QStatusBar* bar = ui->statusBar;
    statusLabel1 = new QLabel;
    statusLabel1->setMinimumSize(200,15);
    statusLabel1->setFrameShape(QFrame::Box);
    statusLabel1->setFrameShadow(QFrame::Sunken);

    statusLabel2 = new QLabel;
    statusLabel2->setMinimumSize(200,15);
    statusLabel2->setFrameShape(QFrame::Box);
    statusLabel2->setFrameShadow(QFrame::Sunken);

    statusLabel3 = new QLabel;
    statusLabel3->setMinimumSize(200,15);
    statusLabel3->setFrameShape(QFrame::Box);
    statusLabel3->setFrameShadow(QFrame::Sunken);

    bar->addWidget(statusLabel1);
    bar->addWidget(statusLabel2);
    bar->addWidget(statusLabel3);

    statusLabel1->setText(tr("forked by NothatDinger"));
    statusLabel2->setText(tr("0000-00-00 00:00::00 星期 "));
    statusLabel3->setText(tr("欢迎使用武汉地铁路线规划系统指南"));
}

//由线路表计算混合颜色
QColor MainWindow::getLinesColor(const QList<int>& linesList)
{
    QColor color1=QColor(255,255,255);
    QColor color2;
    for (int i=0; i<linesList.size(); ++i)
    {
        color2=subwayGraph->getLineColor(linesList[i]);
        color1.setRed(color1.red()*color2.red()/255);
        color1.setGreen(color1.green()*color2.green()/255);
        color1.setBlue(color1.blue()*color2.blue()/255);
    }
    return color1;
}

//获得线路表的名字集
QString MainWindow::getLinesName(const QList<int>& linesList)
{
    QString str;
    str+="\t";
    for (int i=0; i<linesList.size(); ++i)
    {
        str+=" ";
        str+=subwayGraph->getLineName(linesList[i]);
    }
//    qDebug()<<"tip="<<str<<"\n";
    return str;
}

//将站点的经纬度地理坐标转为视图坐标
QPointF MainWindow::transferCoord(QPointF coord)
{
    QPointF minCoord=subwayGraph->getMinCoord();
    QPointF maxCoord=subwayGraph->getMaxCoord();
    double x = (coord.x()-minCoord.x())/(maxCoord.x()-minCoord.x())*NET_WIDTH+MARGIN;
    double y = (maxCoord.y()-coord.y())/(maxCoord.y()-minCoord.y())*NET_HEIGHT+MARGIN;
    return QPointF(x,y);
}

//绘制网络图的边
void MainWindow::drawEdges(const QList<Edge>& edgesList)
{
    for(int i=0; i<edgesList.size(); ++i)
    {
        int s1=edgesList[i].first;
        int s2=edgesList[i].second;

        QList<int> linesList=subwayGraph->getCommonLines(s1, s2);
        QColor color=getLinesColor(linesList);
        QString tip="途经： "+subwayGraph->getStationName(s1)+"--"+subwayGraph->getStationName(s2)+"\n线路：";
        tip+=getLinesName(linesList);
        QPointF s1Pos=transferCoord(subwayGraph->getStationCoord(s1));
        QPointF s2Pos=transferCoord(subwayGraph->getStationCoord(s2));

        QGraphicsLineItem* edgeItem=new QGraphicsLineItem;
        edgeItem->setPen(QPen(color, EDGE_PEN_WIDTH));
        edgeItem->setCursor(Qt::PointingHandCursor);
        edgeItem->setToolTip(tip);
        edgeItem->setPos(s1Pos);
        edgeItem->setLine(0, 0, s2Pos.x()-s1Pos.x(), s2Pos.y()-s1Pos.y());
        scene->addItem(edgeItem);
    }
}

//绘制网络图的站点节点
void MainWindow::drawStations(const QList<int>& stationsList)
{
    for (int i=0; i<stationsList.size(); ++i)
    {
        int s=stationsList[i];
        QString name=subwayGraph->getStationName(s);
        QList<int> linesList=subwayGraph->getStationLinesInfo(s);
        QColor color=getLinesColor(linesList);
        QPointF longiLati=subwayGraph->getStationCoord(s);
        QPointF coord=transferCoord(longiLati);
        QString tip="站名：  "+name+"\n"+
                "经度：  "+QString::number(longiLati.x(),'f',7)+"\n"+
                "纬度：  "+QString::number(longiLati.y(),'f',7)+"\n"+
                "线路："+getLinesName(linesList);

        QGraphicsEllipseItem* stationItem=new QGraphicsEllipseItem;
        stationItem->setRect(-NODE_HALF_WIDTH, -NODE_HALF_WIDTH, NODE_HALF_WIDTH<<1, NODE_HALF_WIDTH<<1);
        stationItem->setPos(coord);
        stationItem->setPen(color);
        stationItem->setCursor(Qt::PointingHandCursor);
        stationItem->setToolTip(tip);

        if(linesList.size()<=1)
        {
            stationItem->setBrush(QColor(QRgb(0xffffff)));
        }

        scene->addItem(stationItem);

        QGraphicsTextItem* textItem=new QGraphicsTextItem;
        textItem->setPlainText(name);
        textItem->setFont(QFont("consolas",4,1));
        textItem->setPos(coord.x(),coord.y()-NODE_HALF_WIDTH*2);
        scene->addItem(textItem);
    }
}


//更新换乘选择信息
void MainWindow::updateTranserQueryInfo()
{
    statusLabel3->setText(tr("已更新数据"));
    QComboBox* comboL1=ui->comboBoxStartLine;
    QComboBox* comboL2=ui->comboBoxDstLine;
    //QComboBox* comboL3=extrafunc->ui->comboBoxcrowd;
    QComboBox* comboL3=extrafunc->ui->comboBoxcrowd;
    QComboBox* comboL4=extrafunc->ui->comboBoxtimetableline;
    QComboBox* comboL5=extrafunc->ui->comboBoxtraverseline;

    comboL1->clear();
    comboL2->clear();
    comboL3->clear();
    comboL4->clear();
    comboL5->clear();
    QList<QString> linesList=subwayGraph->getLinesNameList();
    for(auto &a:linesList)
    {
        comboL1->addItem(a);
        comboL2->addItem(a);
        comboL3->addItem(a);
        comboL4->addItem(a);
        comboL5->addItem(a);
    }
    transferStartLineChanged(comboL1->itemText(0));
    transferDstLineChanged(comboL2->itemText(0));
    timetableLineChanged(comboL4->itemText(0));
    traverseLineChanged(comboL5->itemText(0));
    //crowdSetLineChanged(comboL3->itemText(0));
}

void MainWindow::crowdSetLineChanged()
{
    //QComboBox* combo=extrafunc->ui->comboBoxcrowd;
    QComboBox* combo= extrafunc->ui->comboBoxcrowd;
    combo->clear();

    QList<QString> linesList=subwayGraph->getLinesNameList();

    for(auto &a:linesList)
    {
        combo->addItem(a);
    }
}
void MainWindow::timetableLineChanged(QString lineName)
{
    QComboBox* comboS1=extrafunc->ui->comboBoxtimetablestation;
    comboS1->clear();

    int lineHash=subwayGraph->getLineHash(lineName);
    if(lineHash==-1)
    {
        return ;
    }

    QList<QString> stationsList=subwayGraph->getLineStationsList(lineHash);
    for(auto &a:stationsList)
    {
        comboS1->addItem(a);
    }
}
void MainWindow::traverseLineChanged(QString lineName)
{
    QComboBox* comboS1=extrafunc->ui->comboBoxtraversestation;
    comboS1->clear();

    int lineHash=subwayGraph->getLineHash(lineName);
    if(lineHash==-1)
    {
        return ;
    }

    QList<QString> stationsList=subwayGraph->getLineStationsList(lineHash);
    for(auto &a:stationsList)
    {
        comboS1->addItem(a);
    }
}
//换乘出发线路改变槽函数
void MainWindow::transferStartLineChanged(QString lineName)
{
    QComboBox* comboS1=ui->comboBoxStartStation;
    comboS1->clear();

    int lineHash=subwayGraph->getLineHash(lineName);
    if(lineHash==-1)
    {
        return ;
    }

    QList<QString> stationsList=subwayGraph->getLineStationsList(lineHash);
    for(auto &a:stationsList)
    {
        comboS1->addItem(a);
    }
}

//换乘目的线路改变槽函数
void MainWindow::transferDstLineChanged(QString lineName)
{
    QComboBox* comboS2=ui->comboBoxDstStation;
    comboS2->clear();

    int lineHash=subwayGraph->getLineHash(lineName);
    if(lineHash==-1)
    {
        return ;
    }

    QList<QString> stationsList=subwayGraph->getLineStationsList(lineHash);
    for(auto &a:stationsList)
    {
        comboS2->addItem(a);
    }
}

//换乘查询槽函数
void MainWindow::transferQuery()
{
    int s1=subwayGraph->getStationHash(ui->comboBoxStartStation->currentText());
    int s2=subwayGraph->getStationHash(ui->comboBoxDstStation->currentText());
    //int way=ui->radioButtonMinTime->isChecked()?1:2;
    int tolerance = ui->tolerance->value();
    int starttime = ui->starttime->time().hour()*60+ui->starttime->time().minute();
    if(s1==-1||s2==-1)
    {
        QMessageBox box;
        box.setWindowTitle(tr("换乘查询"));
        box.setWindowIcon(QIcon(":/icon/icon/query.png"));
        box.setIcon(QMessageBox::Warning);
        box.setText(tr("请选择有站点的线路"));
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        if(box.exec()==QMessageBox::Accepted)
        {
            box.close();
        }
    }
    else
    {
        QList<int> stationsList;
        QList<Edge> edgesList;
        Solution b;
        if(ui->radioButtonMinTime->isChecked())
            b=subwayGraph->queryTransferMinTime(s1, s2, stationsList, edgesList, tolerance, starttime);
        else if(ui->radioButtonMinTransfer->isChecked())
            b=subwayGraph->queryTransferMinTransfer(s1, s2, stationsList, edgesList, tolerance, starttime);
        else if(ui->radioButtonMinPrice)
            b=subwayGraph->queryTransferMinDis(s1, s2, stationsList, edgesList, tolerance, starttime);
        else
            b=subwayGraph->queryTransferSumTime(s1, s2, stationsList, edgesList, tolerance, starttime);
        if(b.status)
        {
            statusLabel3->setText(tr("换乘查询成功！"));
            scene->clear();
            drawEdges(edgesList);
            drawStations(stationsList);
            QString text = ("以下线路耗时"+QString::number(b.time)+"min,所需花费"+QString::number(b.price)+"元，需要换乘"+QString::number(b.transfer_times)+"次,平均拥挤度"+QString::number(b.av_crowd)+"%,下一班车将于"+
                            QString::number(b.next_bus_arrival/60)+":"+QString("%1").arg(b.next_bus_arrival%60,2,10,QChar('0'))+"到达\n\n");
            if(b.status==2)
                    text += ("注意，已超出地铁运行时间\n\n");
            for(int i=0; i<stationsList.size(); ++i)
            {
                if(i)
                {
                    text+="\n  ↓\n";
                }
                text+=subwayGraph->getStationName(stationsList[i]);
                QString linesStr=getLinesName(subwayGraph->getStationLinesInfo(stationsList[i]));
                text+=linesStr;
            }
            QTextBrowser* browser=ui->textBrowserRoute;
            browser->clear();
            browser->setText(text);
        }
        else
        {
            QMessageBox box;
            box.setWindowTitle(tr("换乘查询"));
            box.setWindowIcon(QIcon(":/icon/icon/query.png"));
            box.setIcon(QMessageBox::Warning);
            box.setText(tr("您选择的起始和终止站点暂时无法到达！,可能是因为你容忍度太低了"));
            box.addButton(tr("确定"),QMessageBox::AcceptRole);
            if(box.exec()==QMessageBox::Accepted)
            {
                box.close();
            }
        }
    }
}
void MainWindow::timetableQuery(){
    int l1 = subwayGraph->getLineHash(extrafunc->ui->comboBoxtimetableline->currentText());
    int s1 = subwayGraph->getStationHash(extrafunc->ui->comboBoxtimetablestation->currentText());
    int time = extrafunc->ui->timetabletime->time().hour()*60+extrafunc->ui->timetabletime->time().minute();
    QString text = subwayGraph->timetableGet(l1,s1,time);
    QTextBrowser* browser = extrafunc->ui->textBrowsertimetable;
    browser->clear();
    browser->setText(text);
}
void MainWindow::traverseStart(){
    QString currentstation = extrafunc->ui->comboBoxtraversestation->currentText();
    QList<QPair<QString,QString>> list = subwayGraph->traverseSimulate(currentstation);
    QTextBrowser* browser = extrafunc->ui->textBrowsertraverse;
    browser->clear();
    browser->setText(QString("当前站点为")+currentstation);
    QPushButton* b[6] ;
    b[0] = extrafunc->ui->pushButton_1;
    b[1] = extrafunc->ui->pushButton_2;
    b[2] = extrafunc->ui->pushButton_3;
    b[3] = extrafunc->ui->pushButton_4;
    b[4] = extrafunc->ui->pushButton_5;
    b[5] = extrafunc->ui->pushButton_6;
    QLabel *l[6];
    l[0] = extrafunc->ui->label_11;
    l[1] = extrafunc->ui->label_12;
    l[2] = extrafunc->ui->label_13;
    l[3] = extrafunc->ui->label_14;
    l[4] = extrafunc->ui->label_15;
    l[5] = extrafunc->ui->label_16;
    extrafunc->buttonlist.clear();
    for(int i = 0 ; i < list.size() ; i ++){
        b[i]->setText(list[i].first);
        l[i]->setText(list[i].second);
        b[i]->setVisible(true);
        l[i]->setVisible(true);
        extrafunc->buttonlist.push_back(list[i].first);
    }
    for(int i = list.size();i < 6 ; i++){
        b[i]->setVisible(false);
        l[i]->setVisible(false);
    }
}

void MainWindow::traverseButton1(){
    QString Name = extrafunc->buttonlist[0];
    QList<QPair<QString,QString>> list = subwayGraph->traverseSimulate(Name);
    QTextBrowser* browser = extrafunc->ui->textBrowsertraverse;
    browser->clear();
    browser->setText(QString("当前站点为")+Name);
    QPushButton* b[6] ;
    b[0] = extrafunc->ui->pushButton_1;
    b[1] = extrafunc->ui->pushButton_2;
    b[2] = extrafunc->ui->pushButton_3;
    b[3] = extrafunc->ui->pushButton_4;
    b[4] = extrafunc->ui->pushButton_5;
    b[5] = extrafunc->ui->pushButton_6;
    QLabel *l[6];
    l[0] = extrafunc->ui->label_11;
    l[1] = extrafunc->ui->label_12;
    l[2] = extrafunc->ui->label_13;
    l[3] = extrafunc->ui->label_14;
    l[4] = extrafunc->ui->label_15;
    l[5] = extrafunc->ui->label_16;
    extrafunc->buttonlist.clear();
    for(int i = 0 ; i < list.size() ; i ++){
        b[i]->setText(list[i].first);
        l[i]->setText(list[i].second);
        b[i]->setVisible(true);
        l[i]->setVisible(true);
        extrafunc->buttonlist.push_back(list[i].first);
    }
    for(int i = list.size();i < 6 ; i++){
        b[i]->setVisible(false);
        l[i]->setVisible(false);
    }
}
void MainWindow::traverseButton2(){
    QString Name = extrafunc->buttonlist[1];
    QList<QPair<QString,QString>> list = subwayGraph->traverseSimulate(Name);
    QTextBrowser* browser = extrafunc->ui->textBrowsertraverse;
    browser->clear();
    browser->setText(QString("当前站点为")+Name);
    QPushButton* b[6] ;
    b[0] = extrafunc->ui->pushButton_1;
    b[1] = extrafunc->ui->pushButton_2;
    b[2] = extrafunc->ui->pushButton_3;
    b[3] = extrafunc->ui->pushButton_4;
    b[4] = extrafunc->ui->pushButton_5;
    b[5] = extrafunc->ui->pushButton_6;
    QLabel *l[6];
    l[0] = extrafunc->ui->label_11;
    l[1] = extrafunc->ui->label_12;
    l[2] = extrafunc->ui->label_13;
    l[3] = extrafunc->ui->label_14;
    l[4] = extrafunc->ui->label_15;
    l[5] = extrafunc->ui->label_16;
    extrafunc->buttonlist.clear();
    for(int i = 0 ; i < list.size() ; i ++){
        b[i]->setText(list[i].first);
        l[i]->setText(list[i].second);
        b[i]->setVisible(true);
        l[i]->setVisible(true);
        extrafunc->buttonlist.push_back(list[i].first);
    }
    for(int i = list.size();i < 6 ; i++){
        b[i]->setVisible(false);
        l[i]->setVisible(false);
    }
}
void MainWindow::traverseButton3(){
    QString Name = extrafunc->buttonlist[2];
    QList<QPair<QString,QString>> list = subwayGraph->traverseSimulate(Name);
    QTextBrowser* browser = extrafunc->ui->textBrowsertraverse;
    browser->clear();
    browser->setText(QString("当前站点为")+Name);
    QPushButton* b[6] ;
    b[0] = extrafunc->ui->pushButton_1;
    b[1] = extrafunc->ui->pushButton_2;
    b[2] = extrafunc->ui->pushButton_3;
    b[3] = extrafunc->ui->pushButton_4;
    b[4] = extrafunc->ui->pushButton_5;
    b[5] = extrafunc->ui->pushButton_6;
    QLabel *l[6];
    l[0] = extrafunc->ui->label_11;
    l[1] = extrafunc->ui->label_12;
    l[2] = extrafunc->ui->label_13;
    l[3] = extrafunc->ui->label_14;
    l[4] = extrafunc->ui->label_15;
    l[5] = extrafunc->ui->label_16;
    extrafunc->buttonlist.clear();
    for(int i = 0 ; i < list.size() ; i ++){
        b[i]->setText(list[i].first);
        l[i]->setText(list[i].second);
        b[i]->setVisible(true);
        l[i]->setVisible(true);
        extrafunc->buttonlist.push_back(list[i].first);
    }
    for(int i = list.size();i < 6 ; i++){
        b[i]->setVisible(false);
        l[i]->setVisible(false);
    }
}
void MainWindow::traverseButton4(){
    QString Name = extrafunc->buttonlist[3];
    QList<QPair<QString,QString>> list = subwayGraph->traverseSimulate(Name);
    QTextBrowser* browser = extrafunc->ui->textBrowsertraverse;
    browser->clear();
    browser->setText(QString("当前站点为")+Name);
    QPushButton* b[6] ;
    b[0] = extrafunc->ui->pushButton_1;
    b[1] = extrafunc->ui->pushButton_2;
    b[2] = extrafunc->ui->pushButton_3;
    b[3] = extrafunc->ui->pushButton_4;
    b[4] = extrafunc->ui->pushButton_5;
    b[5] = extrafunc->ui->pushButton_6;
    QLabel *l[6];
    l[0] = extrafunc->ui->label_11;
    l[1] = extrafunc->ui->label_12;
    l[2] = extrafunc->ui->label_13;
    l[3] = extrafunc->ui->label_14;
    l[4] = extrafunc->ui->label_15;
    l[5] = extrafunc->ui->label_16;
    extrafunc->buttonlist.clear();
    for(int i = 0 ; i < list.size() ; i ++){
        b[i]->setText(list[i].first);
        l[i]->setText(list[i].second);
        b[i]->setVisible(true);
        l[i]->setVisible(true);
        extrafunc->buttonlist.push_back(list[i].first);
    }
    for(int i = list.size();i < 6 ; i++){
        b[i]->setVisible(false);
        l[i]->setVisible(false);
    }
}
void MainWindow::traverseButton5(){
    QString Name = extrafunc->buttonlist[4];
    QList<QPair<QString,QString>> list = subwayGraph->traverseSimulate(Name);
    QTextBrowser* browser = extrafunc->ui->textBrowsertraverse;
    browser->clear();
    browser->setText(QString("当前站点为")+Name);
    QPushButton* b[6] ;
    b[0] = extrafunc->ui->pushButton_1;
    b[1] = extrafunc->ui->pushButton_2;
    b[2] = extrafunc->ui->pushButton_3;
    b[3] = extrafunc->ui->pushButton_4;
    b[4] = extrafunc->ui->pushButton_5;
    b[5] = extrafunc->ui->pushButton_6;
    QLabel *l[6];
    l[0] = extrafunc->ui->label_11;
    l[1] = extrafunc->ui->label_12;
    l[2] = extrafunc->ui->label_13;
    l[3] = extrafunc->ui->label_14;
    l[4] = extrafunc->ui->label_15;
    l[5] = extrafunc->ui->label_16;
    extrafunc->buttonlist.clear();
    for(int i = 0 ; i < list.size() ; i ++){
        b[i]->setText(list[i].first);
        l[i]->setText(list[i].second);
        b[i]->setVisible(true);
        l[i]->setVisible(true);
        extrafunc->buttonlist.push_back(list[i].first);
    }
    for(int i = list.size();i < 6 ; i++){
        b[i]->setVisible(false);
        l[i]->setVisible(false);
    }
}
void MainWindow::traverseButton6(){
    QString Name = extrafunc->buttonlist[5];
    QList<QPair<QString,QString>> list = subwayGraph->traverseSimulate(Name);
    QTextBrowser* browser = extrafunc->ui->textBrowsertraverse;
    browser->clear();
    browser->setText(QString("当前站点为")+Name);
    QPushButton* b[6] ;
    b[0] = extrafunc->ui->pushButton_1;
    b[1] = extrafunc->ui->pushButton_2;
    b[2] = extrafunc->ui->pushButton_3;
    b[3] = extrafunc->ui->pushButton_4;
    b[4] = extrafunc->ui->pushButton_5;
    b[5] = extrafunc->ui->pushButton_6;
    QLabel *l[6];
    l[0] = extrafunc->ui->label_11;
    l[1] = extrafunc->ui->label_12;
    l[2] = extrafunc->ui->label_13;
    l[3] = extrafunc->ui->label_14;
    l[4] = extrafunc->ui->label_15;
    l[5] = extrafunc->ui->label_16;
    extrafunc->buttonlist.clear();
    for(int i = 0 ; i < list.size() ; i ++){
        b[i]->setText(list[i].first);
        l[i]->setText(list[i].second);
        b[i]->setVisible(true);
        l[i]->setVisible(true);
        extrafunc->buttonlist.push_back(list[i].first);
    }
    for(int i = list.size();i < 6 ; i++){
        b[i]->setVisible(false);
        l[i]->setVisible(false);
    }
}
void MainWindow::tabWidgetCurrentChanged(int index)
{
    QWidget* widget=extrafunc->ui->tabWidget->currentWidget();

    if(widget==extrafunc->tabWigetsVector[0])
    {
        extrafunc->linesNameList=subwayGraph->getLinesNameList();
        crowdSetLineChanged();
    }
    else if(widget==extrafunc->tabWigetsVector[1])
    {
        extrafunc->linesNameList=subwayGraph->getLinesNameList();
        extrafunc->stationsNameList=subwayGraph->getStationsNameList();
        //extrafunc->ui->comboBoxConnectStation1->setMaxCount(extrafunc->stationsNameList.size());
        //extrafunc->ui->comboBoxConnectStation2->setMaxCount(extrafunc->stationsNameList.size());
        //extrafunc->ui->comboBoxConnectLine->setMaxCount(extrafunc->linesNameList.size());
        //extrafunc->updateComboBox();
    }
    else
    {
        extrafunc->ui->pushButton_1->setVisible(false);
        extrafunc->ui->pushButton_2->setVisible(false);
        extrafunc->ui->pushButton_3->setVisible(false);
        extrafunc->ui->pushButton_4->setVisible(false);
        extrafunc->ui->pushButton_5->setVisible(false);
        extrafunc->ui->pushButton_6->setVisible(false);
        extrafunc->ui->label_11->setVisible(false);
        extrafunc->ui->label_12->setVisible(false);
        extrafunc->ui->label_13->setVisible(false);
        extrafunc->ui->label_14->setVisible(false);
        extrafunc->ui->label_15->setVisible(false);
        extrafunc->ui->label_16->setVisible(false);
    }
    Q_UNUSED(index);
}


//视图放大槽函数
void MainWindow::on_toolEnlarge_triggered()
{
    statusLabel3->setText(tr("已放大"));
    ui->graphicsView->scale(1.5,1.5);
}

//动作视图缩小槽函数
void MainWindow::on_toolShrink_triggered()
{
    statusLabel3->setText(tr("已缩小"));
    ui->graphicsView->scale(2.0/3,2.0/3);
}




//动作查看所有线路图槽函数
void MainWindow::on_actionLineMap_triggered()
{
    statusLabel3->setText(tr("图示：武汉地铁网络线路图"));
    scene->clear();
    QList<int> stationsList;
    QList<Edge> edgesList;
    subwayGraph->getGraph(stationsList,edgesList);
    drawEdges(edgesList);
    drawStations(stationsList);
//    qDebug()<<"stations.size()="<<stationsList.size()m<<" edges.size()="<<edgesList.size();
}

void MainWindow::on_actionsetcrowd_triggered()
{
    statusLabel3->setText(tr("请修改拥挤度"));
    crowdSetLineChanged();
    extrafunc->show();
    //ui->graphicsView->scale(1.5,1.5);

}
void MainWindow::on_actionExtraFunc_triggered()
{
    statusLabel3->setText(tr("额外功能"));
    //crowdSetLineChanged();
    extrafunc->show();
    //ui->graphicsView->scale(1.5,1.5);

}


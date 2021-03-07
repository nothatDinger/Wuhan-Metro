#ifndef EXTRAFUNC_H
#define EXTRAFUNC_H

#include <QDialog>
#include <QVector>
#include <QTabWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QIcon>
#include <QString>

class MainWindow;

namespace Ui {
class ExtraFunc;
}

class ExtraFunc: public QDialog
{
    Q_OBJECT

public:
    explicit ExtraFunc(QWidget *parent = 0);

    ~ExtraFunc();
protected:
    Ui::ExtraFunc *ui;
    QVector<QWidget*> tabWigetsVector;  //保存tab部件指针

    QString lineName;                   //保存输入线路名
    QString stationName;                //保存输入站点名
    QList<QString> linesNameList;       //保存选择线路名表
    QList<QString> linesSelected;       //保存选择的线路名
    QList<QString> stationsNameList;    //保存选择站点名表
    QList<QString> buttonlist;
    friend class MainWindow;
};
#endif // EXTRAFUNC_H

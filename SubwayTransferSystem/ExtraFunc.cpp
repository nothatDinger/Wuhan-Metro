#include "ui_ExtraFunc.h"
#include "ExtraFunc.h"
#include <QPixmap>
#include <QColorDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>


ExtraFunc::ExtraFunc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExtraFunc)
{
    ui->setupUi(this);
    tabWigetsVector.push_back(ui->tolerance);
    tabWigetsVector.push_back(ui->timetable);
    tabWigetsVector.push_back(ui->traverse);
}

ExtraFunc::~ExtraFunc(){
    delete ui;
}

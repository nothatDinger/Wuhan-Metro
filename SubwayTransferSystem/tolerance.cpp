#include "ui_tolerance.h"
#include "tolerance.h"
#include <QPixmap>
#include <QColorDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>


Tolerance:: Tolerance(QWidget *parent):
    QWidget(parent),
    ui(new Ui::Tolerance)
{
    ui->setupUi(this);
}

Tolerance:: ~Tolerance(){
    delete ui;
}

void Tolerance::setSetCrowdVisible(){
    ;
}

/********************************************************************************
** Form generated from reading UI file 'extrafunc.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXTRAFUNC_H
#define UI_EXTRAFUNC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExtraFunc
{
public:
    QTabWidget *tabWidget;
    QWidget *tolerance;
    QTimeEdit *starttime;
    QTimeEdit *endtime;
    QSpinBox *crowd;
    QPushButton *POK;
    QLabel *label;
    QComboBox *comboBoxcrowd;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label_5;
    QLabel *label_2;
    QWidget *timetable;
    QLabel *label_6;
    QTimeEdit *timetabletime;
    QComboBox *comboBoxtimetableline;
    QComboBox *comboBoxtimetablestation;
    QLabel *label_7;
    QLabel *label_8;
    QPushButton *pushButtontimetable;
    QTextBrowser *textBrowsertimetable;
    QWidget *traverse;
    QLabel *label_9;
    QComboBox *comboBoxtraverseline;
    QComboBox *comboBoxtraversestation;
    QLabel *label_10;
    QPushButton *pushButton_1;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QTextBrowser *textBrowsertraverse;
    QPushButton *pushButton;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;

    void setupUi(QDialog *ExtraFunc)
    {
        if (ExtraFunc->objectName().isEmpty())
            ExtraFunc->setObjectName(QString::fromUtf8("ExtraFunc"));
        ExtraFunc->resize(474, 349);
        tabWidget = new QTabWidget(ExtraFunc);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 511, 421));
        tabWidget->setFocusPolicy(Qt::WheelFocus);
        tolerance = new QWidget();
        tolerance->setObjectName(QString::fromUtf8("tolerance"));
        starttime = new QTimeEdit(tolerance);
        starttime->setObjectName(QString::fromUtf8("starttime"));
        starttime->setGeometry(QRect(150, 140, 51, 22));
        endtime = new QTimeEdit(tolerance);
        endtime->setObjectName(QString::fromUtf8("endtime"));
        endtime->setGeometry(QRect(270, 140, 61, 22));
        endtime->setTime(QTime(23, 59, 0));
        crowd = new QSpinBox(tolerance);
        crowd->setObjectName(QString::fromUtf8("crowd"));
        crowd->setGeometry(QRect(160, 190, 61, 22));
        crowd->setMaximum(100);
        crowd->setValue(100);
        POK = new QPushButton(tolerance);
        POK->setObjectName(QString::fromUtf8("POK"));
        POK->setGeometry(QRect(290, 260, 80, 20));
        label = new QLabel(tolerance);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 30, 121, 21));
        comboBoxcrowd = new QComboBox(tolerance);
        comboBoxcrowd->setObjectName(QString::fromUtf8("comboBoxcrowd"));
        comboBoxcrowd->setGeometry(QRect(150, 90, 72, 22));
        label_4 = new QLabel(tolerance);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(60, 140, 61, 16));
        label_3 = new QLabel(tolerance);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(230, 140, 20, 20));
        label_5 = new QLabel(tolerance);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(63, 190, 61, 20));
        label_2 = new QLabel(tolerance);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(60, 90, 54, 16));
        tabWidget->addTab(tolerance, QString());
        timetable = new QWidget();
        timetable->setObjectName(QString::fromUtf8("timetable"));
        label_6 = new QLabel(timetable);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(70, 70, 54, 16));
        timetabletime = new QTimeEdit(timetable);
        timetabletime->setObjectName(QString::fromUtf8("timetabletime"));
        timetabletime->setGeometry(QRect(150, 130, 51, 22));
        timetabletime->setTime(QTime(8, 0, 0));
        comboBoxtimetableline = new QComboBox(timetable);
        comboBoxtimetableline->setObjectName(QString::fromUtf8("comboBoxtimetableline"));
        comboBoxtimetableline->setGeometry(QRect(140, 70, 72, 22));
        comboBoxtimetablestation = new QComboBox(timetable);
        comboBoxtimetablestation->setObjectName(QString::fromUtf8("comboBoxtimetablestation"));
        comboBoxtimetablestation->setGeometry(QRect(320, 70, 111, 22));
        label_7 = new QLabel(timetable);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(240, 70, 54, 16));
        label_8 = new QLabel(timetable);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(70, 130, 54, 12));
        pushButtontimetable = new QPushButton(timetable);
        pushButtontimetable->setObjectName(QString::fromUtf8("pushButtontimetable"));
        pushButtontimetable->setGeometry(QRect(300, 130, 80, 20));
        textBrowsertimetable = new QTextBrowser(timetable);
        textBrowsertimetable->setObjectName(QString::fromUtf8("textBrowsertimetable"));
        textBrowsertimetable->setGeometry(QRect(60, 200, 361, 41));
        tabWidget->addTab(timetable, QString());
        traverse = new QWidget();
        traverse->setObjectName(QString::fromUtf8("traverse"));
        label_9 = new QLabel(traverse);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(210, 40, 54, 16));
        comboBoxtraverseline = new QComboBox(traverse);
        comboBoxtraverseline->setObjectName(QString::fromUtf8("comboBoxtraverseline"));
        comboBoxtraverseline->setGeometry(QRect(110, 40, 72, 22));
        comboBoxtraversestation = new QComboBox(traverse);
        comboBoxtraversestation->setObjectName(QString::fromUtf8("comboBoxtraversestation"));
        comboBoxtraversestation->setGeometry(QRect(290, 40, 111, 22));
        label_10 = new QLabel(traverse);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(40, 40, 54, 16));
        pushButton_1 = new QPushButton(traverse);
        pushButton_1->setObjectName(QString::fromUtf8("pushButton_1"));
        pushButton_1->setGeometry(QRect(50, 110, 101, 20));
        pushButton_2 = new QPushButton(traverse);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(49, 130, 101, 20));
        pushButton_3 = new QPushButton(traverse);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(49, 150, 101, 20));
        pushButton_4 = new QPushButton(traverse);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(49, 170, 101, 20));
        pushButton_5 = new QPushButton(traverse);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(49, 190, 101, 20));
        pushButton_6 = new QPushButton(traverse);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(49, 210, 101, 20));
        textBrowsertraverse = new QTextBrowser(traverse);
        textBrowsertraverse->setObjectName(QString::fromUtf8("textBrowsertraverse"));
        textBrowsertraverse->setGeometry(QRect(260, 140, 181, 71));
        pushButton = new QPushButton(traverse);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(290, 70, 80, 20));
        label_11 = new QLabel(traverse);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(180, 110, 54, 12));
        label_12 = new QLabel(traverse);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(180, 130, 54, 12));
        label_13 = new QLabel(traverse);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(180, 150, 54, 12));
        label_14 = new QLabel(traverse);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(180, 170, 54, 12));
        label_15 = new QLabel(traverse);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(180, 190, 54, 12));
        label_16 = new QLabel(traverse);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(180, 210, 54, 12));
        tabWidget->addTab(traverse, QString());

        retranslateUi(ExtraFunc);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ExtraFunc);
    } // setupUi

    void retranslateUi(QDialog *ExtraFunc)
    {
        ExtraFunc->setWindowTitle(QApplication::translate("ExtraFunc", "\351\242\235\345\244\226\345\212\237\350\203\275", nullptr));
        POK->setText(QApplication::translate("ExtraFunc", "\347\241\256\345\256\232", nullptr));
        label->setText(QApplication::translate("ExtraFunc", "\350\256\276\347\275\256\347\272\277\350\267\257\346\213\245\346\214\244\345\272\246", nullptr));
        label_4->setText(QApplication::translate("ExtraFunc", "\351\200\211\346\213\251\346\227\266\351\227\264\346\256\265", nullptr));
        label_3->setText(QApplication::translate("ExtraFunc", "\350\207\263", nullptr));
        label_5->setText(QApplication::translate("ExtraFunc", "\350\256\276\347\275\256\346\213\245\346\214\244\345\272\246\357\274\232", nullptr));
        label_2->setText(QApplication::translate("ExtraFunc", "\351\200\211\346\213\251\347\272\277\350\267\257\357\274\232", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tolerance), QApplication::translate("ExtraFunc", "\346\213\245\346\214\244\345\272\246", nullptr));
        label_6->setText(QApplication::translate("ExtraFunc", "\351\200\211\346\213\251\347\272\277\350\267\257\357\274\232", nullptr));
        timetabletime->setDisplayFormat(QApplication::translate("ExtraFunc", "HH:mm", nullptr));
        label_7->setText(QApplication::translate("ExtraFunc", "\351\200\211\346\213\251\347\253\231\347\202\271\357\274\232", nullptr));
        label_8->setText(QApplication::translate("ExtraFunc", "\345\275\223\345\211\215\346\227\266\351\227\264", nullptr));
        pushButtontimetable->setText(QApplication::translate("ExtraFunc", "\347\241\256\345\256\232", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(timetable), QApplication::translate("ExtraFunc", "\346\227\266\345\210\273\350\241\250", nullptr));
        label_9->setText(QApplication::translate("ExtraFunc", "\351\200\211\346\213\251\347\253\231\347\202\271\357\274\232", nullptr));
        label_10->setText(QApplication::translate("ExtraFunc", "\351\200\211\346\213\251\347\272\277\350\267\257\357\274\232", nullptr));
        pushButton_1->setText(QApplication::translate("ExtraFunc", "PushButton", nullptr));
        pushButton_2->setText(QApplication::translate("ExtraFunc", "PushButton", nullptr));
        pushButton_3->setText(QApplication::translate("ExtraFunc", "PushButton", nullptr));
        pushButton_4->setText(QApplication::translate("ExtraFunc", "PushButton", nullptr));
        pushButton_5->setText(QApplication::translate("ExtraFunc", "PushButton", nullptr));
        pushButton_6->setText(QApplication::translate("ExtraFunc", "PushButton", nullptr));
        pushButton->setText(QApplication::translate("ExtraFunc", "\345\274\200\345\247\213", nullptr));
        label_11->setText(QApplication::translate("ExtraFunc", "TextLabel", nullptr));
        label_12->setText(QApplication::translate("ExtraFunc", "TextLabel", nullptr));
        label_13->setText(QApplication::translate("ExtraFunc", "TextLabel", nullptr));
        label_14->setText(QApplication::translate("ExtraFunc", "TextLabel", nullptr));
        label_15->setText(QApplication::translate("ExtraFunc", "TextLabel", nullptr));
        label_16->setText(QApplication::translate("ExtraFunc", "TextLabel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(traverse), QApplication::translate("ExtraFunc", "\347\253\231\347\202\271\346\265\217\350\247\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ExtraFunc: public Ui_ExtraFunc {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXTRAFUNC_H

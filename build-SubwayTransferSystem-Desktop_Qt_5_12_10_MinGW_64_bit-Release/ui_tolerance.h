/********************************************************************************
** Form generated from reading UI file 'tolerance.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOLERANCE_H
#define UI_TOLERANCE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tolerance
{
public:
    QLabel *label;
    QComboBox *comboBoxcrowd;
    QLabel *label_2;
    QTimeEdit *starttime;
    QTimeEdit *endtime;
    QLabel *label_3;
    QLabel *label_4;
    QSpinBox *crowd;
    QLabel *label_5;
    QPushButton *POK;

    void setupUi(QWidget *Tolerance)
    {
        if (Tolerance->objectName().isEmpty())
            Tolerance->setObjectName(QString::fromUtf8("Tolerance"));
        Tolerance->resize(447, 300);
        label = new QLabel(Tolerance);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 20, 121, 21));
        comboBoxcrowd = new QComboBox(Tolerance);
        comboBoxcrowd->setObjectName(QString::fromUtf8("comboBoxcrowd"));
        comboBoxcrowd->setGeometry(QRect(160, 80, 72, 22));
        label_2 = new QLabel(Tolerance);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(70, 80, 54, 16));
        starttime = new QTimeEdit(Tolerance);
        starttime->setObjectName(QString::fromUtf8("starttime"));
        starttime->setGeometry(QRect(160, 130, 51, 22));
        endtime = new QTimeEdit(Tolerance);
        endtime->setObjectName(QString::fromUtf8("endtime"));
        endtime->setGeometry(QRect(280, 130, 61, 22));
        endtime->setTime(QTime(23, 59, 0));
        label_3 = new QLabel(Tolerance);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(240, 130, 20, 20));
        label_4 = new QLabel(Tolerance);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(70, 130, 61, 16));
        crowd = new QSpinBox(Tolerance);
        crowd->setObjectName(QString::fromUtf8("crowd"));
        crowd->setGeometry(QRect(170, 180, 61, 22));
        crowd->setMaximum(100);
        crowd->setValue(100);
        label_5 = new QLabel(Tolerance);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(73, 180, 61, 20));
        POK = new QPushButton(Tolerance);
        POK->setObjectName(QString::fromUtf8("POK"));
        POK->setGeometry(QRect(300, 250, 80, 20));

        retranslateUi(Tolerance);

        QMetaObject::connectSlotsByName(Tolerance);
    } // setupUi

    void retranslateUi(QWidget *Tolerance)
    {
        Tolerance->setWindowTitle(QApplication::translate("Tolerance", "\351\242\235\345\244\226\350\256\276\347\275\256", nullptr));
        label->setText(QApplication::translate("Tolerance", "\350\256\276\347\275\256\347\272\277\350\267\257\346\213\245\346\214\244\345\272\246", nullptr));
        label_2->setText(QApplication::translate("Tolerance", "\351\200\211\346\213\251\347\272\277\350\267\257\357\274\232", nullptr));
        label_3->setText(QApplication::translate("Tolerance", "\350\207\263", nullptr));
        label_4->setText(QApplication::translate("Tolerance", "\351\200\211\346\213\251\346\227\266\351\227\264\346\256\265", nullptr));
        label_5->setText(QApplication::translate("Tolerance", "\350\256\276\347\275\256\346\213\245\346\214\244\345\272\246\357\274\232", nullptr));
        POK->setText(QApplication::translate("Tolerance", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Tolerance: public Ui_Tolerance {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOLERANCE_H

/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *toolEnlarge;
    QAction *toolShrink;
    QAction *actionsetcrowd;
    QAction *actionLineMap;
    QAction *actionExtraFunc;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *graphicsView;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelTransfer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QTimeEdit *starttime;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QSpinBox *tolerance;
    QHBoxLayout *horizontalLayout4;
    QLabel *labelStart;
    QComboBox *comboBoxStartLine;
    QComboBox *comboBoxStartStation;
    QHBoxLayout *horizontalLayout5;
    QLabel *labelDestination;
    QComboBox *comboBoxDstLine;
    QComboBox *comboBoxDstStation;
    QHBoxLayout *horizontalLayout6;
    QPushButton *pushButtonTransfer;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButtonMinTransfer;
    QRadioButton *radioButtonMinPrice;
    QRadioButton *radioButtonMinTime;
    QRadioButton *radioButton;
    QLabel *labelTransferRoute;
    QTextBrowser *textBrowserRoute;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1030, 684);
        MainWindow->setMinimumSize(QSize(1030, 680));
        QFont font;
        font.setFamily(QString::fromUtf8("Consolas"));
        MainWindow->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/icon/metro-wuhan.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setIconSize(QSize(24, 24));
        toolEnlarge = new QAction(MainWindow);
        toolEnlarge->setObjectName(QString::fromUtf8("toolEnlarge"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/icon/enlarge.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolEnlarge->setIcon(icon1);
        toolEnlarge->setFont(font);
        toolShrink = new QAction(MainWindow);
        toolShrink->setObjectName(QString::fromUtf8("toolShrink"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icon/icon/shrink.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolShrink->setIcon(icon2);
        toolShrink->setFont(font);
        actionsetcrowd = new QAction(MainWindow);
        actionsetcrowd->setObjectName(QString::fromUtf8("actionsetcrowd"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icon/icon/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionsetcrowd->setIcon(icon3);
        actionLineMap = new QAction(MainWindow);
        actionLineMap->setObjectName(QString::fromUtf8("actionLineMap"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icon/icon/map.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLineMap->setIcon(icon4);
        actionLineMap->setFont(font);
        actionExtraFunc = new QAction(MainWindow);
        actionExtraFunc->setObjectName(QString::fromUtf8("actionExtraFunc"));
        actionExtraFunc->setIcon(icon3);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setMinimumSize(QSize(1030, 600));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(10);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(10, 0, 10, 0);
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setMinimumSize(QSize(700, 580));

        horizontalLayout->addWidget(graphicsView);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        labelTransfer = new QLabel(centralWidget);
        labelTransfer->setObjectName(QString::fromUtf8("labelTransfer"));
        labelTransfer->setMinimumSize(QSize(280, 30));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Consolas"));
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setWeight(75);
        labelTransfer->setFont(font1);

        verticalLayout_2->addWidget(labelTransfer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        starttime = new QTimeEdit(centralWidget);
        starttime->setObjectName(QString::fromUtf8("starttime"));
        starttime->setTime(QTime(8, 0, 0));

        horizontalLayout_2->addWidget(starttime);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        tolerance = new QSpinBox(centralWidget);
        tolerance->setObjectName(QString::fromUtf8("tolerance"));
        tolerance->setMinimumSize(QSize(3, 3));
        tolerance->setMaximum(100);
        tolerance->setValue(100);

        horizontalLayout_3->addWidget(tolerance);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout4 = new QHBoxLayout();
        horizontalLayout4->setSpacing(10);
        horizontalLayout4->setObjectName(QString::fromUtf8("horizontalLayout4"));
        labelStart = new QLabel(centralWidget);
        labelStart->setObjectName(QString::fromUtf8("labelStart"));
        labelStart->setMinimumSize(QSize(70, 20));
        labelStart->setFont(font);

        horizontalLayout4->addWidget(labelStart);

        comboBoxStartLine = new QComboBox(centralWidget);
        comboBoxStartLine->addItem(QString());
        comboBoxStartLine->setObjectName(QString::fromUtf8("comboBoxStartLine"));
        comboBoxStartLine->setMinimumSize(QSize(90, 20));
        comboBoxStartLine->setFont(font);

        horizontalLayout4->addWidget(comboBoxStartLine);

        comboBoxStartStation = new QComboBox(centralWidget);
        comboBoxStartStation->addItem(QString());
        comboBoxStartStation->setObjectName(QString::fromUtf8("comboBoxStartStation"));
        comboBoxStartStation->setMinimumSize(QSize(90, 20));
        comboBoxStartStation->setFont(font);

        horizontalLayout4->addWidget(comboBoxStartStation);

        horizontalLayout4->setStretch(0, 7);
        horizontalLayout4->setStretch(1, 9);
        horizontalLayout4->setStretch(2, 9);

        verticalLayout_2->addLayout(horizontalLayout4);

        horizontalLayout5 = new QHBoxLayout();
        horizontalLayout5->setSpacing(10);
        horizontalLayout5->setObjectName(QString::fromUtf8("horizontalLayout5"));
        labelDestination = new QLabel(centralWidget);
        labelDestination->setObjectName(QString::fromUtf8("labelDestination"));
        labelDestination->setMinimumSize(QSize(70, 20));
        labelDestination->setFont(font);

        horizontalLayout5->addWidget(labelDestination);

        comboBoxDstLine = new QComboBox(centralWidget);
        comboBoxDstLine->addItem(QString());
        comboBoxDstLine->setObjectName(QString::fromUtf8("comboBoxDstLine"));
        comboBoxDstLine->setMinimumSize(QSize(90, 20));
        comboBoxDstLine->setFont(font);

        horizontalLayout5->addWidget(comboBoxDstLine);

        comboBoxDstStation = new QComboBox(centralWidget);
        comboBoxDstStation->addItem(QString());
        comboBoxDstStation->setObjectName(QString::fromUtf8("comboBoxDstStation"));
        comboBoxDstStation->setMinimumSize(QSize(90, 20));
        comboBoxDstStation->setFont(font);

        horizontalLayout5->addWidget(comboBoxDstStation);

        horizontalLayout5->setStretch(0, 7);
        horizontalLayout5->setStretch(1, 9);
        horizontalLayout5->setStretch(2, 9);

        verticalLayout_2->addLayout(horizontalLayout5);

        horizontalLayout6 = new QHBoxLayout();
        horizontalLayout6->setSpacing(10);
        horizontalLayout6->setObjectName(QString::fromUtf8("horizontalLayout6"));
        pushButtonTransfer = new QPushButton(centralWidget);
        pushButtonTransfer->setObjectName(QString::fromUtf8("pushButtonTransfer"));
        pushButtonTransfer->setMinimumSize(QSize(70, 30));
        pushButtonTransfer->setFont(font);

        horizontalLayout6->addWidget(pushButtonTransfer);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(190, 30));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        radioButtonMinTransfer = new QRadioButton(groupBox);
        radioButtonMinTransfer->setObjectName(QString::fromUtf8("radioButtonMinTransfer"));
        radioButtonMinTransfer->setMinimumSize(QSize(50, 15));
        radioButtonMinTransfer->setFont(font);

        verticalLayout->addWidget(radioButtonMinTransfer);

        radioButtonMinPrice = new QRadioButton(groupBox);
        radioButtonMinPrice->setObjectName(QString::fromUtf8("radioButtonMinPrice"));
        radioButtonMinPrice->setMinimumSize(QSize(50, 15));

        verticalLayout->addWidget(radioButtonMinPrice);

        radioButtonMinTime = new QRadioButton(groupBox);
        radioButtonMinTime->setObjectName(QString::fromUtf8("radioButtonMinTime"));
        radioButtonMinTime->setMinimumSize(QSize(50, 15));
        radioButtonMinTime->setFont(font);
        radioButtonMinTime->setChecked(true);

        verticalLayout->addWidget(radioButtonMinTime);

        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));

        verticalLayout->addWidget(radioButton);


        horizontalLayout6->addWidget(groupBox);


        verticalLayout_2->addLayout(horizontalLayout6);

        labelTransferRoute = new QLabel(centralWidget);
        labelTransferRoute->setObjectName(QString::fromUtf8("labelTransferRoute"));
        labelTransferRoute->setMinimumSize(QSize(280, 20));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Consolas"));
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setWeight(75);
        labelTransferRoute->setFont(font2);

        verticalLayout_2->addWidget(labelTransferRoute);

        textBrowserRoute = new QTextBrowser(centralWidget);
        textBrowserRoute->setObjectName(QString::fromUtf8("textBrowserRoute"));
        textBrowserRoute->setMinimumSize(QSize(300, 300));
        textBrowserRoute->setFont(font);
        textBrowserRoute->setLineWidth(6);

        verticalLayout_2->addWidget(textBrowserRoute);

        verticalLayout_2->setStretch(0, 3);
        verticalLayout_2->setStretch(3, 2);
        verticalLayout_2->setStretch(4, 2);
        verticalLayout_2->setStretch(6, 2);
        verticalLayout_2->setStretch(7, 32);

        horizontalLayout->addLayout(verticalLayout_2);

        horizontalLayout->setStretch(0, 11);
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setMinimumSize(QSize(0, 0));
        mainToolBar->setIconSize(QSize(24, 24));
        mainToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        statusBar->setMinimumSize(QSize(0, 20));
        MainWindow->setStatusBar(statusBar);
#ifndef QT_NO_SHORTCUT
        labelStart->setBuddy(comboBoxStartLine);
        labelDestination->setBuddy(comboBoxDstLine);
#endif // QT_NO_SHORTCUT

        mainToolBar->addSeparator();
        mainToolBar->addAction(toolEnlarge);
        mainToolBar->addAction(toolShrink);
        mainToolBar->addSeparator();
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionLineMap);
        mainToolBar->addAction(actionExtraFunc);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\345\234\260\351\223\201\346\215\242\344\271\230\346\214\207\345\215\227", nullptr));
        toolEnlarge->setText(QApplication::translate("MainWindow", "\346\224\276\345\244\247", nullptr));
#ifndef QT_NO_TOOLTIP
        toolEnlarge->setToolTip(QApplication::translate("MainWindow", "\347\202\271\345\207\273\346\224\276\345\244\247", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        toolEnlarge->setShortcut(QApplication::translate("MainWindow", "Ctrl+L", nullptr));
#endif // QT_NO_SHORTCUT
        toolShrink->setText(QApplication::translate("MainWindow", "\347\274\251\345\260\217", nullptr));
#ifndef QT_NO_TOOLTIP
        toolShrink->setToolTip(QApplication::translate("MainWindow", "\347\202\271\345\207\273\347\274\251\345\260\217", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        toolShrink->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_NO_SHORTCUT
        actionsetcrowd->setText(QApplication::translate("MainWindow", "setcrowd", nullptr));
#ifndef QT_NO_TOOLTIP
        actionsetcrowd->setToolTip(QApplication::translate("MainWindow", "setcrowd", nullptr));
#endif // QT_NO_TOOLTIP
        actionLineMap->setText(QApplication::translate("MainWindow", "\345\234\260\351\223\201\345\233\276", nullptr));
#ifndef QT_NO_TOOLTIP
        actionLineMap->setToolTip(QApplication::translate("MainWindow", "\345\234\260\351\223\201\347\275\221\347\273\234\347\272\277\350\267\257\345\233\276", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionLineMap->setShortcut(QApplication::translate("MainWindow", "Ctrl+M", nullptr));
#endif // QT_NO_SHORTCUT
        actionExtraFunc->setText(QApplication::translate("MainWindow", "actionExtraFunc", nullptr));
#ifndef QT_NO_TOOLTIP
        actionExtraFunc->setToolTip(QApplication::translate("MainWindow", "actionExtraFunc", nullptr));
#endif // QT_NO_TOOLTIP
        labelTransfer->setText(QApplication::translate("MainWindow", "\346\215\242\344\271\230\346\214\207\345\215\227", nullptr));
        label->setText(QApplication::translate("MainWindow", "   \345\207\272\345\217\221\346\227\266\351\227\264\357\274\210HH:mm\357\274\211\357\274\232", nullptr));
        starttime->setDisplayFormat(QApplication::translate("MainWindow", "HH:mm", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "  \350\203\275\345\256\271\345\277\215\347\232\204\346\213\245\346\214\244\345\272\246\357\274\210%\357\274\211\357\274\232", nullptr));
        tolerance->setSuffix(QString());
        tolerance->setPrefix(QString());
        labelStart->setText(QApplication::translate("MainWindow", "\350\265\267\347\202\271\347\253\231(&S)\357\274\232", nullptr));
        comboBoxStartLine->setItemText(0, QApplication::translate("MainWindow", "\351\200\211\346\213\251\350\267\257\347\272\277", nullptr));

        comboBoxStartStation->setItemText(0, QApplication::translate("MainWindow", "\351\200\211\346\213\251\347\253\231\347\202\271", nullptr));

        labelDestination->setText(QApplication::translate("MainWindow", "\347\273\210\347\202\271\347\253\231(&D)\357\274\232", nullptr));
        comboBoxDstLine->setItemText(0, QApplication::translate("MainWindow", "\351\200\211\346\213\251\350\267\257\347\272\277", nullptr));

        comboBoxDstStation->setItemText(0, QApplication::translate("MainWindow", "\351\200\211\346\213\251\347\253\231\347\202\271", nullptr));

        pushButtonTransfer->setText(QApplication::translate("MainWindow", "\346\215\242\344\271\230", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "\346\215\242\344\271\230\347\255\226\347\225\245", nullptr));
        radioButtonMinTransfer->setText(QApplication::translate("MainWindow", "\346\215\242\344\271\230\346\254\241\346\225\260\346\234\200\345\260\221", nullptr));
        radioButtonMinPrice->setText(QApplication::translate("MainWindow", "\346\211\200\351\234\200\344\273\267\346\240\274\346\234\200\345\260\221", nullptr));
        radioButtonMinTime->setText(QApplication::translate("MainWindow", "\345\212\240\346\235\203\346\227\266\351\227\264\346\234\200\347\237\255", nullptr));
        radioButton->setText(QApplication::translate("MainWindow", "\345\220\210\350\256\241\346\227\266\351\227\264\346\234\200\347\237\255", nullptr));
        labelTransferRoute->setText(QApplication::translate("MainWindow", "\346\215\242\344\271\230\350\267\257\347\272\277\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

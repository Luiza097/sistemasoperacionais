/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label_trem1;
    QLabel *label_trilho1;
    QLabel *label_trilho2;
    QLabel *label_trilho3;
    QLabel *label_trilho4;
    QLabel *label_trilho4_2;
    QLabel *label_trilho1_2;
    QLabel *label_trilho2_2;
    QLabel *label_trem2;
    QLabel *label_trem3;
    QLabel *label_trem4;
    QLabel *label_trem5;
    QLabel *label_trem6;
    QSlider *horizontalSlider;
    QSlider *horizontalSlider_2;
    QSlider *horizontalSlider_3;
    QSlider *horizontalSlider_4;
    QSlider *horizontalSlider_5;
    QSlider *horizontalSlider_6;
    QLabel *label_trilho2_3;
    QLabel *label_trilho2_4;
    QLabel *label_trilho3_2;
    QLabel *label_trilho3_4;
    QLabel *label_trilho3_3;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(948, 545);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        label_trem1 = new QLabel(centralWidget);
        label_trem1->setObjectName("label_trem1");
        label_trem1->setGeometry(QRect(60, 100, 21, 17));
        label_trem1->setStyleSheet(QString::fromUtf8("QLabel { background: green}"));
        label_trilho1 = new QLabel(centralWidget);
        label_trilho1->setObjectName("label_trilho1");
        label_trilho1->setGeometry(QRect(80, 30, 271, 17));
        label_trilho1->setStyleSheet(QString::fromUtf8("QLabel { background: yellow}"));
        label_trilho2 = new QLabel(centralWidget);
        label_trilho2->setObjectName("label_trilho2");
        label_trilho2->setGeometry(QRect(80, 150, 261, 17));
        label_trilho2->setStyleSheet(QString::fromUtf8("QLabel { background: yellow}"));
        label_trilho3 = new QLabel(centralWidget);
        label_trilho3->setObjectName("label_trilho3");
        label_trilho3->setGeometry(QRect(480, 150, 21, 136));
        label_trilho3->setStyleSheet(QString::fromUtf8("QLabel { background: yellow}"));
        label_trilho4 = new QLabel(centralWidget);
        label_trilho4->setObjectName("label_trilho4");
        label_trilho4->setGeometry(QRect(60, 30, 21, 241));
        label_trilho4->setStyleSheet(QString::fromUtf8("QLabel { background: yellow}"));
        label_trilho4_2 = new QLabel(centralWidget);
        label_trilho4_2->setObjectName("label_trilho4_2");
        label_trilho4_2->setGeometry(QRect(600, 30, 21, 131));
        label_trilho4_2->setStyleSheet(QString::fromUtf8("QLabel { background: yellow}"));
        label_trilho1_2 = new QLabel(centralWidget);
        label_trilho1_2->setObjectName("label_trilho1_2");
        label_trilho1_2->setGeometry(QRect(350, 30, 541, 17));
        label_trilho1_2->setStyleSheet(QString::fromUtf8("QLabel { background: yellow}"));
        label_trilho2_2 = new QLabel(centralWidget);
        label_trilho2_2->setObjectName("label_trilho2_2");
        label_trilho2_2->setGeometry(QRect(340, 150, 551, 17));
        label_trilho2_2->setStyleSheet(QString::fromUtf8("QLabel { background: yellow}"));
        label_trem2 = new QLabel(centralWidget);
        label_trem2->setObjectName("label_trem2");
        label_trem2->setGeometry(QRect(470, 30, 21, 17));
        label_trem2->setStyleSheet(QString::fromUtf8("QLabel { background: red}"));
        label_trem3 = new QLabel(centralWidget);
        label_trem3->setObjectName("label_trem3");
        label_trem3->setGeometry(QRect(750, 30, 21, 16));
        label_trem3->setStyleSheet(QString::fromUtf8("background-color: blue;"));
        label_trem4 = new QLabel(centralWidget);
        label_trem4->setObjectName("label_trem4");
        label_trem4->setGeometry(QRect(60, 220, 21, 16));
        label_trem4->setStyleSheet(QString::fromUtf8("background-color: orange;"));
        label_trem5 = new QLabel(centralWidget);
        label_trem5->setObjectName("label_trem5");
        label_trem5->setGeometry(QRect(790, 150, 21, 16));
        label_trem5->setStyleSheet(QString::fromUtf8("background-color: purple;"));
        label_trem6 = new QLabel(centralWidget);
        label_trem6->setObjectName("label_trem6");
        label_trem6->setGeometry(QRect(250, 270, 21, 16));
        label_trem6->setStyleSheet(QString::fromUtf8("background-color: black;"));
        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setGeometry(QRect(60, 340, 160, 16));
        horizontalSlider->setStyleSheet(QString::fromUtf8("QSlider::handle:horizontal{background-color:green}"));
        horizontalSlider->setMaximum(200);
        horizontalSlider->setValue(100);
        horizontalSlider->setOrientation(Qt::Orientation::Horizontal);
        horizontalSlider_2 = new QSlider(centralWidget);
        horizontalSlider_2->setObjectName("horizontalSlider_2");
        horizontalSlider_2->setGeometry(QRect(60, 370, 160, 16));
        horizontalSlider_2->setStyleSheet(QString::fromUtf8("QSlider::handle:horizontal{background-color:red}"));
        horizontalSlider_2->setMaximum(200);
        horizontalSlider_2->setValue(100);
        horizontalSlider_2->setOrientation(Qt::Orientation::Horizontal);
        horizontalSlider_3 = new QSlider(centralWidget);
        horizontalSlider_3->setObjectName("horizontalSlider_3");
        horizontalSlider_3->setGeometry(QRect(60, 390, 160, 16));
        horizontalSlider_3->setStyleSheet(QString::fromUtf8("QSlider::handle:horizontal{background-color:blue}"));
        horizontalSlider_3->setMaximum(200);
        horizontalSlider_3->setValue(100);
        horizontalSlider_3->setOrientation(Qt::Orientation::Horizontal);
        horizontalSlider_4 = new QSlider(centralWidget);
        horizontalSlider_4->setObjectName("horizontalSlider_4");
        horizontalSlider_4->setGeometry(QRect(60, 410, 160, 16));
        horizontalSlider_4->setStyleSheet(QString::fromUtf8("QSlider::handle:horizontal{background-color:orange}"));
        horizontalSlider_4->setMaximum(200);
        horizontalSlider_4->setPageStep(10);
        horizontalSlider_4->setValue(100);
        horizontalSlider_4->setOrientation(Qt::Orientation::Horizontal);
        horizontalSlider_5 = new QSlider(centralWidget);
        horizontalSlider_5->setObjectName("horizontalSlider_5");
        horizontalSlider_5->setGeometry(QRect(60, 440, 160, 16));
        horizontalSlider_5->setStyleSheet(QString::fromUtf8("QSlider::handle:horizontal{background-color:purple}"));
        horizontalSlider_5->setMaximum(200);
        horizontalSlider_5->setValue(100);
        horizontalSlider_5->setOrientation(Qt::Orientation::Horizontal);
        horizontalSlider_6 = new QSlider(centralWidget);
        horizontalSlider_6->setObjectName("horizontalSlider_6");
        horizontalSlider_6->setGeometry(QRect(60, 460, 161, 20));
        horizontalSlider_6->setStyleSheet(QString::fromUtf8("QSlider::handle:horizontal{background-color:black}"));
        horizontalSlider_6->setMaximum(200);
        horizontalSlider_6->setValue(100);
        horizontalSlider_6->setOrientation(Qt::Orientation::Horizontal);
        label_trilho2_3 = new QLabel(centralWidget);
        label_trilho2_3->setObjectName("label_trilho2_3");
        label_trilho2_3->setGeometry(QRect(60, 270, 271, 17));
        label_trilho2_3->setStyleSheet(QString::fromUtf8("QLabel { background: yellow}"));
        label_trilho2_4 = new QLabel(centralWidget);
        label_trilho2_4->setObjectName("label_trilho2_4");
        label_trilho2_4->setGeometry(QRect(320, 270, 571, 17));
        label_trilho2_4->setStyleSheet(QString::fromUtf8("QLabel { background: yellow}"));
        label_trilho3_2 = new QLabel(centralWidget);
        label_trilho3_2->setObjectName("label_trilho3_2");
        label_trilho3_2->setGeometry(QRect(330, 30, 21, 131));
        label_trilho3_2->setStyleSheet(QString::fromUtf8("QLabel { background: yellow}"));
        label_trilho3_4 = new QLabel(centralWidget);
        label_trilho3_4->setObjectName("label_trilho3_4");
        label_trilho3_4->setGeometry(QRect(870, 40, 21, 131));
        label_trilho3_4->setStyleSheet(QString::fromUtf8("QLabel { background: yellow}"));
        label_trilho3_3 = new QLabel(centralWidget);
        label_trilho3_3->setObjectName("label_trilho3_3");
        label_trilho3_3->setGeometry(QRect(870, 140, 21, 141));
        label_trilho3_3->setStyleSheet(QString::fromUtf8("QLabel { background: yellow}"));
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(600, 90, 16, 16));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(330, 90, 16, 16));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(190, 150, 16, 16));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(400, 150, 16, 16));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(550, 150, 16, 16));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(740, 150, 16, 20));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(480, 220, 16, 16));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(60, 270, 16, 16));
        MainWindow->setCentralWidget(centralWidget);
        label_trilho3->raise();
        label_trilho2_3->raise();
        label_trilho2_4->raise();
        label_trilho3_3->raise();
        label_trilho3_2->raise();
        label_trilho4->raise();
        label_trilho1_2->raise();
        label_trilho1->raise();
        label_trilho3_4->raise();
        label_trilho2->raise();
        label_trilho4_2->raise();
        label_trilho2_2->raise();
        horizontalSlider->raise();
        horizontalSlider_2->raise();
        horizontalSlider_3->raise();
        horizontalSlider_4->raise();
        horizontalSlider_5->raise();
        horizontalSlider_6->raise();
        label_trem6->raise();
        label_trem4->raise();
        label_trem1->raise();
        label_trem2->raise();
        label_trem3->raise();
        label_trem5->raise();
        label->raise();
        label_2->raise();
        label_3->raise();
        label_4->raise();
        label_5->raise();
        label_6->raise();
        label_7->raise();
        label_8->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 948, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_trem1->setText(QCoreApplication::translate("MainWindow", "T1", nullptr));
        label_trilho1->setText(QString());
        label_trilho2->setText(QString());
        label_trilho3->setText(QString());
        label_trilho4->setText(QString());
        label_trilho4_2->setText(QString());
        label_trilho1_2->setText(QString());
        label_trilho2_2->setText(QString());
        label_trem2->setText(QCoreApplication::translate("MainWindow", "T2", nullptr));
        label_trem3->setText(QCoreApplication::translate("MainWindow", "T3", nullptr));
        label_trem4->setText(QCoreApplication::translate("MainWindow", "T4", nullptr));
        label_trem5->setText(QCoreApplication::translate("MainWindow", "T5", nullptr));
        label_trem6->setText(QCoreApplication::translate("MainWindow", "T6", nullptr));
        label_trilho2_3->setText(QString());
        label_trilho2_4->setText(QString());
        label_trilho3_2->setText(QString());
        label_trilho3_4->setText(QString());
        label_trilho3_3->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "01", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "00", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "02", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "03", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "04", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "05", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "06", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

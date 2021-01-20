/********************************************************************************
** Form generated from reading UI file 'QtPLCDialogClass.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTPLCDIALOGCLASS_H
#define UI_QTPLCDIALOGCLASS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "../QtPLCLibrary/userle.h"

QT_BEGIN_NAMESPACE

class Ui_QtPLCDialogClass
{
public:
    QTabWidget *tabWidget_PLC;
    QWidget *tab_PLC_Control;
    QVBoxLayout *verticalLayout_9;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_7;
    QSpacerItem *verticalSpacer_10;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_40;
    QLabel *lb_00;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_11;
    QLabel *lb_10;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *verticalSpacer_11;
    QGroupBox *groupBox_7;
    QVBoxLayout *verticalLayout_11;
    QGridLayout *gridLayout_6;
    QPushButton *pb_cmdVaccum;
    QPushButton *pb_cmdBaffle;
    QPushButton *pb_cmdReject;
    QPushButton *pb_cmdCapGet;
    QPushButton *pb_cmdCapGetValve;
    QPushButton *pb_cmdStopSignal;
    QPushButton *pb_cmdChannelSwith;
    QPushButton *pb_cmdCapBackValve;
    QPushButton *pb_cmdYellowAlarmout;
    QPushButton *pb_cmdAlarmSignal;
    QPushButton *pb_cmdAlarmOut;
    QSpacerItem *verticalSpacer_18;
    QGroupBox *groupBox_8;
    QHBoxLayout *horizontalLayout_8;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_15;
    QLabel *label_2;
    QLineEdit *lE_Analogoutput;
    QSpacerItem *horizontalSpacer_17;
    QSpacerItem *verticalSpacer_9;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_7;
    QPushButton *pB_cmdFeedSingleStop;
    QPushButton *pB_cmdAxisFeedPosMov;
    QPushButton *pB_cmdAxisFeedStopMov;
    QPushButton *pB_cmdFeedSingle;
    QPushButton *pB_cmdAxisFeedRelMov;
    QPushButton *pB_cmdAxisFeedJogPos;
    QPushButton *pB_cmdAxisFeedJogNeg;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_8;
    QPushButton *pB_cmdAxisSwingJogPos;
    QPushButton *pB_cmdAxisSwingJogNeg;
    QPushButton *pB_cmdAxisSwingRelMov;
    QPushButton *pB_cmdAxisSwingPosMov;
    QPushButton *pB_cmdAxisSwingStopMov;
    QPushButton *pB_cmdSwing;
    QWidget *tab_6;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_4;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout;
    QPushButton *pB_cmdScaleRead;
    QPushButton *pB_cmdScaleTire;
    QPushButton *pB_cmdScaleCalibExt;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QComboBox *cB_paraScaleSetStable;
    QPushButton *pB_cmdScaleSetStable;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_12;
    QPushButton *pB_cmdAlogtest;
    QSpacerItem *horizontalSpacer_13;
    QSpacerItem *verticalSpacer_3;
    QWidget *tab_8;
    QVBoxLayout *verticalLayout;
    QFrame *frame_4;
    QGridLayout *gridLayout_5;
    QLabel *label_25;
    UserLE *lE_FeedTimeOut;
    UserLE *lE_CapPickInterval;
    UserLE *lE_s_trg_stop1;
    QLabel *label_41;
    QLabel *label_26;
    UserLE *lE_TireDelay;
    QLabel *label_32;
    QSpacerItem *horizontalSpacer;
    UserLE *lE_s_trg_stop0;
    UserLE *lE_CapBackInterval;
    UserLE *lE_ReadDelay;
    UserLE *lE_TireWaitTime;
    QLabel *label_31;
    QLabel *label_5;
    UserLE *lE_StopSignalDelay;
    QLabel *label_4;
    QLabel *label_42;
    QLabel *label_44;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_12;
    QFrame *frame_6;
    QGridLayout *gridLayout_2;
    QLabel *label_9;
    QLineEdit *lE_InterUnderLoad;
    QLineEdit *lE_TOverload;
    QLabel *label_53;
    QLineEdit *lE_GroupSet;
    QLabel *label_54;
    QLabel *label_14;
    QLabel *label_13;
    QLineEdit *lE_TestInterval;
    QLabel *label_55;
    QLineEdit *lE_TDemand;
    QLabel *label_52;
    QLabel *label_12;
    QLabel *label_50;
    QComboBox *cB_TireMode;
    QLineEdit *lE_GroupNo;
    QLineEdit *lE_InterOverLoad;
    QLineEdit *lE_TUnderload;
    QLabel *label_79;
    QSpacerItem *horizontalSpacer_4;
    QLineEdit *lE_SysOveride_2;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer_6;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_3;
    QLabel *label_21;
    QLineEdit *lE_AxisFeedStep;
    QLabel *label_19;
    QLineEdit *lE_AxisFeedErrorNo;
    QLabel *label_22;
    QLineEdit *lE_AxisFeedRelMovDistance;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_9;
    QLabel *label_24;
    QLineEdit *lE_AxisSwingStep;
    QLabel *label_27;
    QLineEdit *lE_AxisSwingErrorNo;
    QLabel *label_28;
    QLineEdit *lE_AxisSwingRelMovDistance;
    QSpacerItem *verticalSpacer_8;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLineEdit *lE_MachineStep;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *lE_Alarm16;
    QLineEdit *lE_AlarmStatus;
    QLabel *label_33;
    QLabel *label_29;
    QLineEdit *lE_TimeInterval;
    QLabel *label_20;
    QSpacerItem *verticalSpacer_7;
    QPushButton *pb_cmdParaSave;
    QFrame *frame_5;
    QGridLayout *gridLayout_4;
    QPushButton *pB_cmdCounterZero_2;
    QPushButton *pB_cmdCounterZero_3;
    QPushButton *pB_cmdCounterZero_5;
    QPushButton *pB_cmdCounterZero_4;
    QFrame *frame;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *groupBox_10;
    QFrame *frame_7;
    QGridLayout *gridLayout_10;
    QFrame *frame_15;
    QVBoxLayout *verticalLayout_19;
    QLineEdit *lE_ScaleResult;
    QSpacerItem *horizontalSpacer_19;
    QLabel *label_10;
    QFrame *frame_8;
    QVBoxLayout *verticalLayout_13;
    QComboBox *cB_ScaleStableState;
    QFrame *frame_14;
    QVBoxLayout *verticalLayout_17;
    QLineEdit *lE_ProdCount;
    QSpacerItem *verticalSpacer_13;
    QSpacerItem *verticalSpacer_15;
    QLabel *label_43;
    QSpacerItem *horizontalSpacer_18;
    QLabel *label_39;
    QFrame *frame_16;
    QVBoxLayout *verticalLayout_18;
    QLineEdit *lE_TOCount;
    QLabel *label_48;
    QFrame *frame_13;
    QVBoxLayout *verticalLayout_16;
    QLineEdit *lE_PassCount;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_8;
    QLineEdit *lE_Finished;
    QSpacerItem *horizontalSpacer_10;
    QLabel *label_49;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_14;
    QLabel *label_18;
    QSpacerItem *verticalSpacer_17;
    QLabel *label_45;
    QLabel *label_15;
    QSpacerItem *verticalSpacer_12;
    QSpacerItem *verticalSpacer_16;
    QLabel *label_16;
    QLabel *label_17;
    QFrame *frame_12;
    QVBoxLayout *verticalLayout_20;
    QLineEdit *lE_RejectCount;
    QFrame *frame_17;
    QVBoxLayout *verticalLayout_21;
    QLineEdit *lE_TUCount;
    QFrame *frame_18;
    QVBoxLayout *verticalLayout_22;
    QLineEdit *lE_Weight;
    QFrame *frame_19;
    QVBoxLayout *verticalLayout_23;
    QLineEdit *lE_GroupIndex;
    QFrame *frame_9;
    QLabel *label_80;
    QFrame *frame_10;
    QVBoxLayout *verticalLayout_14;
    QLineEdit *lE_SysOveride;
    QLabel *label_78;
    QFrame *frame_11;
    QVBoxLayout *verticalLayout_15;
    QLineEdit *lE_BatchName;
    QLabel *lb_logo;
    QPushButton *pB_dtDlg;
    QFrame *frame_20;
    QPushButton *pB_SetUp;
    QPushButton *pB_cmdStart;

    void setupUi(QDialog *QtPLCDialogClass)
    {
        if (QtPLCDialogClass->objectName().isEmpty())
            QtPLCDialogClass->setObjectName(QString::fromUtf8("QtPLCDialogClass"));
        QtPLCDialogClass->resize(2273, 893);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\271\274\345\234\206"));
        font.setPointSize(20);
        QtPLCDialogClass->setFont(font);
        QtPLCDialogClass->setLayoutDirection(Qt::LeftToRight);
        tabWidget_PLC = new QTabWidget(QtPLCDialogClass);
        tabWidget_PLC->setObjectName(QString::fromUtf8("tabWidget_PLC"));
        tabWidget_PLC->setGeometry(QRect(0, 0, 849, 755));
        tabWidget_PLC->setMinimumSize(QSize(849, 755));
        tabWidget_PLC->setMaximumSize(QSize(849, 755));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(20);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setWeight(75);
        tabWidget_PLC->setFont(font1);
        tabWidget_PLC->setStyleSheet(QString::fromUtf8(""));
        tabWidget_PLC->setTabShape(QTabWidget::Rounded);
        tab_PLC_Control = new QWidget();
        tab_PLC_Control->setObjectName(QString::fromUtf8("tab_PLC_Control"));
        verticalLayout_9 = new QVBoxLayout(tab_PLC_Control);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        tabWidget = new QTabWidget(tab_PLC_Control);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setMinimumSize(QSize(0, 0));
        tabWidget->setMaximumSize(QSize(122222, 111111));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_7 = new QVBoxLayout(tab);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalSpacer_10 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_10);

        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_6 = new QHBoxLayout(groupBox);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_7);

        label_40 = new QLabel(groupBox);
        label_40->setObjectName(QString::fromUtf8("label_40"));
        label_40->setMinimumSize(QSize(210, 0));
        label_40->setMaximumSize(QSize(210, 16777215));

        horizontalLayout_6->addWidget(label_40);

        lb_00 = new QLabel(groupBox);
        lb_00->setObjectName(QString::fromUtf8("lb_00"));
        lb_00->setMinimumSize(QSize(32, 32));
        lb_00->setMaximumSize(QSize(32, 32));
        lb_00->setPixmap(QPixmap(QString::fromUtf8("C:/Users/33741/Desktop/QtConsoleApplication1/QtClassLibrary1/ico/redLed.png")));

        horizontalLayout_6->addWidget(lb_00);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_9);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setMinimumSize(QSize(210, 0));
        label_11->setMaximumSize(QSize(210, 16777215));

        horizontalLayout_6->addWidget(label_11);

        lb_10 = new QLabel(groupBox);
        lb_10->setObjectName(QString::fromUtf8("lb_10"));
        lb_10->setMinimumSize(QSize(32, 32));
        lb_10->setMaximumSize(QSize(32, 32));
        lb_10->setPixmap(QPixmap(QString::fromUtf8("C:/Users/33741/Desktop/QtConsoleApplication1/QtClassLibrary1/ico/redLed.png")));

        horizontalLayout_6->addWidget(lb_10);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_8);


        verticalLayout_7->addWidget(groupBox);

        verticalSpacer_11 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_11);

        groupBox_7 = new QGroupBox(tab);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        verticalLayout_11 = new QVBoxLayout(groupBox_7);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setSpacing(6);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        pb_cmdVaccum = new QPushButton(groupBox_7);
        pb_cmdVaccum->setObjectName(QString::fromUtf8("pb_cmdVaccum"));
        pb_cmdVaccum->setMinimumSize(QSize(250, 44));
        pb_cmdVaccum->setMaximumSize(QSize(127, 44));
        pb_cmdVaccum->setCheckable(true);

        gridLayout_6->addWidget(pb_cmdVaccum, 0, 0, 1, 1);

        pb_cmdBaffle = new QPushButton(groupBox_7);
        pb_cmdBaffle->setObjectName(QString::fromUtf8("pb_cmdBaffle"));
        pb_cmdBaffle->setMinimumSize(QSize(250, 44));
        pb_cmdBaffle->setMaximumSize(QSize(127, 44));
        pb_cmdBaffle->setCheckable(true);

        gridLayout_6->addWidget(pb_cmdBaffle, 0, 1, 1, 1);

        pb_cmdReject = new QPushButton(groupBox_7);
        pb_cmdReject->setObjectName(QString::fromUtf8("pb_cmdReject"));
        pb_cmdReject->setMinimumSize(QSize(250, 44));
        pb_cmdReject->setMaximumSize(QSize(127, 44));
        pb_cmdReject->setCheckable(true);

        gridLayout_6->addWidget(pb_cmdReject, 0, 2, 1, 1);

        pb_cmdCapGet = new QPushButton(groupBox_7);
        pb_cmdCapGet->setObjectName(QString::fromUtf8("pb_cmdCapGet"));
        pb_cmdCapGet->setMinimumSize(QSize(250, 44));
        pb_cmdCapGet->setMaximumSize(QSize(127, 44));
        pb_cmdCapGet->setCheckable(true);

        gridLayout_6->addWidget(pb_cmdCapGet, 1, 0, 1, 1);

        pb_cmdCapGetValve = new QPushButton(groupBox_7);
        pb_cmdCapGetValve->setObjectName(QString::fromUtf8("pb_cmdCapGetValve"));
        pb_cmdCapGetValve->setMinimumSize(QSize(250, 44));
        pb_cmdCapGetValve->setMaximumSize(QSize(127, 44));
        pb_cmdCapGetValve->setCheckable(true);

        gridLayout_6->addWidget(pb_cmdCapGetValve, 1, 1, 1, 1);

        pb_cmdStopSignal = new QPushButton(groupBox_7);
        pb_cmdStopSignal->setObjectName(QString::fromUtf8("pb_cmdStopSignal"));
        pb_cmdStopSignal->setMinimumSize(QSize(250, 44));
        pb_cmdStopSignal->setMaximumSize(QSize(127, 44));
        pb_cmdStopSignal->setCheckable(true);

        gridLayout_6->addWidget(pb_cmdStopSignal, 1, 2, 1, 1);

        pb_cmdChannelSwith = new QPushButton(groupBox_7);
        pb_cmdChannelSwith->setObjectName(QString::fromUtf8("pb_cmdChannelSwith"));
        pb_cmdChannelSwith->setMinimumSize(QSize(250, 44));
        pb_cmdChannelSwith->setMaximumSize(QSize(127, 44));
        pb_cmdChannelSwith->setCheckable(true);

        gridLayout_6->addWidget(pb_cmdChannelSwith, 2, 0, 1, 1);

        pb_cmdCapBackValve = new QPushButton(groupBox_7);
        pb_cmdCapBackValve->setObjectName(QString::fromUtf8("pb_cmdCapBackValve"));
        pb_cmdCapBackValve->setMinimumSize(QSize(250, 44));
        pb_cmdCapBackValve->setMaximumSize(QSize(127, 44));
        pb_cmdCapBackValve->setCheckable(true);

        gridLayout_6->addWidget(pb_cmdCapBackValve, 2, 1, 1, 1);

        pb_cmdYellowAlarmout = new QPushButton(groupBox_7);
        pb_cmdYellowAlarmout->setObjectName(QString::fromUtf8("pb_cmdYellowAlarmout"));
        pb_cmdYellowAlarmout->setMinimumSize(QSize(250, 44));
        pb_cmdYellowAlarmout->setMaximumSize(QSize(127, 44));
        pb_cmdYellowAlarmout->setCheckable(true);

        gridLayout_6->addWidget(pb_cmdYellowAlarmout, 2, 2, 1, 1);

        pb_cmdAlarmSignal = new QPushButton(groupBox_7);
        pb_cmdAlarmSignal->setObjectName(QString::fromUtf8("pb_cmdAlarmSignal"));
        pb_cmdAlarmSignal->setMinimumSize(QSize(250, 44));
        pb_cmdAlarmSignal->setMaximumSize(QSize(127, 44));
        pb_cmdAlarmSignal->setCheckable(true);

        gridLayout_6->addWidget(pb_cmdAlarmSignal, 3, 0, 1, 1);

        pb_cmdAlarmOut = new QPushButton(groupBox_7);
        pb_cmdAlarmOut->setObjectName(QString::fromUtf8("pb_cmdAlarmOut"));
        pb_cmdAlarmOut->setMinimumSize(QSize(250, 44));
        pb_cmdAlarmOut->setMaximumSize(QSize(127, 44));
        pb_cmdAlarmOut->setCheckable(true);

        gridLayout_6->addWidget(pb_cmdAlarmOut, 3, 1, 1, 1);


        verticalLayout_11->addLayout(gridLayout_6);


        verticalLayout_7->addWidget(groupBox_7);

        verticalSpacer_18 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_18);

        groupBox_8 = new QGroupBox(tab);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        horizontalLayout_8 = new QHBoxLayout(groupBox_8);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_15);

        label_2 = new QLabel(groupBox_8);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_9->addWidget(label_2);

        lE_Analogoutput = new QLineEdit(groupBox_8);
        lE_Analogoutput->setObjectName(QString::fromUtf8("lE_Analogoutput"));
        lE_Analogoutput->setEnabled(false);

        horizontalLayout_9->addWidget(lE_Analogoutput);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_17);


        horizontalLayout_8->addLayout(horizontalLayout_9);


        verticalLayout_7->addWidget(groupBox_8);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_9);

        tabWidget->addTab(tab, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        verticalLayout_5 = new QVBoxLayout(tab_4);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        groupBox_2 = new QGroupBox(tab_4);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_7 = new QGridLayout(groupBox_2);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        pB_cmdFeedSingleStop = new QPushButton(groupBox_2);
        pB_cmdFeedSingleStop->setObjectName(QString::fromUtf8("pB_cmdFeedSingleStop"));

        gridLayout_7->addWidget(pB_cmdFeedSingleStop, 2, 1, 1, 1);

        pB_cmdAxisFeedPosMov = new QPushButton(groupBox_2);
        pB_cmdAxisFeedPosMov->setObjectName(QString::fromUtf8("pB_cmdAxisFeedPosMov"));

        gridLayout_7->addWidget(pB_cmdAxisFeedPosMov, 1, 1, 1, 1);

        pB_cmdAxisFeedStopMov = new QPushButton(groupBox_2);
        pB_cmdAxisFeedStopMov->setObjectName(QString::fromUtf8("pB_cmdAxisFeedStopMov"));

        gridLayout_7->addWidget(pB_cmdAxisFeedStopMov, 1, 2, 1, 1);

        pB_cmdFeedSingle = new QPushButton(groupBox_2);
        pB_cmdFeedSingle->setObjectName(QString::fromUtf8("pB_cmdFeedSingle"));

        gridLayout_7->addWidget(pB_cmdFeedSingle, 2, 0, 1, 1);

        pB_cmdAxisFeedRelMov = new QPushButton(groupBox_2);
        pB_cmdAxisFeedRelMov->setObjectName(QString::fromUtf8("pB_cmdAxisFeedRelMov"));

        gridLayout_7->addWidget(pB_cmdAxisFeedRelMov, 1, 0, 1, 1);

        pB_cmdAxisFeedJogPos = new QPushButton(groupBox_2);
        pB_cmdAxisFeedJogPos->setObjectName(QString::fromUtf8("pB_cmdAxisFeedJogPos"));

        gridLayout_7->addWidget(pB_cmdAxisFeedJogPos, 0, 0, 1, 1);

        pB_cmdAxisFeedJogNeg = new QPushButton(groupBox_2);
        pB_cmdAxisFeedJogNeg->setObjectName(QString::fromUtf8("pB_cmdAxisFeedJogNeg"));

        gridLayout_7->addWidget(pB_cmdAxisFeedJogNeg, 0, 1, 1, 1);


        verticalLayout_5->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(tab_4);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_8 = new QGridLayout(groupBox_3);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        pB_cmdAxisSwingJogPos = new QPushButton(groupBox_3);
        pB_cmdAxisSwingJogPos->setObjectName(QString::fromUtf8("pB_cmdAxisSwingJogPos"));

        gridLayout_8->addWidget(pB_cmdAxisSwingJogPos, 0, 0, 1, 1);

        pB_cmdAxisSwingJogNeg = new QPushButton(groupBox_3);
        pB_cmdAxisSwingJogNeg->setObjectName(QString::fromUtf8("pB_cmdAxisSwingJogNeg"));

        gridLayout_8->addWidget(pB_cmdAxisSwingJogNeg, 0, 1, 1, 1);

        pB_cmdAxisSwingRelMov = new QPushButton(groupBox_3);
        pB_cmdAxisSwingRelMov->setObjectName(QString::fromUtf8("pB_cmdAxisSwingRelMov"));

        gridLayout_8->addWidget(pB_cmdAxisSwingRelMov, 1, 0, 1, 1);

        pB_cmdAxisSwingPosMov = new QPushButton(groupBox_3);
        pB_cmdAxisSwingPosMov->setObjectName(QString::fromUtf8("pB_cmdAxisSwingPosMov"));

        gridLayout_8->addWidget(pB_cmdAxisSwingPosMov, 1, 1, 1, 1);

        pB_cmdAxisSwingStopMov = new QPushButton(groupBox_3);
        pB_cmdAxisSwingStopMov->setObjectName(QString::fromUtf8("pB_cmdAxisSwingStopMov"));

        gridLayout_8->addWidget(pB_cmdAxisSwingStopMov, 1, 2, 1, 1);

        pB_cmdSwing = new QPushButton(groupBox_3);
        pB_cmdSwing->setObjectName(QString::fromUtf8("pB_cmdSwing"));

        gridLayout_8->addWidget(pB_cmdSwing, 2, 0, 1, 1);


        verticalLayout_5->addWidget(groupBox_3);

        tabWidget->addTab(tab_4, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        verticalLayout_2 = new QVBoxLayout(tab_6);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_4);

        groupBox_5 = new QGroupBox(tab_6);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setFlat(false);
        verticalLayout_10 = new QVBoxLayout(groupBox_5);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pB_cmdScaleRead = new QPushButton(groupBox_5);
        pB_cmdScaleRead->setObjectName(QString::fromUtf8("pB_cmdScaleRead"));

        horizontalLayout->addWidget(pB_cmdScaleRead);

        pB_cmdScaleTire = new QPushButton(groupBox_5);
        pB_cmdScaleTire->setObjectName(QString::fromUtf8("pB_cmdScaleTire"));

        horizontalLayout->addWidget(pB_cmdScaleTire);

        pB_cmdScaleCalibExt = new QPushButton(groupBox_5);
        pB_cmdScaleCalibExt->setObjectName(QString::fromUtf8("pB_cmdScaleCalibExt"));

        horizontalLayout->addWidget(pB_cmdScaleCalibExt);


        verticalLayout_10->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_10->addItem(verticalSpacer);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(groupBox_5);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        cB_paraScaleSetStable = new QComboBox(groupBox_5);
        cB_paraScaleSetStable->addItem(QString());
        cB_paraScaleSetStable->addItem(QString());
        cB_paraScaleSetStable->addItem(QString());
        cB_paraScaleSetStable->addItem(QString());
        cB_paraScaleSetStable->setObjectName(QString::fromUtf8("cB_paraScaleSetStable"));

        horizontalLayout_2->addWidget(cB_paraScaleSetStable);


        horizontalLayout_7->addLayout(horizontalLayout_2);

        pB_cmdScaleSetStable = new QPushButton(groupBox_5);
        pB_cmdScaleSetStable->setObjectName(QString::fromUtf8("pB_cmdScaleSetStable"));

        horizontalLayout_7->addWidget(pB_cmdScaleSetStable);


        verticalLayout_10->addLayout(horizontalLayout_7);


        verticalLayout_2->addWidget(groupBox_5);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_12);

        pB_cmdAlogtest = new QPushButton(tab_6);
        pB_cmdAlogtest->setObjectName(QString::fromUtf8("pB_cmdAlogtest"));

        horizontalLayout_3->addWidget(pB_cmdAlogtest);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_13);


        verticalLayout_2->addLayout(horizontalLayout_3);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        tabWidget->addTab(tab_6, QString());

        verticalLayout_9->addWidget(tabWidget);

        tabWidget_PLC->addTab(tab_PLC_Control, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName(QString::fromUtf8("tab_8"));
        verticalLayout = new QVBoxLayout(tab_8);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame_4 = new QFrame(tab_8);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setFont(font1);
        frame_4->setFrameShape(QFrame::Box);
        frame_4->setFrameShadow(QFrame::Sunken);
        frame_4->setLineWidth(2);
        gridLayout_5 = new QGridLayout(frame_4);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_25 = new QLabel(frame_4);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_25->sizePolicy().hasHeightForWidth());
        label_25->setSizePolicy(sizePolicy);
        label_25->setMinimumSize(QSize(0, 30));
        label_25->setMaximumSize(QSize(232323, 30));
        label_25->setFont(font1);
        label_25->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(label_25, 0, 0, 1, 1);

        lE_FeedTimeOut = new UserLE(frame_4);
        lE_FeedTimeOut->setObjectName(QString::fromUtf8("lE_FeedTimeOut"));
        lE_FeedTimeOut->setMinimumSize(QSize(120, 35));
        lE_FeedTimeOut->setMaximumSize(QSize(3434, 35));
        lE_FeedTimeOut->setFont(font1);
        lE_FeedTimeOut->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(lE_FeedTimeOut, 3, 1, 1, 1);

        lE_CapPickInterval = new UserLE(frame_4);
        lE_CapPickInterval->setObjectName(QString::fromUtf8("lE_CapPickInterval"));
        lE_CapPickInterval->setMinimumSize(QSize(120, 35));
        lE_CapPickInterval->setMaximumSize(QSize(3434, 35));
        lE_CapPickInterval->setFont(font1);
        lE_CapPickInterval->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(lE_CapPickInterval, 0, 1, 1, 1);

        lE_s_trg_stop1 = new UserLE(frame_4);
        lE_s_trg_stop1->setObjectName(QString::fromUtf8("lE_s_trg_stop1"));
        lE_s_trg_stop1->setMinimumSize(QSize(120, 35));
        lE_s_trg_stop1->setMaximumSize(QSize(3434, 35));
        lE_s_trg_stop1->setFont(font1);
        lE_s_trg_stop1->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(lE_s_trg_stop1, 1, 4, 1, 1);

        label_41 = new QLabel(frame_4);
        label_41->setObjectName(QString::fromUtf8("label_41"));
        sizePolicy.setHeightForWidth(label_41->sizePolicy().hasHeightForWidth());
        label_41->setSizePolicy(sizePolicy);
        label_41->setMinimumSize(QSize(0, 30));
        label_41->setMaximumSize(QSize(232323, 30));
        label_41->setFont(font1);
        label_41->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(label_41, 3, 3, 1, 1);

        label_26 = new QLabel(frame_4);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        sizePolicy.setHeightForWidth(label_26->sizePolicy().hasHeightForWidth());
        label_26->setSizePolicy(sizePolicy);
        label_26->setMinimumSize(QSize(80, 30));
        label_26->setMaximumSize(QSize(234234, 30));
        label_26->setFont(font1);
        label_26->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(label_26, 1, 0, 1, 1);

        lE_TireDelay = new UserLE(frame_4);
        lE_TireDelay->setObjectName(QString::fromUtf8("lE_TireDelay"));
        lE_TireDelay->setMinimumSize(QSize(120, 35));
        lE_TireDelay->setMaximumSize(QSize(3434, 35));
        lE_TireDelay->setFont(font1);
        lE_TireDelay->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(lE_TireDelay, 2, 4, 1, 1);

        label_32 = new QLabel(frame_4);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        sizePolicy.setHeightForWidth(label_32->sizePolicy().hasHeightForWidth());
        label_32->setSizePolicy(sizePolicy);
        label_32->setMinimumSize(QSize(0, 30));
        label_32->setMaximumSize(QSize(232323, 30));
        label_32->setFont(font1);
        label_32->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(label_32, 2, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer, 2, 2, 1, 1);

        lE_s_trg_stop0 = new UserLE(frame_4);
        lE_s_trg_stop0->setObjectName(QString::fromUtf8("lE_s_trg_stop0"));
        lE_s_trg_stop0->setMinimumSize(QSize(120, 35));
        lE_s_trg_stop0->setMaximumSize(QSize(3434, 35));
        lE_s_trg_stop0->setFont(font1);
        lE_s_trg_stop0->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(lE_s_trg_stop0, 1, 1, 1, 1);

        lE_CapBackInterval = new UserLE(frame_4);
        lE_CapBackInterval->setObjectName(QString::fromUtf8("lE_CapBackInterval"));
        lE_CapBackInterval->setMinimumSize(QSize(120, 35));
        lE_CapBackInterval->setMaximumSize(QSize(3434, 35));
        lE_CapBackInterval->setFont(font1);
        lE_CapBackInterval->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(lE_CapBackInterval, 0, 4, 1, 1);

        lE_ReadDelay = new UserLE(frame_4);
        lE_ReadDelay->setObjectName(QString::fromUtf8("lE_ReadDelay"));
        lE_ReadDelay->setMinimumSize(QSize(120, 35));
        lE_ReadDelay->setMaximumSize(QSize(3434, 35));
        lE_ReadDelay->setFont(font1);
        lE_ReadDelay->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(lE_ReadDelay, 3, 4, 1, 1);

        lE_TireWaitTime = new UserLE(frame_4);
        lE_TireWaitTime->setObjectName(QString::fromUtf8("lE_TireWaitTime"));
        lE_TireWaitTime->setMinimumSize(QSize(120, 35));
        lE_TireWaitTime->setMaximumSize(QSize(3434, 35));
        lE_TireWaitTime->setFont(font1);
        lE_TireWaitTime->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(lE_TireWaitTime, 2, 1, 1, 1);

        label_31 = new QLabel(frame_4);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        sizePolicy.setHeightForWidth(label_31->sizePolicy().hasHeightForWidth());
        label_31->setSizePolicy(sizePolicy);
        label_31->setMinimumSize(QSize(0, 30));
        label_31->setMaximumSize(QSize(234234, 30));
        label_31->setFont(font1);
        label_31->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(label_31, 1, 3, 1, 1);

        label_5 = new QLabel(frame_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setMinimumSize(QSize(0, 30));
        label_5->setMaximumSize(QSize(500, 30));
        label_5->setFont(font1);
        label_5->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(label_5, 0, 3, 1, 1);

        lE_StopSignalDelay = new UserLE(frame_4);
        lE_StopSignalDelay->setObjectName(QString::fromUtf8("lE_StopSignalDelay"));
        lE_StopSignalDelay->setMinimumSize(QSize(120, 35));
        lE_StopSignalDelay->setMaximumSize(QSize(3434, 35));
        lE_StopSignalDelay->setFont(font1);
        lE_StopSignalDelay->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(lE_StopSignalDelay, 4, 4, 1, 1);

        label_4 = new QLabel(frame_4);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setMinimumSize(QSize(0, 30));
        label_4->setMaximumSize(QSize(444444, 30));
        label_4->setFont(font1);
        label_4->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(label_4, 3, 0, 1, 1);

        label_42 = new QLabel(frame_4);
        label_42->setObjectName(QString::fromUtf8("label_42"));
        sizePolicy.setHeightForWidth(label_42->sizePolicy().hasHeightForWidth());
        label_42->setSizePolicy(sizePolicy);
        label_42->setMinimumSize(QSize(0, 30));
        label_42->setMaximumSize(QSize(232323, 30));
        label_42->setFont(font1);
        label_42->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(label_42, 2, 0, 1, 1);

        label_44 = new QLabel(frame_4);
        label_44->setObjectName(QString::fromUtf8("label_44"));
        sizePolicy.setHeightForWidth(label_44->sizePolicy().hasHeightForWidth());
        label_44->setSizePolicy(sizePolicy);
        label_44->setMinimumSize(QSize(0, 30));
        label_44->setMaximumSize(QSize(232323, 30));
        label_44->setFont(font1);
        label_44->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(label_44, 4, 3, 1, 1);


        verticalLayout->addWidget(frame_4);

        tabWidget_PLC->addTab(tab_8, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_12 = new QVBoxLayout(tab_2);
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        frame_6 = new QFrame(tab_2);
        frame_6->setObjectName(QString::fromUtf8("frame_6"));
        frame_6->setFont(font1);
        frame_6->setFrameShape(QFrame::Box);
        frame_6->setFrameShadow(QFrame::Sunken);
        frame_6->setLineWidth(2);
        gridLayout_2 = new QGridLayout(frame_6);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_9 = new QLabel(frame_6);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setMinimumSize(QSize(0, 0));
        label_9->setMaximumSize(QSize(1572323, 232323));
        label_9->setFont(font1);

        gridLayout_2->addWidget(label_9, 3, 3, 1, 1);

        lE_InterUnderLoad = new QLineEdit(frame_6);
        lE_InterUnderLoad->setObjectName(QString::fromUtf8("lE_InterUnderLoad"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lE_InterUnderLoad->sizePolicy().hasHeightForWidth());
        lE_InterUnderLoad->setSizePolicy(sizePolicy1);
        lE_InterUnderLoad->setMinimumSize(QSize(0, 42));
        lE_InterUnderLoad->setMaximumSize(QSize(100888, 42));
        lE_InterUnderLoad->setFont(font1);

        gridLayout_2->addWidget(lE_InterUnderLoad, 2, 1, 1, 1);

        lE_TOverload = new QLineEdit(frame_6);
        lE_TOverload->setObjectName(QString::fromUtf8("lE_TOverload"));
        sizePolicy1.setHeightForWidth(lE_TOverload->sizePolicy().hasHeightForWidth());
        lE_TOverload->setSizePolicy(sizePolicy1);
        lE_TOverload->setMinimumSize(QSize(0, 42));
        lE_TOverload->setMaximumSize(QSize(100888, 42));
        lE_TOverload->setFont(font1);

        gridLayout_2->addWidget(lE_TOverload, 3, 1, 1, 1);

        label_53 = new QLabel(frame_6);
        label_53->setObjectName(QString::fromUtf8("label_53"));
        label_53->setMinimumSize(QSize(0, 0));
        label_53->setMaximumSize(QSize(1572323, 232323));
        label_53->setFont(font1);

        gridLayout_2->addWidget(label_53, 3, 0, 1, 1);

        lE_GroupSet = new QLineEdit(frame_6);
        lE_GroupSet->setObjectName(QString::fromUtf8("lE_GroupSet"));
        lE_GroupSet->setFont(font1);

        gridLayout_2->addWidget(lE_GroupSet, 1, 4, 1, 1);

        label_54 = new QLabel(frame_6);
        label_54->setObjectName(QString::fromUtf8("label_54"));
        label_54->setMinimumSize(QSize(0, 0));
        label_54->setMaximumSize(QSize(1572323, 232323));
        label_54->setFont(font1);

        gridLayout_2->addWidget(label_54, 4, 0, 1, 1);

        label_14 = new QLabel(frame_6);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setMinimumSize(QSize(0, 0));
        label_14->setMaximumSize(QSize(1572323, 232323));
        label_14->setFont(font1);

        gridLayout_2->addWidget(label_14, 0, 0, 1, 1);

        label_13 = new QLabel(frame_6);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setMinimumSize(QSize(0, 0));
        label_13->setMaximumSize(QSize(1572323, 232323));
        label_13->setFont(font1);

        gridLayout_2->addWidget(label_13, 1, 0, 1, 1);

        lE_TestInterval = new QLineEdit(frame_6);
        lE_TestInterval->setObjectName(QString::fromUtf8("lE_TestInterval"));
        sizePolicy1.setHeightForWidth(lE_TestInterval->sizePolicy().hasHeightForWidth());
        lE_TestInterval->setSizePolicy(sizePolicy1);
        lE_TestInterval->setMinimumSize(QSize(0, 42));
        lE_TestInterval->setMaximumSize(QSize(16777215, 42));
        lE_TestInterval->setFont(font1);

        gridLayout_2->addWidget(lE_TestInterval, 2, 4, 1, 1);

        label_55 = new QLabel(frame_6);
        label_55->setObjectName(QString::fromUtf8("label_55"));
        label_55->setFont(font1);

        gridLayout_2->addWidget(label_55, 0, 3, 1, 1);

        lE_TDemand = new QLineEdit(frame_6);
        lE_TDemand->setObjectName(QString::fromUtf8("lE_TDemand"));
        sizePolicy1.setHeightForWidth(lE_TDemand->sizePolicy().hasHeightForWidth());
        lE_TDemand->setSizePolicy(sizePolicy1);
        lE_TDemand->setMinimumSize(QSize(0, 42));
        lE_TDemand->setMaximumSize(QSize(100888, 42));
        lE_TDemand->setFont(font1);

        gridLayout_2->addWidget(lE_TDemand, 0, 1, 1, 1);

        label_52 = new QLabel(frame_6);
        label_52->setObjectName(QString::fromUtf8("label_52"));
        label_52->setFont(font1);

        gridLayout_2->addWidget(label_52, 1, 3, 1, 1);

        label_12 = new QLabel(frame_6);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setMinimumSize(QSize(0, 0));
        label_12->setMaximumSize(QSize(1572323, 232323));
        label_12->setFont(font1);

        gridLayout_2->addWidget(label_12, 2, 0, 1, 1);

        label_50 = new QLabel(frame_6);
        label_50->setObjectName(QString::fromUtf8("label_50"));
        label_50->setMinimumSize(QSize(0, 0));
        label_50->setMaximumSize(QSize(1572323, 232323));
        label_50->setFont(font1);

        gridLayout_2->addWidget(label_50, 2, 3, 1, 1);

        cB_TireMode = new QComboBox(frame_6);
        cB_TireMode->addItem(QString());
        cB_TireMode->addItem(QString());
        cB_TireMode->setObjectName(QString::fromUtf8("cB_TireMode"));
        cB_TireMode->setMinimumSize(QSize(165, 0));
        cB_TireMode->setFont(font1);

        gridLayout_2->addWidget(cB_TireMode, 0, 4, 1, 1);

        lE_GroupNo = new QLineEdit(frame_6);
        lE_GroupNo->setObjectName(QString::fromUtf8("lE_GroupNo"));
        lE_GroupNo->setEnabled(false);
        sizePolicy1.setHeightForWidth(lE_GroupNo->sizePolicy().hasHeightForWidth());
        lE_GroupNo->setSizePolicy(sizePolicy1);
        lE_GroupNo->setMinimumSize(QSize(0, 42));
        lE_GroupNo->setMaximumSize(QSize(16777215, 42));
        lE_GroupNo->setFont(font1);

        gridLayout_2->addWidget(lE_GroupNo, 4, 4, 1, 1);

        lE_InterOverLoad = new QLineEdit(frame_6);
        lE_InterOverLoad->setObjectName(QString::fromUtf8("lE_InterOverLoad"));
        sizePolicy1.setHeightForWidth(lE_InterOverLoad->sizePolicy().hasHeightForWidth());
        lE_InterOverLoad->setSizePolicy(sizePolicy1);
        lE_InterOverLoad->setMinimumSize(QSize(0, 42));
        lE_InterOverLoad->setMaximumSize(QSize(100888, 42));
        lE_InterOverLoad->setFont(font1);

        gridLayout_2->addWidget(lE_InterOverLoad, 1, 1, 1, 1);

        lE_TUnderload = new QLineEdit(frame_6);
        lE_TUnderload->setObjectName(QString::fromUtf8("lE_TUnderload"));
        sizePolicy1.setHeightForWidth(lE_TUnderload->sizePolicy().hasHeightForWidth());
        lE_TUnderload->setSizePolicy(sizePolicy1);
        lE_TUnderload->setMinimumSize(QSize(0, 42));
        lE_TUnderload->setMaximumSize(QSize(100888, 42));
        lE_TUnderload->setFont(font1);

        gridLayout_2->addWidget(lE_TUnderload, 4, 1, 1, 1);

        label_79 = new QLabel(frame_6);
        label_79->setObjectName(QString::fromUtf8("label_79"));
        label_79->setMinimumSize(QSize(0, 0));
        label_79->setMaximumSize(QSize(1572323, 232323));
        label_79->setFont(font1);

        gridLayout_2->addWidget(label_79, 4, 3, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 2, 2, 1, 1);

        lE_SysOveride_2 = new QLineEdit(frame_6);
        lE_SysOveride_2->setObjectName(QString::fromUtf8("lE_SysOveride_2"));
        lE_SysOveride_2->setEnabled(false);
        sizePolicy1.setHeightForWidth(lE_SysOveride_2->sizePolicy().hasHeightForWidth());
        lE_SysOveride_2->setSizePolicy(sizePolicy1);
        lE_SysOveride_2->setMinimumSize(QSize(0, 42));
        lE_SysOveride_2->setMaximumSize(QSize(16777215, 42));
        lE_SysOveride_2->setFont(font1);

        gridLayout_2->addWidget(lE_SysOveride_2, 3, 4, 1, 1);


        verticalLayout_12->addWidget(frame_6);

        tabWidget_PLC->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        verticalLayout_4 = new QVBoxLayout(tab_3);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_6);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        groupBox_4 = new QGroupBox(tab_3);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setFlat(false);
        groupBox_4->setCheckable(false);
        gridLayout_3 = new QGridLayout(groupBox_4);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_21 = new QLabel(groupBox_4);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        gridLayout_3->addWidget(label_21, 0, 0, 1, 1);

        lE_AxisFeedStep = new QLineEdit(groupBox_4);
        lE_AxisFeedStep->setObjectName(QString::fromUtf8("lE_AxisFeedStep"));
        lE_AxisFeedStep->setEnabled(false);
        lE_AxisFeedStep->setMinimumSize(QSize(150, 0));
        lE_AxisFeedStep->setMaximumSize(QSize(150, 16777215));

        gridLayout_3->addWidget(lE_AxisFeedStep, 0, 1, 1, 1);

        label_19 = new QLabel(groupBox_4);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout_3->addWidget(label_19, 1, 0, 1, 1);

        lE_AxisFeedErrorNo = new QLineEdit(groupBox_4);
        lE_AxisFeedErrorNo->setObjectName(QString::fromUtf8("lE_AxisFeedErrorNo"));
        lE_AxisFeedErrorNo->setEnabled(false);
        lE_AxisFeedErrorNo->setMinimumSize(QSize(150, 0));
        lE_AxisFeedErrorNo->setMaximumSize(QSize(150, 16777215));

        gridLayout_3->addWidget(lE_AxisFeedErrorNo, 1, 1, 1, 1);

        label_22 = new QLabel(groupBox_4);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        gridLayout_3->addWidget(label_22, 2, 0, 1, 1);

        lE_AxisFeedRelMovDistance = new QLineEdit(groupBox_4);
        lE_AxisFeedRelMovDistance->setObjectName(QString::fromUtf8("lE_AxisFeedRelMovDistance"));
        lE_AxisFeedRelMovDistance->setEnabled(false);
        lE_AxisFeedRelMovDistance->setMinimumSize(QSize(150, 0));
        lE_AxisFeedRelMovDistance->setMaximumSize(QSize(150, 16777215));

        gridLayout_3->addWidget(lE_AxisFeedRelMovDistance, 2, 1, 1, 1);


        horizontalLayout_4->addWidget(groupBox_4);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        groupBox_6 = new QGroupBox(tab_3);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        gridLayout_9 = new QGridLayout(groupBox_6);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        label_24 = new QLabel(groupBox_6);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        gridLayout_9->addWidget(label_24, 0, 0, 1, 1);

        lE_AxisSwingStep = new QLineEdit(groupBox_6);
        lE_AxisSwingStep->setObjectName(QString::fromUtf8("lE_AxisSwingStep"));
        lE_AxisSwingStep->setEnabled(false);
        lE_AxisSwingStep->setMinimumSize(QSize(150, 0));
        lE_AxisSwingStep->setMaximumSize(QSize(150, 16777215));

        gridLayout_9->addWidget(lE_AxisSwingStep, 0, 1, 1, 1);

        label_27 = new QLabel(groupBox_6);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        gridLayout_9->addWidget(label_27, 1, 0, 1, 1);

        lE_AxisSwingErrorNo = new QLineEdit(groupBox_6);
        lE_AxisSwingErrorNo->setObjectName(QString::fromUtf8("lE_AxisSwingErrorNo"));
        lE_AxisSwingErrorNo->setEnabled(false);
        lE_AxisSwingErrorNo->setMinimumSize(QSize(150, 0));
        lE_AxisSwingErrorNo->setMaximumSize(QSize(150, 16777215));

        gridLayout_9->addWidget(lE_AxisSwingErrorNo, 1, 1, 1, 1);

        label_28 = new QLabel(groupBox_6);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        gridLayout_9->addWidget(label_28, 2, 0, 1, 1);

        lE_AxisSwingRelMovDistance = new QLineEdit(groupBox_6);
        lE_AxisSwingRelMovDistance->setObjectName(QString::fromUtf8("lE_AxisSwingRelMovDistance"));
        lE_AxisSwingRelMovDistance->setEnabled(false);
        lE_AxisSwingRelMovDistance->setMinimumSize(QSize(150, 0));
        lE_AxisSwingRelMovDistance->setMaximumSize(QSize(150, 16777215));

        gridLayout_9->addWidget(lE_AxisSwingRelMovDistance, 2, 1, 1, 1);


        horizontalLayout_4->addWidget(groupBox_6);


        verticalLayout_4->addLayout(horizontalLayout_4);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_8);

        frame_2 = new QFrame(tab_3);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::Box);
        frame_2->setFrameShadow(QFrame::Sunken);
        frame_2->setLineWidth(2);
        verticalLayout_3 = new QVBoxLayout(frame_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_3 = new QLabel(frame_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 1, 1, 1, 1);

        lE_MachineStep = new QLineEdit(frame_2);
        lE_MachineStep->setObjectName(QString::fromUtf8("lE_MachineStep"));
        lE_MachineStep->setEnabled(false);
        lE_MachineStep->setMinimumSize(QSize(150, 0));
        lE_MachineStep->setMaximumSize(QSize(300, 16777215));

        gridLayout->addWidget(lE_MachineStep, 2, 3, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 2, 4, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 1, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 2, 1, 1);

        lE_Alarm16 = new QLineEdit(frame_2);
        lE_Alarm16->setObjectName(QString::fromUtf8("lE_Alarm16"));
        lE_Alarm16->setEnabled(false);
        lE_Alarm16->setMinimumSize(QSize(150, 0));
        lE_Alarm16->setMaximumSize(QSize(300, 16777215));

        gridLayout->addWidget(lE_Alarm16, 1, 3, 1, 1);

        lE_AlarmStatus = new QLineEdit(frame_2);
        lE_AlarmStatus->setObjectName(QString::fromUtf8("lE_AlarmStatus"));
        lE_AlarmStatus->setEnabled(false);
        lE_AlarmStatus->setMinimumSize(QSize(150, 0));
        lE_AlarmStatus->setMaximumSize(QSize(300, 16777215));

        gridLayout->addWidget(lE_AlarmStatus, 0, 3, 1, 1);

        label_33 = new QLabel(frame_2);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label_33, 3, 1, 1, 1);

        label_29 = new QLabel(frame_2);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label_29, 2, 1, 1, 1);

        lE_TimeInterval = new QLineEdit(frame_2);
        lE_TimeInterval->setObjectName(QString::fromUtf8("lE_TimeInterval"));
        lE_TimeInterval->setEnabled(false);
        lE_TimeInterval->setMinimumSize(QSize(150, 0));
        lE_TimeInterval->setMaximumSize(QSize(300, 16777215));

        gridLayout->addWidget(lE_TimeInterval, 3, 3, 1, 1);

        label_20 = new QLabel(frame_2);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label_20, 0, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout);


        verticalLayout_4->addWidget(frame_2);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_7);

        tabWidget_PLC->addTab(tab_3, QString());
        pb_cmdParaSave = new QPushButton(QtPLCDialogClass);
        pb_cmdParaSave->setObjectName(QString::fromUtf8("pb_cmdParaSave"));
        pb_cmdParaSave->setGeometry(QRect(750, 800, 90, 50));
        pb_cmdParaSave->setMinimumSize(QSize(90, 50));
        pb_cmdParaSave->setMaximumSize(QSize(90, 50));
        pb_cmdParaSave->setCheckable(false);
        frame_5 = new QFrame(QtPLCDialogClass);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setGeometry(QRect(310, 770, 847, 182));
        frame_5->setMinimumSize(QSize(847, 182));
        frame_5->setMaximumSize(QSize(847, 182));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\350\277\267\344\275\240\347\256\200\350\217\261\345\277\203"));
        font2.setPointSize(24);
        frame_5->setFont(font2);
        frame_5->setFrameShape(QFrame::Box);
        frame_5->setFrameShadow(QFrame::Sunken);
        frame_5->setLineWidth(3);
        gridLayout_4 = new QGridLayout(frame_5);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        pB_cmdCounterZero_2 = new QPushButton(frame_5);
        pB_cmdCounterZero_2->setObjectName(QString::fromUtf8("pB_cmdCounterZero_2"));
        sizePolicy.setHeightForWidth(pB_cmdCounterZero_2->sizePolicy().hasHeightForWidth());
        pB_cmdCounterZero_2->setSizePolicy(sizePolicy);
        pB_cmdCounterZero_2->setMinimumSize(QSize(0, 80));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\350\277\267\344\275\240\347\256\200\350\217\261\345\277\203"));
        font3.setPointSize(36);
        pB_cmdCounterZero_2->setFont(font3);

        gridLayout_4->addWidget(pB_cmdCounterZero_2, 0, 0, 1, 1);

        pB_cmdCounterZero_3 = new QPushButton(frame_5);
        pB_cmdCounterZero_3->setObjectName(QString::fromUtf8("pB_cmdCounterZero_3"));
        sizePolicy.setHeightForWidth(pB_cmdCounterZero_3->sizePolicy().hasHeightForWidth());
        pB_cmdCounterZero_3->setSizePolicy(sizePolicy);
        pB_cmdCounterZero_3->setMinimumSize(QSize(0, 80));
        pB_cmdCounterZero_3->setFont(font3);

        gridLayout_4->addWidget(pB_cmdCounterZero_3, 0, 1, 1, 1);

        pB_cmdCounterZero_5 = new QPushButton(frame_5);
        pB_cmdCounterZero_5->setObjectName(QString::fromUtf8("pB_cmdCounterZero_5"));
        sizePolicy.setHeightForWidth(pB_cmdCounterZero_5->sizePolicy().hasHeightForWidth());
        pB_cmdCounterZero_5->setSizePolicy(sizePolicy);
        pB_cmdCounterZero_5->setMinimumSize(QSize(0, 80));
        pB_cmdCounterZero_5->setFont(font3);

        gridLayout_4->addWidget(pB_cmdCounterZero_5, 1, 0, 1, 1);

        pB_cmdCounterZero_4 = new QPushButton(frame_5);
        pB_cmdCounterZero_4->setObjectName(QString::fromUtf8("pB_cmdCounterZero_4"));
        sizePolicy.setHeightForWidth(pB_cmdCounterZero_4->sizePolicy().hasHeightForWidth());
        pB_cmdCounterZero_4->setSizePolicy(sizePolicy);
        pB_cmdCounterZero_4->setMinimumSize(QSize(0, 80));
        pB_cmdCounterZero_4->setFont(font3);

        gridLayout_4->addWidget(pB_cmdCounterZero_4, 1, 1, 1, 1);

        frame = new QFrame(QtPLCDialogClass);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(1250, 10, 847, 755));
        frame->setMinimumSize(QSize(847, 755));
        frame->setMaximumSize(QSize(847, 755));
        QFont font4;
        font4.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font4.setPointSize(20);
        font4.setBold(true);
        font4.setWeight(75);
        frame->setFont(font4);
        frame->setAutoFillBackground(true);
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Sunken);
        frame->setLineWidth(3);
        verticalLayout_6 = new QVBoxLayout(frame);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        groupBox_10 = new QGroupBox(frame);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        QFont font5;
        font5.setFamily(QString::fromUtf8("System"));
        groupBox_10->setFont(font5);
        groupBox_10->setStyleSheet(QString::fromUtf8(""));
        groupBox_10->setFlat(false);
        groupBox_10->setCheckable(false);
        frame_7 = new QFrame(groupBox_10);
        frame_7->setObjectName(QString::fromUtf8("frame_7"));
        frame_7->setGeometry(QRect(10, 37, 797, 521));
        QFont font6;
        font6.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font6.setBold(false);
        font6.setWeight(50);
        frame_7->setFont(font6);
        frame_7->setFrameShape(QFrame::Box);
        frame_7->setFrameShadow(QFrame::Sunken);
        frame_7->setLineWidth(3);
        gridLayout_10 = new QGridLayout(frame_7);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        frame_15 = new QFrame(frame_7);
        frame_15->setObjectName(QString::fromUtf8("frame_15"));
        frame_15->setStyleSheet(QString::fromUtf8("background-color: rgb(235, 235, 235);"));
        frame_15->setFrameShape(QFrame::Panel);
        frame_15->setFrameShadow(QFrame::Raised);
        frame_15->setLineWidth(3);
        verticalLayout_19 = new QVBoxLayout(frame_15);
        verticalLayout_19->setSpacing(6);
        verticalLayout_19->setContentsMargins(11, 11, 11, 11);
        verticalLayout_19->setObjectName(QString::fromUtf8("verticalLayout_19"));
        verticalLayout_19->setContentsMargins(0, 0, 0, 0);
        lE_ScaleResult = new QLineEdit(frame_15);
        lE_ScaleResult->setObjectName(QString::fromUtf8("lE_ScaleResult"));
        lE_ScaleResult->setEnabled(false);
        sizePolicy1.setHeightForWidth(lE_ScaleResult->sizePolicy().hasHeightForWidth());
        lE_ScaleResult->setSizePolicy(sizePolicy1);
        QFont font7;
        font7.setFamily(QString::fromUtf8("Arial Black"));
        font7.setPointSize(20);
        font7.setBold(true);
        font7.setWeight(75);
        lE_ScaleResult->setFont(font7);
        lE_ScaleResult->setStyleSheet(QString::fromUtf8(""));
        lE_ScaleResult->setFrame(false);

        verticalLayout_19->addWidget(lE_ScaleResult);


        gridLayout_10->addWidget(frame_15, 7, 2, 1, 1);

        horizontalSpacer_19 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_19, 7, 5, 1, 1);

        label_10 = new QLabel(frame_7);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setMinimumSize(QSize(140, 35));
        label_10->setMaximumSize(QSize(140, 35));
        QFont font8;
        font8.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font8.setBold(true);
        font8.setWeight(75);
        label_10->setFont(font8);

        gridLayout_10->addWidget(label_10, 1, 0, 1, 1);

        frame_8 = new QFrame(frame_7);
        frame_8->setObjectName(QString::fromUtf8("frame_8"));
        frame_8->setStyleSheet(QString::fromUtf8("background-color: rgb(235, 235, 235);"));
        frame_8->setFrameShape(QFrame::Panel);
        frame_8->setFrameShadow(QFrame::Raised);
        frame_8->setLineWidth(3);
        verticalLayout_13 = new QVBoxLayout(frame_8);
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        verticalLayout_13->setContentsMargins(0, 0, 0, 0);
        cB_ScaleStableState = new QComboBox(frame_8);
        cB_ScaleStableState->addItem(QString());
        cB_ScaleStableState->addItem(QString());
        cB_ScaleStableState->addItem(QString());
        cB_ScaleStableState->addItem(QString());
        cB_ScaleStableState->setObjectName(QString::fromUtf8("cB_ScaleStableState"));
        cB_ScaleStableState->setEnabled(false);
        QFont font9;
        font9.setFamily(QString::fromUtf8("\345\271\274\345\234\206"));
        font9.setPointSize(19);
        font9.setBold(true);
        font9.setWeight(75);
        cB_ScaleStableState->setFont(font9);
        cB_ScaleStableState->setStyleSheet(QString::fromUtf8(""));
        cB_ScaleStableState->setFrame(false);

        verticalLayout_13->addWidget(cB_ScaleStableState);


        gridLayout_10->addWidget(frame_8, 10, 2, 1, 1);

        frame_14 = new QFrame(frame_7);
        frame_14->setObjectName(QString::fromUtf8("frame_14"));
        frame_14->setStyleSheet(QString::fromUtf8("background-color: rgb(235, 235, 235);"));
        frame_14->setFrameShape(QFrame::Panel);
        frame_14->setFrameShadow(QFrame::Raised);
        frame_14->setLineWidth(3);
        verticalLayout_17 = new QVBoxLayout(frame_14);
        verticalLayout_17->setSpacing(6);
        verticalLayout_17->setContentsMargins(11, 11, 11, 11);
        verticalLayout_17->setObjectName(QString::fromUtf8("verticalLayout_17"));
        verticalLayout_17->setContentsMargins(0, 0, 0, 0);
        lE_ProdCount = new QLineEdit(frame_14);
        lE_ProdCount->setObjectName(QString::fromUtf8("lE_ProdCount"));
        lE_ProdCount->setEnabled(false);
        sizePolicy1.setHeightForWidth(lE_ProdCount->sizePolicy().hasHeightForWidth());
        lE_ProdCount->setSizePolicy(sizePolicy1);
        lE_ProdCount->setFont(font7);
        lE_ProdCount->setStyleSheet(QString::fromUtf8(""));
        lE_ProdCount->setFrame(false);

        verticalLayout_17->addWidget(lE_ProdCount);


        gridLayout_10->addWidget(frame_14, 3, 2, 1, 1);

        verticalSpacer_13 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_10->addItem(verticalSpacer_13, 6, 2, 1, 1);

        verticalSpacer_15 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_10->addItem(verticalSpacer_15, 2, 2, 1, 1);

        label_43 = new QLabel(frame_7);
        label_43->setObjectName(QString::fromUtf8("label_43"));
        label_43->setMinimumSize(QSize(140, 35));
        label_43->setMaximumSize(QSize(140, 35));
        label_43->setFont(font8);

        gridLayout_10->addWidget(label_43, 7, 4, 1, 1);

        horizontalSpacer_18 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_18, 7, 1, 1, 1);

        label_39 = new QLabel(frame_7);
        label_39->setObjectName(QString::fromUtf8("label_39"));
        label_39->setMinimumSize(QSize(140, 35));
        label_39->setMaximumSize(QSize(140, 35));
        label_39->setFont(font8);

        gridLayout_10->addWidget(label_39, 3, 0, 1, 1);

        frame_16 = new QFrame(frame_7);
        frame_16->setObjectName(QString::fromUtf8("frame_16"));
        frame_16->setStyleSheet(QString::fromUtf8("background-color: rgb(235, 235, 235);"));
        frame_16->setFrameShape(QFrame::Panel);
        frame_16->setFrameShadow(QFrame::Raised);
        frame_16->setLineWidth(3);
        verticalLayout_18 = new QVBoxLayout(frame_16);
        verticalLayout_18->setSpacing(6);
        verticalLayout_18->setContentsMargins(11, 11, 11, 11);
        verticalLayout_18->setObjectName(QString::fromUtf8("verticalLayout_18"));
        verticalLayout_18->setContentsMargins(0, 0, 0, 0);
        lE_TOCount = new QLineEdit(frame_16);
        lE_TOCount->setObjectName(QString::fromUtf8("lE_TOCount"));
        lE_TOCount->setEnabled(false);
        sizePolicy1.setHeightForWidth(lE_TOCount->sizePolicy().hasHeightForWidth());
        lE_TOCount->setSizePolicy(sizePolicy1);
        lE_TOCount->setFont(font7);
        lE_TOCount->setStyleSheet(QString::fromUtf8(""));
        lE_TOCount->setFrame(false);

        verticalLayout_18->addWidget(lE_TOCount);


        gridLayout_10->addWidget(frame_16, 5, 2, 1, 1);

        label_48 = new QLabel(frame_7);
        label_48->setObjectName(QString::fromUtf8("label_48"));
        label_48->setMinimumSize(QSize(140, 35));
        label_48->setMaximumSize(QSize(140, 35));
        label_48->setFont(font8);

        gridLayout_10->addWidget(label_48, 5, 4, 1, 1);

        frame_13 = new QFrame(frame_7);
        frame_13->setObjectName(QString::fromUtf8("frame_13"));
        frame_13->setStyleSheet(QString::fromUtf8("background-color: rgb(235, 235, 235);"));
        frame_13->setFrameShape(QFrame::Panel);
        frame_13->setFrameShadow(QFrame::Raised);
        frame_13->setLineWidth(3);
        verticalLayout_16 = new QVBoxLayout(frame_13);
        verticalLayout_16->setSpacing(6);
        verticalLayout_16->setContentsMargins(11, 11, 11, 11);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        verticalLayout_16->setContentsMargins(0, 0, 0, 0);
        lE_PassCount = new QLineEdit(frame_13);
        lE_PassCount->setObjectName(QString::fromUtf8("lE_PassCount"));
        lE_PassCount->setEnabled(false);
        sizePolicy1.setHeightForWidth(lE_PassCount->sizePolicy().hasHeightForWidth());
        lE_PassCount->setSizePolicy(sizePolicy1);
        lE_PassCount->setFont(font7);
        lE_PassCount->setStyleSheet(QString::fromUtf8(""));
        lE_PassCount->setFrame(false);

        verticalLayout_16->addWidget(lE_PassCount);


        gridLayout_10->addWidget(frame_13, 1, 2, 1, 1);

        frame_3 = new QFrame(frame_7);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setAutoFillBackground(false);
        frame_3->setStyleSheet(QString::fromUtf8("background-color: rgb(235, 235, 235);"));
        frame_3->setFrameShape(QFrame::Panel);
        frame_3->setFrameShadow(QFrame::Raised);
        frame_3->setLineWidth(3);
        verticalLayout_8 = new QVBoxLayout(frame_3);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        lE_Finished = new QLineEdit(frame_3);
        lE_Finished->setObjectName(QString::fromUtf8("lE_Finished"));
        lE_Finished->setEnabled(false);
        sizePolicy1.setHeightForWidth(lE_Finished->sizePolicy().hasHeightForWidth());
        lE_Finished->setSizePolicy(sizePolicy1);
        lE_Finished->setFont(font7);
        lE_Finished->setAutoFillBackground(false);
        lE_Finished->setStyleSheet(QString::fromUtf8(""));
        lE_Finished->setFrame(false);

        verticalLayout_8->addWidget(lE_Finished);


        gridLayout_10->addWidget(frame_3, 13, 2, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_10, 7, 3, 1, 1);

        label_49 = new QLabel(frame_7);
        label_49->setObjectName(QString::fromUtf8("label_49"));
        label_49->setMinimumSize(QSize(140, 35));
        label_49->setMaximumSize(QSize(140, 35));
        label_49->setFont(font8);

        gridLayout_10->addWidget(label_49, 5, 0, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_10->addItem(verticalSpacer_5, 0, 2, 1, 1);

        verticalSpacer_14 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_10->addItem(verticalSpacer_14, 11, 2, 1, 1);

        label_18 = new QLabel(frame_7);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setMinimumSize(QSize(140, 35));
        label_18->setMaximumSize(QSize(140, 35));
        label_18->setFont(font8);

        gridLayout_10->addWidget(label_18, 13, 4, 1, 1);

        verticalSpacer_17 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_10->addItem(verticalSpacer_17, 8, 2, 1, 1);

        label_45 = new QLabel(frame_7);
        label_45->setObjectName(QString::fromUtf8("label_45"));
        label_45->setMinimumSize(QSize(140, 35));
        label_45->setMaximumSize(QSize(140, 35));
        label_45->setFont(font8);

        gridLayout_10->addWidget(label_45, 10, 0, 1, 1);

        label_15 = new QLabel(frame_7);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setMinimumSize(QSize(140, 35));
        label_15->setMaximumSize(QSize(140, 35));
        label_15->setFont(font8);

        gridLayout_10->addWidget(label_15, 13, 0, 1, 1);

        verticalSpacer_12 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_10->addItem(verticalSpacer_12, 15, 2, 1, 1);

        verticalSpacer_16 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_10->addItem(verticalSpacer_16, 4, 2, 1, 1);

        label_16 = new QLabel(frame_7);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setMinimumSize(QSize(140, 35));
        label_16->setMaximumSize(QSize(140, 35));
        label_16->setFont(font8);

        gridLayout_10->addWidget(label_16, 7, 0, 1, 1);

        label_17 = new QLabel(frame_7);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setMinimumSize(QSize(140, 35));
        label_17->setMaximumSize(QSize(140, 35));
        label_17->setFont(font8);

        gridLayout_10->addWidget(label_17, 1, 4, 1, 1);

        frame_12 = new QFrame(frame_7);
        frame_12->setObjectName(QString::fromUtf8("frame_12"));
        frame_12->setStyleSheet(QString::fromUtf8("background-color: rgb(235, 235, 235);"));
        frame_12->setFrameShape(QFrame::Panel);
        frame_12->setFrameShadow(QFrame::Raised);
        frame_12->setLineWidth(3);
        verticalLayout_20 = new QVBoxLayout(frame_12);
        verticalLayout_20->setSpacing(6);
        verticalLayout_20->setContentsMargins(11, 11, 11, 11);
        verticalLayout_20->setObjectName(QString::fromUtf8("verticalLayout_20"));
        verticalLayout_20->setContentsMargins(0, 0, 0, 0);
        lE_RejectCount = new QLineEdit(frame_12);
        lE_RejectCount->setObjectName(QString::fromUtf8("lE_RejectCount"));
        lE_RejectCount->setEnabled(false);
        sizePolicy1.setHeightForWidth(lE_RejectCount->sizePolicy().hasHeightForWidth());
        lE_RejectCount->setSizePolicy(sizePolicy1);
        lE_RejectCount->setFont(font7);
        lE_RejectCount->setStyleSheet(QString::fromUtf8(""));
        lE_RejectCount->setFrame(false);
        lE_RejectCount->setEchoMode(QLineEdit::Normal);

        verticalLayout_20->addWidget(lE_RejectCount);


        gridLayout_10->addWidget(frame_12, 1, 6, 1, 1);

        frame_17 = new QFrame(frame_7);
        frame_17->setObjectName(QString::fromUtf8("frame_17"));
        frame_17->setStyleSheet(QString::fromUtf8("background-color: rgb(235, 235, 235);"));
        frame_17->setFrameShape(QFrame::Panel);
        frame_17->setFrameShadow(QFrame::Raised);
        frame_17->setLineWidth(3);
        verticalLayout_21 = new QVBoxLayout(frame_17);
        verticalLayout_21->setSpacing(6);
        verticalLayout_21->setContentsMargins(11, 11, 11, 11);
        verticalLayout_21->setObjectName(QString::fromUtf8("verticalLayout_21"));
        verticalLayout_21->setContentsMargins(0, 0, 0, 0);
        lE_TUCount = new QLineEdit(frame_17);
        lE_TUCount->setObjectName(QString::fromUtf8("lE_TUCount"));
        lE_TUCount->setEnabled(false);
        sizePolicy1.setHeightForWidth(lE_TUCount->sizePolicy().hasHeightForWidth());
        lE_TUCount->setSizePolicy(sizePolicy1);
        lE_TUCount->setFont(font7);
        lE_TUCount->setStyleSheet(QString::fromUtf8(""));
        lE_TUCount->setFrame(false);

        verticalLayout_21->addWidget(lE_TUCount);


        gridLayout_10->addWidget(frame_17, 5, 6, 1, 1);

        frame_18 = new QFrame(frame_7);
        frame_18->setObjectName(QString::fromUtf8("frame_18"));
        frame_18->setStyleSheet(QString::fromUtf8("background-color: rgb(235, 235, 235);"));
        frame_18->setFrameShape(QFrame::Panel);
        frame_18->setFrameShadow(QFrame::Raised);
        frame_18->setLineWidth(3);
        verticalLayout_22 = new QVBoxLayout(frame_18);
        verticalLayout_22->setSpacing(6);
        verticalLayout_22->setContentsMargins(11, 11, 11, 11);
        verticalLayout_22->setObjectName(QString::fromUtf8("verticalLayout_22"));
        verticalLayout_22->setContentsMargins(0, 0, 0, 0);
        lE_Weight = new QLineEdit(frame_18);
        lE_Weight->setObjectName(QString::fromUtf8("lE_Weight"));
        lE_Weight->setEnabled(false);
        sizePolicy1.setHeightForWidth(lE_Weight->sizePolicy().hasHeightForWidth());
        lE_Weight->setSizePolicy(sizePolicy1);
        lE_Weight->setFont(font7);
        lE_Weight->setStyleSheet(QString::fromUtf8(""));
        lE_Weight->setFrame(false);

        verticalLayout_22->addWidget(lE_Weight);


        gridLayout_10->addWidget(frame_18, 7, 6, 1, 1);

        frame_19 = new QFrame(frame_7);
        frame_19->setObjectName(QString::fromUtf8("frame_19"));
        frame_19->setStyleSheet(QString::fromUtf8("background-color: rgb(235, 235, 235);"));
        frame_19->setFrameShape(QFrame::Panel);
        frame_19->setFrameShadow(QFrame::Raised);
        frame_19->setLineWidth(3);
        verticalLayout_23 = new QVBoxLayout(frame_19);
        verticalLayout_23->setSpacing(6);
        verticalLayout_23->setContentsMargins(11, 11, 11, 11);
        verticalLayout_23->setObjectName(QString::fromUtf8("verticalLayout_23"));
        verticalLayout_23->setContentsMargins(0, 0, 0, 0);
        lE_GroupIndex = new QLineEdit(frame_19);
        lE_GroupIndex->setObjectName(QString::fromUtf8("lE_GroupIndex"));
        lE_GroupIndex->setEnabled(false);
        sizePolicy1.setHeightForWidth(lE_GroupIndex->sizePolicy().hasHeightForWidth());
        lE_GroupIndex->setSizePolicy(sizePolicy1);
        lE_GroupIndex->setFont(font7);
        lE_GroupIndex->setStyleSheet(QString::fromUtf8(""));
        lE_GroupIndex->setFrame(false);

        verticalLayout_23->addWidget(lE_GroupIndex);


        gridLayout_10->addWidget(frame_19, 13, 6, 1, 1);

        frame_9 = new QFrame(groupBox_10);
        frame_9->setObjectName(QString::fromUtf8("frame_9"));
        frame_9->setGeometry(QRect(140, 565, 501, 151));
        frame_9->setFrameShape(QFrame::Box);
        frame_9->setFrameShadow(QFrame::Sunken);
        frame_9->setLineWidth(3);
        label_80 = new QLabel(frame_9);
        label_80->setObjectName(QString::fromUtf8("label_80"));
        label_80->setGeometry(QRect(16, 23, 140, 35));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_80->sizePolicy().hasHeightForWidth());
        label_80->setSizePolicy(sizePolicy2);
        label_80->setMinimumSize(QSize(140, 35));
        label_80->setMaximumSize(QSize(140, 35));
        label_80->setFont(font8);
        frame_10 = new QFrame(frame_9);
        frame_10->setObjectName(QString::fromUtf8("frame_10"));
        frame_10->setGeometry(QRect(164, 10, 321, 61));
        frame_10->setStyleSheet(QString::fromUtf8("background-color: rgb(235, 235, 235);"));
        frame_10->setFrameShape(QFrame::Panel);
        frame_10->setFrameShadow(QFrame::Raised);
        frame_10->setLineWidth(3);
        verticalLayout_14 = new QVBoxLayout(frame_10);
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setContentsMargins(11, 11, 11, 11);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        lE_SysOveride = new QLineEdit(frame_10);
        lE_SysOveride->setObjectName(QString::fromUtf8("lE_SysOveride"));
        sizePolicy1.setHeightForWidth(lE_SysOveride->sizePolicy().hasHeightForWidth());
        lE_SysOveride->setSizePolicy(sizePolicy1);
        lE_SysOveride->setMinimumSize(QSize(0, 0));
        lE_SysOveride->setMaximumSize(QSize(16777215, 12312313));
        lE_SysOveride->setFont(font7);
        lE_SysOveride->setStyleSheet(QString::fromUtf8(""));
        lE_SysOveride->setFrame(false);

        verticalLayout_14->addWidget(lE_SysOveride);

        label_78 = new QLabel(frame_9);
        label_78->setObjectName(QString::fromUtf8("label_78"));
        label_78->setGeometry(QRect(16, 92, 140, 35));
        sizePolicy2.setHeightForWidth(label_78->sizePolicy().hasHeightForWidth());
        label_78->setSizePolicy(sizePolicy2);
        label_78->setMinimumSize(QSize(140, 35));
        label_78->setMaximumSize(QSize(140, 35));
        label_78->setFont(font8);
        frame_11 = new QFrame(frame_9);
        frame_11->setObjectName(QString::fromUtf8("frame_11"));
        frame_11->setGeometry(QRect(164, 80, 321, 60));
        frame_11->setStyleSheet(QString::fromUtf8("background-color: rgb(235, 235, 235);"));
        frame_11->setFrameShape(QFrame::Panel);
        frame_11->setFrameShadow(QFrame::Raised);
        frame_11->setLineWidth(3);
        verticalLayout_15 = new QVBoxLayout(frame_11);
        verticalLayout_15->setSpacing(6);
        verticalLayout_15->setContentsMargins(11, 11, 11, 11);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        lE_BatchName = new QLineEdit(frame_11);
        lE_BatchName->setObjectName(QString::fromUtf8("lE_BatchName"));
        sizePolicy1.setHeightForWidth(lE_BatchName->sizePolicy().hasHeightForWidth());
        lE_BatchName->setSizePolicy(sizePolicy1);
        lE_BatchName->setMinimumSize(QSize(0, 0));
        lE_BatchName->setMaximumSize(QSize(16777215, 234324));
        lE_BatchName->setFont(font7);
        lE_BatchName->setStyleSheet(QString::fromUtf8(""));
        lE_BatchName->setFrame(false);

        verticalLayout_15->addWidget(lE_BatchName);

        lb_logo = new QLabel(groupBox_10);
        lb_logo->setObjectName(QString::fromUtf8("lb_logo"));
        lb_logo->setGeometry(QRect(5, 580, 130, 130));
        sizePolicy2.setHeightForWidth(lb_logo->sizePolicy().hasHeightForWidth());
        lb_logo->setSizePolicy(sizePolicy2);
        lb_logo->setMinimumSize(QSize(130, 130));
        lb_logo->setMaximumSize(QSize(130, 130));
        lb_logo->setScaledContents(true);
        pB_dtDlg = new QPushButton(groupBox_10);
        pB_dtDlg->setObjectName(QString::fromUtf8("pB_dtDlg"));
        pB_dtDlg->setGeometry(QRect(650, 580, 41, 31));
        sizePolicy.setHeightForWidth(pB_dtDlg->sizePolicy().hasHeightForWidth());
        pB_dtDlg->setSizePolicy(sizePolicy);
        pB_dtDlg->setMinimumSize(QSize(0, 0));
        pB_dtDlg->setMaximumSize(QSize(16777215, 16777215));
        QFont font10;
        font10.setFamily(QString::fromUtf8("\350\277\267\344\275\240\347\256\200\350\217\261\345\277\203"));
        font10.setPointSize(60);
        font10.setBold(false);
        font10.setItalic(false);
        font10.setWeight(50);
        pB_dtDlg->setFont(font10);
        pB_dtDlg->setLayoutDirection(Qt::RightToLeft);
        pB_dtDlg->setStyleSheet(QString::fromUtf8("background-color: rgb(200, 200, 100);\n"
"font: 60pt \"\350\277\267\344\275\240\347\256\200\350\217\261\345\277\203\";"));
        pB_dtDlg->setCheckable(true);

        verticalLayout_6->addWidget(groupBox_10);

        frame_20 = new QFrame(QtPLCDialogClass);
        frame_20->setObjectName(QString::fromUtf8("frame_20"));
        frame_20->setGeometry(QRect(858, 0, 376, 755));
        frame_20->setMinimumSize(QSize(0, 0));
        frame_20->setMaximumSize(QSize(7898, 7788));
        frame_20->setAutoFillBackground(true);
        frame_20->setFrameShape(QFrame::Box);
        frame_20->setFrameShadow(QFrame::Sunken);
        frame_20->setLineWidth(3);
        pB_SetUp = new QPushButton(frame_20);
        pB_SetUp->setObjectName(QString::fromUtf8("pB_SetUp"));
        pB_SetUp->setEnabled(true);
        pB_SetUp->setGeometry(QRect(15, 15, 41, 45));
        sizePolicy.setHeightForWidth(pB_SetUp->sizePolicy().hasHeightForWidth());
        pB_SetUp->setSizePolicy(sizePolicy);
        pB_SetUp->setMinimumSize(QSize(0, 45));
        QFont font11;
        font11.setFamily(QString::fromUtf8("\345\271\274\345\234\206"));
        font11.setPointSize(36);
        pB_SetUp->setFont(font11);
        pB_SetUp->setCheckable(true);
        pB_cmdStart = new QPushButton(frame_20);
        pB_cmdStart->setObjectName(QString::fromUtf8("pB_cmdStart"));
        pB_cmdStart->setGeometry(QRect(15, 550, 347, 200));
        sizePolicy.setHeightForWidth(pB_cmdStart->sizePolicy().hasHeightForWidth());
        pB_cmdStart->setSizePolicy(sizePolicy);
        pB_cmdStart->setMinimumSize(QSize(0, 0));
        pB_cmdStart->setMaximumSize(QSize(16777215, 16777215));
        pB_cmdStart->setFont(font10);
        pB_cmdStart->setLayoutDirection(Qt::RightToLeft);
        pB_cmdStart->setStyleSheet(QString::fromUtf8("background-color: rgb(200, 200, 100);\n"
"font: 60pt \"\350\277\267\344\275\240\347\256\200\350\217\261\345\277\203\";"));
        pB_cmdStart->setCheckable(true);

        retranslateUi(QtPLCDialogClass);

        tabWidget_PLC->setCurrentIndex(1);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QtPLCDialogClass);
    } // setupUi

    void retranslateUi(QDialog *QtPLCDialogClass)
    {
        QtPLCDialogClass->setWindowTitle(QCoreApplication::translate("QtPLCDialogClass", "QtPLCDialogClass", nullptr));
        groupBox->setTitle(QCoreApplication::translate("QtPLCDialogClass", "DI", nullptr));
        label_40->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\203\266\345\233\212\344\270\213\350\220\275\346\243\200\346\265\213", nullptr));
        lb_00->setText(QString());
        label_11->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\221\206\350\207\202\344\275\215\347\275\256\346\243\200\346\265\213", nullptr));
        lb_10->setText(QString());
        groupBox_7->setTitle(QCoreApplication::translate("QtPLCDialogClass", "DO", nullptr));
        pb_cmdVaccum->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\234\237\347\251\272\345\217\221\347\224\237\345\231\250", nullptr));
        pb_cmdBaffle->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\214\241    \346\235\277", nullptr));
        pb_cmdReject->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\216\222\345\272\237\347\224\265\347\243\201\351\223\201", nullptr));
        pb_cmdCapGet->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\217\226\346\226\231\347\224\265\347\243\201\351\223\201", nullptr));
        pb_cmdCapGetValve->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\217\226\346\226\231\347\224\265\347\243\201\351\230\200", nullptr));
        pb_cmdStopSignal->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\201\234\346\234\272\344\277\241\345\217\267", nullptr));
        pb_cmdChannelSwith->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\203\266\345\233\212\351\200\232\351\201\223\345\210\207\346\215\242", nullptr));
        pb_cmdCapBackValve->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\233\236\346\226\231\347\224\265\347\243\201\351\230\200", nullptr));
        pb_cmdYellowAlarmout->setText(QCoreApplication::translate("QtPLCDialogClass", "\351\273\204\347\201\257\346\212\245\350\255\246", nullptr));
        pb_cmdAlarmSignal->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\212\245\350\255\246\350\276\223\345\207\272", nullptr));
        pb_cmdAlarmOut->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\212\245\350\255\246\350\234\202\351\270\243\345\231\250", nullptr));
        groupBox_8->setTitle(QCoreApplication::translate("QtPLCDialogClass", "AO", nullptr));
        label_2->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\250\241\346\213\237\351\207\217\350\276\223\345\207\272", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QString());
        groupBox_2->setTitle(QCoreApplication::translate("QtPLCDialogClass", "\344\270\213\346\226\231", nullptr));
        pB_cmdFeedSingleStop->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\215\225\347\262\222\344\270\213\346\226\231\345\201\234\346\255\242", nullptr));
        pB_cmdAxisFeedPosMov->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\255\243\345\220\221\350\277\236\347\273\255\350\277\220\345\212\250", nullptr));
        pB_cmdAxisFeedStopMov->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\201\234\346\255\242\350\277\220\345\212\250", nullptr));
        pB_cmdFeedSingle->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\215\225\347\262\222\344\270\213\346\226\231", nullptr));
        pB_cmdAxisFeedRelMov->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\233\270\345\257\271\350\277\220\345\212\250", nullptr));
        pB_cmdAxisFeedJogPos->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\255\243\350\275\254\347\202\271\345\212\250", nullptr));
        pB_cmdAxisFeedJogNeg->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\217\215\350\275\254\347\202\271\345\212\250", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("QtPLCDialogClass", "\346\227\213\350\275\254", nullptr));
        pB_cmdAxisSwingJogPos->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\255\243\350\275\254\347\202\271\345\212\250", nullptr));
        pB_cmdAxisSwingJogNeg->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\217\215\350\275\254\347\202\271\345\212\250", nullptr));
        pB_cmdAxisSwingRelMov->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\233\270\345\257\271\350\277\220\345\212\250", nullptr));
        pB_cmdAxisSwingPosMov->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\255\243\345\220\221\350\277\236\347\273\255\350\277\220\345\212\250", nullptr));
        pB_cmdAxisSwingStopMov->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\201\234\346\255\242\350\277\220\345\212\250", nullptr));
        pB_cmdSwing->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\227\213\350\275\254\345\215\225\345\267\245\344\275\215", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QString());
        groupBox_5->setTitle(QCoreApplication::translate("QtPLCDialogClass", "\347\247\260\351\207\215", nullptr));
        pB_cmdScaleRead->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\247\244\350\257\273\346\225\260\345\221\275\344\273\244", nullptr));
        pB_cmdScaleTire->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\247\244\346\270\205\351\233\266", nullptr));
        pB_cmdScaleCalibExt->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\247\244\345\244\226\351\203\250\346\240\241\346\255\243", nullptr));
        label->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\250\263\345\256\232\347\212\266\346\200\201\350\256\276\345\256\232\347\233\256\346\240\207:", nullptr));
        cB_paraScaleSetStable->setItemText(0, QCoreApplication::translate("QtPLCDialogClass", "\351\235\236\345\270\270\347\250\263\345\256\232", nullptr));
        cB_paraScaleSetStable->setItemText(1, QCoreApplication::translate("QtPLCDialogClass", "\347\250\263\345\256\232", nullptr));
        cB_paraScaleSetStable->setItemText(2, QCoreApplication::translate("QtPLCDialogClass", "\344\270\215\347\250\263\345\256\232", nullptr));
        cB_paraScaleSetStable->setItemText(3, QCoreApplication::translate("QtPLCDialogClass", "\351\235\236\345\270\270\344\270\215\347\250\263\345\256\232", nullptr));

        pB_cmdScaleSetStable->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\256\276\345\256\232\347\247\244\347\250\263\345\256\232\347\212\266\346\200\201", nullptr));
        pB_cmdAlogtest->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\250\241\346\213\237\351\207\217\350\276\223\345\207\272\346\265\213\350\257\225", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QString());
        tabWidget_PLC->setTabText(tabWidget_PLC->indexOf(tab_PLC_Control), QString());
        label_25->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\207\252\345\212\250\345\217\226\346\226\231\345\221\250\346\234\237", nullptr));
        label_41->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\257\273\346\225\260\345\273\266\350\277\237\345\220\257\345\212\250\346\227\266\351\227\264", nullptr));
        label_26->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\201\234\346\255\242\344\275\215\347\275\2561", nullptr));
        label_32->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\216\273\347\232\256\345\273\266\350\277\237\345\220\257\345\212\250\346\227\266\351\227\264", nullptr));
        label_31->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\201\234\346\255\242\344\275\215\347\275\2562", nullptr));
        label_5->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\210\220\345\223\201\350\277\224\350\277\230\345\221\250\346\234\237", nullptr));
        label_4->setText(QCoreApplication::translate("QtPLCDialogClass", "\344\270\213\346\226\231\350\266\205\346\227\266\346\227\266\351\227\264", nullptr));
        label_42->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\216\273\347\232\256\347\255\211\345\276\205\346\227\266\351\227\264", nullptr));
        label_44->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\277\236\347\273\255\350\266\205\351\231\220\345\201\234\346\234\272\346\225\260", nullptr));
        tabWidget_PLC->setTabText(tabWidget_PLC->indexOf(tab_8), QString());
        label_9->setText(QCoreApplication::translate("QtPLCDialogClass", "\351\200\237 \345\272\246(rpm)", nullptr));
        lE_InterUnderLoad->setText(QCoreApplication::translate("QtPLCDialogClass", "0.299", nullptr));
        lE_TOverload->setText(QCoreApplication::translate("QtPLCDialogClass", "0.323", nullptr));
        label_53->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\266\205\351\207\215\351\207\215\351\207\217(g)", nullptr));
        lE_GroupSet->setText(QCoreApplication::translate("QtPLCDialogClass", "20", nullptr));
        label_54->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\266\205\350\275\273\351\207\215\351\207\217(g)", nullptr));
        label_14->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\234\237\346\234\233\351\207\215\351\207\217(g)", nullptr));
        label_13->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\206\205\346\216\247\344\270\212\351\231\220(g)", nullptr));
        lE_TestInterval->setText(QCoreApplication::translate("QtPLCDialogClass", "60", nullptr));
        label_55->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\216\273\347\232\256\346\226\271\345\274\217", nullptr));
        lE_TDemand->setText(QCoreApplication::translate("QtPLCDialogClass", "0.313", nullptr));
        label_52->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\257\217\347\273\204\346\243\200\346\265\213\346\225\260", nullptr));
        label_12->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\206\205\346\216\247\344\270\213\351\231\220(g)", nullptr));
        label_50->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\273\204\351\227\264\351\232\224(s)", nullptr));
        cB_TireMode->setItemText(0, QCoreApplication::translate("QtPLCDialogClass", "\346\257\217\347\273\204\345\216\273\347\232\256", nullptr));
        cB_TireMode->setItemText(1, QCoreApplication::translate("QtPLCDialogClass", "\346\257\217\346\254\241\345\216\273\347\232\256", nullptr));

        lE_GroupNo->setText(QCoreApplication::translate("QtPLCDialogClass", "45", nullptr));
        lE_InterOverLoad->setText(QCoreApplication::translate("QtPLCDialogClass", "0.345", nullptr));
        lE_TUnderload->setText(QCoreApplication::translate("QtPLCDialogClass", "0.300", nullptr));
        label_79->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\275\223\345\211\215\347\273\204\345\217\267", nullptr));
        lE_SysOveride_2->setText(QCoreApplication::translate("QtPLCDialogClass", "120", nullptr));
        tabWidget_PLC->setTabText(tabWidget_PLC->indexOf(tab_2), QString());
        groupBox_4->setTitle(QCoreApplication::translate("QtPLCDialogClass", "\344\270\213\346\226\231\347\224\265\346\234\272", nullptr));
        label_21->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\212\266\346\200\201\346\234\272\346\255\245\351\252\244", nullptr));
        label_19->setText(QCoreApplication::translate("QtPLCDialogClass", "\351\224\231\350\257\257\344\273\243\347\240\201", nullptr));
        label_22->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\233\270\345\257\271\350\277\220\345\212\250\350\267\235\347\246\273", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("QtPLCDialogClass", "\346\227\213\350\275\254\347\224\265\346\234\272", nullptr));
        label_24->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\212\266\346\200\201\346\234\272\346\255\245\351\252\244", nullptr));
        label_27->setText(QCoreApplication::translate("QtPLCDialogClass", "\351\224\231\350\257\257\344\273\243\347\240\201", nullptr));
        label_28->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\233\270\345\257\271\350\277\220\345\212\250\350\267\235\347\246\273", nullptr));
        label_3->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\212\245\350\255\246\344\275\215", nullptr));
        label_33->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\265\213\351\207\217\345\256\236\351\231\205\351\227\264\351\232\224\346\227\266\351\227\264", nullptr));
        label_29->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\263\273\347\273\237\350\277\220\350\241\214\347\212\266\346\200\201\346\234\272\346\255\245\351\252\244", nullptr));
        label_20->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\212\245\350\255\246\347\212\266\346\200\201", nullptr));
        tabWidget_PLC->setTabText(tabWidget_PLC->indexOf(tab_3), QString());
        pb_cmdParaSave->setText(QCoreApplication::translate("QtPLCDialogClass", "\344\277\235\345\255\230", nullptr));
        pB_cmdCounterZero_2->setText(QCoreApplication::translate("QtPLCDialogClass", "PLC\347\233\221\346\216\247", nullptr));
        pB_cmdCounterZero_3->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\263\273\347\273\237\345\217\202\346\225\260", nullptr));
        pB_cmdCounterZero_5->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\277\220\350\241\214\347\212\266\346\200\201", nullptr));
        pB_cmdCounterZero_4->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\277\220\350\241\214\345\217\202\346\225\260", nullptr));
        groupBox_10->setTitle(QCoreApplication::translate("QtPLCDialogClass", "          .                          ", nullptr));
        lE_ScaleResult->setText(QCoreApplication::translate("QtPLCDialogClass", "0.567", nullptr));
        label_10->setText(QCoreApplication::translate("QtPLCDialogClass", "\351\200\232\350\277\207\350\256\241\346\225\260", nullptr));
        cB_ScaleStableState->setItemText(0, QCoreApplication::translate("QtPLCDialogClass", "\351\235\236\345\270\270\347\250\263\345\256\232", nullptr));
        cB_ScaleStableState->setItemText(1, QCoreApplication::translate("QtPLCDialogClass", "\347\250\263\345\256\232", nullptr));
        cB_ScaleStableState->setItemText(2, QCoreApplication::translate("QtPLCDialogClass", "\344\270\215\347\250\263\345\256\232", nullptr));
        cB_ScaleStableState->setItemText(3, QCoreApplication::translate("QtPLCDialogClass", "\351\235\236\345\270\270\344\270\215\347\250\263\345\256\232", nullptr));

        lE_ProdCount->setText(QCoreApplication::translate("QtPLCDialogClass", "14", nullptr));
        label_43->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\234\254\346\254\241\351\207\215\351\207\217", nullptr));
        label_39->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\247\260\351\207\215\350\256\241\346\225\260", nullptr));
        lE_TOCount->setText(QCoreApplication::translate("QtPLCDialogClass", "1", nullptr));
        label_48->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\277\207\350\275\273\350\256\241\346\225\260", nullptr));
        lE_PassCount->setText(QCoreApplication::translate("QtPLCDialogClass", "13", nullptr));
        lE_Finished->setText(QCoreApplication::translate("QtPLCDialogClass", "1", nullptr));
        label_49->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\277\207\351\207\215\350\256\241\346\225\260", nullptr));
        label_18->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\234\254\347\273\204\345\272\217\345\217\267", nullptr));
        label_45->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\250\263\345\256\232\347\212\266\346\200\201", nullptr));
        label_15->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\234\254\347\273\204\347\273\223\346\235\237", nullptr));
        label_16->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\275\223\345\211\215\350\257\273\346\225\260", nullptr));
        label_17->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\211\224\345\272\237\350\256\241\346\225\260", nullptr));
        lE_RejectCount->setText(QCoreApplication::translate("QtPLCDialogClass", "1", nullptr));
        lE_TUCount->setText(QCoreApplication::translate("QtPLCDialogClass", "3", nullptr));
        lE_Weight->setText(QCoreApplication::translate("QtPLCDialogClass", "0.234", nullptr));
        lE_GroupIndex->setText(QCoreApplication::translate("QtPLCDialogClass", "13", nullptr));
        label_80->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\277\220\350\241\214\351\200\237\345\272\246\357\274\232", nullptr));
        lE_SysOveride->setText(QCoreApplication::translate("QtPLCDialogClass", "120", nullptr));
        label_78->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\224\237\344\272\247\346\211\271\345\217\267\357\274\232", nullptr));
        lE_BatchName->setText(QCoreApplication::translate("QtPLCDialogClass", "123456789", nullptr));
        lb_logo->setText(QString());
        pB_dtDlg->setText(QString());
        pB_SetUp->setText(QString());
        pB_cmdStart->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class QtPLCDialogClass: public Ui_QtPLCDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTPLCDIALOGCLASS_H

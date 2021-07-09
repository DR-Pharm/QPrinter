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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

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
    QGridLayout *gridLayout_11;
    QLabel *label_40;
    QLabel *label_46;
    QLabel *lb_00;
    QLabel *lb_10;
    QLabel *label_11;
    QLabel *lb_20;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer_11;
    QGroupBox *groupBox_7;
    QVBoxLayout *verticalLayout_11;
    QGridLayout *gridLayout_6;
    QPushButton *pb_cmdReject;
    QPushButton *pb_cmdChannelSwith;
    QPushButton *pb_cmdVaccum;
    QPushButton *pb_cmdCapGet;
    QPushButton *pb_cmdCapGetValve;
    QPushButton *pb_cmdCapBackValve;
    QPushButton *pb_cmdAlarmOut;
    QPushButton *pb_cmdStopSignal;
    QPushButton *pb_cmdAlarmSignal;
    QPushButton *pb_cmdYellowAlarmout;
    QPushButton *pb_cmdBaffle;
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
    QPushButton *pB_cmdAxisFeedPosMov;
    QPushButton *pB_cmdFeedSingle;
    QPushButton *pB_cmdAxisFeedStopMov;
    QPushButton *pB_cmdAxisFeedJogNeg;
    QPushButton *pB_cmdFeedSingleStop;
    QPushButton *pB_cmdAxisFeedJogPos;
    QLabel *label_22;
    QLineEdit *lE_AxisFeedRelMovDistance;
    QPushButton *pB_cmdAxisFeedRelMov;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_8;
    QPushButton *pB_cmdAxisSwingJogPos;
    QPushButton *pB_cmdAxisSwingJogNeg;
    QPushButton *pB_cmdAxisSwingStopMov;
    QPushButton *pB_cmdAxisSwingPosMov;
    QPushButton *pB_cmdSwing;
    QLabel *label_28;
    QPushButton *pB_cmdAxisSwingRelMov;
    QLineEdit *lE_AxisSwingRelMovDistance;
    QWidget *tab_6;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *groupBox_9;
    QGridLayout *gridLayout_12;
    QSpacerItem *verticalSpacer_17;
    QSpacerItem *verticalSpacer_19;
    QPushButton *pB_cmdFeedFive;
    QLabel *label_62;
    QPushButton *pB_cmdFeedshakelevel;
    QPushButton *pB_cmdFeedhome;
    QLabel *label_30;
    QLineEdit *lE_MultiCount;
    QPushButton *pB_cmdFeedShake;
    QPushButton *pB_cmdFeedshakestop;
    QLineEdit *lE_FeedOveride;
    QLineEdit *lE_Feed_shakeoffset;
    QPushButton *pB_cmdFeedShakefive;
    QLabel *label_57;
    QSpacerItem *verticalSpacer_3;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout;
    QPushButton *pB_cmdScaleTire;
    QPushButton *pB_cmdScaleCalibExt;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_14;
    QPushButton *pB_showPrt;
    QPushButton *pB_cmdAlogtest;
    QSpacerItem *horizontalSpacer_11;
    QSpacerItem *verticalSpacer;
    QWidget *tab_8;
    QVBoxLayout *verticalLayout;
    QFrame *frame_4;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_11;
    QPushButton *pB_Read1;
    QPushButton *pB_Write1;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_5;
    QLabel *label_31;
    QLabel *label_41;
    QLineEdit *lE_FeedTimeOut;
    QSpacerItem *horizontalSpacer_20;
    QLineEdit *lE_CapBackInterval;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_5;
    QLineEdit *lE_ReadDelay;
    QLabel *label_4;
    QLineEdit *lE_s_trg_stop1;
    QLineEdit *lE_s_trg_stop0;
    QLabel *label_26;
    QLabel *label_25;
    QLineEdit *lE_CapPickInterval;
    QLabel *label_32;
    QLineEdit *lE_TireDelay;
    QLabel *label_42;
    QLineEdit *lE_TireWaitTime;
    QLineEdit *lE_StopSignalDelay;
    QLabel *label_44;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_12;
    QFrame *frame_6;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_2;
    QLabel *label_58;
    QLabel *label_53;
    QLineEdit *lE_TestInterval;
    QComboBox *cB_Feedmode;
    QLineEdit *lE_GroupSet;
    QLineEdit *lE_TDemand;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *lE_TUnderload;
    QLabel *label_14;
    QLineEdit *lE_TOverload;
    QLineEdit *lE_InterUnderLoad;
    QLabel *label_52;
    QSpacerItem *horizontalSpacer;
    QLabel *label_12;
    QLabel *label_54;
    QLabel *label_56;
    QLabel *label_13;
    QLineEdit *lE_InterOverLoad;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *pB_Read2;
    QPushButton *pB_Write2;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer_6;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_3;
    QLabel *label_21;
    QLabel *label_19;
    QLineEdit *lE_AxisFeedErrorNo;
    QLineEdit *lE_AxisFeedStep;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_9;
    QLabel *label_24;
    QLineEdit *lE_AxisSwingErrorNo;
    QLineEdit *lE_AxisSwingStep;
    QLabel *label_27;
    QSpacerItem *verticalSpacer_8;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_6;
    QLineEdit *lE_AlarmStatus;
    QLabel *label_20;
    QLineEdit *lE_TimeInterval;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_33;
    QSpacerItem *verticalSpacer_7;
    QWidget *tab_5;
    QGroupBox *gB_User;
    QVBoxLayout *verticalLayout_25;
    QLabel *label_65;
    QLineEdit *lE_SetUserName;
    QLabel *label_66;
    QComboBox *cB_SetUserPermission;
    QLabel *label_67;
    QLineEdit *lE_SetUserSecretNum;
    QPushButton *pB_AddUser;
    QTabWidget *tabWidget_Users;
    QWidget *widget_UsersChoice_2;
    QVBoxLayout *verticalLayout_26;
    QLabel *label_68;
    QComboBox *cB_Users;
    QLabel *label_69;
    QTreeWidget *treeWidget_2;
    QPushButton *pB_Users_Delete;
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
    QLabel *label_10;
    QFrame *frame_22;
    QVBoxLayout *verticalLayout_27;
    QLineEdit *lE_MachineStep;
    QFrame *frame_19;
    QVBoxLayout *verticalLayout_23;
    QLineEdit *lE_GroupIndex;
    QLabel *label_48;
    QFrame *frame_14;
    QVBoxLayout *verticalLayout_17;
    QLineEdit *lE_ProdCount;
    QLabel *label_50;
    QSpacerItem *verticalSpacer_13;
    QFrame *frame_13;
    QVBoxLayout *verticalLayout_16;
    QLineEdit *lE_PassCount;
    QLabel *label_79;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_8;
    QLineEdit *lE_Finished;
    QLabel *label_17;
    QFrame *frame_21;
    QVBoxLayout *verticalLayout_24;
    QLineEdit *lE_GroupNo;
    QLabel *label_18;
    QLabel *label_16;
    QSpacerItem *verticalSpacer_16;
    QSpacerItem *verticalSpacer_12;
    QSpacerItem *verticalSpacer_14;
    QLabel *label_39;
    QSpacerItem *verticalSpacer_5;
    QFrame *frame_15;
    QVBoxLayout *verticalLayout_19;
    QLineEdit *lE_ScaleResult;
    QFrame *frame_17;
    QVBoxLayout *verticalLayout_21;
    QLineEdit *lE_TUCount;
    QSpacerItem *horizontalSpacer_19;
    QSpacerItem *verticalSpacer_15;
    QLabel *label_15;
    QFrame *frame_16;
    QVBoxLayout *verticalLayout_18;
    QLineEdit *lE_TOCount;
    QSpacerItem *horizontalSpacer_18;
    QSpacerItem *horizontalSpacer_10;
    QLabel *label_49;
    QFrame *frame_12;
    QVBoxLayout *verticalLayout_20;
    QLineEdit *lE_RejectCount;
    QFrame *frame_9;
    QLabel *label_80;
    QFrame *frame_10;
    QVBoxLayout *verticalLayout_14;
    QLineEdit *lE_SysOveride;
    QLabel *label_78;
    QFrame *frame_11;
    QVBoxLayout *verticalLayout_15;
    QLineEdit *lE_BatchName;
    QLabel *label_81;
    QLabel *lb_logo;
    QPushButton *pB_dtDlg;
    QFrame *frame_20;
    QPushButton *pB_SetUp;
    QPushButton *pB_cmdStart;
    QLabel *lb_alm;
    QWidget *widget;
    QWidget *layoutWidget_3;
    QGridLayout *gridLayout_13;
    QLineEdit *lE_GroupMax;
    QLineEdit *lE_GroupMinRatio;
    QLabel *label_8;
    QLabel *label_29;
    QLabel *label_6;
    QLineEdit *lE_GroupMin;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *horizontalSpacer_12;
    QLabel *label_34;
    QLineEdit *lE_GroupMaxRatio;
    QLineEdit *lE_GroupAvg;
    QLabel *label_7;
    QLineEdit *lE_GroupSum;
    QLabel *label_3;
    QLineEdit *lE_GroupIndex_2;
    QLabel *label;
    QLineEdit *lE_GroupNo_2;
    QLabel *label_9;
    QTableWidget *tableWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_One;
    QGroupBox *groupBox_11;
    QGridLayout *gridLayout_14;
    QPushButton *pB_printCurve;
    QLabel *label_37;
    QLabel *label_23;
    QPushButton *pB_startSearch;
    QLabel *label_36;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *lE_year2;
    QLabel *label_51;
    QLineEdit *lE_month2;
    QLabel *label_55;
    QLineEdit *lE_day2;
    QLabel *label_59;
    QLineEdit *lE_hour2;
    QLabel *label_60;
    QLineEdit *lE_minute2;
    QLabel *label_35;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lE_year1;
    QLabel *label_38;
    QLineEdit *lE_month1;
    QLabel *label_43;
    QLineEdit *lE_day1;
    QLabel *label_47;
    QLineEdit *lE_hour1;
    QLabel *label_45;
    QLineEdit *lE_minute1;
    QLineEdit *lE_print1;
    QPushButton *pB_printData;
    QPushButton *pB_printData_2;
    QLineEdit *lE_print2;
    QLabel *label_61;
    QLabel *lb_searchResult;
    QPushButton *pB_copyIn;

    void setupUi(QDialog *QtPLCDialogClass)
    {
        if (QtPLCDialogClass->objectName().isEmpty())
            QtPLCDialogClass->setObjectName(QString::fromUtf8("QtPLCDialogClass"));
        QtPLCDialogClass->resize(4000, 893);
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
        gridLayout_11 = new QGridLayout();
        gridLayout_11->setSpacing(6);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        label_40 = new QLabel(groupBox);
        label_40->setObjectName(QString::fromUtf8("label_40"));
        label_40->setMinimumSize(QSize(230, 0));
        label_40->setMaximumSize(QSize(230, 16777215));
        label_40->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(label_40, 0, 0, 1, 1);

        label_46 = new QLabel(groupBox);
        label_46->setObjectName(QString::fromUtf8("label_46"));
        label_46->setMinimumSize(QSize(230, 0));
        label_46->setMaximumSize(QSize(230, 16777215));
        label_46->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(label_46, 1, 0, 1, 1);

        lb_00 = new QLabel(groupBox);
        lb_00->setObjectName(QString::fromUtf8("lb_00"));
        lb_00->setMinimumSize(QSize(32, 32));
        lb_00->setMaximumSize(QSize(32, 32));
        lb_00->setPixmap(QPixmap(QString::fromUtf8("C:/Users/33741/Desktop/QtConsoleApplication1/QtClassLibrary1/ico/redLed.png")));

        gridLayout_11->addWidget(lb_00, 0, 1, 1, 1);

        lb_10 = new QLabel(groupBox);
        lb_10->setObjectName(QString::fromUtf8("lb_10"));
        lb_10->setMinimumSize(QSize(32, 32));
        lb_10->setMaximumSize(QSize(32, 32));
        lb_10->setPixmap(QPixmap(QString::fromUtf8("C:/Users/33741/Desktop/QtConsoleApplication1/QtClassLibrary1/ico/redLed.png")));

        gridLayout_11->addWidget(lb_10, 0, 4, 1, 1);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setMinimumSize(QSize(230, 0));
        label_11->setMaximumSize(QSize(230, 16777215));
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(label_11, 0, 3, 1, 1);

        lb_20 = new QLabel(groupBox);
        lb_20->setObjectName(QString::fromUtf8("lb_20"));
        lb_20->setMinimumSize(QSize(32, 32));
        lb_20->setMaximumSize(QSize(32, 32));
        lb_20->setPixmap(QPixmap(QString::fromUtf8("C:/Users/33741/Desktop/QtConsoleApplication1/QtClassLibrary1/ico/redLed.png")));

        gridLayout_11->addWidget(lb_20, 1, 1, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_11->addItem(horizontalSpacer_7, 0, 2, 1, 1);


        horizontalLayout_6->addLayout(gridLayout_11);


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
        pb_cmdReject = new QPushButton(groupBox_7);
        pb_cmdReject->setObjectName(QString::fromUtf8("pb_cmdReject"));
        pb_cmdReject->setMinimumSize(QSize(250, 44));
        pb_cmdReject->setMaximumSize(QSize(127, 44));
        pb_cmdReject->setCheckable(true);

        gridLayout_6->addWidget(pb_cmdReject, 0, 0, 1, 1);

        pb_cmdChannelSwith = new QPushButton(groupBox_7);
        pb_cmdChannelSwith->setObjectName(QString::fromUtf8("pb_cmdChannelSwith"));
        pb_cmdChannelSwith->setMinimumSize(QSize(250, 44));
        pb_cmdChannelSwith->setMaximumSize(QSize(127, 44));
        pb_cmdChannelSwith->setCheckable(true);

        gridLayout_6->addWidget(pb_cmdChannelSwith, 0, 1, 1, 1);

        pb_cmdVaccum = new QPushButton(groupBox_7);
        pb_cmdVaccum->setObjectName(QString::fromUtf8("pb_cmdVaccum"));
        pb_cmdVaccum->setMinimumSize(QSize(250, 44));
        pb_cmdVaccum->setMaximumSize(QSize(127, 44));
        pb_cmdVaccum->setCheckable(true);

        gridLayout_6->addWidget(pb_cmdVaccum, 0, 2, 1, 1);

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

        pb_cmdCapBackValve = new QPushButton(groupBox_7);
        pb_cmdCapBackValve->setObjectName(QString::fromUtf8("pb_cmdCapBackValve"));
        pb_cmdCapBackValve->setMinimumSize(QSize(250, 44));
        pb_cmdCapBackValve->setMaximumSize(QSize(127, 44));
        pb_cmdCapBackValve->setCheckable(true);

        gridLayout_6->addWidget(pb_cmdCapBackValve, 1, 2, 1, 1);

        pb_cmdAlarmOut = new QPushButton(groupBox_7);
        pb_cmdAlarmOut->setObjectName(QString::fromUtf8("pb_cmdAlarmOut"));
        pb_cmdAlarmOut->setMinimumSize(QSize(250, 44));
        pb_cmdAlarmOut->setMaximumSize(QSize(127, 44));
        pb_cmdAlarmOut->setCheckable(true);

        gridLayout_6->addWidget(pb_cmdAlarmOut, 2, 0, 1, 1);

        pb_cmdStopSignal = new QPushButton(groupBox_7);
        pb_cmdStopSignal->setObjectName(QString::fromUtf8("pb_cmdStopSignal"));
        pb_cmdStopSignal->setMinimumSize(QSize(250, 44));
        pb_cmdStopSignal->setMaximumSize(QSize(127, 44));
        pb_cmdStopSignal->setCheckable(true);

        gridLayout_6->addWidget(pb_cmdStopSignal, 2, 1, 1, 1);

        pb_cmdAlarmSignal = new QPushButton(groupBox_7);
        pb_cmdAlarmSignal->setObjectName(QString::fromUtf8("pb_cmdAlarmSignal"));
        pb_cmdAlarmSignal->setMinimumSize(QSize(250, 44));
        pb_cmdAlarmSignal->setMaximumSize(QSize(127, 44));
        pb_cmdAlarmSignal->setCheckable(true);

        gridLayout_6->addWidget(pb_cmdAlarmSignal, 2, 2, 1, 1);

        pb_cmdYellowAlarmout = new QPushButton(groupBox_7);
        pb_cmdYellowAlarmout->setObjectName(QString::fromUtf8("pb_cmdYellowAlarmout"));
        pb_cmdYellowAlarmout->setMinimumSize(QSize(250, 44));
        pb_cmdYellowAlarmout->setMaximumSize(QSize(127, 44));
        pb_cmdYellowAlarmout->setCheckable(true);

        gridLayout_6->addWidget(pb_cmdYellowAlarmout, 3, 0, 1, 1);

        pb_cmdBaffle = new QPushButton(groupBox_7);
        pb_cmdBaffle->setObjectName(QString::fromUtf8("pb_cmdBaffle"));
        pb_cmdBaffle->setMinimumSize(QSize(250, 44));
        pb_cmdBaffle->setMaximumSize(QSize(127, 44));
        pb_cmdBaffle->setCheckable(true);

        gridLayout_6->addWidget(pb_cmdBaffle, 3, 1, 1, 1);


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
        label_2->setMinimumSize(QSize(230, 0));
        label_2->setMaximumSize(QSize(230, 16777215));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_9->addWidget(label_2);

        lE_Analogoutput = new QLineEdit(groupBox_8);
        lE_Analogoutput->setObjectName(QString::fromUtf8("lE_Analogoutput"));
        lE_Analogoutput->setEnabled(false);
        lE_Analogoutput->setMinimumSize(QSize(230, 0));
        lE_Analogoutput->setMaximumSize(QSize(230, 16777215));
        lE_Analogoutput->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

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
        pB_cmdAxisFeedPosMov = new QPushButton(groupBox_2);
        pB_cmdAxisFeedPosMov->setObjectName(QString::fromUtf8("pB_cmdAxisFeedPosMov"));
        pB_cmdAxisFeedPosMov->setMinimumSize(QSize(220, 0));
        pB_cmdAxisFeedPosMov->setMaximumSize(QSize(220, 16777215));

        gridLayout_7->addWidget(pB_cmdAxisFeedPosMov, 2, 1, 1, 1);

        pB_cmdFeedSingle = new QPushButton(groupBox_2);
        pB_cmdFeedSingle->setObjectName(QString::fromUtf8("pB_cmdFeedSingle"));
        pB_cmdFeedSingle->setMinimumSize(QSize(220, 0));
        pB_cmdFeedSingle->setMaximumSize(QSize(220, 16777215));

        gridLayout_7->addWidget(pB_cmdFeedSingle, 3, 0, 1, 1);

        pB_cmdAxisFeedStopMov = new QPushButton(groupBox_2);
        pB_cmdAxisFeedStopMov->setObjectName(QString::fromUtf8("pB_cmdAxisFeedStopMov"));
        pB_cmdAxisFeedStopMov->setMinimumSize(QSize(220, 0));
        pB_cmdAxisFeedStopMov->setMaximumSize(QSize(220, 16777215));

        gridLayout_7->addWidget(pB_cmdAxisFeedStopMov, 2, 2, 1, 1);

        pB_cmdAxisFeedJogNeg = new QPushButton(groupBox_2);
        pB_cmdAxisFeedJogNeg->setObjectName(QString::fromUtf8("pB_cmdAxisFeedJogNeg"));
        pB_cmdAxisFeedJogNeg->setMinimumSize(QSize(220, 0));
        pB_cmdAxisFeedJogNeg->setMaximumSize(QSize(220, 16777215));

        gridLayout_7->addWidget(pB_cmdAxisFeedJogNeg, 0, 1, 1, 1);

        pB_cmdFeedSingleStop = new QPushButton(groupBox_2);
        pB_cmdFeedSingleStop->setObjectName(QString::fromUtf8("pB_cmdFeedSingleStop"));
        pB_cmdFeedSingleStop->setMinimumSize(QSize(220, 0));
        pB_cmdFeedSingleStop->setMaximumSize(QSize(220, 16777215));

        gridLayout_7->addWidget(pB_cmdFeedSingleStop, 3, 1, 1, 1);

        pB_cmdAxisFeedJogPos = new QPushButton(groupBox_2);
        pB_cmdAxisFeedJogPos->setObjectName(QString::fromUtf8("pB_cmdAxisFeedJogPos"));
        pB_cmdAxisFeedJogPos->setMinimumSize(QSize(220, 0));
        pB_cmdAxisFeedJogPos->setMaximumSize(QSize(220, 16777215));

        gridLayout_7->addWidget(pB_cmdAxisFeedJogPos, 0, 0, 1, 1);

        label_22 = new QLabel(groupBox_2);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setMinimumSize(QSize(220, 0));
        label_22->setMaximumSize(QSize(220, 16777215));
        label_22->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_7->addWidget(label_22, 1, 0, 1, 1);

        lE_AxisFeedRelMovDistance = new QLineEdit(groupBox_2);
        lE_AxisFeedRelMovDistance->setObjectName(QString::fromUtf8("lE_AxisFeedRelMovDistance"));
        lE_AxisFeedRelMovDistance->setEnabled(true);
        lE_AxisFeedRelMovDistance->setMinimumSize(QSize(220, 0));
        lE_AxisFeedRelMovDistance->setMaximumSize(QSize(220, 16777215));

        gridLayout_7->addWidget(lE_AxisFeedRelMovDistance, 1, 1, 1, 1);

        pB_cmdAxisFeedRelMov = new QPushButton(groupBox_2);
        pB_cmdAxisFeedRelMov->setObjectName(QString::fromUtf8("pB_cmdAxisFeedRelMov"));
        pB_cmdAxisFeedRelMov->setMinimumSize(QSize(220, 0));
        pB_cmdAxisFeedRelMov->setMaximumSize(QSize(220, 16777215));

        gridLayout_7->addWidget(pB_cmdAxisFeedRelMov, 1, 2, 1, 1);


        verticalLayout_5->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(tab_4);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_8 = new QGridLayout(groupBox_3);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        pB_cmdAxisSwingJogPos = new QPushButton(groupBox_3);
        pB_cmdAxisSwingJogPos->setObjectName(QString::fromUtf8("pB_cmdAxisSwingJogPos"));
        pB_cmdAxisSwingJogPos->setMinimumSize(QSize(220, 0));
        pB_cmdAxisSwingJogPos->setMaximumSize(QSize(220, 16777215));

        gridLayout_8->addWidget(pB_cmdAxisSwingJogPos, 0, 0, 1, 1);

        pB_cmdAxisSwingJogNeg = new QPushButton(groupBox_3);
        pB_cmdAxisSwingJogNeg->setObjectName(QString::fromUtf8("pB_cmdAxisSwingJogNeg"));
        pB_cmdAxisSwingJogNeg->setMinimumSize(QSize(220, 0));
        pB_cmdAxisSwingJogNeg->setMaximumSize(QSize(220, 16777215));

        gridLayout_8->addWidget(pB_cmdAxisSwingJogNeg, 0, 1, 1, 1);

        pB_cmdAxisSwingStopMov = new QPushButton(groupBox_3);
        pB_cmdAxisSwingStopMov->setObjectName(QString::fromUtf8("pB_cmdAxisSwingStopMov"));
        pB_cmdAxisSwingStopMov->setMinimumSize(QSize(220, 0));
        pB_cmdAxisSwingStopMov->setMaximumSize(QSize(220, 16777215));

        gridLayout_8->addWidget(pB_cmdAxisSwingStopMov, 2, 2, 1, 1);

        pB_cmdAxisSwingPosMov = new QPushButton(groupBox_3);
        pB_cmdAxisSwingPosMov->setObjectName(QString::fromUtf8("pB_cmdAxisSwingPosMov"));
        pB_cmdAxisSwingPosMov->setMinimumSize(QSize(220, 0));
        pB_cmdAxisSwingPosMov->setMaximumSize(QSize(220, 16777215));

        gridLayout_8->addWidget(pB_cmdAxisSwingPosMov, 2, 1, 1, 1);

        pB_cmdSwing = new QPushButton(groupBox_3);
        pB_cmdSwing->setObjectName(QString::fromUtf8("pB_cmdSwing"));
        pB_cmdSwing->setMinimumSize(QSize(220, 0));
        pB_cmdSwing->setMaximumSize(QSize(220, 16777215));

        gridLayout_8->addWidget(pB_cmdSwing, 3, 0, 1, 1);

        label_28 = new QLabel(groupBox_3);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setMinimumSize(QSize(220, 0));
        label_28->setMaximumSize(QSize(220, 16777215));
        label_28->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(label_28, 1, 0, 1, 1);

        pB_cmdAxisSwingRelMov = new QPushButton(groupBox_3);
        pB_cmdAxisSwingRelMov->setObjectName(QString::fromUtf8("pB_cmdAxisSwingRelMov"));
        pB_cmdAxisSwingRelMov->setMinimumSize(QSize(220, 0));
        pB_cmdAxisSwingRelMov->setMaximumSize(QSize(220, 16777215));

        gridLayout_8->addWidget(pB_cmdAxisSwingRelMov, 1, 2, 1, 1);

        lE_AxisSwingRelMovDistance = new QLineEdit(groupBox_3);
        lE_AxisSwingRelMovDistance->setObjectName(QString::fromUtf8("lE_AxisSwingRelMovDistance"));
        lE_AxisSwingRelMovDistance->setEnabled(true);
        lE_AxisSwingRelMovDistance->setMinimumSize(QSize(220, 0));
        lE_AxisSwingRelMovDistance->setMaximumSize(QSize(220, 16777215));

        gridLayout_8->addWidget(lE_AxisSwingRelMovDistance, 1, 1, 1, 1);


        verticalLayout_5->addWidget(groupBox_3);

        tabWidget->addTab(tab_4, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        verticalLayout_2 = new QVBoxLayout(tab_6);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        groupBox_9 = new QGroupBox(tab_6);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        gridLayout_12 = new QGridLayout(groupBox_9);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        verticalSpacer_17 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_12->addItem(verticalSpacer_17, 3, 1, 1, 1);

        verticalSpacer_19 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_12->addItem(verticalSpacer_19, 1, 1, 1, 1);

        pB_cmdFeedFive = new QPushButton(groupBox_9);
        pB_cmdFeedFive->setObjectName(QString::fromUtf8("pB_cmdFeedFive"));
        pB_cmdFeedFive->setMinimumSize(QSize(150, 0));
        pB_cmdFeedFive->setMaximumSize(QSize(220, 16777215));

        gridLayout_12->addWidget(pB_cmdFeedFive, 2, 1, 1, 1);

        label_62 = new QLabel(groupBox_9);
        label_62->setObjectName(QString::fromUtf8("label_62"));
        label_62->setMinimumSize(QSize(150, 0));
        label_62->setMaximumSize(QSize(220, 232323));
        label_62->setFont(font1);
        label_62->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_12->addWidget(label_62, 6, 0, 1, 1);

        pB_cmdFeedshakelevel = new QPushButton(groupBox_9);
        pB_cmdFeedshakelevel->setObjectName(QString::fromUtf8("pB_cmdFeedshakelevel"));
        pB_cmdFeedshakelevel->setMinimumSize(QSize(150, 0));
        pB_cmdFeedshakelevel->setMaximumSize(QSize(220, 16777215));

        gridLayout_12->addWidget(pB_cmdFeedshakelevel, 0, 2, 1, 1);

        pB_cmdFeedhome = new QPushButton(groupBox_9);
        pB_cmdFeedhome->setObjectName(QString::fromUtf8("pB_cmdFeedhome"));
        pB_cmdFeedhome->setMinimumSize(QSize(150, 0));
        pB_cmdFeedhome->setMaximumSize(QSize(220, 16777215));

        gridLayout_12->addWidget(pB_cmdFeedhome, 2, 0, 1, 1);

        label_30 = new QLabel(groupBox_9);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_30->sizePolicy().hasHeightForWidth());
        label_30->setSizePolicy(sizePolicy);
        label_30->setMinimumSize(QSize(150, 30));
        label_30->setMaximumSize(QSize(220, 30));
        label_30->setFont(font1);
        label_30->setStyleSheet(QString::fromUtf8(""));
        label_30->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_12->addWidget(label_30, 5, 0, 1, 1);

        lE_MultiCount = new QLineEdit(groupBox_9);
        lE_MultiCount->setObjectName(QString::fromUtf8("lE_MultiCount"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lE_MultiCount->sizePolicy().hasHeightForWidth());
        lE_MultiCount->setSizePolicy(sizePolicy1);
        lE_MultiCount->setMinimumSize(QSize(150, 42));
        lE_MultiCount->setMaximumSize(QSize(220, 42));
        lE_MultiCount->setFont(font1);

        gridLayout_12->addWidget(lE_MultiCount, 6, 1, 1, 1);

        pB_cmdFeedShake = new QPushButton(groupBox_9);
        pB_cmdFeedShake->setObjectName(QString::fromUtf8("pB_cmdFeedShake"));
        pB_cmdFeedShake->setMinimumSize(QSize(150, 0));
        pB_cmdFeedShake->setMaximumSize(QSize(220, 16777215));

        gridLayout_12->addWidget(pB_cmdFeedShake, 0, 0, 1, 1);

        pB_cmdFeedshakestop = new QPushButton(groupBox_9);
        pB_cmdFeedshakestop->setObjectName(QString::fromUtf8("pB_cmdFeedshakestop"));
        pB_cmdFeedshakestop->setMinimumSize(QSize(150, 0));
        pB_cmdFeedshakestop->setMaximumSize(QSize(220, 16777215));

        gridLayout_12->addWidget(pB_cmdFeedshakestop, 0, 1, 1, 1);

        lE_FeedOveride = new QLineEdit(groupBox_9);
        lE_FeedOveride->setObjectName(QString::fromUtf8("lE_FeedOveride"));
        lE_FeedOveride->setMinimumSize(QSize(150, 42));
        lE_FeedOveride->setMaximumSize(QSize(220, 42));
        lE_FeedOveride->setFont(font1);

        gridLayout_12->addWidget(lE_FeedOveride, 4, 1, 1, 1);

        lE_Feed_shakeoffset = new QLineEdit(groupBox_9);
        lE_Feed_shakeoffset->setObjectName(QString::fromUtf8("lE_Feed_shakeoffset"));
        lE_Feed_shakeoffset->setMinimumSize(QSize(150, 42));
        lE_Feed_shakeoffset->setMaximumSize(QSize(220, 42));
        lE_Feed_shakeoffset->setFont(font1);
        lE_Feed_shakeoffset->setStyleSheet(QString::fromUtf8(""));

        gridLayout_12->addWidget(lE_Feed_shakeoffset, 5, 1, 1, 1);

        pB_cmdFeedShakefive = new QPushButton(groupBox_9);
        pB_cmdFeedShakefive->setObjectName(QString::fromUtf8("pB_cmdFeedShakefive"));
        pB_cmdFeedShakefive->setMinimumSize(QSize(150, 0));
        pB_cmdFeedShakefive->setMaximumSize(QSize(220, 16777215));

        gridLayout_12->addWidget(pB_cmdFeedShakefive, 2, 2, 1, 1);

        label_57 = new QLabel(groupBox_9);
        label_57->setObjectName(QString::fromUtf8("label_57"));
        label_57->setMinimumSize(QSize(150, 0));
        label_57->setMaximumSize(QSize(220, 16777215));
        label_57->setFont(font1);
        label_57->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_12->addWidget(label_57, 4, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox_9);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

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
        pB_cmdScaleTire = new QPushButton(groupBox_5);
        pB_cmdScaleTire->setObjectName(QString::fromUtf8("pB_cmdScaleTire"));
        pB_cmdScaleTire->setMinimumSize(QSize(220, 0));
        pB_cmdScaleTire->setMaximumSize(QSize(220, 16777215));

        horizontalLayout->addWidget(pB_cmdScaleTire);

        pB_cmdScaleCalibExt = new QPushButton(groupBox_5);
        pB_cmdScaleCalibExt->setObjectName(QString::fromUtf8("pB_cmdScaleCalibExt"));
        pB_cmdScaleCalibExt->setMinimumSize(QSize(220, 0));
        pB_cmdScaleCalibExt->setMaximumSize(QSize(220, 16777215));

        horizontalLayout->addWidget(pB_cmdScaleCalibExt);


        verticalLayout_10->addLayout(horizontalLayout);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_10->addItem(verticalSpacer_4);


        verticalLayout_2->addWidget(groupBox_5);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_14);

        pB_showPrt = new QPushButton(tab_6);
        pB_showPrt->setObjectName(QString::fromUtf8("pB_showPrt"));
        pB_showPrt->setMinimumSize(QSize(220, 0));
        pB_showPrt->setMaximumSize(QSize(220, 16777215));
        pB_showPrt->setCheckable(true);

        horizontalLayout_5->addWidget(pB_showPrt);

        pB_cmdAlogtest = new QPushButton(tab_6);
        pB_cmdAlogtest->setObjectName(QString::fromUtf8("pB_cmdAlogtest"));
        pB_cmdAlogtest->setEnabled(false);
        pB_cmdAlogtest->setMinimumSize(QSize(220, 0));
        pB_cmdAlogtest->setMaximumSize(QSize(220, 16777215));

        horizontalLayout_5->addWidget(pB_cmdAlogtest);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_11);


        verticalLayout_2->addLayout(horizontalLayout_5);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

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
        layoutWidget_2 = new QWidget(frame_4);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(10, 590, 801, 44));
        horizontalLayout_11 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        pB_Read1 = new QPushButton(layoutWidget_2);
        pB_Read1->setObjectName(QString::fromUtf8("pB_Read1"));

        horizontalLayout_11->addWidget(pB_Read1);

        pB_Write1 = new QPushButton(layoutWidget_2);
        pB_Write1->setObjectName(QString::fromUtf8("pB_Write1"));

        horizontalLayout_11->addWidget(pB_Write1);

        layoutWidget = new QWidget(frame_4);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(3, 13, 847, 561));
        gridLayout_5 = new QGridLayout(layoutWidget);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        label_31 = new QLabel(layoutWidget);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        sizePolicy.setHeightForWidth(label_31->sizePolicy().hasHeightForWidth());
        label_31->setSizePolicy(sizePolicy);
        label_31->setMinimumSize(QSize(230, 30));
        label_31->setMaximumSize(QSize(230, 30));
        label_31->setFont(font1);
        label_31->setStyleSheet(QString::fromUtf8(""));
        label_31->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_31, 0, 3, 1, 1);

        label_41 = new QLabel(layoutWidget);
        label_41->setObjectName(QString::fromUtf8("label_41"));
        sizePolicy.setHeightForWidth(label_41->sizePolicy().hasHeightForWidth());
        label_41->setSizePolicy(sizePolicy);
        label_41->setMinimumSize(QSize(230, 30));
        label_41->setMaximumSize(QSize(230, 30));
        label_41->setFont(font1);
        label_41->setStyleSheet(QString::fromUtf8(""));
        label_41->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_41, 3, 3, 1, 1);

        lE_FeedTimeOut = new QLineEdit(layoutWidget);
        lE_FeedTimeOut->setObjectName(QString::fromUtf8("lE_FeedTimeOut"));
        lE_FeedTimeOut->setMinimumSize(QSize(150, 35));
        lE_FeedTimeOut->setMaximumSize(QSize(150, 35));
        lE_FeedTimeOut->setFont(font1);
        lE_FeedTimeOut->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(lE_FeedTimeOut, 1, 4, 1, 1);

        horizontalSpacer_20 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_20, 2, 5, 1, 1);

        lE_CapBackInterval = new QLineEdit(layoutWidget);
        lE_CapBackInterval->setObjectName(QString::fromUtf8("lE_CapBackInterval"));
        lE_CapBackInterval->setMinimumSize(QSize(150, 35));
        lE_CapBackInterval->setMaximumSize(QSize(150, 35));
        lE_CapBackInterval->setFont(font1);
        lE_CapBackInterval->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(lE_CapBackInterval, 2, 4, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_4, 4, 2, 1, 1);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setMinimumSize(QSize(230, 30));
        label_5->setMaximumSize(QSize(230, 30));
        label_5->setFont(font1);
        label_5->setStyleSheet(QString::fromUtf8(""));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_5, 2, 3, 1, 1);

        lE_ReadDelay = new QLineEdit(layoutWidget);
        lE_ReadDelay->setObjectName(QString::fromUtf8("lE_ReadDelay"));
        lE_ReadDelay->setMinimumSize(QSize(150, 35));
        lE_ReadDelay->setMaximumSize(QSize(150, 35));
        lE_ReadDelay->setFont(font1);
        lE_ReadDelay->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(lE_ReadDelay, 3, 4, 1, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setMinimumSize(QSize(230, 30));
        label_4->setMaximumSize(QSize(230, 30));
        label_4->setFont(font1);
        label_4->setStyleSheet(QString::fromUtf8(""));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_4, 1, 3, 1, 1);

        lE_s_trg_stop1 = new QLineEdit(layoutWidget);
        lE_s_trg_stop1->setObjectName(QString::fromUtf8("lE_s_trg_stop1"));
        lE_s_trg_stop1->setMinimumSize(QSize(150, 35));
        lE_s_trg_stop1->setMaximumSize(QSize(150, 35));
        lE_s_trg_stop1->setFont(font1);
        lE_s_trg_stop1->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(lE_s_trg_stop1, 0, 4, 1, 1);

        lE_s_trg_stop0 = new QLineEdit(layoutWidget);
        lE_s_trg_stop0->setObjectName(QString::fromUtf8("lE_s_trg_stop0"));
        lE_s_trg_stop0->setMinimumSize(QSize(150, 35));
        lE_s_trg_stop0->setMaximumSize(QSize(150, 35));
        lE_s_trg_stop0->setFont(font1);
        lE_s_trg_stop0->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(lE_s_trg_stop0, 0, 1, 1, 1);

        label_26 = new QLabel(layoutWidget);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        sizePolicy.setHeightForWidth(label_26->sizePolicy().hasHeightForWidth());
        label_26->setSizePolicy(sizePolicy);
        label_26->setMinimumSize(QSize(220, 30));
        label_26->setMaximumSize(QSize(220, 30));
        label_26->setFont(font1);
        label_26->setStyleSheet(QString::fromUtf8(""));
        label_26->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_26, 0, 0, 1, 1);

        label_25 = new QLabel(layoutWidget);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        sizePolicy.setHeightForWidth(label_25->sizePolicy().hasHeightForWidth());
        label_25->setSizePolicy(sizePolicy);
        label_25->setMinimumSize(QSize(220, 30));
        label_25->setMaximumSize(QSize(220, 30));
        label_25->setFont(font1);
        label_25->setStyleSheet(QString::fromUtf8(""));
        label_25->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_25, 1, 0, 1, 1);

        lE_CapPickInterval = new QLineEdit(layoutWidget);
        lE_CapPickInterval->setObjectName(QString::fromUtf8("lE_CapPickInterval"));
        lE_CapPickInterval->setMinimumSize(QSize(150, 35));
        lE_CapPickInterval->setMaximumSize(QSize(150, 35));
        lE_CapPickInterval->setFont(font1);
        lE_CapPickInterval->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(lE_CapPickInterval, 1, 1, 1, 1);

        label_32 = new QLabel(layoutWidget);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        sizePolicy.setHeightForWidth(label_32->sizePolicy().hasHeightForWidth());
        label_32->setSizePolicy(sizePolicy);
        label_32->setMinimumSize(QSize(220, 30));
        label_32->setMaximumSize(QSize(220, 30));
        label_32->setFont(font1);
        label_32->setStyleSheet(QString::fromUtf8(""));
        label_32->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_32, 2, 0, 1, 1);

        lE_TireDelay = new QLineEdit(layoutWidget);
        lE_TireDelay->setObjectName(QString::fromUtf8("lE_TireDelay"));
        lE_TireDelay->setMinimumSize(QSize(150, 35));
        lE_TireDelay->setMaximumSize(QSize(150, 35));
        lE_TireDelay->setFont(font1);
        lE_TireDelay->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(lE_TireDelay, 2, 1, 1, 1);

        label_42 = new QLabel(layoutWidget);
        label_42->setObjectName(QString::fromUtf8("label_42"));
        sizePolicy.setHeightForWidth(label_42->sizePolicy().hasHeightForWidth());
        label_42->setSizePolicy(sizePolicy);
        label_42->setMinimumSize(QSize(220, 30));
        label_42->setMaximumSize(QSize(220, 30));
        label_42->setFont(font1);
        label_42->setStyleSheet(QString::fromUtf8(""));
        label_42->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_42, 3, 0, 1, 1);

        lE_TireWaitTime = new QLineEdit(layoutWidget);
        lE_TireWaitTime->setObjectName(QString::fromUtf8("lE_TireWaitTime"));
        lE_TireWaitTime->setMinimumSize(QSize(150, 35));
        lE_TireWaitTime->setMaximumSize(QSize(150, 35));
        lE_TireWaitTime->setFont(font1);
        lE_TireWaitTime->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(lE_TireWaitTime, 3, 1, 1, 1);

        lE_StopSignalDelay = new QLineEdit(layoutWidget);
        lE_StopSignalDelay->setObjectName(QString::fromUtf8("lE_StopSignalDelay"));
        lE_StopSignalDelay->setMinimumSize(QSize(150, 35));
        lE_StopSignalDelay->setMaximumSize(QSize(150, 35));
        lE_StopSignalDelay->setFont(font1);
        lE_StopSignalDelay->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(lE_StopSignalDelay, 4, 4, 1, 1);

        label_44 = new QLabel(layoutWidget);
        label_44->setObjectName(QString::fromUtf8("label_44"));
        sizePolicy.setHeightForWidth(label_44->sizePolicy().hasHeightForWidth());
        label_44->setSizePolicy(sizePolicy);
        label_44->setMinimumSize(QSize(240, 30));
        label_44->setMaximumSize(QSize(240, 30));
        label_44->setFont(font1);
        label_44->setStyleSheet(QString::fromUtf8(""));
        label_44->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

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
        layoutWidget1 = new QWidget(frame_6);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(13, 13, 801, 561));
        gridLayout_2 = new QGridLayout(layoutWidget1);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_58 = new QLabel(layoutWidget1);
        label_58->setObjectName(QString::fromUtf8("label_58"));
        label_58->setMinimumSize(QSize(200, 0));
        label_58->setMaximumSize(QSize(200, 16777215));
        label_58->setFont(font1);
        label_58->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_58, 1, 3, 1, 1);

        label_53 = new QLabel(layoutWidget1);
        label_53->setObjectName(QString::fromUtf8("label_53"));
        label_53->setMinimumSize(QSize(200, 0));
        label_53->setMaximumSize(QSize(200, 232323));
        label_53->setFont(font1);
        label_53->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_53, 3, 0, 1, 1);

        lE_TestInterval = new QLineEdit(layoutWidget1);
        lE_TestInterval->setObjectName(QString::fromUtf8("lE_TestInterval"));
        sizePolicy1.setHeightForWidth(lE_TestInterval->sizePolicy().hasHeightForWidth());
        lE_TestInterval->setSizePolicy(sizePolicy1);
        lE_TestInterval->setMinimumSize(QSize(150, 42));
        lE_TestInterval->setMaximumSize(QSize(150, 42));
        lE_TestInterval->setFont(font1);

        gridLayout_2->addWidget(lE_TestInterval, 2, 4, 1, 1);

        cB_Feedmode = new QComboBox(layoutWidget1);
        cB_Feedmode->addItem(QString());
        cB_Feedmode->addItem(QString());
        cB_Feedmode->setObjectName(QString::fromUtf8("cB_Feedmode"));
        cB_Feedmode->setMinimumSize(QSize(150, 0));
        cB_Feedmode->setMaximumSize(QSize(150, 16777215));
        cB_Feedmode->setFont(font1);

        gridLayout_2->addWidget(cB_Feedmode, 1, 4, 1, 1);

        lE_GroupSet = new QLineEdit(layoutWidget1);
        lE_GroupSet->setObjectName(QString::fromUtf8("lE_GroupSet"));
        lE_GroupSet->setMinimumSize(QSize(150, 0));
        lE_GroupSet->setMaximumSize(QSize(150, 16777215));
        lE_GroupSet->setFont(font1);

        gridLayout_2->addWidget(lE_GroupSet, 0, 4, 1, 1);

        lE_TDemand = new QLineEdit(layoutWidget1);
        lE_TDemand->setObjectName(QString::fromUtf8("lE_TDemand"));
        sizePolicy1.setHeightForWidth(lE_TDemand->sizePolicy().hasHeightForWidth());
        lE_TDemand->setSizePolicy(sizePolicy1);
        lE_TDemand->setMinimumSize(QSize(150, 42));
        lE_TDemand->setMaximumSize(QSize(150, 42));
        lE_TDemand->setFont(font1);

        gridLayout_2->addWidget(lE_TDemand, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 2, 5, 1, 1);

        lE_TUnderload = new QLineEdit(layoutWidget1);
        lE_TUnderload->setObjectName(QString::fromUtf8("lE_TUnderload"));
        sizePolicy1.setHeightForWidth(lE_TUnderload->sizePolicy().hasHeightForWidth());
        lE_TUnderload->setSizePolicy(sizePolicy1);
        lE_TUnderload->setMinimumSize(QSize(150, 42));
        lE_TUnderload->setMaximumSize(QSize(150, 42));
        lE_TUnderload->setFont(font1);

        gridLayout_2->addWidget(lE_TUnderload, 4, 1, 1, 1);

        label_14 = new QLabel(layoutWidget1);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setMinimumSize(QSize(200, 0));
        label_14->setMaximumSize(QSize(200, 232323));
        label_14->setFont(font1);
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_14, 0, 0, 1, 1);

        lE_TOverload = new QLineEdit(layoutWidget1);
        lE_TOverload->setObjectName(QString::fromUtf8("lE_TOverload"));
        sizePolicy1.setHeightForWidth(lE_TOverload->sizePolicy().hasHeightForWidth());
        lE_TOverload->setSizePolicy(sizePolicy1);
        lE_TOverload->setMinimumSize(QSize(150, 42));
        lE_TOverload->setMaximumSize(QSize(150, 42));
        lE_TOverload->setFont(font1);

        gridLayout_2->addWidget(lE_TOverload, 3, 1, 1, 1);

        lE_InterUnderLoad = new QLineEdit(layoutWidget1);
        lE_InterUnderLoad->setObjectName(QString::fromUtf8("lE_InterUnderLoad"));
        sizePolicy1.setHeightForWidth(lE_InterUnderLoad->sizePolicy().hasHeightForWidth());
        lE_InterUnderLoad->setSizePolicy(sizePolicy1);
        lE_InterUnderLoad->setMinimumSize(QSize(150, 42));
        lE_InterUnderLoad->setMaximumSize(QSize(150, 42));
        lE_InterUnderLoad->setFont(font1);

        gridLayout_2->addWidget(lE_InterUnderLoad, 2, 1, 1, 1);

        label_52 = new QLabel(layoutWidget1);
        label_52->setObjectName(QString::fromUtf8("label_52"));
        label_52->setMinimumSize(QSize(200, 0));
        label_52->setMaximumSize(QSize(200, 16777215));
        label_52->setFont(font1);
        label_52->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_52, 0, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 2, 2, 1, 1);

        label_12 = new QLabel(layoutWidget1);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setMinimumSize(QSize(200, 0));
        label_12->setMaximumSize(QSize(200, 232323));
        label_12->setFont(font1);
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_12, 2, 0, 1, 1);

        label_54 = new QLabel(layoutWidget1);
        label_54->setObjectName(QString::fromUtf8("label_54"));
        label_54->setMinimumSize(QSize(200, 0));
        label_54->setMaximumSize(QSize(200, 232323));
        label_54->setFont(font1);
        label_54->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_54, 4, 0, 1, 1);

        label_56 = new QLabel(layoutWidget1);
        label_56->setObjectName(QString::fromUtf8("label_56"));
        label_56->setMinimumSize(QSize(200, 0));
        label_56->setMaximumSize(QSize(200, 232323));
        label_56->setFont(font1);
        label_56->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_56, 2, 3, 1, 1);

        label_13 = new QLabel(layoutWidget1);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setMinimumSize(QSize(200, 0));
        label_13->setMaximumSize(QSize(200, 232323));
        label_13->setFont(font1);
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_13, 1, 0, 1, 1);

        lE_InterOverLoad = new QLineEdit(layoutWidget1);
        lE_InterOverLoad->setObjectName(QString::fromUtf8("lE_InterOverLoad"));
        sizePolicy1.setHeightForWidth(lE_InterOverLoad->sizePolicy().hasHeightForWidth());
        lE_InterOverLoad->setSizePolicy(sizePolicy1);
        lE_InterOverLoad->setMinimumSize(QSize(150, 42));
        lE_InterOverLoad->setMaximumSize(QSize(150, 42));
        lE_InterOverLoad->setFont(font1);

        gridLayout_2->addWidget(lE_InterOverLoad, 1, 1, 1, 1);

        layoutWidget2 = new QWidget(frame_6);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 590, 801, 44));
        horizontalLayout_10 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        pB_Read2 = new QPushButton(layoutWidget2);
        pB_Read2->setObjectName(QString::fromUtf8("pB_Read2"));

        horizontalLayout_10->addWidget(pB_Read2);

        pB_Write2 = new QPushButton(layoutWidget2);
        pB_Write2->setObjectName(QString::fromUtf8("pB_Write2"));

        horizontalLayout_10->addWidget(pB_Write2);


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
        label_21->setMinimumSize(QSize(180, 0));
        label_21->setMaximumSize(QSize(180, 16777215));
        label_21->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_21, 0, 0, 1, 1);

        label_19 = new QLabel(groupBox_4);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setMinimumSize(QSize(180, 0));
        label_19->setMaximumSize(QSize(180, 16777215));
        label_19->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_19, 1, 0, 1, 1);

        lE_AxisFeedErrorNo = new QLineEdit(groupBox_4);
        lE_AxisFeedErrorNo->setObjectName(QString::fromUtf8("lE_AxisFeedErrorNo"));
        lE_AxisFeedErrorNo->setEnabled(false);
        lE_AxisFeedErrorNo->setMinimumSize(QSize(180, 0));
        lE_AxisFeedErrorNo->setMaximumSize(QSize(180, 16777215));

        gridLayout_3->addWidget(lE_AxisFeedErrorNo, 1, 1, 1, 1);

        lE_AxisFeedStep = new QLineEdit(groupBox_4);
        lE_AxisFeedStep->setObjectName(QString::fromUtf8("lE_AxisFeedStep"));
        lE_AxisFeedStep->setEnabled(false);
        lE_AxisFeedStep->setMinimumSize(QSize(180, 0));
        lE_AxisFeedStep->setMaximumSize(QSize(180, 16777215));

        gridLayout_3->addWidget(lE_AxisFeedStep, 0, 1, 1, 1);


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
        label_24->setMinimumSize(QSize(180, 0));
        label_24->setMaximumSize(QSize(180, 16777215));
        label_24->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_9->addWidget(label_24, 0, 0, 1, 1);

        lE_AxisSwingErrorNo = new QLineEdit(groupBox_6);
        lE_AxisSwingErrorNo->setObjectName(QString::fromUtf8("lE_AxisSwingErrorNo"));
        lE_AxisSwingErrorNo->setEnabled(false);
        lE_AxisSwingErrorNo->setMinimumSize(QSize(180, 0));
        lE_AxisSwingErrorNo->setMaximumSize(QSize(180, 16777215));

        gridLayout_9->addWidget(lE_AxisSwingErrorNo, 1, 1, 1, 1);

        lE_AxisSwingStep = new QLineEdit(groupBox_6);
        lE_AxisSwingStep->setObjectName(QString::fromUtf8("lE_AxisSwingStep"));
        lE_AxisSwingStep->setEnabled(false);
        lE_AxisSwingStep->setMinimumSize(QSize(180, 0));
        lE_AxisSwingStep->setMaximumSize(QSize(180, 16777215));

        gridLayout_9->addWidget(lE_AxisSwingStep, 0, 1, 1, 1);

        label_27 = new QLabel(groupBox_6);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setMinimumSize(QSize(180, 0));
        label_27->setMaximumSize(QSize(180, 16777215));
        label_27->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_9->addWidget(label_27, 1, 0, 1, 1);


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
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 1, 3, 1, 1);

        lE_AlarmStatus = new QLineEdit(frame_2);
        lE_AlarmStatus->setObjectName(QString::fromUtf8("lE_AlarmStatus"));
        lE_AlarmStatus->setEnabled(false);
        lE_AlarmStatus->setMinimumSize(QSize(220, 0));
        lE_AlarmStatus->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(lE_AlarmStatus, 0, 2, 1, 1);

        label_20 = new QLabel(frame_2);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setMinimumSize(QSize(220, 0));
        label_20->setMaximumSize(QSize(220, 16777215));
        label_20->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_20, 0, 1, 1, 1);

        lE_TimeInterval = new QLineEdit(frame_2);
        lE_TimeInterval->setObjectName(QString::fromUtf8("lE_TimeInterval"));
        lE_TimeInterval->setEnabled(false);
        lE_TimeInterval->setMinimumSize(QSize(220, 0));
        lE_TimeInterval->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(lE_TimeInterval, 3, 2, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 1, 0, 1, 1);

        label_33 = new QLabel(frame_2);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setMinimumSize(QSize(220, 0));
        label_33->setMaximumSize(QSize(220, 16777215));
        label_33->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_33, 3, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout);


        verticalLayout_4->addWidget(frame_2);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_7);

        tabWidget_PLC->addTab(tab_3, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        gB_User = new QGroupBox(tab_5);
        gB_User->setObjectName(QString::fromUtf8("gB_User"));
        gB_User->setGeometry(QRect(525, 65, 291, 491));
        gB_User->setStyleSheet(QString::fromUtf8("font: 18pt \"\345\271\274\345\234\206\";"));
        verticalLayout_25 = new QVBoxLayout(gB_User);
        verticalLayout_25->setSpacing(6);
        verticalLayout_25->setContentsMargins(11, 11, 11, 11);
        verticalLayout_25->setObjectName(QString::fromUtf8("verticalLayout_25"));
        label_65 = new QLabel(gB_User);
        label_65->setObjectName(QString::fromUtf8("label_65"));
        label_65->setMinimumSize(QSize(0, 30));
        label_65->setMaximumSize(QSize(16777215, 30));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\271\274\345\234\206"));
        font2.setPointSize(18);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(50);
        label_65->setFont(font2);
        label_65->setStyleSheet(QString::fromUtf8("font: 18pt \"\345\271\274\345\234\206\";"));

        verticalLayout_25->addWidget(label_65);

        lE_SetUserName = new QLineEdit(gB_User);
        lE_SetUserName->setObjectName(QString::fromUtf8("lE_SetUserName"));
        lE_SetUserName->setMinimumSize(QSize(0, 36));
        lE_SetUserName->setMaximumSize(QSize(16777215, 36));
        lE_SetUserName->setStyleSheet(QString::fromUtf8("background-color: rgb(225, 225, 225);\n"
"font: 18pt \"\345\271\274\345\234\206\";"));
        lE_SetUserName->setMaxLength(15);

        verticalLayout_25->addWidget(lE_SetUserName);

        label_66 = new QLabel(gB_User);
        label_66->setObjectName(QString::fromUtf8("label_66"));
        label_66->setMinimumSize(QSize(0, 30));
        label_66->setMaximumSize(QSize(16777215, 30));
        label_66->setFont(font2);
        label_66->setStyleSheet(QString::fromUtf8("font: 18pt \"\345\271\274\345\234\206\";"));

        verticalLayout_25->addWidget(label_66);

        cB_SetUserPermission = new QComboBox(gB_User);
        cB_SetUserPermission->addItem(QString());
        cB_SetUserPermission->addItem(QString());
        cB_SetUserPermission->addItem(QString());
        cB_SetUserPermission->addItem(QString());
        cB_SetUserPermission->setObjectName(QString::fromUtf8("cB_SetUserPermission"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(cB_SetUserPermission->sizePolicy().hasHeightForWidth());
        cB_SetUserPermission->setSizePolicy(sizePolicy2);
        cB_SetUserPermission->setMinimumSize(QSize(0, 36));
        cB_SetUserPermission->setMaximumSize(QSize(16777215, 36));
        cB_SetUserPermission->setFont(font2);
        cB_SetUserPermission->setStyleSheet(QString::fromUtf8("font: 18pt \"\345\271\274\345\234\206\";"));

        verticalLayout_25->addWidget(cB_SetUserPermission);

        label_67 = new QLabel(gB_User);
        label_67->setObjectName(QString::fromUtf8("label_67"));
        label_67->setMinimumSize(QSize(0, 30));
        label_67->setMaximumSize(QSize(16777215, 30));
        label_67->setFont(font2);
        label_67->setStyleSheet(QString::fromUtf8("font: 18pt \"\345\271\274\345\234\206\";"));

        verticalLayout_25->addWidget(label_67);

        lE_SetUserSecretNum = new QLineEdit(gB_User);
        lE_SetUserSecretNum->setObjectName(QString::fromUtf8("lE_SetUserSecretNum"));
        lE_SetUserSecretNum->setMinimumSize(QSize(0, 36));
        lE_SetUserSecretNum->setMaximumSize(QSize(16777215, 36));
        lE_SetUserSecretNum->setStyleSheet(QString::fromUtf8("background-color: rgb(225, 225, 225);\n"
"font: 18pt \"\345\271\274\345\234\206\";"));
        lE_SetUserSecretNum->setMaxLength(15);

        verticalLayout_25->addWidget(lE_SetUserSecretNum);

        pB_AddUser = new QPushButton(gB_User);
        pB_AddUser->setObjectName(QString::fromUtf8("pB_AddUser"));
        pB_AddUser->setMinimumSize(QSize(0, 66));
        pB_AddUser->setMaximumSize(QSize(16777215, 66));
        pB_AddUser->setFont(font2);
        pB_AddUser->setStyleSheet(QString::fromUtf8("font: 18pt \"\345\271\274\345\234\206\";"));

        verticalLayout_25->addWidget(pB_AddUser);

        tabWidget_Users = new QTabWidget(tab_5);
        tabWidget_Users->setObjectName(QString::fromUtf8("tabWidget_Users"));
        tabWidget_Users->setGeometry(QRect(50, 40, 451, 611));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\271\274\345\234\206"));
        font3.setPointSize(20);
        font3.setBold(false);
        font3.setItalic(false);
        font3.setWeight(50);
        tabWidget_Users->setFont(font3);
        tabWidget_Users->setStyleSheet(QString::fromUtf8("font: 20pt \"\345\271\274\345\234\206\";"));
        widget_UsersChoice_2 = new QWidget(tab_5);
        widget_UsersChoice_2->setObjectName(QString::fromUtf8("widget_UsersChoice_2"));
        widget_UsersChoice_2->setEnabled(true);
        widget_UsersChoice_2->setGeometry(QRect(75, 275, 405, 354));
        widget_UsersChoice_2->setMinimumSize(QSize(405, 354));
        widget_UsersChoice_2->setMaximumSize(QSize(405, 354));
        widget_UsersChoice_2->setContextMenuPolicy(Qt::DefaultContextMenu);
        widget_UsersChoice_2->setAutoFillBackground(true);
        widget_UsersChoice_2->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_26 = new QVBoxLayout(widget_UsersChoice_2);
        verticalLayout_26->setSpacing(6);
        verticalLayout_26->setContentsMargins(11, 11, 11, 11);
        verticalLayout_26->setObjectName(QString::fromUtf8("verticalLayout_26"));
        verticalLayout_26->setSizeConstraint(QLayout::SetDefaultConstraint);
        label_68 = new QLabel(widget_UsersChoice_2);
        label_68->setObjectName(QString::fromUtf8("label_68"));
        label_68->setMinimumSize(QSize(0, 30));
        label_68->setMaximumSize(QSize(16777215, 30));
        label_68->setFont(font2);

        verticalLayout_26->addWidget(label_68);

        cB_Users = new QComboBox(widget_UsersChoice_2);
        cB_Users->addItem(QString());
        cB_Users->addItem(QString());
        cB_Users->addItem(QString());
        cB_Users->addItem(QString());
        cB_Users->setObjectName(QString::fromUtf8("cB_Users"));
        cB_Users->setMinimumSize(QSize(0, 36));
        cB_Users->setMaximumSize(QSize(16777215, 36));
        cB_Users->setFont(font2);
        cB_Users->setStyleSheet(QString::fromUtf8("font: 18pt \"\345\271\274\345\234\206\";"));

        verticalLayout_26->addWidget(cB_Users);

        label_69 = new QLabel(widget_UsersChoice_2);
        label_69->setObjectName(QString::fromUtf8("label_69"));
        label_69->setMinimumSize(QSize(0, 30));
        label_69->setMaximumSize(QSize(16777215, 30));
        label_69->setFont(font2);

        verticalLayout_26->addWidget(label_69);

        treeWidget_2 = new QTreeWidget(widget_UsersChoice_2);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget_2->setHeaderItem(__qtreewidgetitem);
        treeWidget_2->setObjectName(QString::fromUtf8("treeWidget_2"));
        treeWidget_2->setStyleSheet(QString::fromUtf8("font: 18pt \"\345\271\274\345\234\206\";"));

        verticalLayout_26->addWidget(treeWidget_2);

        pB_Users_Delete = new QPushButton(tab_5);
        pB_Users_Delete->setObjectName(QString::fromUtf8("pB_Users_Delete"));
        pB_Users_Delete->setGeometry(QRect(540, 580, 267, 66));
        pB_Users_Delete->setMinimumSize(QSize(267, 66));
        pB_Users_Delete->setMaximumSize(QSize(267, 66));
        pB_Users_Delete->setStyleSheet(QString::fromUtf8("font: 20pt \"\345\271\274\345\234\206\";"));
        tabWidget_PLC->addTab(tab_5, QString());
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
        QFont font4;
        font4.setFamily(QString::fromUtf8("\350\277\267\344\275\240\347\256\200\350\217\261\345\277\203"));
        font4.setPointSize(24);
        frame_5->setFont(font4);
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
        QFont font5;
        font5.setFamily(QString::fromUtf8("\350\277\267\344\275\240\347\256\200\350\217\261\345\277\203"));
        font5.setPointSize(36);
        pB_cmdCounterZero_2->setFont(font5);

        gridLayout_4->addWidget(pB_cmdCounterZero_2, 0, 0, 1, 1);

        pB_cmdCounterZero_3 = new QPushButton(frame_5);
        pB_cmdCounterZero_3->setObjectName(QString::fromUtf8("pB_cmdCounterZero_3"));
        sizePolicy.setHeightForWidth(pB_cmdCounterZero_3->sizePolicy().hasHeightForWidth());
        pB_cmdCounterZero_3->setSizePolicy(sizePolicy);
        pB_cmdCounterZero_3->setMinimumSize(QSize(0, 80));
        pB_cmdCounterZero_3->setFont(font5);

        gridLayout_4->addWidget(pB_cmdCounterZero_3, 0, 1, 1, 1);

        pB_cmdCounterZero_5 = new QPushButton(frame_5);
        pB_cmdCounterZero_5->setObjectName(QString::fromUtf8("pB_cmdCounterZero_5"));
        sizePolicy.setHeightForWidth(pB_cmdCounterZero_5->sizePolicy().hasHeightForWidth());
        pB_cmdCounterZero_5->setSizePolicy(sizePolicy);
        pB_cmdCounterZero_5->setMinimumSize(QSize(0, 80));
        pB_cmdCounterZero_5->setFont(font5);

        gridLayout_4->addWidget(pB_cmdCounterZero_5, 1, 0, 1, 1);

        pB_cmdCounterZero_4 = new QPushButton(frame_5);
        pB_cmdCounterZero_4->setObjectName(QString::fromUtf8("pB_cmdCounterZero_4"));
        sizePolicy.setHeightForWidth(pB_cmdCounterZero_4->sizePolicy().hasHeightForWidth());
        pB_cmdCounterZero_4->setSizePolicy(sizePolicy);
        pB_cmdCounterZero_4->setMinimumSize(QSize(0, 80));
        pB_cmdCounterZero_4->setFont(font5);

        gridLayout_4->addWidget(pB_cmdCounterZero_4, 1, 1, 1, 1);

        frame = new QFrame(QtPLCDialogClass);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(1250, 10, 847, 755));
        frame->setMinimumSize(QSize(847, 755));
        frame->setMaximumSize(QSize(847, 755));
        QFont font6;
        font6.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font6.setPointSize(20);
        font6.setBold(true);
        font6.setWeight(75);
        frame->setFont(font6);
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
        QFont font7;
        font7.setFamily(QString::fromUtf8("System"));
        font7.setPointSize(20);
        font7.setBold(true);
        font7.setWeight(75);
        groupBox_10->setFont(font7);
        groupBox_10->setStyleSheet(QString::fromUtf8(""));
        groupBox_10->setFlat(false);
        groupBox_10->setCheckable(false);
        frame_7 = new QFrame(groupBox_10);
        frame_7->setObjectName(QString::fromUtf8("frame_7"));
        frame_7->setGeometry(QRect(10, 37, 797, 521));
        QFont font8;
        font8.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font8.setPointSize(20);
        font8.setBold(false);
        font8.setWeight(50);
        frame_7->setFont(font8);
        frame_7->setFrameShape(QFrame::Box);
        frame_7->setFrameShadow(QFrame::Sunken);
        frame_7->setLineWidth(3);
        gridLayout_10 = new QGridLayout(frame_7);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        label_10 = new QLabel(frame_7);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setMinimumSize(QSize(140, 35));
        label_10->setMaximumSize(QSize(140, 35));
        label_10->setFont(font6);

        gridLayout_10->addWidget(label_10, 1, 0, 1, 1);

        frame_22 = new QFrame(frame_7);
        frame_22->setObjectName(QString::fromUtf8("frame_22"));
        frame_22->setStyleSheet(QString::fromUtf8("background-color: rgb(235, 235, 235);"));
        frame_22->setFrameShape(QFrame::Panel);
        frame_22->setFrameShadow(QFrame::Raised);
        frame_22->setLineWidth(3);
        verticalLayout_27 = new QVBoxLayout(frame_22);
        verticalLayout_27->setSpacing(6);
        verticalLayout_27->setContentsMargins(11, 11, 11, 11);
        verticalLayout_27->setObjectName(QString::fromUtf8("verticalLayout_27"));
        verticalLayout_27->setContentsMargins(0, 0, 0, 0);
        lE_MachineStep = new QLineEdit(frame_22);
        lE_MachineStep->setObjectName(QString::fromUtf8("lE_MachineStep"));
        lE_MachineStep->setEnabled(false);
        sizePolicy1.setHeightForWidth(lE_MachineStep->sizePolicy().hasHeightForWidth());
        lE_MachineStep->setSizePolicy(sizePolicy1);
        QFont font9;
        font9.setFamily(QString::fromUtf8("Arial Black"));
        font9.setPointSize(19);
        font9.setBold(true);
        font9.setWeight(75);
        lE_MachineStep->setFont(font9);
        lE_MachineStep->setStyleSheet(QString::fromUtf8(""));
        lE_MachineStep->setFrame(false);

        verticalLayout_27->addWidget(lE_MachineStep);


        gridLayout_10->addWidget(frame_22, 3, 6, 1, 1);

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
        lE_GroupIndex->setFont(font9);
        lE_GroupIndex->setStyleSheet(QString::fromUtf8(""));
        lE_GroupIndex->setFrame(false);

        verticalLayout_23->addWidget(lE_GroupIndex);


        gridLayout_10->addWidget(frame_19, 11, 6, 1, 1);

        label_48 = new QLabel(frame_7);
        label_48->setObjectName(QString::fromUtf8("label_48"));
        label_48->setMinimumSize(QSize(140, 35));
        label_48->setMaximumSize(QSize(140, 35));
        label_48->setFont(font6);

        gridLayout_10->addWidget(label_48, 5, 4, 1, 1);

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
        lE_ProdCount->setFont(font9);
        lE_ProdCount->setStyleSheet(QString::fromUtf8(""));
        lE_ProdCount->setFrame(false);

        verticalLayout_17->addWidget(lE_ProdCount);


        gridLayout_10->addWidget(frame_14, 3, 2, 1, 1);

        label_50 = new QLabel(frame_7);
        label_50->setObjectName(QString::fromUtf8("label_50"));
        label_50->setMinimumSize(QSize(140, 35));
        label_50->setMaximumSize(QSize(140, 35));
        label_50->setFont(font6);

        gridLayout_10->addWidget(label_50, 3, 4, 1, 1);

        verticalSpacer_13 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_10->addItem(verticalSpacer_13, 6, 2, 1, 1);

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
        lE_PassCount->setFont(font9);
        lE_PassCount->setStyleSheet(QString::fromUtf8(""));
        lE_PassCount->setFrame(false);

        verticalLayout_16->addWidget(lE_PassCount);


        gridLayout_10->addWidget(frame_13, 1, 2, 1, 1);

        label_79 = new QLabel(frame_7);
        label_79->setObjectName(QString::fromUtf8("label_79"));
        label_79->setMinimumSize(QSize(140, 35));
        label_79->setMaximumSize(QSize(140, 35));
        label_79->setFont(font1);

        gridLayout_10->addWidget(label_79, 7, 4, 1, 1);

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
        lE_Finished->setFont(font9);
        lE_Finished->setAutoFillBackground(false);
        lE_Finished->setStyleSheet(QString::fromUtf8(""));
        lE_Finished->setFrame(false);

        verticalLayout_8->addWidget(lE_Finished);


        gridLayout_10->addWidget(frame_3, 11, 2, 1, 1);

        label_17 = new QLabel(frame_7);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setMinimumSize(QSize(140, 35));
        label_17->setMaximumSize(QSize(140, 35));
        label_17->setFont(font6);

        gridLayout_10->addWidget(label_17, 1, 4, 1, 1);

        frame_21 = new QFrame(frame_7);
        frame_21->setObjectName(QString::fromUtf8("frame_21"));
        frame_21->setStyleSheet(QString::fromUtf8("background-color: rgb(235, 235, 235);"));
        frame_21->setFrameShape(QFrame::Panel);
        frame_21->setFrameShadow(QFrame::Raised);
        frame_21->setLineWidth(3);
        verticalLayout_24 = new QVBoxLayout(frame_21);
        verticalLayout_24->setSpacing(6);
        verticalLayout_24->setContentsMargins(11, 11, 11, 11);
        verticalLayout_24->setObjectName(QString::fromUtf8("verticalLayout_24"));
        verticalLayout_24->setContentsMargins(0, 0, 0, 0);
        lE_GroupNo = new QLineEdit(frame_21);
        lE_GroupNo->setObjectName(QString::fromUtf8("lE_GroupNo"));
        lE_GroupNo->setEnabled(false);
        sizePolicy1.setHeightForWidth(lE_GroupNo->sizePolicy().hasHeightForWidth());
        lE_GroupNo->setSizePolicy(sizePolicy1);
        lE_GroupNo->setFont(font9);
        lE_GroupNo->setStyleSheet(QString::fromUtf8(""));
        lE_GroupNo->setFrame(false);

        verticalLayout_24->addWidget(lE_GroupNo);


        gridLayout_10->addWidget(frame_21, 7, 6, 1, 1);

        label_18 = new QLabel(frame_7);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setMinimumSize(QSize(140, 35));
        label_18->setMaximumSize(QSize(140, 35));
        label_18->setFont(font6);

        gridLayout_10->addWidget(label_18, 11, 4, 1, 1);

        label_16 = new QLabel(frame_7);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setMinimumSize(QSize(140, 35));
        label_16->setMaximumSize(QSize(140, 35));
        label_16->setFont(font6);

        gridLayout_10->addWidget(label_16, 7, 0, 1, 1);

        verticalSpacer_16 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_10->addItem(verticalSpacer_16, 4, 2, 1, 1);

        verticalSpacer_12 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_10->addItem(verticalSpacer_12, 13, 2, 1, 1);

        verticalSpacer_14 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_10->addItem(verticalSpacer_14, 9, 2, 1, 1);

        label_39 = new QLabel(frame_7);
        label_39->setObjectName(QString::fromUtf8("label_39"));
        label_39->setMinimumSize(QSize(140, 35));
        label_39->setMaximumSize(QSize(140, 35));
        label_39->setFont(font6);

        gridLayout_10->addWidget(label_39, 3, 0, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_10->addItem(verticalSpacer_5, 0, 2, 1, 1);

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
        lE_ScaleResult->setFont(font9);
        lE_ScaleResult->setStyleSheet(QString::fromUtf8(""));
        lE_ScaleResult->setFrame(false);

        verticalLayout_19->addWidget(lE_ScaleResult);


        gridLayout_10->addWidget(frame_15, 7, 2, 1, 1);

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
        lE_TUCount->setFont(font9);
        lE_TUCount->setStyleSheet(QString::fromUtf8(""));
        lE_TUCount->setFrame(false);

        verticalLayout_21->addWidget(lE_TUCount);


        gridLayout_10->addWidget(frame_17, 5, 6, 1, 1);

        horizontalSpacer_19 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_19, 7, 5, 1, 1);

        verticalSpacer_15 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_10->addItem(verticalSpacer_15, 2, 2, 1, 1);

        label_15 = new QLabel(frame_7);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setMinimumSize(QSize(140, 35));
        label_15->setMaximumSize(QSize(140, 35));
        label_15->setFont(font6);

        gridLayout_10->addWidget(label_15, 11, 0, 1, 1);

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
        lE_TOCount->setFont(font9);
        lE_TOCount->setStyleSheet(QString::fromUtf8(""));
        lE_TOCount->setFrame(false);

        verticalLayout_18->addWidget(lE_TOCount);


        gridLayout_10->addWidget(frame_16, 5, 2, 1, 1);

        horizontalSpacer_18 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_18, 7, 1, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_10, 7, 3, 1, 1);

        label_49 = new QLabel(frame_7);
        label_49->setObjectName(QString::fromUtf8("label_49"));
        label_49->setMinimumSize(QSize(140, 35));
        label_49->setMaximumSize(QSize(140, 35));
        label_49->setFont(font6);

        gridLayout_10->addWidget(label_49, 5, 0, 1, 1);

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
        lE_RejectCount->setFont(font9);
        lE_RejectCount->setStyleSheet(QString::fromUtf8(""));
        lE_RejectCount->setFrame(false);
        lE_RejectCount->setEchoMode(QLineEdit::Normal);

        verticalLayout_20->addWidget(lE_RejectCount);


        gridLayout_10->addWidget(frame_12, 1, 6, 1, 1);

        frame_9 = new QFrame(groupBox_10);
        frame_9->setObjectName(QString::fromUtf8("frame_9"));
        frame_9->setGeometry(QRect(140, 565, 501, 151));
        frame_9->setFrameShape(QFrame::Box);
        frame_9->setFrameShadow(QFrame::Sunken);
        frame_9->setLineWidth(3);
        label_80 = new QLabel(frame_9);
        label_80->setObjectName(QString::fromUtf8("label_80"));
        label_80->setGeometry(QRect(16, 30, 140, 35));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_80->sizePolicy().hasHeightForWidth());
        label_80->setSizePolicy(sizePolicy3);
        label_80->setMinimumSize(QSize(140, 35));
        label_80->setMaximumSize(QSize(140, 35));
        label_80->setFont(font6);
        frame_10 = new QFrame(frame_9);
        frame_10->setObjectName(QString::fromUtf8("frame_10"));
        frame_10->setGeometry(QRect(164, 10, 291, 61));
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
        lE_SysOveride->setFont(font9);
        lE_SysOveride->setStyleSheet(QString::fromUtf8(""));
        lE_SysOveride->setFrame(false);

        verticalLayout_14->addWidget(lE_SysOveride);

        label_78 = new QLabel(frame_9);
        label_78->setObjectName(QString::fromUtf8("label_78"));
        label_78->setGeometry(QRect(16, 100, 140, 35));
        sizePolicy3.setHeightForWidth(label_78->sizePolicy().hasHeightForWidth());
        label_78->setSizePolicy(sizePolicy3);
        label_78->setMinimumSize(QSize(140, 35));
        label_78->setMaximumSize(QSize(140, 35));
        label_78->setFont(font6);
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
        lE_BatchName->setFont(font9);
        lE_BatchName->setStyleSheet(QString::fromUtf8(""));
        lE_BatchName->setFrame(false);

        verticalLayout_15->addWidget(lE_BatchName);

        label_81 = new QLabel(frame_9);
        label_81->setObjectName(QString::fromUtf8("label_81"));
        label_81->setGeometry(QRect(460, 30, 20, 35));
        sizePolicy3.setHeightForWidth(label_81->sizePolicy().hasHeightForWidth());
        label_81->setSizePolicy(sizePolicy3);
        label_81->setMinimumSize(QSize(20, 35));
        label_81->setMaximumSize(QSize(20, 35));
        label_81->setFont(font6);
        lb_logo = new QLabel(groupBox_10);
        lb_logo->setObjectName(QString::fromUtf8("lb_logo"));
        lb_logo->setGeometry(QRect(5, 580, 130, 130));
        sizePolicy3.setHeightForWidth(lb_logo->sizePolicy().hasHeightForWidth());
        lb_logo->setSizePolicy(sizePolicy3);
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
        lb_alm = new QLabel(frame_20);
        lb_alm->setObjectName(QString::fromUtf8("lb_alm"));
        lb_alm->setGeometry(QRect(10, 550, 351, 191));
        QFont font12;
        font12.setFamily(QString::fromUtf8("\351\224\220\345\255\227\347\234\237\350\250\200\344\275\223\345\205\215\350\264\271\345\225\206\347\224\250"));
        font12.setPointSize(19);
        font12.setBold(false);
        font12.setItalic(false);
        font12.setWeight(50);
        lb_alm->setFont(font12);
        lb_alm->setStyleSheet(QString::fromUtf8("background-color: rgb(217, 217, 0);\n"
"color: rgb(255, 32, 25);\n"
"font: 19pt \"\351\224\220\345\255\227\347\234\237\350\250\200\344\275\223\345\205\215\350\264\271\345\225\206\347\224\250\";"));
        lb_alm->setFrameShape(QFrame::Box);
        lb_alm->setFrameShadow(QFrame::Sunken);
        lb_alm->setLineWidth(6);
        lb_alm->setMidLineWidth(3);
        lb_alm->setScaledContents(false);
        widget = new QWidget(QtPLCDialogClass);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(2150, 10, 851, 581));
        QFont font13;
        font13.setPointSize(12);
        widget->setFont(font13);
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        layoutWidget_3 = new QWidget(widget);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(130, 10, 711, 71));
        gridLayout_13 = new QGridLayout(layoutWidget_3);
        gridLayout_13->setSpacing(6);
        gridLayout_13->setContentsMargins(11, 11, 11, 11);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        gridLayout_13->setContentsMargins(0, 0, 0, 0);
        lE_GroupMax = new QLineEdit(layoutWidget_3);
        lE_GroupMax->setObjectName(QString::fromUtf8("lE_GroupMax"));
        lE_GroupMax->setEnabled(false);
        QFont font14;
        font14.setFamily(QString::fromUtf8("\345\271\274\345\234\206"));
        font14.setPointSize(12);
        lE_GroupMax->setFont(font14);

        gridLayout_13->addWidget(lE_GroupMax, 1, 1, 1, 1);

        lE_GroupMinRatio = new QLineEdit(layoutWidget_3);
        lE_GroupMinRatio->setObjectName(QString::fromUtf8("lE_GroupMinRatio"));
        lE_GroupMinRatio->setEnabled(false);
        lE_GroupMinRatio->setFont(font14);

        gridLayout_13->addWidget(lE_GroupMinRatio, 1, 10, 1, 1);

        label_8 = new QLabel(layoutWidget_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font14);

        gridLayout_13->addWidget(label_8, 1, 6, 1, 1);

        label_29 = new QLabel(layoutWidget_3);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setFont(font14);

        gridLayout_13->addWidget(label_29, 1, 9, 1, 1);

        label_6 = new QLabel(layoutWidget_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font14);

        gridLayout_13->addWidget(label_6, 1, 0, 1, 1);

        lE_GroupMin = new QLineEdit(layoutWidget_3);
        lE_GroupMin->setObjectName(QString::fromUtf8("lE_GroupMin"));
        lE_GroupMin->setEnabled(false);
        lE_GroupMin->setFont(font14);

        gridLayout_13->addWidget(lE_GroupMin, 1, 7, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_13->addItem(horizontalSpacer_8, 1, 5, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_13->addItem(horizontalSpacer_9, 1, 2, 1, 1);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_13->addItem(horizontalSpacer_12, 1, 8, 1, 1);

        label_34 = new QLabel(layoutWidget_3);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        label_34->setFont(font14);

        gridLayout_13->addWidget(label_34, 1, 3, 1, 1);

        lE_GroupMaxRatio = new QLineEdit(layoutWidget_3);
        lE_GroupMaxRatio->setObjectName(QString::fromUtf8("lE_GroupMaxRatio"));
        lE_GroupMaxRatio->setEnabled(false);
        lE_GroupMaxRatio->setFont(font14);

        gridLayout_13->addWidget(lE_GroupMaxRatio, 1, 4, 1, 1);

        lE_GroupAvg = new QLineEdit(layoutWidget_3);
        lE_GroupAvg->setObjectName(QString::fromUtf8("lE_GroupAvg"));
        lE_GroupAvg->setEnabled(false);
        lE_GroupAvg->setFont(font14);

        gridLayout_13->addWidget(lE_GroupAvg, 0, 10, 1, 1);

        label_7 = new QLabel(layoutWidget_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font14);

        gridLayout_13->addWidget(label_7, 0, 9, 1, 1);

        lE_GroupSum = new QLineEdit(layoutWidget_3);
        lE_GroupSum->setObjectName(QString::fromUtf8("lE_GroupSum"));
        lE_GroupSum->setEnabled(false);
        lE_GroupSum->setFont(font14);

        gridLayout_13->addWidget(lE_GroupSum, 0, 7, 1, 1);

        label_3 = new QLabel(layoutWidget_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font14);

        gridLayout_13->addWidget(label_3, 0, 6, 1, 1);

        lE_GroupIndex_2 = new QLineEdit(layoutWidget_3);
        lE_GroupIndex_2->setObjectName(QString::fromUtf8("lE_GroupIndex_2"));
        lE_GroupIndex_2->setEnabled(false);
        lE_GroupIndex_2->setFont(font14);

        gridLayout_13->addWidget(lE_GroupIndex_2, 0, 4, 1, 1);

        label = new QLabel(layoutWidget_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font14);

        gridLayout_13->addWidget(label, 0, 3, 1, 1);

        lE_GroupNo_2 = new QLineEdit(layoutWidget_3);
        lE_GroupNo_2->setObjectName(QString::fromUtf8("lE_GroupNo_2"));
        lE_GroupNo_2->setEnabled(false);
        lE_GroupNo_2->setFont(font14);

        gridLayout_13->addWidget(lE_GroupNo_2, 0, 1, 1, 1);

        label_9 = new QLabel(layoutWidget_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font14);

        gridLayout_13->addWidget(label_9, 0, 0, 1, 1);

        tableWidget = new QTableWidget(widget);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(10, 10, 111, 561));
        QFont font15;
        font15.setFamily(QString::fromUtf8("\345\271\274\345\234\206"));
        font15.setPointSize(12);
        font15.setBold(false);
        font15.setItalic(false);
        font15.setWeight(50);
        tableWidget->setFont(font15);
        tableWidget->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\271\274\345\234\206\";"));
        gridLayoutWidget = new QWidget(widget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(120, 270, 721, 311));
        gridLayout_One = new QGridLayout(gridLayoutWidget);
        gridLayout_One->setSpacing(6);
        gridLayout_One->setContentsMargins(11, 11, 11, 11);
        gridLayout_One->setObjectName(QString::fromUtf8("gridLayout_One"));
        gridLayout_One->setContentsMargins(0, 0, 0, 0);
        groupBox_11 = new QGroupBox(widget);
        groupBox_11->setObjectName(QString::fromUtf8("groupBox_11"));
        groupBox_11->setGeometry(QRect(130, 90, 711, 181));
        groupBox_11->setFont(font14);
        gridLayout_14 = new QGridLayout(groupBox_11);
        gridLayout_14->setSpacing(6);
        gridLayout_14->setContentsMargins(11, 11, 11, 11);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        pB_printCurve = new QPushButton(groupBox_11);
        pB_printCurve->setObjectName(QString::fromUtf8("pB_printCurve"));
        pB_printCurve->setMinimumSize(QSize(0, 40));
        pB_printCurve->setMaximumSize(QSize(16777215, 40));
        pB_printCurve->setFont(font14);

        gridLayout_14->addWidget(pB_printCurve, 2, 4, 1, 1);

        label_37 = new QLabel(groupBox_11);
        label_37->setObjectName(QString::fromUtf8("label_37"));
        label_37->setFont(font14);

        gridLayout_14->addWidget(label_37, 0, 2, 1, 1);

        label_23 = new QLabel(groupBox_11);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setFont(font14);

        gridLayout_14->addWidget(label_23, 2, 2, 1, 1);

        pB_startSearch = new QPushButton(groupBox_11);
        pB_startSearch->setObjectName(QString::fromUtf8("pB_startSearch"));
        pB_startSearch->setMinimumSize(QSize(0, 40));
        pB_startSearch->setMaximumSize(QSize(16777215, 40));
        pB_startSearch->setFont(font14);

        gridLayout_14->addWidget(pB_startSearch, 0, 4, 1, 1);

        label_36 = new QLabel(groupBox_11);
        label_36->setObjectName(QString::fromUtf8("label_36"));
        label_36->setFont(font14);

        gridLayout_14->addWidget(label_36, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lE_year2 = new QLineEdit(groupBox_11);
        lE_year2->setObjectName(QString::fromUtf8("lE_year2"));
        lE_year2->setEnabled(false);
        sizePolicy3.setHeightForWidth(lE_year2->sizePolicy().hasHeightForWidth());
        lE_year2->setSizePolicy(sizePolicy3);
        lE_year2->setMinimumSize(QSize(50, 0));
        lE_year2->setMaximumSize(QSize(50, 16777215));
        lE_year2->setFont(font14);
        lE_year2->setMaxLength(4);
        lE_year2->setFrame(true);

        horizontalLayout_3->addWidget(lE_year2);

        label_51 = new QLabel(groupBox_11);
        label_51->setObjectName(QString::fromUtf8("label_51"));
        label_51->setFont(font14);

        horizontalLayout_3->addWidget(label_51);

        lE_month2 = new QLineEdit(groupBox_11);
        lE_month2->setObjectName(QString::fromUtf8("lE_month2"));
        lE_month2->setEnabled(false);
        sizePolicy3.setHeightForWidth(lE_month2->sizePolicy().hasHeightForWidth());
        lE_month2->setSizePolicy(sizePolicy3);
        lE_month2->setMinimumSize(QSize(25, 0));
        lE_month2->setMaximumSize(QSize(25, 16777215));
        lE_month2->setFont(font14);
        lE_month2->setMaxLength(2);
        lE_month2->setFrame(true);

        horizontalLayout_3->addWidget(lE_month2);

        label_55 = new QLabel(groupBox_11);
        label_55->setObjectName(QString::fromUtf8("label_55"));
        label_55->setFont(font14);

        horizontalLayout_3->addWidget(label_55);

        lE_day2 = new QLineEdit(groupBox_11);
        lE_day2->setObjectName(QString::fromUtf8("lE_day2"));
        lE_day2->setEnabled(false);
        sizePolicy3.setHeightForWidth(lE_day2->sizePolicy().hasHeightForWidth());
        lE_day2->setSizePolicy(sizePolicy3);
        lE_day2->setMinimumSize(QSize(25, 0));
        lE_day2->setMaximumSize(QSize(25, 16777215));
        lE_day2->setFont(font14);
        lE_day2->setMaxLength(2);
        lE_day2->setFrame(true);

        horizontalLayout_3->addWidget(lE_day2);

        label_59 = new QLabel(groupBox_11);
        label_59->setObjectName(QString::fromUtf8("label_59"));
        label_59->setFont(font14);

        horizontalLayout_3->addWidget(label_59);

        lE_hour2 = new QLineEdit(groupBox_11);
        lE_hour2->setObjectName(QString::fromUtf8("lE_hour2"));
        lE_hour2->setEnabled(true);
        sizePolicy3.setHeightForWidth(lE_hour2->sizePolicy().hasHeightForWidth());
        lE_hour2->setSizePolicy(sizePolicy3);
        lE_hour2->setMinimumSize(QSize(25, 0));
        lE_hour2->setMaximumSize(QSize(25, 16777215));
        lE_hour2->setFont(font14);
        lE_hour2->setMaxLength(2);
        lE_hour2->setFrame(true);

        horizontalLayout_3->addWidget(lE_hour2);

        label_60 = new QLabel(groupBox_11);
        label_60->setObjectName(QString::fromUtf8("label_60"));
        label_60->setFont(font14);

        horizontalLayout_3->addWidget(label_60);

        lE_minute2 = new QLineEdit(groupBox_11);
        lE_minute2->setObjectName(QString::fromUtf8("lE_minute2"));
        lE_minute2->setEnabled(true);
        sizePolicy3.setHeightForWidth(lE_minute2->sizePolicy().hasHeightForWidth());
        lE_minute2->setSizePolicy(sizePolicy3);
        lE_minute2->setMinimumSize(QSize(25, 0));
        lE_minute2->setMaximumSize(QSize(25, 16777215));
        lE_minute2->setFont(font14);
        lE_minute2->setMaxLength(2);
        lE_minute2->setFrame(true);

        horizontalLayout_3->addWidget(lE_minute2);


        gridLayout_14->addLayout(horizontalLayout_3, 0, 3, 1, 1);

        label_35 = new QLabel(groupBox_11);
        label_35->setObjectName(QString::fromUtf8("label_35"));
        label_35->setFont(font14);

        gridLayout_14->addWidget(label_35, 2, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lE_year1 = new QLineEdit(groupBox_11);
        lE_year1->setObjectName(QString::fromUtf8("lE_year1"));
        lE_year1->setEnabled(true);
        sizePolicy3.setHeightForWidth(lE_year1->sizePolicy().hasHeightForWidth());
        lE_year1->setSizePolicy(sizePolicy3);
        lE_year1->setMinimumSize(QSize(50, 0));
        lE_year1->setMaximumSize(QSize(50, 16777215));
        lE_year1->setFont(font14);
        lE_year1->setMaxLength(4);
        lE_year1->setFrame(true);

        horizontalLayout_2->addWidget(lE_year1);

        label_38 = new QLabel(groupBox_11);
        label_38->setObjectName(QString::fromUtf8("label_38"));
        label_38->setFont(font14);

        horizontalLayout_2->addWidget(label_38);

        lE_month1 = new QLineEdit(groupBox_11);
        lE_month1->setObjectName(QString::fromUtf8("lE_month1"));
        lE_month1->setEnabled(true);
        sizePolicy3.setHeightForWidth(lE_month1->sizePolicy().hasHeightForWidth());
        lE_month1->setSizePolicy(sizePolicy3);
        lE_month1->setMinimumSize(QSize(25, 0));
        lE_month1->setMaximumSize(QSize(25, 16777215));
        lE_month1->setFont(font14);
        lE_month1->setMaxLength(2);
        lE_month1->setFrame(true);

        horizontalLayout_2->addWidget(lE_month1);

        label_43 = new QLabel(groupBox_11);
        label_43->setObjectName(QString::fromUtf8("label_43"));
        label_43->setFont(font14);

        horizontalLayout_2->addWidget(label_43);

        lE_day1 = new QLineEdit(groupBox_11);
        lE_day1->setObjectName(QString::fromUtf8("lE_day1"));
        lE_day1->setEnabled(true);
        sizePolicy3.setHeightForWidth(lE_day1->sizePolicy().hasHeightForWidth());
        lE_day1->setSizePolicy(sizePolicy3);
        lE_day1->setMinimumSize(QSize(25, 0));
        lE_day1->setMaximumSize(QSize(25, 16777215));
        lE_day1->setFont(font14);
        lE_day1->setMaxLength(2);
        lE_day1->setFrame(true);

        horizontalLayout_2->addWidget(lE_day1);

        label_47 = new QLabel(groupBox_11);
        label_47->setObjectName(QString::fromUtf8("label_47"));
        label_47->setFont(font14);

        horizontalLayout_2->addWidget(label_47);

        lE_hour1 = new QLineEdit(groupBox_11);
        lE_hour1->setObjectName(QString::fromUtf8("lE_hour1"));
        lE_hour1->setEnabled(true);
        sizePolicy3.setHeightForWidth(lE_hour1->sizePolicy().hasHeightForWidth());
        lE_hour1->setSizePolicy(sizePolicy3);
        lE_hour1->setMinimumSize(QSize(25, 0));
        lE_hour1->setMaximumSize(QSize(25, 16777215));
        lE_hour1->setFont(font14);
        lE_hour1->setMaxLength(2);
        lE_hour1->setFrame(true);

        horizontalLayout_2->addWidget(lE_hour1);

        label_45 = new QLabel(groupBox_11);
        label_45->setObjectName(QString::fromUtf8("label_45"));
        label_45->setFont(font14);

        horizontalLayout_2->addWidget(label_45);

        lE_minute1 = new QLineEdit(groupBox_11);
        lE_minute1->setObjectName(QString::fromUtf8("lE_minute1"));
        lE_minute1->setEnabled(true);
        sizePolicy3.setHeightForWidth(lE_minute1->sizePolicy().hasHeightForWidth());
        lE_minute1->setSizePolicy(sizePolicy3);
        lE_minute1->setMinimumSize(QSize(25, 0));
        lE_minute1->setMaximumSize(QSize(25, 16777215));
        lE_minute1->setFont(font14);
        lE_minute1->setMaxLength(2);
        lE_minute1->setFrame(true);

        horizontalLayout_2->addWidget(lE_minute1);


        gridLayout_14->addLayout(horizontalLayout_2, 0, 1, 1, 1);

        lE_print1 = new QLineEdit(groupBox_11);
        lE_print1->setObjectName(QString::fromUtf8("lE_print1"));
        lE_print1->setEnabled(true);
        lE_print1->setFont(font14);

        gridLayout_14->addWidget(lE_print1, 2, 1, 1, 1);

        pB_printData = new QPushButton(groupBox_11);
        pB_printData->setObjectName(QString::fromUtf8("pB_printData"));
        pB_printData->setMinimumSize(QSize(0, 40));
        pB_printData->setMaximumSize(QSize(16777215, 40));
        pB_printData->setFont(font14);

        gridLayout_14->addWidget(pB_printData, 2, 5, 1, 1);

        pB_printData_2 = new QPushButton(groupBox_11);
        pB_printData_2->setObjectName(QString::fromUtf8("pB_printData_2"));
        pB_printData_2->setMinimumSize(QSize(0, 40));
        pB_printData_2->setMaximumSize(QSize(16777215, 40));
        pB_printData_2->setFont(font14);

        gridLayout_14->addWidget(pB_printData_2, 0, 5, 1, 1);

        lE_print2 = new QLineEdit(groupBox_11);
        lE_print2->setObjectName(QString::fromUtf8("lE_print2"));
        lE_print2->setEnabled(true);
        lE_print2->setFont(font14);

        gridLayout_14->addWidget(lE_print2, 2, 3, 1, 1);

        label_61 = new QLabel(groupBox_11);
        label_61->setObjectName(QString::fromUtf8("label_61"));
        label_61->setFont(font14);

        gridLayout_14->addWidget(label_61, 1, 0, 1, 1);

        lb_searchResult = new QLabel(groupBox_11);
        lb_searchResult->setObjectName(QString::fromUtf8("lb_searchResult"));
        lb_searchResult->setFont(font14);

        gridLayout_14->addWidget(lb_searchResult, 1, 1, 1, 1);

        pB_copyIn = new QPushButton(groupBox_11);
        pB_copyIn->setObjectName(QString::fromUtf8("pB_copyIn"));
        pB_copyIn->setMinimumSize(QSize(0, 40));
        pB_copyIn->setMaximumSize(QSize(16777215, 40));
        pB_copyIn->setFont(font14);

        gridLayout_14->addWidget(pB_copyIn, 1, 3, 1, 1);

        layoutWidget_3->raise();
        gridLayoutWidget->raise();
        tableWidget->raise();
        groupBox_11->raise();

        retranslateUi(QtPLCDialogClass);

        tabWidget_PLC->setCurrentIndex(2);
        tabWidget->setCurrentIndex(2);
        cB_Feedmode->setCurrentIndex(0);
        tabWidget_Users->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(QtPLCDialogClass);
    } // setupUi

    void retranslateUi(QDialog *QtPLCDialogClass)
    {
        QtPLCDialogClass->setWindowTitle(QCoreApplication::translate("QtPLCDialogClass", "QtPLCDialogClass", nullptr));
        groupBox->setTitle(QCoreApplication::translate("QtPLCDialogClass", "DI", nullptr));
        label_40->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\203\266\345\233\212\344\270\213\350\220\275\346\243\200\346\265\213", nullptr));
        label_46->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\203\266\345\233\212\344\270\213\350\220\275\346\243\200\346\265\2131", nullptr));
        lb_00->setText(QString());
        lb_10->setText(QString());
        label_11->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\221\206\350\207\202\344\275\215\347\275\256\346\243\200\346\265\213", nullptr));
        lb_20->setText(QString());
        groupBox_7->setTitle(QCoreApplication::translate("QtPLCDialogClass", "DO", nullptr));
        pb_cmdReject->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\216\222\345\272\237\347\224\265\347\243\201\351\223\201", nullptr));
        pb_cmdChannelSwith->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\203\266\345\233\212\351\200\232\351\201\223\345\210\207\346\215\242", nullptr));
        pb_cmdVaccum->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\234\237\347\251\272\345\217\221\347\224\237\345\231\250", nullptr));
        pb_cmdCapGet->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\217\226\346\226\231\347\224\265\347\243\201\351\223\201", nullptr));
        pb_cmdCapGetValve->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\217\226\346\226\231\347\224\265\347\243\201\351\230\200", nullptr));
        pb_cmdCapBackValve->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\233\236\346\226\231\347\224\265\347\243\201\351\230\200", nullptr));
        pb_cmdAlarmOut->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\212\245\350\255\246\350\234\202\351\270\243\345\231\250", nullptr));
        pb_cmdStopSignal->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\201\234\346\234\272\344\277\241\345\217\267", nullptr));
        pb_cmdAlarmSignal->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\212\245\350\255\246\350\276\223\345\207\272", nullptr));
        pb_cmdYellowAlarmout->setText(QCoreApplication::translate("QtPLCDialogClass", "\351\273\204\347\201\257\346\212\245\350\255\246", nullptr));
        pb_cmdBaffle->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\214\241    \346\235\277", nullptr));
        groupBox_8->setTitle(QCoreApplication::translate("QtPLCDialogClass", "AO", nullptr));
        label_2->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\250\241\346\213\237\351\207\217\350\276\223\345\207\272", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QString());
        groupBox_2->setTitle(QCoreApplication::translate("QtPLCDialogClass", "\344\270\213\346\226\231", nullptr));
        pB_cmdAxisFeedPosMov->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\255\243\345\220\221\350\277\236\347\273\255\350\277\220\345\212\250", nullptr));
        pB_cmdFeedSingle->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\215\225\347\262\222\344\270\213\346\226\231", nullptr));
        pB_cmdAxisFeedStopMov->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\201\234\346\255\242\350\277\220\345\212\250", nullptr));
        pB_cmdAxisFeedJogNeg->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\217\215\350\275\254\347\202\271\345\212\250", nullptr));
        pB_cmdFeedSingleStop->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\215\225\347\262\222\344\270\213\346\226\231\345\201\234\346\255\242", nullptr));
        pB_cmdAxisFeedJogPos->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\255\243\350\275\254\347\202\271\345\212\250", nullptr));
        label_22->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\233\270\345\257\271\350\277\220\345\212\250\350\267\235\347\246\273", nullptr));
        lE_AxisFeedRelMovDistance->setText(QCoreApplication::translate("QtPLCDialogClass", "0", nullptr));
        pB_cmdAxisFeedRelMov->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\233\270\345\257\271\350\277\220\345\212\250", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("QtPLCDialogClass", "\346\227\213\350\275\254", nullptr));
        pB_cmdAxisSwingJogPos->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\255\243\350\275\254\347\202\271\345\212\250", nullptr));
        pB_cmdAxisSwingJogNeg->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\217\215\350\275\254\347\202\271\345\212\250", nullptr));
        pB_cmdAxisSwingStopMov->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\201\234\346\255\242\350\277\220\345\212\250", nullptr));
        pB_cmdAxisSwingPosMov->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\255\243\345\220\221\350\277\236\347\273\255\350\277\220\345\212\250", nullptr));
        pB_cmdSwing->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\227\213\350\275\254\345\215\225\345\267\245\344\275\215", nullptr));
        label_28->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\233\270\345\257\271\350\277\220\345\212\250\350\267\235\347\246\273", nullptr));
        pB_cmdAxisSwingRelMov->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\233\270\345\257\271\350\277\220\345\212\250", nullptr));
        lE_AxisSwingRelMovDistance->setText(QCoreApplication::translate("QtPLCDialogClass", "0", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QString());
        groupBox_9->setTitle(QCoreApplication::translate("QtPLCDialogClass", "\344\270\213\346\226\231", nullptr));
        pB_cmdFeedFive->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\203\266\345\233\212\350\220\275\346\226\231\345\244\232\347\262\222", nullptr));
        label_62->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\220\275\345\244\232\347\262\222\346\225\260", nullptr));
        pB_cmdFeedshakelevel->setText(QCoreApplication::translate("QtPLCDialogClass", "\344\270\213\346\226\231\346\221\207\346\221\206\346\260\264\345\271\263", nullptr));
        pB_cmdFeedhome->setText(QCoreApplication::translate("QtPLCDialogClass", "\344\270\213\346\226\231\345\257\273\345\217\202", nullptr));
        label_30->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\211\207\345\211\202\346\221\206\345\212\250\350\267\235\347\246\273", nullptr));
        lE_MultiCount->setText(QCoreApplication::translate("QtPLCDialogClass", "0", nullptr));
        pB_cmdFeedShake->setText(QCoreApplication::translate("QtPLCDialogClass", "\344\270\213\346\226\231\346\221\207\346\221\206", nullptr));
        pB_cmdFeedshakestop->setText(QCoreApplication::translate("QtPLCDialogClass", "\344\270\213\346\226\231\346\221\207\346\221\206\345\201\234\346\255\242", nullptr));
        lE_FeedOveride->setText(QCoreApplication::translate("QtPLCDialogClass", "0", nullptr));
        lE_Feed_shakeoffset->setText(QCoreApplication::translate("QtPLCDialogClass", "0", nullptr));
        pB_cmdFeedShakefive->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\211\207\345\211\202\350\220\275\346\226\231\345\244\232\347\262\222", nullptr));
        label_57->setText(QCoreApplication::translate("QtPLCDialogClass", "\344\270\213\346\226\231\351\200\237\345\272\246", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("QtPLCDialogClass", "\347\247\260\351\207\215\350\256\276\347\275\256", nullptr));
        pB_cmdScaleTire->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\247\244\346\270\205\351\233\266", nullptr));
        pB_cmdScaleCalibExt->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\247\244\345\244\226\351\203\250\346\240\241\346\255\243", nullptr));
        pB_showPrt->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\211\223\345\215\260\350\256\276\347\275\256", nullptr));
        pB_cmdAlogtest->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\250\241\346\213\237\350\276\223\345\207\272\346\265\213\350\257\225", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QString());
        tabWidget_PLC->setTabText(tabWidget_PLC->indexOf(tab_PLC_Control), QString());
        pB_Read1->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\257\273\345\217\226", nullptr));
        pB_Write1->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\206\231\345\205\245", nullptr));
        label_31->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\201\234\346\255\242\344\275\215\347\275\2562 mm", nullptr));
        label_41->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\257\273\346\225\260\345\273\266\350\277\237\346\227\266\351\227\264s", nullptr));
        lE_FeedTimeOut->setText(QCoreApplication::translate("QtPLCDialogClass", "0", nullptr));
        lE_CapBackInterval->setText(QCoreApplication::translate("QtPLCDialogClass", "0.00", nullptr));
        label_5->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\210\220\345\223\201\350\277\224\350\277\230\345\221\250\346\234\237s", nullptr));
        lE_ReadDelay->setText(QCoreApplication::translate("QtPLCDialogClass", "0.00", nullptr));
        label_4->setText(QCoreApplication::translate("QtPLCDialogClass", "\344\270\213\346\226\231\350\266\205\346\227\266\346\227\266\351\227\264s", nullptr));
        lE_s_trg_stop1->setText(QCoreApplication::translate("QtPLCDialogClass", "0", nullptr));
        lE_s_trg_stop0->setText(QCoreApplication::translate("QtPLCDialogClass", "0", nullptr));
        label_26->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\201\234\346\255\242\344\275\215\347\275\2561 mm", nullptr));
        label_25->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\207\252\345\212\250\345\217\226\346\226\231\345\221\250\346\234\237s", nullptr));
        lE_CapPickInterval->setText(QCoreApplication::translate("QtPLCDialogClass", "0.00", nullptr));
        label_32->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\216\273\347\232\256\345\273\266\350\277\237\346\227\266\351\227\264s", nullptr));
        lE_TireDelay->setText(QCoreApplication::translate("QtPLCDialogClass", "0.00", nullptr));
        label_42->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\216\273\347\232\256\347\255\211\345\276\205\346\227\266\351\227\264s", nullptr));
        lE_TireWaitTime->setText(QCoreApplication::translate("QtPLCDialogClass", "0.00", nullptr));
        lE_StopSignalDelay->setText(QCoreApplication::translate("QtPLCDialogClass", "0", nullptr));
        label_44->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\277\236\347\273\255\350\266\205\351\231\220\345\201\234\346\234\272\346\225\260", nullptr));
        tabWidget_PLC->setTabText(tabWidget_PLC->indexOf(tab_8), QString());
        label_58->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\243\200\346\265\213\347\211\251", nullptr));
        label_53->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\266\205\351\207\215\351\207\215\351\207\217(g)", nullptr));
        lE_TestInterval->setText(QCoreApplication::translate("QtPLCDialogClass", "0", nullptr));
        cB_Feedmode->setItemText(0, QCoreApplication::translate("QtPLCDialogClass", "\350\203\266\345\233\212", nullptr));
        cB_Feedmode->setItemText(1, QCoreApplication::translate("QtPLCDialogClass", "\347\211\207\345\211\202", nullptr));

        lE_GroupSet->setText(QCoreApplication::translate("QtPLCDialogClass", "0", nullptr));
        lE_TDemand->setText(QCoreApplication::translate("QtPLCDialogClass", "0.000", nullptr));
        lE_TUnderload->setText(QCoreApplication::translate("QtPLCDialogClass", "0.000", nullptr));
        label_14->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\234\237\346\234\233\351\207\215\351\207\217(g)", nullptr));
        lE_TOverload->setText(QCoreApplication::translate("QtPLCDialogClass", "0.000", nullptr));
        lE_InterUnderLoad->setText(QCoreApplication::translate("QtPLCDialogClass", "0.000", nullptr));
        label_52->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\257\217\347\273\204\346\225\260\351\207\217", nullptr));
        label_12->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\206\205\346\216\247\344\270\213\351\231\220(g)", nullptr));
        label_54->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\266\205\350\275\273\351\207\215\351\207\217(g)", nullptr));
        label_56->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\265\213\350\257\225\351\227\264\351\232\224(s)", nullptr));
        label_13->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\206\205\346\216\247\344\270\212\351\231\220(g)", nullptr));
        lE_InterOverLoad->setText(QCoreApplication::translate("QtPLCDialogClass", "0.000", nullptr));
        pB_Read2->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\257\273\345\217\226", nullptr));
        pB_Write2->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\206\231\345\205\245", nullptr));
        tabWidget_PLC->setTabText(tabWidget_PLC->indexOf(tab_2), QString());
        groupBox_4->setTitle(QCoreApplication::translate("QtPLCDialogClass", "\344\270\213\346\226\231\347\224\265\346\234\272", nullptr));
        label_21->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\212\266\346\200\201\346\234\272\346\255\245\351\252\244", nullptr));
        label_19->setText(QCoreApplication::translate("QtPLCDialogClass", "\351\224\231\350\257\257\344\273\243\347\240\201", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("QtPLCDialogClass", "\346\227\213\350\275\254\347\224\265\346\234\272", nullptr));
        label_24->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\212\266\346\200\201\346\234\272\346\255\245\351\252\244", nullptr));
        label_27->setText(QCoreApplication::translate("QtPLCDialogClass", "\351\224\231\350\257\257\344\273\243\347\240\201", nullptr));
        label_20->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\212\245\350\255\246\347\212\266\346\200\201", nullptr));
        label_33->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\265\213\351\207\217\345\256\236\351\231\205\351\227\264\351\232\224", nullptr));
        tabWidget_PLC->setTabText(tabWidget_PLC->indexOf(tab_3), QString());
        gB_User->setTitle(QCoreApplication::translate("QtPLCDialogClass", "\346\267\273\345\212\240\350\207\252\345\256\232\344\271\211\347\224\250\346\210\267", nullptr));
        label_65->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\256\276\347\275\256\347\224\250\346\210\267\345\220\215\347\247\260\357\274\232", nullptr));
        lE_SetUserName->setText(QString());
        lE_SetUserName->setPlaceholderText(QCoreApplication::translate("QtPLCDialogClass", "[a-zA-Z0-9_]+$", nullptr));
        label_66->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\256\276\347\275\256\347\224\250\346\210\267\346\235\203\351\231\220\357\274\232", nullptr));
        cB_SetUserPermission->setItemText(0, QCoreApplication::translate("QtPLCDialogClass", "\347\256\241\347\220\206\345\221\230\357\274\2320", nullptr));
        cB_SetUserPermission->setItemText(1, QCoreApplication::translate("QtPLCDialogClass", "\345\267\245\347\250\213\345\270\210\357\274\2321", nullptr));
        cB_SetUserPermission->setItemText(2, QCoreApplication::translate("QtPLCDialogClass", "\346\223\215\344\275\234\345\221\230\357\274\2322", nullptr));
        cB_SetUserPermission->setItemText(3, QCoreApplication::translate("QtPLCDialogClass", "\344\273\243\347\240\201\344\272\272\345\221\230\357\274\2323", nullptr));

        label_67->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\256\276\347\275\256\345\257\206\347\240\201\357\274\232", nullptr));
        lE_SetUserSecretNum->setPlaceholderText(QCoreApplication::translate("QtPLCDialogClass", "[0-9]+$", nullptr));
        pB_AddUser->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\267\273\345\212\240", nullptr));
        label_68->setStyleSheet(QCoreApplication::translate("QtPLCDialogClass", "font: 18pt \"\345\271\274\345\234\206\";", nullptr));
        label_68->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\235\203\351\231\220\345\220\215\347\247\260\357\274\232", nullptr));
        cB_Users->setItemText(0, QCoreApplication::translate("QtPLCDialogClass", "\347\256\241\347\220\206\345\221\230", nullptr));
        cB_Users->setItemText(1, QCoreApplication::translate("QtPLCDialogClass", "\345\267\245\347\250\213\345\270\210", nullptr));
        cB_Users->setItemText(2, QCoreApplication::translate("QtPLCDialogClass", "\346\223\215\344\275\234\345\221\230", nullptr));
        cB_Users->setItemText(3, QCoreApplication::translate("QtPLCDialogClass", "\344\273\243\347\240\201\344\272\272\345\221\230", nullptr));

        label_69->setStyleSheet(QCoreApplication::translate("QtPLCDialogClass", "font: 18pt \"\345\271\274\345\234\206\";", nullptr));
        label_69->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\235\203\351\231\220\346\217\217\350\277\260\357\274\232", nullptr));
        pB_Users_Delete->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\210\240\351\231\244", nullptr));
        tabWidget_PLC->setTabText(tabWidget_PLC->indexOf(tab_5), QString());
        pb_cmdParaSave->setText(QCoreApplication::translate("QtPLCDialogClass", "\344\277\235\345\255\230", nullptr));
        pB_cmdCounterZero_2->setText(QCoreApplication::translate("QtPLCDialogClass", "PLC\347\233\221\346\216\247", nullptr));
        pB_cmdCounterZero_3->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\263\273\347\273\237\345\217\202\346\225\260", nullptr));
        pB_cmdCounterZero_5->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\277\220\350\241\214\347\212\266\346\200\201", nullptr));
        pB_cmdCounterZero_4->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\277\220\350\241\214\345\217\202\346\225\260", nullptr));
        groupBox_10->setTitle(QCoreApplication::translate("QtPLCDialogClass", "          .                          ", nullptr));
        label_10->setText(QCoreApplication::translate("QtPLCDialogClass", "\351\200\232\350\277\207\350\256\241\346\225\260", nullptr));
        lE_MachineStep->setText(QCoreApplication::translate("QtPLCDialogClass", "0", nullptr));
        lE_GroupIndex->setText(QCoreApplication::translate("QtPLCDialogClass", "0", nullptr));
        label_48->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\277\207\350\275\273\350\256\241\346\225\260", nullptr));
        lE_ProdCount->setText(QCoreApplication::translate("QtPLCDialogClass", "0", nullptr));
        label_50->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\255\245\351\252\244", nullptr));
        lE_PassCount->setText(QCoreApplication::translate("QtPLCDialogClass", "0", nullptr));
        label_79->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\275\223\345\211\215\347\273\204\345\217\267", nullptr));
        lE_Finished->setText(QCoreApplication::translate("QtPLCDialogClass", "0", nullptr));
        label_17->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\211\224\345\272\237\350\256\241\346\225\260", nullptr));
        lE_GroupNo->setText(QCoreApplication::translate("QtPLCDialogClass", "0", nullptr));
        label_18->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\234\254\347\273\204\345\272\217\345\217\267", nullptr));
        label_16->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\275\223\345\211\215\350\257\273\346\225\260", nullptr));
        label_39->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\247\260\351\207\215\350\256\241\346\225\260", nullptr));
        lE_ScaleResult->setText(QCoreApplication::translate("QtPLCDialogClass", "0.000", nullptr));
        lE_TUCount->setText(QCoreApplication::translate("QtPLCDialogClass", "0", nullptr));
        label_15->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\234\254\347\273\204\347\273\223\346\235\237", nullptr));
        lE_TOCount->setText(QCoreApplication::translate("QtPLCDialogClass", "0", nullptr));
        label_49->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\277\207\351\207\215\350\256\241\346\225\260", nullptr));
        lE_RejectCount->setText(QCoreApplication::translate("QtPLCDialogClass", "0", nullptr));
        label_80->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\277\220\350\241\214\351\200\237\345\272\246\357\274\232", nullptr));
        lE_SysOveride->setText(QCoreApplication::translate("QtPLCDialogClass", "0", nullptr));
        label_78->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\224\237\344\272\247\346\211\271\345\217\267\357\274\232", nullptr));
        lE_BatchName->setText(QString());
        label_81->setText(QCoreApplication::translate("QtPLCDialogClass", "%", nullptr));
        lb_logo->setText(QString());
        pB_dtDlg->setText(QString());
        pB_SetUp->setText(QString());
        pB_cmdStart->setText(QString());
        lb_alm->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\263\273\347\273\237\346\212\245\350\255\246\357\274\214\350\257\267\345\205\210\345\244\215\344\275\215\357\274\201", nullptr));
        label_8->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\234\200\345\260\217\345\200\274(g)", nullptr));
        label_29->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\267\256\345\274\202\345\200\274(\345\260\217)", nullptr));
        label_6->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\234\200\345\244\247\345\200\274(g)", nullptr));
        label_34->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\267\256\345\274\202\345\200\274(\345\244\247)", nullptr));
        label_7->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\271\263\345\235\207\345\200\274(g)", nullptr));
        label_3->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\200\273\345\222\214(g)", nullptr));
        label->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\254\241\346\225\260", nullptr));
        label_9->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\273\204\345\217\267", nullptr));
        groupBox_11->setTitle(QCoreApplication::translate("QtPLCDialogClass", "\346\211\223\345\215\260", nullptr));
        pB_printCurve->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\211\223\345\215\260\346\225\260\346\215\256\346\233\262\347\272\277", nullptr));
        label_37->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\207\263", nullptr));
        label_23->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\207\263", nullptr));
        pB_startSearch->setText(QCoreApplication::translate("QtPLCDialogClass", "\345\274\200\345\247\213\346\220\234\347\264\242", nullptr));
        label_36->setText(QCoreApplication::translate("QtPLCDialogClass", "\346\220\234\347\264\242\357\274\232", nullptr));
        lE_year2->setText(QCoreApplication::translate("QtPLCDialogClass", "2021", nullptr));
        label_51->setText(QCoreApplication::translate("QtPLCDialogClass", "/", nullptr));
        lE_month2->setText(QCoreApplication::translate("QtPLCDialogClass", "06", nullptr));
        label_55->setText(QCoreApplication::translate("QtPLCDialogClass", "/", nullptr));
        lE_day2->setText(QCoreApplication::translate("QtPLCDialogClass", "06", nullptr));
        label_59->setText(QString());
        lE_hour2->setText(QCoreApplication::translate("QtPLCDialogClass", "06", nullptr));
        label_60->setText(QCoreApplication::translate("QtPLCDialogClass", ":", nullptr));
        lE_minute2->setText(QCoreApplication::translate("QtPLCDialogClass", "06", nullptr));
        label_35->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\273\204\345\217\267\357\274\232", nullptr));
        lE_year1->setText(QCoreApplication::translate("QtPLCDialogClass", "2021", nullptr));
        label_38->setText(QCoreApplication::translate("QtPLCDialogClass", "/", nullptr));
        lE_month1->setText(QCoreApplication::translate("QtPLCDialogClass", "06", nullptr));
        label_43->setText(QCoreApplication::translate("QtPLCDialogClass", "/", nullptr));
        lE_day1->setText(QCoreApplication::translate("QtPLCDialogClass", "06", nullptr));
        label_47->setText(QString());
        lE_hour1->setText(QCoreApplication::translate("QtPLCDialogClass", "06", nullptr));
        label_45->setText(QCoreApplication::translate("QtPLCDialogClass", ":", nullptr));
        lE_minute1->setText(QCoreApplication::translate("QtPLCDialogClass", "06", nullptr));
        pB_printData->setText(QString());
        pB_printData_2->setText(QString());
        label_61->setText(QCoreApplication::translate("QtPLCDialogClass", "\347\273\223\346\236\234\357\274\232", nullptr));
        lb_searchResult->setText(QString());
        pB_copyIn->setText(QCoreApplication::translate("QtPLCDialogClass", "\350\264\264\345\205\245\342\206\223", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtPLCDialogClass: public Ui_QtPLCDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTPLCDIALOGCLASS_H

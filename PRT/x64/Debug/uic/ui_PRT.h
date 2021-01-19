/********************************************************************************
** Form generated from reading UI file 'PRT.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRT_H
#define UI_PRT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PRTClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_5;
    QWidget *widget;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QComboBox *cB_PrintMode;
    QLabel *label;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QCheckBox *cB_Curve;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QCheckBox *checkBox;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *cB_Average;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QCheckBox *checkBox_2;
    QFrame *frame_4;
    QVBoxLayout *verticalLayout_6;
    QLabel *lb_PrinterName;
    QPushButton *pB_Print;
    QPushButton *pB_PrintDirect;

    void setupUi(QMainWindow *PRTClass)
    {
        if (PRTClass->objectName().isEmpty())
            PRTClass->setObjectName(QString::fromUtf8("PRTClass"));
        PRTClass->setWindowModality(Qt::NonModal);
        PRTClass->resize(1280, 800);
        PRTClass->setMinimumSize(QSize(1280, 800));
        PRTClass->setMaximumSize(QSize(1280, 800));
        centralWidget = new QWidget(PRTClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_4 = new QHBoxLayout(centralWidget);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout_5 = new QHBoxLayout(groupBox_2);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        widget = new QWidget(groupBox_2);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(0, 0));
        widget->setMaximumSize(QSize(3434, 3434));
        groupBox = new QGroupBox(widget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(340, 27, 385, 571));
        groupBox->setMinimumSize(QSize(385, 0));
        groupBox->setMaximumSize(QSize(385, 781));
        QFont font;
        font.setFamily(QString::fromUtf8("\350\277\267\344\275\240\347\256\200\350\217\261\345\277\203"));
        font.setPointSize(20);
        groupBox->setFont(font);
        groupBox->setFlat(false);
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        frame_3 = new QFrame(groupBox);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setFrameShape(QFrame::Box);
        frame_3->setFrameShadow(QFrame::Sunken);
        frame_3->setLineWidth(2);
        frame_3->setMidLineWidth(0);
        verticalLayout_4 = new QVBoxLayout(frame_3);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_4 = new QLabel(frame_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(20);
        font1.setBold(true);
        font1.setWeight(75);
        label_4->setFont(font1);

        horizontalLayout_3->addWidget(label_4);

        cB_PrintMode = new QComboBox(frame_3);
        cB_PrintMode->addItem(QString());
        cB_PrintMode->addItem(QString());
        cB_PrintMode->setObjectName(QString::fromUtf8("cB_PrintMode"));

        horizontalLayout_3->addWidget(cB_PrintMode);


        verticalLayout_4->addLayout(horizontalLayout_3);

        label = new QLabel(frame_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font1);

        verticalLayout_4->addWidget(label);


        verticalLayout_3->addWidget(frame_3);

        frame = new QFrame(groupBox);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Sunken);
        frame->setLineWidth(2);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        cB_Curve = new QCheckBox(frame);
        cB_Curve->setObjectName(QString::fromUtf8("cB_Curve"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\350\277\267\344\275\240\347\256\200\350\217\261\345\277\203"));
        font2.setPointSize(36);
        cB_Curve->setFont(font2);
        cB_Curve->setChecked(true);

        verticalLayout->addWidget(cB_Curve);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font1);

        horizontalLayout->addWidget(label_2);

        lineEdit = new QLineEdit(frame);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setFont(font1);

        horizontalLayout->addWidget(lineEdit);

        checkBox = new QCheckBox(frame);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setFont(font1);

        horizontalLayout->addWidget(checkBox);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_3->addWidget(frame);

        frame_2 = new QFrame(groupBox);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::Box);
        frame_2->setFrameShadow(QFrame::Sunken);
        frame_2->setLineWidth(2);
        verticalLayout_2 = new QVBoxLayout(frame_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        cB_Average = new QCheckBox(frame_2);
        cB_Average->setObjectName(QString::fromUtf8("cB_Average"));
        cB_Average->setFont(font2);
        cB_Average->setChecked(true);

        verticalLayout_2->addWidget(cB_Average);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(frame_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);

        horizontalLayout_2->addWidget(label_3);

        lineEdit_2 = new QLineEdit(frame_2);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setFont(font1);

        horizontalLayout_2->addWidget(lineEdit_2);

        checkBox_2 = new QCheckBox(frame_2);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setFont(font1);

        horizontalLayout_2->addWidget(checkBox_2);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout_3->addWidget(frame_2);

        frame_4 = new QFrame(groupBox);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setFrameShape(QFrame::Box);
        frame_4->setFrameShadow(QFrame::Sunken);
        frame_4->setLineWidth(2);
        verticalLayout_6 = new QVBoxLayout(frame_4);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        lb_PrinterName = new QLabel(frame_4);
        lb_PrinterName->setObjectName(QString::fromUtf8("lb_PrinterName"));
        lb_PrinterName->setFont(font1);

        verticalLayout_6->addWidget(lb_PrinterName);


        verticalLayout_3->addWidget(frame_4);

        pB_Print = new QPushButton(groupBox);
        pB_Print->setObjectName(QString::fromUtf8("pB_Print"));
        pB_Print->setStyleSheet(QString::fromUtf8("font: 36pt \"\350\277\267\344\275\240\347\256\200\350\217\261\345\277\203\";"));

        verticalLayout_3->addWidget(pB_Print);

        pB_PrintDirect = new QPushButton(groupBox);
        pB_PrintDirect->setObjectName(QString::fromUtf8("pB_PrintDirect"));
        pB_PrintDirect->setEnabled(true);
        pB_PrintDirect->setStyleSheet(QString::fromUtf8("font: 36pt \"\350\277\267\344\275\240\347\256\200\350\217\261\345\277\203\";"));

        verticalLayout_3->addWidget(pB_PrintDirect);


        horizontalLayout_5->addWidget(widget);


        horizontalLayout_4->addWidget(groupBox_2);

        PRTClass->setCentralWidget(centralWidget);

        retranslateUi(PRTClass);

        QMetaObject::connectSlotsByName(PRTClass);
    } // setupUi

    void retranslateUi(QMainWindow *PRTClass)
    {
        PRTClass->setWindowTitle(QCoreApplication::translate("PRTClass", "PRT", nullptr));
        groupBox_2->setTitle(QString());
        groupBox->setTitle(QCoreApplication::translate("PRTClass", "\346\211\223\345\215\260", nullptr));
        label_4->setText(QCoreApplication::translate("PRTClass", "\346\211\223\345\215\260\346\250\241\345\274\217:", nullptr));
        cB_PrintMode->setItemText(0, QCoreApplication::translate("PRTClass", "\346\211\213\345\212\250", nullptr));
        cB_PrintMode->setItemText(1, QCoreApplication::translate("PRTClass", "\350\207\252\345\212\250", nullptr));

        label->setText(QCoreApplication::translate("PRTClass", "\346\234\200\345\244\247\345\217\257\346\211\223\345\215\260\346\225\260\357\274\2320", nullptr));
        cB_Curve->setText(QCoreApplication::translate("PRTClass", "\346\233\262\347\272\277\345\233\276\350\241\250", nullptr));
        label_2->setText(QCoreApplication::translate("PRTClass", "\346\211\223\345\215\260\346\225\260", nullptr));
        checkBox->setText(QCoreApplication::translate("PRTClass", "\345\205\250\351\203\250", nullptr));
        cB_Average->setText(QCoreApplication::translate("PRTClass", "\345\235\207\345\200\274\345\233\276\350\241\250", nullptr));
        label_3->setText(QCoreApplication::translate("PRTClass", "\346\211\223\345\215\260\346\225\260", nullptr));
        checkBox_2->setText(QCoreApplication::translate("PRTClass", "\345\205\250\351\203\250", nullptr));
        lb_PrinterName->setText(QCoreApplication::translate("PRTClass", "1111111111111111111", nullptr));
        pB_Print->setText(QCoreApplication::translate("PRTClass", "\346\211\223\345\215\260\351\242\204\350\247\210", nullptr));
        pB_PrintDirect->setText(QCoreApplication::translate("PRTClass", "\346\211\223\345\215\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PRTClass: public Ui_PRTClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRT_H

/********************************************************************************
** Form generated from reading UI file 'WindowOut.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOWOUT_H
#define UI_WINDOWOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_WindowOut
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;

    void setupUi(QDialog *WindowOut)
    {
        if (WindowOut->objectName().isEmpty())
            WindowOut->setObjectName(QString::fromUtf8("WindowOut"));
        WindowOut->setWindowModality(Qt::WindowModal);
        WindowOut->resize(690, 168);
        WindowOut->setMinimumSize(QSize(690, 168));
        WindowOut->setMaximumSize(QSize(690, 168));
        WindowOut->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        verticalLayout = new QVBoxLayout(WindowOut);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(WindowOut);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\271\274\345\234\206"));
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);


        retranslateUi(WindowOut);

        QMetaObject::connectSlotsByName(WindowOut);
    } // setupUi

    void retranslateUi(QDialog *WindowOut)
    {
        WindowOut->setWindowTitle(QCoreApplication::translate("WindowOut", "WindowOut", nullptr));
        label->setText(QCoreApplication::translate("WindowOut", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowOut: public Ui_WindowOut {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOWOUT_H

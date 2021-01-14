/********************************************************************************
** Form generated from reading UI file 'RockeyARM.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROCKEYARM_H
#define UI_ROCKEYARM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_RockeyARM
{
public:

    void setupUi(QDialog *RockeyARM)
    {
        if (RockeyARM->objectName().isEmpty())
            RockeyARM->setObjectName(QString::fromUtf8("RockeyARM"));
        RockeyARM->resize(400, 300);

        retranslateUi(RockeyARM);

        QMetaObject::connectSlotsByName(RockeyARM);
    } // setupUi

    void retranslateUi(QDialog *RockeyARM)
    {
        RockeyARM->setWindowTitle(QCoreApplication::translate("RockeyARM", "RockeyARM", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RockeyARM: public Ui_RockeyARM {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROCKEYARM_H

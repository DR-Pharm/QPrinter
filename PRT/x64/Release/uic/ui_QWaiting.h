/********************************************************************************
** Form generated from reading UI file 'QWaiting.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QWAITING_H
#define UI_QWAITING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QWaiting
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *QWaiting)
    {
        if (QWaiting->objectName().isEmpty())
            QWaiting->setObjectName(QString::fromUtf8("QWaiting"));
        QWaiting->resize(374, 117);
        QWaiting->setMinimumSize(QSize(20, 20));
        QWaiting->setMaximumSize(QSize(400, 400));
        QWaiting->setContextMenuPolicy(Qt::DefaultContextMenu);
        verticalLayout = new QVBoxLayout(QWaiting);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(QWaiting);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setAutoFillBackground(false);
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 221);"));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Sunken);
        frame->setLineWidth(1);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(50, 50));
        label->setMaximumSize(QSize(50, 50));

        horizontalLayout->addWidget(label);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(240, 50));
        label_2->setMaximumSize(QSize(240, 50));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        label_2->setFont(font);

        horizontalLayout->addWidget(label_2);


        verticalLayout->addWidget(frame);


        retranslateUi(QWaiting);

        QMetaObject::connectSlotsByName(QWaiting);
    } // setupUi

    void retranslateUi(QWidget *QWaiting)
    {
        QWaiting->setWindowTitle(QCoreApplication::translate("QWaiting", "QWaiting", nullptr));
        label->setText(QCoreApplication::translate("QWaiting", "TextLabel", nullptr));
        label_2->setText(QCoreApplication::translate("QWaiting", "\346\211\223\345\215\260\346\255\243\345\234\250\350\277\233\350\241\214,\350\257\267\347\250\215\347\255\211...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QWaiting: public Ui_QWaiting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QWAITING_H

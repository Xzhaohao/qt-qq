/********************************************************************************
** Form generated from reading UI file 'receiveFile.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECEIVEFILE_H
#define UI_RECEIVEFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReceiveFile
{
public:
    QWidget *titleWidget;
    QWidget *bodyWidget;
    QLabel *label;
    QPushButton *okBtn;
    QPushButton *cancelBtn;

    void setupUi(QWidget *ReceiveFile)
    {
        if (ReceiveFile->objectName().isEmpty())
            ReceiveFile->setObjectName(QString::fromUtf8("ReceiveFile"));
        ReceiveFile->resize(515, 160);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ReceiveFile->sizePolicy().hasHeightForWidth());
        ReceiveFile->setSizePolicy(sizePolicy);
        ReceiveFile->setMinimumSize(QSize(515, 160));
        ReceiveFile->setMaximumSize(QSize(515, 160));
        titleWidget = new QWidget(ReceiveFile);
        titleWidget->setObjectName(QString::fromUtf8("titleWidget"));
        titleWidget->setGeometry(QRect(0, 0, 515, 50));
        titleWidget->setProperty("titleSkin", QVariant(true));
        bodyWidget = new QWidget(ReceiveFile);
        bodyWidget->setObjectName(QString::fromUtf8("bodyWidget"));
        bodyWidget->setGeometry(QRect(0, 50, 515, 110));
        bodyWidget->setProperty("bottomSkin", QVariant(true));
        label = new QLabel(bodyWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 421, 25));
        okBtn = new QPushButton(bodyWidget);
        okBtn->setObjectName(QString::fromUtf8("okBtn"));
        okBtn->setGeometry(QRect(270, 60, 93, 28));
        cancelBtn = new QPushButton(bodyWidget);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));
        cancelBtn->setGeometry(QRect(380, 60, 93, 28));

        retranslateUi(ReceiveFile);

        QMetaObject::connectSlotsByName(ReceiveFile);
    } // setupUi

    void retranslateUi(QWidget *ReceiveFile)
    {
        ReceiveFile->setWindowTitle(QApplication::translate("ReceiveFile", "ReceiveFile", nullptr));
        label->setText(QApplication::translate("ReceiveFile", "\346\235\245\350\207\252xxx\345\217\221\346\235\245\346\226\207\344\273\266:\346\230\257\345\220\246\346\216\245\345\217\227?", nullptr));
        okBtn->setText(QApplication::translate("ReceiveFile", "\347\241\256\345\256\232", nullptr));
        cancelBtn->setText(QApplication::translate("ReceiveFile", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ReceiveFile: public Ui_ReceiveFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECEIVEFILE_H

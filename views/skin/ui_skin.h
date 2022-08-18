/********************************************************************************
** Form generated from reading UI file 'skin.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SKIN_H
#define UI_SKIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SkinWindow
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *titleWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *titleIcon;
    QSpacerItem *horizontalSpacer;
    QPushButton *sysMin;
    QPushButton *sysClose;
    QWidget *bodyWidget;
    QGridLayout *gridLayout;

    void setupUi(QWidget *SkinWindow)
    {
        if (SkinWindow->objectName().isEmpty())
            SkinWindow->setObjectName(QString::fromUtf8("SkinWindow"));
        SkinWindow->resize(404, 309);
        verticalLayout = new QVBoxLayout(SkinWindow);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        titleWidget = new QWidget(SkinWindow);
        titleWidget->setObjectName(QString::fromUtf8("titleWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(titleWidget->sizePolicy().hasHeightForWidth());
        titleWidget->setSizePolicy(sizePolicy);
        titleWidget->setProperty("titleSkin", QVariant(true));
        horizontalLayout = new QHBoxLayout(titleWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(12, 0, 0, 0);
        titleIcon = new QLabel(titleWidget);
        titleIcon->setObjectName(QString::fromUtf8("titleIcon"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(titleIcon->sizePolicy().hasHeightForWidth());
        titleIcon->setSizePolicy(sizePolicy1);
        titleIcon->setMinimumSize(QSize(42, 18));
        titleIcon->setMaximumSize(QSize(42, 18));

        horizontalLayout->addWidget(titleIcon);

        horizontalSpacer = new QSpacerItem(295, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        sysMin = new QPushButton(titleWidget);
        sysMin->setObjectName(QString::fromUtf8("sysMin"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(sysMin->sizePolicy().hasHeightForWidth());
        sysMin->setSizePolicy(sizePolicy2);
        sysMin->setMinimumSize(QSize(24, 24));
        sysMin->setMaximumSize(QSize(24, 24));

        horizontalLayout->addWidget(sysMin);

        sysClose = new QPushButton(titleWidget);
        sysClose->setObjectName(QString::fromUtf8("sysClose"));
        sizePolicy2.setHeightForWidth(sysClose->sizePolicy().hasHeightForWidth());
        sysClose->setSizePolicy(sizePolicy2);
        sysClose->setMinimumSize(QSize(24, 24));
        sysClose->setMaximumSize(QSize(24, 24));

        horizontalLayout->addWidget(sysClose);


        verticalLayout->addWidget(titleWidget);

        bodyWidget = new QWidget(SkinWindow);
        bodyWidget->setObjectName(QString::fromUtf8("bodyWidget"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(bodyWidget->sizePolicy().hasHeightForWidth());
        bodyWidget->setSizePolicy(sizePolicy3);
        gridLayout = new QGridLayout(bodyWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

        verticalLayout->addWidget(bodyWidget);


        retranslateUi(SkinWindow);

        QMetaObject::connectSlotsByName(SkinWindow);
    } // setupUi

    void retranslateUi(QWidget *SkinWindow)
    {
        SkinWindow->setWindowTitle(QApplication::translate("SkinWindow", "SkinWindow", nullptr));
        titleIcon->setText(QString());
        sysMin->setText(QString());
        sysClose->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SkinWindow: public Ui_SkinWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SKIN_H

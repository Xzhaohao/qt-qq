/********************************************************************************
** Form generated from reading UI file 'contactItem.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTACTITEM_H
#define UI_CONTACTITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ContactItem
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *avatarWrap;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QLabel *userName;
    QLabel *signName;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *ContactItem)
    {
        if (ContactItem->objectName().isEmpty())
            ContactItem->setObjectName(QString::fromUtf8("ContactItem"));
        ContactItem->resize(483, 54);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ContactItem->sizePolicy().hasHeightForWidth());
        ContactItem->setSizePolicy(sizePolicy);
        ContactItem->setMinimumSize(QSize(0, 54));
        ContactItem->setMaximumSize(QSize(16777215, 54));
        horizontalLayout = new QHBoxLayout(ContactItem);
        horizontalLayout->setSpacing(12);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(6, 0, 6, 0);
        avatarWrap = new QLabel(ContactItem);
        avatarWrap->setObjectName(QString::fromUtf8("avatarWrap"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(avatarWrap->sizePolicy().hasHeightForWidth());
        avatarWrap->setSizePolicy(sizePolicy1);
        avatarWrap->setMinimumSize(QSize(40, 40));
        avatarWrap->setMaximumSize(QSize(40, 40));

        horizontalLayout->addWidget(avatarWrap);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer = new QSpacerItem(100, 5, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        userName = new QLabel(ContactItem);
        userName->setObjectName(QString::fromUtf8("userName"));

        verticalLayout->addWidget(userName);

        signName = new QLabel(ContactItem);
        signName->setObjectName(QString::fromUtf8("signName"));

        verticalLayout->addWidget(signName);

        verticalSpacer_2 = new QSpacerItem(100, 5, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(ContactItem);

        QMetaObject::connectSlotsByName(ContactItem);
    } // setupUi

    void retranslateUi(QWidget *ContactItem)
    {
        ContactItem->setWindowTitle(QApplication::translate("ContactItem", "ContactItem", nullptr));
        avatarWrap->setText(QString());
        userName->setText(QString());
        signName->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ContactItem: public Ui_ContactItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTACTITEM_H

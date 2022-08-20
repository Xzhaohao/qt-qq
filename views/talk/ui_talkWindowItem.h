/********************************************************************************
** Form generated from reading UI file 'talkWindowItem.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TALKWINDOWITEM_H
#define UI_TALKWINDOWITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TalkWindowItem
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *avatarLabel;
    QLabel *msgLabel;
    QPushButton *tCloseBtn;

    void setupUi(QWidget *TalkWindowItem)
    {
        if (TalkWindowItem->objectName().isEmpty())
            TalkWindowItem->setObjectName(QString::fromUtf8("TalkWindowItem"));
        TalkWindowItem->resize(404, 42);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TalkWindowItem->sizePolicy().hasHeightForWidth());
        TalkWindowItem->setSizePolicy(sizePolicy);
        TalkWindowItem->setMinimumSize(QSize(0, 42));
        TalkWindowItem->setMaximumSize(QSize(16777215, 42));
        horizontalLayout = new QHBoxLayout(TalkWindowItem);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(6, 6, 6, 6);
        avatarLabel = new QLabel(TalkWindowItem);
        avatarLabel->setObjectName(QString::fromUtf8("avatarLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(avatarLabel->sizePolicy().hasHeightForWidth());
        avatarLabel->setSizePolicy(sizePolicy1);
        avatarLabel->setMinimumSize(QSize(30, 30));
        avatarLabel->setMaximumSize(QSize(30, 30));

        horizontalLayout->addWidget(avatarLabel);

        msgLabel = new QLabel(TalkWindowItem);
        msgLabel->setObjectName(QString::fromUtf8("msgLabel"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(msgLabel->sizePolicy().hasHeightForWidth());
        msgLabel->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(msgLabel);

        tCloseBtn = new QPushButton(TalkWindowItem);
        tCloseBtn->setObjectName(QString::fromUtf8("tCloseBtn"));
        sizePolicy1.setHeightForWidth(tCloseBtn->sizePolicy().hasHeightForWidth());
        tCloseBtn->setSizePolicy(sizePolicy1);
        tCloseBtn->setMinimumSize(QSize(16, 16));
        tCloseBtn->setMaximumSize(QSize(16, 16));

        horizontalLayout->addWidget(tCloseBtn);


        retranslateUi(TalkWindowItem);

        QMetaObject::connectSlotsByName(TalkWindowItem);
    } // setupUi

    void retranslateUi(QWidget *TalkWindowItem)
    {
        TalkWindowItem->setWindowTitle(QApplication::translate("TalkWindowItem", "TalkWindowItem", nullptr));
        avatarLabel->setText(QString());
        msgLabel->setText(QString());
        tCloseBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TalkWindowItem: public Ui_TalkWindowItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TALKWINDOWITEM_H

/********************************************************************************
** Form generated from reading UI file 'talkWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TALKWINDOW_H
#define UI_TALKWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "../../components/msgEdit/QMsgTextEdit.h"
#include "../../components/msgView/msgWebView.h"

QT_BEGIN_NAMESPACE

class Ui_TalkWindow
{
public:
    QVBoxLayout *verticalLayout_6;
    QWidget *titleWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *nameLabel;
    QPushButton *sysMin;
    QPushButton *sysClose;
    QLabel *signLabel;
    QWidget *funWidget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *addToolBtn;
    QPushButton *addHumanBtn;
    QPushButton *appBtn;
    QPushButton *videoBtn;
    QPushButton *toolsetBtn;
    QSpacerItem *horizontalSpacer;
    QSplitter *splitter;
    QSplitter *bodySplitter;
    QWidget *bodyWidget;
    QVBoxLayout *verticalLayout_4;
    QFrame *frameWidget;
    QVBoxLayout *verticalLayout_3;
    MsgWebView *msgWidget;
    QWidget *bottomWidget;
    QVBoxLayout *verticalLayout_2;
    QWidget *moduleWidget;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *faceBtn;
    QPushButton *fileopenBtn;
    QSpacerItem *horizontalSpacer_2;
    QMsgTextEdit *textEdit;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_3;
    QToolButton *closeBtn;
    QToolButton *sendBtn;
    QWidget *widget;
    QVBoxLayout *verticalLayout_5;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QTreeWidget *treeWidget;

    void setupUi(QWidget *TalkWindow)
    {
        if (TalkWindow->objectName().isEmpty())
            TalkWindow->setObjectName(QString::fromUtf8("TalkWindow"));
        TalkWindow->resize(880, 439);
        verticalLayout_6 = new QVBoxLayout(TalkWindow);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        titleWidget = new QWidget(TalkWindow);
        titleWidget->setObjectName(QString::fromUtf8("titleWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(titleWidget->sizePolicy().hasHeightForWidth());
        titleWidget->setSizePolicy(sizePolicy);
        titleWidget->setMinimumSize(QSize(0, 84));
        titleWidget->setMaximumSize(QSize(16777215, 84));
        titleWidget->setProperty("bottomSkin", QVariant(true));
        verticalLayout = new QVBoxLayout(titleWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(6, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        nameLabel = new QLabel(titleWidget);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));
        sizePolicy.setHeightForWidth(nameLabel->sizePolicy().hasHeightForWidth());
        nameLabel->setSizePolicy(sizePolicy);
        nameLabel->setMinimumSize(QSize(0, 27));
        nameLabel->setMaximumSize(QSize(16777215, 27));
        QFont font;
        font.setFamily(QString::fromUtf8("AcadEref"));
        font.setPointSize(12);
        nameLabel->setFont(font);

        horizontalLayout->addWidget(nameLabel);

        sysMin = new QPushButton(titleWidget);
        sysMin->setObjectName(QString::fromUtf8("sysMin"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(sysMin->sizePolicy().hasHeightForWidth());
        sysMin->setSizePolicy(sizePolicy1);
        sysMin->setMinimumSize(QSize(30, 27));
        sysMin->setMaximumSize(QSize(30, 27));
        sysMin->setFocusPolicy(Qt::ClickFocus);
        sysMin->setIconSize(QSize(30, 30));

        horizontalLayout->addWidget(sysMin);

        sysClose = new QPushButton(titleWidget);
        sysClose->setObjectName(QString::fromUtf8("sysClose"));
        sizePolicy1.setHeightForWidth(sysClose->sizePolicy().hasHeightForWidth());
        sysClose->setSizePolicy(sizePolicy1);
        sysClose->setMinimumSize(QSize(30, 27));
        sysClose->setMaximumSize(QSize(30, 27));
        sysClose->setFocusPolicy(Qt::ClickFocus);
        sysClose->setIconSize(QSize(30, 30));

        horizontalLayout->addWidget(sysClose);


        verticalLayout->addLayout(horizontalLayout);

        signLabel = new QLabel(titleWidget);
        signLabel->setObjectName(QString::fromUtf8("signLabel"));
        sizePolicy.setHeightForWidth(signLabel->sizePolicy().hasHeightForWidth());
        signLabel->setSizePolicy(sizePolicy);
        signLabel->setMaximumSize(QSize(16777215, 20));
        signLabel->setSizeIncrement(QSize(0, 20));
        QFont font1;
        font1.setFamily(QString::fromUtf8("AcadEref"));
        font1.setPointSize(10);
        signLabel->setFont(font1);

        verticalLayout->addWidget(signLabel);

        funWidget = new QWidget(titleWidget);
        funWidget->setObjectName(QString::fromUtf8("funWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(funWidget->sizePolicy().hasHeightForWidth());
        funWidget->setSizePolicy(sizePolicy2);
        funWidget->setMinimumSize(QSize(0, 34));
        funWidget->setMaximumSize(QSize(16777215, 600));
        horizontalLayout_2 = new QHBoxLayout(funWidget);
        horizontalLayout_2->setSpacing(8);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 6, 0);
        addToolBtn = new QPushButton(funWidget);
        addToolBtn->setObjectName(QString::fromUtf8("addToolBtn"));
        sizePolicy1.setHeightForWidth(addToolBtn->sizePolicy().hasHeightForWidth());
        addToolBtn->setSizePolicy(sizePolicy1);
        addToolBtn->setMinimumSize(QSize(25, 25));
        addToolBtn->setMaximumSize(QSize(25, 25));
        addToolBtn->setProperty("hasBorder", QVariant(true));

        horizontalLayout_2->addWidget(addToolBtn);

        addHumanBtn = new QPushButton(funWidget);
        addHumanBtn->setObjectName(QString::fromUtf8("addHumanBtn"));
        sizePolicy1.setHeightForWidth(addHumanBtn->sizePolicy().hasHeightForWidth());
        addHumanBtn->setSizePolicy(sizePolicy1);
        addHumanBtn->setMinimumSize(QSize(25, 25));
        addHumanBtn->setMaximumSize(QSize(25, 25));
        addHumanBtn->setProperty("hasBorder", QVariant(true));

        horizontalLayout_2->addWidget(addHumanBtn);

        appBtn = new QPushButton(funWidget);
        appBtn->setObjectName(QString::fromUtf8("appBtn"));
        sizePolicy1.setHeightForWidth(appBtn->sizePolicy().hasHeightForWidth());
        appBtn->setSizePolicy(sizePolicy1);
        appBtn->setMinimumSize(QSize(25, 25));
        appBtn->setMaximumSize(QSize(25, 25));
        appBtn->setProperty("hasBorder", QVariant(true));

        horizontalLayout_2->addWidget(appBtn);

        videoBtn = new QPushButton(funWidget);
        videoBtn->setObjectName(QString::fromUtf8("videoBtn"));
        sizePolicy1.setHeightForWidth(videoBtn->sizePolicy().hasHeightForWidth());
        videoBtn->setSizePolicy(sizePolicy1);
        videoBtn->setMinimumSize(QSize(25, 25));
        videoBtn->setMaximumSize(QSize(25, 25));
        videoBtn->setProperty("hasBorder", QVariant(true));

        horizontalLayout_2->addWidget(videoBtn);

        toolsetBtn = new QPushButton(funWidget);
        toolsetBtn->setObjectName(QString::fromUtf8("toolsetBtn"));
        sizePolicy1.setHeightForWidth(toolsetBtn->sizePolicy().hasHeightForWidth());
        toolsetBtn->setSizePolicy(sizePolicy1);
        toolsetBtn->setMinimumSize(QSize(25, 25));
        toolsetBtn->setMaximumSize(QSize(25, 25));
        toolsetBtn->setProperty("hasBorder", QVariant(true));

        horizontalLayout_2->addWidget(toolsetBtn);

        horizontalSpacer = new QSpacerItem(700, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addWidget(funWidget);


        verticalLayout_6->addWidget(titleWidget);

        splitter = new QSplitter(TalkWindow);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        sizePolicy2.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy2);
        splitter->setOrientation(Qt::Horizontal);
        bodySplitter = new QSplitter(splitter);
        bodySplitter->setObjectName(QString::fromUtf8("bodySplitter"));
        bodySplitter->setOrientation(Qt::Vertical);
        bodySplitter->setHandleWidth(1);
        bodySplitter->setChildrenCollapsible(false);
        bodyWidget = new QWidget(bodySplitter);
        bodyWidget->setObjectName(QString::fromUtf8("bodyWidget"));
        sizePolicy2.setHeightForWidth(bodyWidget->sizePolicy().hasHeightForWidth());
        bodyWidget->setSizePolicy(sizePolicy2);
        verticalLayout_4 = new QVBoxLayout(bodyWidget);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        frameWidget = new QFrame(bodyWidget);
        frameWidget->setObjectName(QString::fromUtf8("frameWidget"));
        sizePolicy2.setHeightForWidth(frameWidget->sizePolicy().hasHeightForWidth());
        frameWidget->setSizePolicy(sizePolicy2);
        frameWidget->setFrameShape(QFrame::StyledPanel);
        frameWidget->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frameWidget);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 1, 0, 1);
        msgWidget = new MsgWebView(frameWidget);
        msgWidget->setObjectName(QString::fromUtf8("msgWidget"));

        verticalLayout_3->addWidget(msgWidget);


        verticalLayout_4->addWidget(frameWidget);

        bodySplitter->addWidget(bodyWidget);
        bottomWidget = new QWidget(bodySplitter);
        bottomWidget->setObjectName(QString::fromUtf8("bottomWidget"));
        sizePolicy.setHeightForWidth(bottomWidget->sizePolicy().hasHeightForWidth());
        bottomWidget->setSizePolicy(sizePolicy);
        bottomWidget->setMinimumSize(QSize(0, 138));
        bottomWidget->setMaximumSize(QSize(16777215, 400));
        verticalLayout_2 = new QVBoxLayout(bottomWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        moduleWidget = new QWidget(bottomWidget);
        moduleWidget->setObjectName(QString::fromUtf8("moduleWidget"));
        sizePolicy.setHeightForWidth(moduleWidget->sizePolicy().hasHeightForWidth());
        moduleWidget->setSizePolicy(sizePolicy);
        moduleWidget->setMinimumSize(QSize(0, 24));
        moduleWidget->setMaximumSize(QSize(16777215, 24));
        horizontalLayout_3 = new QHBoxLayout(moduleWidget);
        horizontalLayout_3->setSpacing(8);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(8, 0, 8, 0);
        faceBtn = new QPushButton(moduleWidget);
        faceBtn->setObjectName(QString::fromUtf8("faceBtn"));
        sizePolicy1.setHeightForWidth(faceBtn->sizePolicy().hasHeightForWidth());
        faceBtn->setSizePolicy(sizePolicy1);
        faceBtn->setMinimumSize(QSize(20, 20));
        faceBtn->setMaximumSize(QSize(20, 20));
        faceBtn->setProperty("hasBorder", QVariant(true));

        horizontalLayout_3->addWidget(faceBtn);

        fileopenBtn = new QPushButton(moduleWidget);
        fileopenBtn->setObjectName(QString::fromUtf8("fileopenBtn"));
        sizePolicy1.setHeightForWidth(fileopenBtn->sizePolicy().hasHeightForWidth());
        fileopenBtn->setSizePolicy(sizePolicy1);
        fileopenBtn->setMinimumSize(QSize(20, 20));
        fileopenBtn->setMaximumSize(QSize(20, 20));
        fileopenBtn->setProperty("hasBorder", QVariant(true));

        horizontalLayout_3->addWidget(fileopenBtn);

        horizontalSpacer_2 = new QSpacerItem(519, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_2->addWidget(moduleWidget);

        textEdit = new QMsgTextEdit(bottomWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setContextMenuPolicy(Qt::NoContextMenu);
        textEdit->setFrameShape(QFrame::NoFrame);

        verticalLayout_2->addWidget(textEdit);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_3 = new QSpacerItem(348, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        closeBtn = new QToolButton(bottomWidget);
        closeBtn->setObjectName(QString::fromUtf8("closeBtn"));
        closeBtn->setMinimumSize(QSize(68, 24));
        closeBtn->setMaximumSize(QSize(68, 24));

        horizontalLayout_4->addWidget(closeBtn);

        sendBtn = new QToolButton(bottomWidget);
        sendBtn->setObjectName(QString::fromUtf8("sendBtn"));
        sendBtn->setMinimumSize(QSize(90, 24));
        sendBtn->setMaximumSize(QSize(90, 24));

        horizontalLayout_4->addWidget(sendBtn);


        verticalLayout_2->addLayout(horizontalLayout_4);

        bodySplitter->addWidget(bottomWidget);
        splitter->addWidget(bodySplitter);
        widget = new QWidget(splitter);
        widget->setObjectName(QString::fromUtf8("widget"));
        sizePolicy2.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy2);
        widget->setMinimumSize(QSize(280, 0));
        widget->setMaximumSize(QSize(280, 16777215));
        verticalLayout_5 = new QVBoxLayout(widget);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(widget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 280, 355));
        sizePolicy2.setHeightForWidth(scrollAreaWidgetContents_2->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents_2->setSizePolicy(sizePolicy2);
        treeWidget = new QTreeWidget(scrollAreaWidgetContents_2);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setGeometry(QRect(0, 0, 278, 355));
        treeWidget->setFrameShape(QFrame::NoFrame);
        treeWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        treeWidget->setEditTriggers(QAbstractItemView::AllEditTriggers);
        treeWidget->setIndentation(0);
        treeWidget->setHeaderHidden(true);
        scrollArea->setWidget(scrollAreaWidgetContents_2);

        verticalLayout_5->addWidget(scrollArea);

        splitter->addWidget(widget);

        verticalLayout_6->addWidget(splitter);


        retranslateUi(TalkWindow);

        QMetaObject::connectSlotsByName(TalkWindow);
    } // setupUi

    void retranslateUi(QWidget *TalkWindow)
    {
        TalkWindow->setWindowTitle(QApplication::translate("TalkWindow", "TalkWindow", nullptr));
        nameLabel->setText(QString());
#ifndef QT_NO_STATUSTIP
        sysMin->setStatusTip(QApplication::translate("TalkWindow", "\346\234\200\345\260\217\345\214\226", nullptr));
#endif // QT_NO_STATUSTIP
        sysMin->setText(QString());
#ifndef QT_NO_STATUSTIP
        sysClose->setStatusTip(QApplication::translate("TalkWindow", "\345\205\263\351\227\255", nullptr));
#endif // QT_NO_STATUSTIP
        sysClose->setText(QString());
        signLabel->setText(QString());
        addToolBtn->setText(QString());
        addHumanBtn->setText(QString());
        appBtn->setText(QString());
        videoBtn->setText(QString());
        toolsetBtn->setText(QString());
        faceBtn->setText(QString());
        fileopenBtn->setText(QString());
        closeBtn->setText(QApplication::translate("TalkWindow", "\345\205\263\351\227\255", nullptr));
        sendBtn->setText(QApplication::translate("TalkWindow", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TalkWindow: public Ui_TalkWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TALKWINDOW_H

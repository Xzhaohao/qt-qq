/********************************************************************************
** Form generated from reading UI file 'mainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QVBoxLayout *verticalLayout_5;
    QWidget *titleWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *titleIcon;
    QSpacerItem *horizontalSpacer;
    QPushButton *placeHold1;
    QPushButton *placeHold2;
    QPushButton *sysMin;
    QPushButton *sysClose;
    QHBoxLayout *horizontalLayout_3;
    QLabel *headLabel;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *nameLabel;
    QPushButton *statusBtn;
    QPushButton *levelBtn;
    QLineEdit *signature;
    QWidget *appWidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QWidget *searchWidget;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *searchInput;
    QPushButton *searchBtn;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_6;
    QTreeWidget *treeWidget;
    QWidget *bottomWidget;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *bottomLayout_up;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *bottomBtn_1;
    QPushButton *bottomBtn_2;
    QPushButton *bottomBtn_3;
    QPushButton *bottomBtn_4;
    QPushButton *bottomBtn_5;
    QPushButton *bottomBtn_6;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *bottomBtn_7;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(280, 680);
        MainWindow->setMinimumSize(QSize(280, 680));
        verticalLayout_5 = new QVBoxLayout(MainWindow);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        titleWidget = new QWidget(MainWindow);
        titleWidget->setObjectName(QString::fromUtf8("titleWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(titleWidget->sizePolicy().hasHeightForWidth());
        titleWidget->setSizePolicy(sizePolicy);
        titleWidget->setMinimumSize(QSize(280, 116));
        titleWidget->setProperty("titleSkin", QVariant(true));
        verticalLayout_2 = new QVBoxLayout(titleWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(12, -1, -1, -1);
        titleIcon = new QLabel(titleWidget);
        titleIcon->setObjectName(QString::fromUtf8("titleIcon"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(titleIcon->sizePolicy().hasHeightForWidth());
        titleIcon->setSizePolicy(sizePolicy1);
        titleIcon->setMinimumSize(QSize(42, 18));
        titleIcon->setMaximumSize(QSize(42, 18));

        horizontalLayout->addWidget(titleIcon);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        placeHold1 = new QPushButton(titleWidget);
        placeHold1->setObjectName(QString::fromUtf8("placeHold1"));
        sizePolicy1.setHeightForWidth(placeHold1->sizePolicy().hasHeightForWidth());
        placeHold1->setSizePolicy(sizePolicy1);
        placeHold1->setMinimumSize(QSize(24, 24));
        placeHold1->setMaximumSize(QSize(24, 24));

        horizontalLayout->addWidget(placeHold1);

        placeHold2 = new QPushButton(titleWidget);
        placeHold2->setObjectName(QString::fromUtf8("placeHold2"));
        sizePolicy1.setHeightForWidth(placeHold2->sizePolicy().hasHeightForWidth());
        placeHold2->setSizePolicy(sizePolicy1);
        placeHold2->setMinimumSize(QSize(24, 24));
        placeHold2->setMaximumSize(QSize(24, 24));

        horizontalLayout->addWidget(placeHold2);

        sysMin = new QPushButton(titleWidget);
        sysMin->setObjectName(QString::fromUtf8("sysMin"));
        sizePolicy1.setHeightForWidth(sysMin->sizePolicy().hasHeightForWidth());
        sysMin->setSizePolicy(sizePolicy1);
        sysMin->setMinimumSize(QSize(24, 24));
        sysMin->setMaximumSize(QSize(24, 24));

        horizontalLayout->addWidget(sysMin);

        sysClose = new QPushButton(titleWidget);
        sysClose->setObjectName(QString::fromUtf8("sysClose"));
        sizePolicy1.setHeightForWidth(sysClose->sizePolicy().hasHeightForWidth());
        sysClose->setSizePolicy(sizePolicy1);
        sysClose->setMinimumSize(QSize(24, 24));
        sysClose->setMaximumSize(QSize(24, 24));

        horizontalLayout->addWidget(sysClose);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(12, 6, 12, 6);
        headLabel = new QLabel(titleWidget);
        headLabel->setObjectName(QString::fromUtf8("headLabel"));
        sizePolicy1.setHeightForWidth(headLabel->sizePolicy().hasHeightForWidth());
        headLabel->setSizePolicy(sizePolicy1);
        headLabel->setMinimumSize(QSize(68, 68));
        headLabel->setMaximumSize(QSize(68, 68));

        horizontalLayout_3->addWidget(headLabel);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(4);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        nameLabel = new QLabel(titleWidget);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));
        nameLabel->setMinimumSize(QSize(0, 22));
        nameLabel->setMaximumSize(QSize(16777215, 22));
        nameLabel->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"                                                            "));

        horizontalLayout_2->addWidget(nameLabel);

        statusBtn = new QPushButton(titleWidget);
        statusBtn->setObjectName(QString::fromUtf8("statusBtn"));
        sizePolicy1.setHeightForWidth(statusBtn->sizePolicy().hasHeightForWidth());
        statusBtn->setSizePolicy(sizePolicy1);
        statusBtn->setMinimumSize(QSize(34, 22));
        statusBtn->setMaximumSize(QSize(34, 22));
        statusBtn->setProperty("hasBorder", QVariant(true));

        horizontalLayout_2->addWidget(statusBtn);

        levelBtn = new QPushButton(titleWidget);
        levelBtn->setObjectName(QString::fromUtf8("levelBtn"));
        sizePolicy1.setHeightForWidth(levelBtn->sizePolicy().hasHeightForWidth());
        levelBtn->setSizePolicy(sizePolicy1);
        levelBtn->setMinimumSize(QSize(22, 16));
        levelBtn->setMaximumSize(QSize(22, 16));
        levelBtn->setProperty("hasBorder", QVariant(true));

        horizontalLayout_2->addWidget(levelBtn);


        verticalLayout->addLayout(horizontalLayout_2);

        signature = new QLineEdit(titleWidget);
        signature->setObjectName(QString::fromUtf8("signature"));
        signature->setMinimumSize(QSize(0, 22));
        signature->setMaximumSize(QSize(16777215, 22));
        signature->setStyleSheet(QString::fromUtf8("padding-left: 3px;"));
        signature->setFrame(false);

        verticalLayout->addWidget(signature);

        appWidget = new QWidget(titleWidget);
        appWidget->setObjectName(QString::fromUtf8("appWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(appWidget->sizePolicy().hasHeightForWidth());
        appWidget->setSizePolicy(sizePolicy2);
        appWidget->setMaximumSize(QSize(16777215, 22));
        appWidget->setSizeIncrement(QSize(0, 22));

        verticalLayout->addWidget(appWidget);


        horizontalLayout_3->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout_3);


        verticalLayout_5->addWidget(titleWidget);

        widget = new QWidget(MainWindow);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy3);
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(1, 0, 1, 0);
        searchWidget = new QWidget(widget);
        searchWidget->setObjectName(QString::fromUtf8("searchWidget"));
        sizePolicy2.setHeightForWidth(searchWidget->sizePolicy().hasHeightForWidth());
        searchWidget->setSizePolicy(sizePolicy2);
        searchWidget->setMinimumSize(QSize(0, 30));
        searchWidget->setMaximumSize(QSize(16777215, 30));
        horizontalLayout_4 = new QHBoxLayout(searchWidget);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(6, 0, 6, 0);
        searchInput = new QLineEdit(searchWidget);
        searchInput->setObjectName(QString::fromUtf8("searchInput"));
        searchInput->setMinimumSize(QSize(0, 30));
        searchInput->setMaximumSize(QSize(16777215, 30));
        searchInput->setStyleSheet(QString::fromUtf8("padding-left: 3px;"));
        searchInput->setFrame(false);

        horizontalLayout_4->addWidget(searchInput);

        searchBtn = new QPushButton(searchWidget);
        searchBtn->setObjectName(QString::fromUtf8("searchBtn"));
        searchBtn->setMinimumSize(QSize(16, 16));
        searchBtn->setMaximumSize(QSize(16, 16));

        horizontalLayout_4->addWidget(searchBtn);


        verticalLayout_3->addWidget(searchWidget);

        scrollArea = new QScrollArea(widget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 278, 474));
        sizePolicy3.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy3);
        verticalLayout_6 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        treeWidget = new QTreeWidget(scrollAreaWidgetContents);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setFrameShape(QFrame::NoFrame);
        treeWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        treeWidget->setEditTriggers(QAbstractItemView::AllEditTriggers);
        treeWidget->setIndentation(0);
        treeWidget->setHeaderHidden(true);
        treeWidget->setExpandsOnDoubleClick(false);

        verticalLayout_6->addWidget(treeWidget);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_3->addWidget(scrollArea);


        verticalLayout_5->addWidget(widget);

        bottomWidget = new QWidget(MainWindow);
        bottomWidget->setObjectName(QString::fromUtf8("bottomWidget"));
        sizePolicy2.setHeightForWidth(bottomWidget->sizePolicy().hasHeightForWidth());
        bottomWidget->setSizePolicy(sizePolicy2);
        bottomWidget->setMinimumSize(QSize(0, 60));
        bottomWidget->setMaximumSize(QSize(16777215, 60));
        bottomWidget->setProperty("bottomSkin", QVariant(true));
        verticalLayout_4 = new QVBoxLayout(bottomWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(6, 6, 6, 6);
        bottomLayout_up = new QHBoxLayout();
        bottomLayout_up->setSpacing(6);
        bottomLayout_up->setObjectName(QString::fromUtf8("bottomLayout_up"));

        verticalLayout_4->addLayout(bottomLayout_up);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        bottomBtn_1 = new QPushButton(bottomWidget);
        bottomBtn_1->setObjectName(QString::fromUtf8("bottomBtn_1"));
        sizePolicy1.setHeightForWidth(bottomBtn_1->sizePolicy().hasHeightForWidth());
        bottomBtn_1->setSizePolicy(sizePolicy1);
        bottomBtn_1->setMinimumSize(QSize(24, 24));
        bottomBtn_1->setMaximumSize(QSize(24, 24));

        horizontalLayout_5->addWidget(bottomBtn_1);

        bottomBtn_2 = new QPushButton(bottomWidget);
        bottomBtn_2->setObjectName(QString::fromUtf8("bottomBtn_2"));
        sizePolicy1.setHeightForWidth(bottomBtn_2->sizePolicy().hasHeightForWidth());
        bottomBtn_2->setSizePolicy(sizePolicy1);
        bottomBtn_2->setMinimumSize(QSize(24, 24));
        bottomBtn_2->setMaximumSize(QSize(24, 24));

        horizontalLayout_5->addWidget(bottomBtn_2);

        bottomBtn_3 = new QPushButton(bottomWidget);
        bottomBtn_3->setObjectName(QString::fromUtf8("bottomBtn_3"));
        sizePolicy1.setHeightForWidth(bottomBtn_3->sizePolicy().hasHeightForWidth());
        bottomBtn_3->setSizePolicy(sizePolicy1);
        bottomBtn_3->setMinimumSize(QSize(24, 24));
        bottomBtn_3->setMaximumSize(QSize(24, 24));

        horizontalLayout_5->addWidget(bottomBtn_3);

        bottomBtn_4 = new QPushButton(bottomWidget);
        bottomBtn_4->setObjectName(QString::fromUtf8("bottomBtn_4"));
        sizePolicy1.setHeightForWidth(bottomBtn_4->sizePolicy().hasHeightForWidth());
        bottomBtn_4->setSizePolicy(sizePolicy1);
        bottomBtn_4->setMinimumSize(QSize(24, 24));
        bottomBtn_4->setMaximumSize(QSize(24, 24));

        horizontalLayout_5->addWidget(bottomBtn_4);

        bottomBtn_5 = new QPushButton(bottomWidget);
        bottomBtn_5->setObjectName(QString::fromUtf8("bottomBtn_5"));
        sizePolicy1.setHeightForWidth(bottomBtn_5->sizePolicy().hasHeightForWidth());
        bottomBtn_5->setSizePolicy(sizePolicy1);
        bottomBtn_5->setMinimumSize(QSize(24, 24));
        bottomBtn_5->setMaximumSize(QSize(24, 24));

        horizontalLayout_5->addWidget(bottomBtn_5);

        bottomBtn_6 = new QPushButton(bottomWidget);
        bottomBtn_6->setObjectName(QString::fromUtf8("bottomBtn_6"));
        sizePolicy1.setHeightForWidth(bottomBtn_6->sizePolicy().hasHeightForWidth());
        bottomBtn_6->setSizePolicy(sizePolicy1);
        bottomBtn_6->setMinimumSize(QSize(24, 24));
        bottomBtn_6->setMaximumSize(QSize(24, 24));

        horizontalLayout_5->addWidget(bottomBtn_6);

        horizontalSpacer_2 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        bottomBtn_7 = new QPushButton(bottomWidget);
        bottomBtn_7->setObjectName(QString::fromUtf8("bottomBtn_7"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(bottomBtn_7->sizePolicy().hasHeightForWidth());
        bottomBtn_7->setSizePolicy(sizePolicy4);
        bottomBtn_7->setMinimumSize(QSize(24, 24));
        bottomBtn_7->setMaximumSize(QSize(86, 24));

        horizontalLayout_5->addWidget(bottomBtn_7);


        verticalLayout_4->addLayout(horizontalLayout_5);

        verticalLayout_4->setStretch(0, 1);
        verticalLayout_4->setStretch(1, 1);

        verticalLayout_5->addWidget(bottomWidget);


        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        titleIcon->setText(QString());
        placeHold1->setText(QString());
        placeHold2->setText(QString());
        sysMin->setText(QString());
        sysClose->setText(QString());
        headLabel->setText(QString());
        nameLabel->setText(QApplication::translate("MainWindow", "\347\220\211\347\222\203\344\271\213\351\270\237", nullptr));
        statusBtn->setText(QString());
        levelBtn->setText(QString());
        signature->setPlaceholderText(QApplication::translate("MainWindow", "\344\270\252\346\200\247\347\255\276\345\220\215", nullptr));
        searchInput->setPlaceholderText(QApplication::translate("MainWindow", "\346\220\234\347\264\242\350\201\224\347\263\273\344\272\272\343\200\201\347\276\244", nullptr));
        searchBtn->setText(QString());
        bottomBtn_1->setText(QString());
        bottomBtn_2->setText(QString());
        bottomBtn_3->setText(QString());
        bottomBtn_4->setText(QString());
        bottomBtn_5->setText(QString());
        bottomBtn_6->setText(QString());
        bottomBtn_7->setText(QApplication::translate("MainWindow", "\345\272\224\347\224\250\345\256\235", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

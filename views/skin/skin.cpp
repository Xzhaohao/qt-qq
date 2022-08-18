#include "skin.h"

Skin::Skin(QWidget *parent) : BaseWindow(parent), ui(new Ui::SkinWindow) {
    ui->setupUi(this);
    loadStyleSheet("skinWindow");
    setAttribute(Qt::WA_DeleteOnClose);
    initControl();
}

Skin::~Skin() {
    delete ui;
}

void Skin::initControl() {
    QList<QColor> colorList = {
            QColor(22, 154, 218), QColor(40, 138, 221), QColor(49, 166, 107), QColor(218, 67, 68),
            QColor(177, 99, 158), QColor(107, 81, 92), QColor(89, 92, 160), QColor(21, 156, 199),
            QColor(79, 169, 172), QColor(155, 183, 154), QColor(128, 77, 77), QColor(240, 188, 189)
    };
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 4; column++) {
            auto *label = new ClickLabel(this);
            // 设置光标状态
            label->setCursor(Qt::PointingHandCursor);
            connect(label, &ClickLabel::clicked, [row, column, colorList]() {
                NotifyManger::getInstance()->notifyOtherWindowChangeSkin(colorList.at(row * 4 + column));
            });

            label->setFixedSize(84, 84);
            QPalette palette;
            palette.setColor(QPalette::Background, colorList.at(row * 4 + column));
            label->setAutoFillBackground(true);
            label->setPalette(palette);

            ui->gridLayout->addWidget(label, row, column);
        }
    }

    connect(ui->sysMin, SIGNAL(clicked(bool)), this, SLOT(onShowMin(bool)));
    connect(ui->sysClose, SIGNAL(clicked()), this, SLOT(onShowClose()));
}

void Skin::onShowClose() {
    close();
}
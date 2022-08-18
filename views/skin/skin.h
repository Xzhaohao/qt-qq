#ifndef __SKIN_H
#define __SKIN_H

#include "ui_skin.h"
#include "../base/baseWindow.h"
#include "../../components/clickLabel/clickLabel.h"

/**
 * 换肤
 */
class Skin : public BaseWindow {
Q_OBJECT
public:
    explicit Skin(QWidget *parent = nullptr);

    ~Skin() override;

public:
    void initControl();

public slots:

    void onShowClose();

private:
    Ui::SkinWindow *ui;
};

#endif // __SKIN_H

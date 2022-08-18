#ifndef __CUSTOM_MENU_H
#define __CUSTOM_MENU_H

#include <QMenu>
#include <QMap>
#include "../../utils/commonUtils.h"

class CustomMenu : public QMenu {
Q_OBJECT

public:
    explicit CustomMenu(QWidget *parent = nullptr);

    ~CustomMenu() override;

public:
    void addCustomMenu(const QString &text, const QString &icon, const QString &name);

    QAction *getAction(const QString &text);

private:
    QMap<QString, QAction *> mMenuActionMap;
};

#endif // __CUSTOM_MENU_H

#include "customMenu.h"

CustomMenu::CustomMenu(QWidget *parent) : QMenu(parent) {
    setAttribute(Qt::WA_TranslucentBackground);
    CommonUtils::loadStyleSheet(this, "menu");
}

CustomMenu::~CustomMenu() = default;

void CustomMenu::addCustomMenu(const QString &text, const QString &icon, const QString &name) {
    QAction *pAction = addAction(QIcon(icon), name);
    mMenuActionMap.insert(text, pAction);
}

QAction *CustomMenu::getAction(const QString &text) {
    return mMenuActionMap[text];
}

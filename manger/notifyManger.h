#ifndef NOTIFY_MANGER_H
#define NOTIFY_MANGER_H

#include <QObject>
#include "../utils/commonUtils.h"

class NotifyManger : public QObject {
Q_OBJECT

public:
    NotifyManger();

    ~NotifyManger() override;

signals:

    void signalSkinChanged(const QColor &color);

public:
    static NotifyManger *getInstance();

    void notifyOtherWindowChangeSkin(const QColor &color);

private:
    static NotifyManger *instance;
};

#endif // NOTIFY_MANGER_H

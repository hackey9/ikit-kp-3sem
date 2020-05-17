#pragma once

class Store;

#include <QString>
#include <QUuid>

class Store
{
public:
    Store(QString address);
    Store(QUuid id, QString address);

    QUuid id;
    QString address;
};


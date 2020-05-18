#pragma once

class Product;

#include <QUuid>
#include <QString>
#include <QList>
#include "detail.h"

class Product
{
public:
    Product();
    Product(QUuid id, QString code, QString name, QUuid store_id, QList<Detail> details);
    Product(QString code, QString name, QUuid store_id, QList<Detail> details);

    QUuid id;
    QString code;
    QString name;
    QUuid store_id;
    QList<Detail> details;
};

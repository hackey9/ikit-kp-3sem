#pragma once

class Product;

#include <QUuid>
#include <QString>
#include <QVector>
#include "detail.h"

class Product
{
public:
    Product(QUuid id, QString code, QString name, QUuid store_id, QVector<Detail> details);
    Product(QString code, QString name, QUuid store_id, QVector<Detail> details);

    QUuid id;
    QString code;
    QString name;
    QUuid store_id;
    QVector<Detail> details;
};

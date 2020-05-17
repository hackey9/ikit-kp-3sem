#include "product.h"


Product::Product(QUuid id, QString code, QString name, QUuid store_id, QVector<Detail> details)
    : id(id), code(code), name(name), store_id(store_id), details(details)
{
}


Product::Product(QString code, QString name, QUuid store_id, QVector<Detail> details)
    : id(QUuid::createUuid()), code(code), name(name), store_id(store_id), details(details)
{
}

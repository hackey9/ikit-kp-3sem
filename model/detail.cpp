#include "detail.h"

Detail::Detail(QString code, QString name, QUuid &store_id, QUuid &provider_id)
    : id(QUuid::createUuid()), code(code), name(name), store_id(store_id), provider_id(provider_id)
{

}

Detail::Detail(QUuid id, QString code, QString name, QUuid &store_id, QUuid &provider_id)
    : id(id), code(code), name(name), store_id(store_id), provider_id(provider_id)
{

}

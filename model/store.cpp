#include "store.h"

Store::Store(QString address)
    : id(QUuid::createUuid()),
      address(address)
{
}

Store::Store(QUuid id, QString address)
    : id(id),
      address(address)
{
}

Store::Store()
{
}

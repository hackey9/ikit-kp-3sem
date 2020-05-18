#include "company.h"

Company::Company(QUuid id, QString title, QUuid user_id, QUuid store_id)
    : id(id), title(title), user_id(user_id), store_id(store_id)
{
}

Company::Company(QString title, QUuid user_id, QUuid store_id)
    : id(QUuid::createUuid()), title(title), user_id(user_id), store_id(store_id)
{
}

Company::Company()
{
}

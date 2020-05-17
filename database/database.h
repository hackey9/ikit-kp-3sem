#pragma once

class Database;

#include <QUuid>
#include <QString>
#include <QDataStream>
#include "users.h"
#include "storages.h"
#include "details.h"
#include "companies.h"
#include "products.h"


class Database
{
public:
    Database();

    Users users;
    Storages storages;
    Details details;
    Companies companies;
    Products products;
};

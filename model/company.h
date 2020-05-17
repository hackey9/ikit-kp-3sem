#pragma once

class Company;

#include <QString>
#include <QUuid>


class Company
{
public:
    Company(QUuid id, QString title, QUuid user_id, QUuid store_id);
    Company(QString title, QUuid user_id, QUuid store_id);

    QUuid id;
    QString title;
    QUuid user_id;
    QUuid store_id;
};

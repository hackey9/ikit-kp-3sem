#pragma once

#include <QString>
#include <QUuid>

class Detail
{
public:
    Detail(QString code, QString name, QUuid &store_id, QUuid &provider_id);
    Detail(QUuid id, QString code, QString name, QUuid &store_id, QUuid &provider_id);

    QUuid id;
    QString code;
    QString name;
    QUuid store_id;
    QUuid provider_id;
};


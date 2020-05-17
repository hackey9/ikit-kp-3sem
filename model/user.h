#pragma once

class User;
enum UserGroup : int;

#include <QString>
#include <QUuid>
#include <QCryptographicHash>


enum UserGroup : int
{
    Admin,
    Dispatcher,
    Provider,
};

class User
{
public:

    User(QString username, QString password, UserGroup group);
    User(QUuid id, QString username, QString passwordHash, UserGroup group);

    QUuid id;
    QString username;
    QString passwordHash;
    UserGroup group;

    bool CheckPassword(QString password) const;
    void SetPassword(QString password);

private:
    QString hashPassword(QString password) const;
};


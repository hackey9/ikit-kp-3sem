#include "user.h"

User::User(QString username, QString password, UserGroup group) :
    id(QUuid::createUuid()),
    username(username),
    passwordHash(hashPassword(password)),
    group(group)
{
}

User::User(QUuid id, QString username, QString passwordHash, UserGroup group) :
    id(id),
    username(username),
    passwordHash(passwordHash),
    group(group)
{
}

bool User::CheckPassword(QString password) const
{
    return hashPassword(password) == this->passwordHash;
}

void User::SetPassword(QString password)
{
    this->passwordHash = hashPassword(password);
}

QString User::hashPassword(QString password) const
{
    return QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Algorithm::Sha256).toHex();
}

User::User()
{
}

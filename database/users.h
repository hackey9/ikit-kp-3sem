#pragma once

class Users;

#include <QUuid>
#include <QString>
#include <QVector>
#include <QFile>
#include <QDataStream>
#include <QIODevice>
#include "../model/user.h"

class Users
{
    QString filename;
    QVector<User> items;

public:
    Users();

    QVector<User> All() const;

    bool Exists(QUuid id) const;
    User Get(QUuid id) const;

    bool Insert(const User &new_item);
    bool Update(const User &updated_item);
    bool Delete(const User &deleted_item);
    void Clear();

    bool haveUniqueRestriction(const User &left, const User &right, bool compareId = true);

    void readFromStream(QDataStream &stream);
    void writeToStream(QDataStream &stream, const User &item) const;

    void LoadFromFile();
    void SaveToFile() const;

    QUuid FindByUsername(QString username) const;
};


#pragma once


#include <QUuid>
#include <QString>
#include <QVector>
#include <QFile>
#include <QDataStream>
#include <QIODevice>
#include "../model/store.h"


class Storages
{
    QString filename;
    QVector<Store> items;

public:
    Storages();

    QVector<Store> All() const;

    bool Exists(QUuid id) const;
    Store Get(QUuid id) const;

    bool Insert(const Store &new_item);
    bool Update(const Store &updated_item);
    bool Delete(const Store &deleted_item);
    void Clear();

    bool haveUniqueRestriction(const Store &left, const Store &right, bool compareId = true);

    void readFromStream(QDataStream &stream);
    void writeToStream(QDataStream &stream, const Store &item) const;

    void LoadFromFile();
    void SaveToFile() const;
};


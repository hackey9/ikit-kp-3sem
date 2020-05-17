#pragma once

#include <QUuid>
#include <QString>
#include <QVector>
#include <QFile>
#include <QDataStream>
#include <QIODevice>
#include "../model/detail.h"

class Details
{
    QString filename;
    QVector<Detail> items;

public:
    Details();

    QVector<Detail> All() const;

    bool Exists(QUuid id) const;
    Detail Get(QUuid id) const;

    bool Insert(const Detail &new_item);
    bool Update(const Detail &updated_item);
    bool Delete(const Detail &deleted_item);
    void Clear();

    bool haveUniqueRestriction(const Detail &left, const Detail &right, bool compareId = true);

    void readFromStream(QDataStream &stream);
    void writeToStream(QDataStream &stream, const Detail &item) const;

    void LoadFromFile();
    void SaveToFile() const;
};


#pragma once

#include <QUuid>
#include <QString>
#include <QVector>
#include <QFile>
#include <QDataStream>
#include <QIODevice>
#include "../model/company.h"

class Companies
{
    QString filename;
    QVector<Company> items;

public:
    Companies();

    QVector<Company> All() const;

    bool Exists(QUuid id) const;
    Company Get(QUuid id) const;

    QVector<Company> FindByUserId(QUuid user_id) const;

    bool Insert(const Company &new_item);
    bool Update(const Company &updated_item);
    bool Delete(const Company &deleted_item);
    void Clear();

    bool haveUniqueRestriction(const Company &left, const Company &right, bool compareId = true);

    void readFromStream(QDataStream &stream);
    void writeToStream(QDataStream &stream, const Company &item) const;

    void LoadFromFile();
    void SaveToFile() const;
};

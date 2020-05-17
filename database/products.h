#pragma once

#include <QUuid>
#include <QString>
#include <QVector>
#include <QFile>
#include <QDataStream>
#include <QIODevice>
#include "../model/product.h"

class Products
{
    QString filename;
    QVector<Product> items;

public:
    Products();

    QVector<Product> All() const;

    bool Exists(QUuid id) const;
    Product Get(QUuid id) const;

    bool Insert(const Product &new_item);
    bool Update(const Product &updated_item);
    bool Delete(const Product &deleted_item);
    void Clear();

    bool haveUniqueRestriction(const Product &left, const Product &right, bool compareId = true);

    void readFromStream(QDataStream &stream);
    void writeToStream(QDataStream &stream, const Product &item) const;

    void LoadFromFile();
    void SaveToFile() const;
};

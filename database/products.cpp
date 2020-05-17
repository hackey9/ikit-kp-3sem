#include "products.h"

Products::Products()
    : filename("products.bin")
{
    this->LoadFromFile();
    this->SaveToFile();
}

QVector<Product> Products::All() const
{
    return items;
}

bool Products::Exists(QUuid id) const
{
    for(const auto &item : items)
    {
        if (item.id == id)
            return true;
    }

    return false;
}

Product Products::Get(QUuid id) const
{
    for(const auto &item : items)
    {
        if (item.id == id)
            return item;
    }

    throw 0;
}

bool Products::Insert(const Product &new_item)
{
    for(const auto &item : items)
    {
        if (this->haveUniqueRestriction(item, new_item, true))
            return false;
    }

    items.push_back(new_item);

    SaveToFile();
    return true;
}

bool Products::Update(const Product &updated_item)
{
    auto target_it = items.end();

    for (auto it = items.begin(); it != items.end(); it++)
    {
        if (it->id == updated_item.id)
        {
            target_it = it;
        }
        else
        {
            if (this->haveUniqueRestriction(*it, updated_item))
                return false;
        }
    }

    if (target_it != items.end())
    {
        *target_it = updated_item;

        this->SaveToFile();
        return true;
    }
    return false;
}

bool Products::Delete(const Product &deleted_item)
{
    for (auto it = items.begin(); it != items.end(); it++)
    {
        if (it->id == deleted_item.id)
        {
            items.erase(it);

            SaveToFile();
            return true;
        }
    }
    return false;
}

void Products::Clear()
{
    items.clear();
    SaveToFile();
}

bool Products::haveUniqueRestriction(const Product &left, const Product &right, bool compareId)
{
    if (compareId)
    {
        if (left.id == right.id)
            return true;
    }

    return false;
}

void Products::LoadFromFile()
{
    items.clear();

    QFile file(filename);
    if (!file.exists())
        return;

    file.open(QIODevice::ReadOnly);
    QDataStream stream(&file);

    int count = 0;
    stream >> count;

    items.reserve(count);

    for (int i = 0; i < count; i++)
    {
        this->readFromStream(stream);
    }

    file.close();
}

void Products::SaveToFile() const
{
    QFile file(filename);
    file.open(QFile::OpenModeFlag::Truncate | QFile::OpenModeFlag::WriteOnly);
    QDataStream stream(&file);

    const int count = items.count();

    stream << count;

    for (const auto &item : items)
    {
        this->writeToStream(stream, item);
    }

    file.close();
}

void Products::readFromStream(QDataStream &stream)
{
    QUuid id;
    QString code;
    QString name;
    QUuid store_id;
    QVector<Detail> details;

    int details_count;

    stream >> id;
    stream >> code;
    stream >> name;
    stream >> store_id;

    stream >> details_count;
    for (int i = 0; i < details_count; i++)
    {
        QUuid detail_id;
        QString detail_code;
        QString detail_name;
        QUuid detail_store_id;
        QUuid detail_provider_id;

        stream >> detail_id;
        stream >> detail_code;
        stream >> detail_name;
        stream >> detail_store_id;
        stream >> detail_provider_id;

        details.push_back(Detail(detail_id, detail_code, detail_name, detail_store_id, detail_provider_id));
    }

    items.push_back(Product(id, code, name, store_id, details));
}

void Products::writeToStream(QDataStream &stream, const Product &item) const
{
    stream << item.id;
    stream << item.code;
    stream << item.name;
    stream << item.store_id;

    stream << item.details.count();

    for (const Detail &detail : item.details)
    {
        stream << detail.id;
        stream << detail.code;
        stream << detail.name;
        stream << detail.store_id;
        stream << detail.provider_id;
    }
}

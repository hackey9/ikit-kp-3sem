#include "storages.h"

Storages::Storages()
    : filename("storages.bin")
{
    this->LoadFromFile();
    this->SaveToFile();
}

QVector<Store> Storages::All() const
{
    return items;
}

bool Storages::Exists(QUuid id) const
{
    for(const Store &item : items)
    {
        if (item.id == id)
            return true;
    }

    return false;
}

Store Storages::Get(QUuid id) const
{
    for(const Store &item : items)
    {
        if (item.id == id)
            return item;
    }

    throw 0;
}

bool Storages::Insert(const Store &new_item)
{
    for(const Store &item : items)
    {
        if (this->haveUniqueRestriction(item, new_item, true))
            return false;
    }

    items.push_back(new_item);

    SaveToFile();
    return true;
}

bool Storages::Update(const Store &updated_item)
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

bool Storages::Delete(const Store &deleted_item)
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

void Storages::Clear()
{
    items.clear();
    SaveToFile();
}

bool Storages::haveUniqueRestriction(const Store &left, const Store &right, bool compareId)
{
    if (compareId)
    {
        if (left.id == right.id)
            return true;
    }

    if (left.address == right.address)
        return true;

    return false;
}

void Storages::LoadFromFile()
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

void Storages::SaveToFile() const
{
    QFile file(filename);
    file.open(QFile::OpenModeFlag::Truncate | QFile::OpenModeFlag::WriteOnly);
    QDataStream stream(&file);

    const int count = items.count();

    stream << count;

    for (const Store &item : items)
    {
        this->writeToStream(stream, item);
    }

    file.close();
}

void Storages::readFromStream(QDataStream &stream)
{
    QUuid id;
    QString address;

    stream >> id;
    stream >> address;

    items.push_back(Store(id, address));
}

void Storages::writeToStream(QDataStream &stream, const Store &item) const
{
    stream << item.id;
    stream << item.address;
}

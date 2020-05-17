#include "details.h"

Details::Details()
    : filename("details.bin")
{
    this->LoadFromFile();
    this->SaveToFile();
}

QVector<Detail> Details::All() const
{
    return items;
}

bool Details::Exists(QUuid id) const
{
    for(const Detail &item : items)
    {
        if (item.id == id)
            return true;
    }

    return false;
}

Detail Details::Get(QUuid id) const
{
    for(const Detail &item : items)
    {
        if (item.id == id)
            return item;
    }

    throw 0;
}

bool Details::Insert(const Detail &new_item)
{
    for(const Detail &item : items)
    {
        if (this->haveUniqueRestriction(item, new_item, true))
            return false;
    }

    items.push_back(new_item);

    SaveToFile();
    return true;
}

bool Details::Update(const Detail &updated_item)
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

bool Details::Delete(const Detail &deleted_item)
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

void Details::Clear()
{
    items.clear();
    SaveToFile();
}

bool Details::haveUniqueRestriction(const Detail &left, const Detail &right, bool compareId)
{
    if (compareId)
    {
        if (left.id == right.id)
            return true;
    }

    return false;
}

void Details::LoadFromFile()
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

void Details::SaveToFile() const
{
    QFile file(filename);
    file.open(QFile::OpenModeFlag::Truncate | QFile::OpenModeFlag::WriteOnly);
    QDataStream stream(&file);

    const int count = items.count();

    stream << count;

    for (const Detail &item : items)
    {
        this->writeToStream(stream, item);
    }

    file.close();
}

void Details::readFromStream(QDataStream &stream)
{
    QUuid id;
    QString code;
    QString name;
    QUuid store_id;
    QUuid provider_id;

    stream >> id;
    stream >> code;
    stream >> name;
    stream >> store_id;
    stream >> provider_id;

    items.push_back(Detail(id, code, name, store_id, provider_id));
}

void Details::writeToStream(QDataStream &stream, const Detail &item) const
{
    stream << item.id;
    stream << item.code;
    stream << item.name;
    stream << item.store_id;
    stream << item.provider_id;
}

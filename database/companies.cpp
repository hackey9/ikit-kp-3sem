#include "companies.h"

Companies::Companies()
    : filename("companies.bin")
{
    this->LoadFromFile();
    this->SaveToFile();
}

QVector<Company> Companies::All() const
{
    return items;
}

bool Companies::Exists(QUuid id) const
{
    for(const auto &item : items)
    {
        if (item.id == id)
            return true;
    }

    return false;
}

Company Companies::Get(QUuid id) const
{
    for(const auto &item : items)
    {
        if (item.id == id)
            return item;
    }

    throw 0;
}

QVector<Company> Companies::FindByUserId(QUuid user_id) const
{
    QVector<Company> user_items;

    for (const auto &item : items)
    {
        if (item.user_id == user_id)
        {
            user_items.push_back(item);
        }
    }
    return user_items;
}

bool Companies::Insert(const Company &new_item)
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

bool Companies::Update(const Company &updated_item)
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

bool Companies::Delete(const Company &deleted_item)
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

void Companies::Clear()
{
    items.clear();
    SaveToFile();
}

bool Companies::haveUniqueRestriction(const Company &left, const Company &right, bool compareId)
{
    if (compareId)
    {
        if (left.id == right.id)
            return true;
    }

    if (left.title == right.title)
        return true;

    return false;
}

void Companies::LoadFromFile()
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

void Companies::SaveToFile() const
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

void Companies::readFromStream(QDataStream &stream)
{
    QUuid id;
    QString title;
    QUuid user_id;
    QUuid store_id;

    stream >> id;
    stream >> title;
    stream >> user_id;
    stream >> store_id;

    items.push_back(Company(id, title, user_id, store_id));
}

void Companies::writeToStream(QDataStream &stream, const Company &item) const
{
    stream << item.id;
    stream << item.title;
    stream << item.user_id;
    stream << item.store_id;
}

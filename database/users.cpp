#include "users.h"

Users::Users()
    : filename("users.bin")
{
    this->LoadFromFile();
    this->SaveToFile();
}

QVector<User> Users::All() const
{
    return items;
}

bool Users::Exists(QUuid id) const
{
    for(const User &item : items)
    {
        if (item.id == id)
            return true;
    }

    return false;
}

User Users::Get(QUuid id) const
{
    for(const User &item : items)
    {
        if (item.id == id)
            return item;
    }

    throw 0;
}

bool Users::Insert(const User &new_item)
{
    for(const User &item : items)
    {
        if (this->haveUniqueRestriction(item, new_item, true))
            return false;
    }

    items.push_back(new_item);

    SaveToFile();
    return true;
}

bool Users::Update(const User &updated_item)
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

bool Users::Delete(const User &deleted_item)
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

void Users::Clear()
{
    items.clear();
    SaveToFile();
}

bool Users::haveUniqueRestriction(const User &left, const User &right, bool compareId)
{
    if (compareId)
    {
        if (left.id == right.id)
            return true;
    }

    return false;
}

void Users::LoadFromFile()
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

void Users::SaveToFile() const
{
    QFile file(filename);
    file.open(QFile::OpenModeFlag::Truncate | QFile::OpenModeFlag::WriteOnly);
    QDataStream stream(&file);

    const int count = items.count();

    stream << count;

    for (const User &item : items)
    {
        this->writeToStream(stream, item);
    }

    file.close();
}

QUuid Users::FindByUsername(QString username) const
{
    for (const User &item : items)
    {
        if (item.username == username)
            return item.id;
    }
    return QUuid();
}

void Users::readFromStream(QDataStream &stream)
{
    QUuid id;
    QString username;
    QString passwordHash;
    UserGroup group;

    stream >> id;
    stream >> username;
    stream >> passwordHash;
    stream >> group;

    items.push_back(User(id, username, passwordHash, group));
}

void Users::writeToStream(QDataStream &stream, const User &item) const
{
    stream << item.id;
    stream << item.username;
    stream << item.passwordHash;
    stream << item.group;
}

#pragma once
#include <QWidget>
#include "../model/user.h"
#include "../database/database.h"


namespace Ui {
class UserWidget;
}

class UserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserWidget(Database &db, User user, QWidget *parent = nullptr);
    ~UserWidget();

signals:
    void onUserUpdated();

private slots:
    void on_EditButton_clicked();

private:
    Ui::UserWidget *ui;
    Database &db;
    User user;

    QString groupToText(UserGroup group);
};

#pragma once

#include <QDialog>
#include "../database/database.h"
#include "../model/user.h"

namespace Ui {
class UserCreateDialog;
}

class UserCreateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserCreateDialog(Database &db, QWidget *parent = nullptr);
    ~UserCreateDialog();

signals:
    void onUserCreated();

private slots:
    void on_CreateUserButton_clicked();

private:
    Ui::UserCreateDialog *ui;
    Database &db;
};


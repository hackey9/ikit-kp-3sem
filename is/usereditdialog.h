#pragma once

#include <QDialog>
#include "../model/user.h"
#include "../database/database.h"


namespace Ui {
class UserEditDialog;
}

class UserEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserEditDialog(Database &db, User user, QWidget *parent = nullptr);
    ~UserEditDialog();

signals:
    void onUserUpdated();

private slots:
    void on_UsernameButton_clicked();

    void on_GroupButton_clicked();

    void on_PasswordButton_clicked();

private:
    Ui::UserEditDialog *ui;
    Database &db;
    User user;
};

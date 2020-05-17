#pragma once

#include <QDialog>
#include "../model/user.h"
#include "../database/database.h"

namespace Ui {
class ChangePasswordDialog;
}

class ChangePasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePasswordDialog(Database &db, User user, QWidget *parent = nullptr);
    ~ChangePasswordDialog();

private slots:
    void on_ChangeButton_clicked();

private:
    Ui::ChangePasswordDialog *ui;
    Database &db;
    User user;
};


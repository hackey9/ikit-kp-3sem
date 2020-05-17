#pragma once

#include <QMainWindow>
#include "../database/database.h"
#include "../model/user.h"

namespace Ui {
class UsersWindow;
}

class UsersWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UsersWindow(Database &db, User user, QWidget *parent = nullptr);
    ~UsersWindow();

private slots:
    void on_NewUserButton_clicked();

    void on_CloseButton_clicked();

private:
    Ui::UsersWindow *ui;
    Database &db;
    User user;

    void updateList();
};


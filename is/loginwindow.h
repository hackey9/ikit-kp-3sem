#pragma once

#include <QMainWindow>
#include "../database/database.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(Database &db, QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_pushButton_clicked();

    void on_ResetDatabaseButton_clicked();

private:
    Ui::LoginWindow *ui;
    Database &db;
};


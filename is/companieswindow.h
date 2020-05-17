#pragma once

#include <QMainWindow>
#include "../database/database.h"

namespace Ui {
class CompaniesWindow;
}

class CompaniesWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CompaniesWindow(Database &db, const User &user, QWidget *parent = nullptr);
    ~CompaniesWindow();

private slots:
    void on_CloseButton_clicked();

    void on_CreateStoreButton_clicked();

private:
    Ui::CompaniesWindow *ui;
    Database &db;
    User user;

    void updateItems();
};


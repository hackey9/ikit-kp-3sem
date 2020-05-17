#pragma once

#include <QMainWindow>
#include "../database/database.h"

namespace Ui {
class ProductsWindow;
}

class ProductsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProductsWindow(Database &db, const User &user, QWidget *parent = nullptr);
    ~ProductsWindow();

private slots:
    void on_CloseButton_clicked();

    void on_CreateStoreButton_clicked();

private:
    Ui::ProductsWindow *ui;
    Database &db;
    User user;

    void updateItems();
};

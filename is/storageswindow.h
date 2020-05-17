#pragma once

#include <QMainWindow>
#include "../database/database.h"
#include "../model/store.h"

namespace Ui {
class StoragesWindow;
}

class StoragesWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StoragesWindow(Database &db, User user, QWidget *parent = nullptr);
    ~StoragesWindow();

private slots:
    void on_CreateStoreButton_clicked();

    void on_CloseButton_clicked();

private:
    Ui::StoragesWindow *ui;
    Database &db;
    User user;

    void updateItems();
};

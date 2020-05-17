#pragma once

#include <QMainWindow>
#include "../database/database.h"

namespace Ui {
class DetailsWindow;
}

class DetailsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DetailsWindow(Database &db, const User &user, QWidget *parent = nullptr);
    ~DetailsWindow();

private slots:
    void on_CloseButton_clicked();

private:
    Ui::DetailsWindow *ui;
    Database &db;
    User user;

    void updateItems();
};


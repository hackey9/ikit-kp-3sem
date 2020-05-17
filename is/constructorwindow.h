#pragma once

#include <QMainWindow>
#include "../database/database.h"

namespace Ui {
class ConstructorWindow;
}

class ConstructorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConstructorWindow(Database &db, QWidget *parent = nullptr);
    ~ConstructorWindow();

signals:
    void onProductBuilt();

private slots:
    void on_BuildButton_clicked();

private:
    Ui::ConstructorWindow *ui;
    Database &db;
    QVector<Detail> storedDetails;
    QVector<Detail> selectedDetails;

    void updateItems();
};


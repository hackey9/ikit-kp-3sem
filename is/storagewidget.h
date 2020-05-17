#pragma once

#include <QWidget>
#include "../database/database.h"
#include "../model/store.h"

namespace Ui {
class StorageWidget;
}

class StorageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StorageWidget(Database &db, Store store, QWidget *parent = nullptr);
    ~StorageWidget();

signals:
    void onStorageChanged();

private slots:
    void on_EditButton_clicked();

private:
    Ui::StorageWidget *ui;
    Database &db;
    Store store;
};


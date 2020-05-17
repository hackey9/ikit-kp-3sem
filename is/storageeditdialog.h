#pragma once

#include <QDialog>
#include "../database/database.h"
#include "../model/store.h"

namespace Ui {
class StorageEditDialog;
}

class StorageEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StorageEditDialog(Database &db, Store store, QWidget *parent = nullptr);
    ~StorageEditDialog();

signals:
    void onStorageChanged();

private slots:
    void on_ChangeStorageButton_clicked();

private:
    Ui::StorageEditDialog *ui;
    Database &db;
    Store store;
};


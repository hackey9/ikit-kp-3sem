#pragma once

#include <QDialog>
#include "../database/database.h"

namespace Ui {
class StorageCreateDialog;
}

class StorageCreateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StorageCreateDialog(Database &db, QWidget *parent = nullptr);
    ~StorageCreateDialog();

signals:
    void onStoreCreated();

private slots:
    void on_AddStorageButton_clicked();

private:
    Ui::StorageCreateDialog *ui;
    Database &db;
};

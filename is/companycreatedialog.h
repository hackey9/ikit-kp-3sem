#pragma once

#include <QDialog>
#include <QVector>
#include "../database/database.h"

namespace Ui {
class CompanyCreateDialog;
}

class CompanyCreateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CompanyCreateDialog(Database &db, QWidget *parent = nullptr);
    ~CompanyCreateDialog();

signals:
    void onCompanyCreated();

private slots:
    void on_CreateCompanyButton_clicked();

private:
    Ui::CompanyCreateDialog *ui;
    Database &db;
    QVector<User> providers;
    QVector<Store> storages;
};


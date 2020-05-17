#pragma once

#include <QDialog>
#include "../database/database.h"

namespace Ui {
class CompanyEditDialog;
}

class CompanyEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CompanyEditDialog(Database &db, const Company &company, QWidget *parent = nullptr);
    ~CompanyEditDialog();

signals:
    void onCompanyEdited();

private slots:
    void on_ChangeNameButton_clicked();

    void on_ChangeUsernameButton_clicked();

    void on_ChangeStoreButton_clicked();

private:
    Ui::CompanyEditDialog *ui;
    Database &db;
    Company company;
};

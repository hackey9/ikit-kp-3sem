#pragma once

#include <QWidget>
#include "../database/database.h"

namespace Ui {
class CompanyWidget;
}

class CompanyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CompanyWidget(Database &db, Company company, QWidget *parent = nullptr);
    ~CompanyWidget();

signals:
    void onCompanyChanged(CompanyWidget *sender);

private slots:
    void on_EditButton_clicked();

private:
    Ui::CompanyWidget *ui;
    Database &db;
    Company company;
};

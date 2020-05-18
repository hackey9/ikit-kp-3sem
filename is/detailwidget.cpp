#include "detailwidget.h"
#include "ui_detailwidget.h"
#include <QMessageBox>
#include <QPushButton>

DetailWidget::DetailWidget(Database &db, Detail detail, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DetailWidget),
    db(db),
    detail(detail)
{
    ui->setupUi(this);

    ui->CodeLabel->setText(detail.code);
    ui->NameLabel->setText(detail.name);

    if (db.storages.Exists(detail.store_id))
    {
        Store store = db.storages.Get(detail.store_id);
        ui->AddressLabel->setText(store.address);
    }
    else
    {
        ui->AddressLabel->setText("(адрес не указан)");
    }

    if (db.companies.Exists(detail.provider_id))
    {
        Company company = db.companies.Get(detail.provider_id);
        ui->ProviderLabel->setText(company.title);
    }
    else
    {
        ui->ProviderLabel->setText("(поставщик не указан)");
    }
}

DetailWidget::~DetailWidget()
{
    delete ui;
}

void DetailWidget::on_DeleteButton_clicked()
{
    auto confirm = QMessageBox::question(this, "Удалить деталь?", detail.name, QMessageBox::Yes | QMessageBox::No);

    if (confirm == QMessageBox::Yes)
    {
        db.details.Delete(detail);
        emit onDetailChanged(this);
    }
}

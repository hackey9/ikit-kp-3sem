#include "storageeditdialog.h"
#include "ui_storageeditdialog.h"

#include <QMessageBox>

StorageEditDialog::StorageEditDialog(Database &db, Store store, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StorageEditDialog),
    db(db),
    store(store)
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModality::ApplicationModal);

    ui->InitialStorageNameInput->setText(store.address);
    ui->AddressInput->setText(store.address);
}

StorageEditDialog::~StorageEditDialog()
{
    delete ui;
}

void StorageEditDialog::on_ChangeStorageButton_clicked()
{
    QString address = ui->AddressInput->text().trimmed();

    if (address.length() < 2)
    {
        QMessageBox message;
        message.setText("Минимум 2 символа");
        message.exec();
        return;
    }

    Store updated_store = store;
    updated_store.address = address;

    if (db.storages.Update(updated_store))
    {
        emit onStorageChanged();

        QMessageBox message;
        message.setText("Адрес изменён");
        message.exec();

        close();
    }
    else
    {
        QMessageBox message;
        message.setText("Адрес не был изменён.");
        message.setDetailedText("Возможно, склад с таким адресом уже существует.");
        message.exec();
    }
}

#include "storagecreatedialog.h"
#include "ui_storagecreatedialog.h"
#include "storagecreatedialog.h"

#include <QMessageBox>

StorageCreateDialog::StorageCreateDialog(Database &db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StorageCreateDialog),
    db(db)
{
    ui->setupUi(this);

    setWindowModality(Qt::WindowModality::ApplicationModal);
}

StorageCreateDialog::~StorageCreateDialog()
{
    delete ui;
}

void StorageCreateDialog::on_AddStorageButton_clicked()
{
    QString address = ui->AddressInput->text().trimmed();

    if (address.length() < 2)
    {
        QMessageBox message;
        message.setText("Минимум 2 символа");
        message.exec();
        return;
    }

    Store store(address);

    if (db.storages.Insert(store))
    {
        emit onStoreCreated();

        QMessageBox message;
        message.setText("Склад добавлен.");
        message.exec();

        close();
        deleteLater();
    }
    else
    {
        QMessageBox message;
        message.setText("Скад не был добавлен.");
        message.setDetailedText("Возможно, скад с таким адресом уже существует");
        message.exec();
    }
}

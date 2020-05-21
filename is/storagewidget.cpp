#include "storagewidget.h"
#include "ui_storagewidget.h"
#include "storageeditdialog.h"
#include <QMessageBox>

StorageWidget::StorageWidget(Database &db, Store store, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StorageWidget),
    db(db),
    store(store)
{
    ui->setupUi(this);

    ui->AddressLabel->setText(store.address);
}

StorageWidget::~StorageWidget()
{
    delete ui;
}

void StorageWidget::on_EditButton_clicked()
{
    StorageEditDialog *dialog = new StorageEditDialog(db, store);
    dialog->show();

    QObject::connect(dialog, &StorageEditDialog::onStorageChanged, [=](){ emit onStorageChanged(); });
}

void StorageWidget::on_pushButton_clicked()
{
    if (QMessageBox::question(this, "Удалить склад?", store.address) == QMessageBox::Yes)
    {
        db.storages.Delete(store);
        emit onStorageChanged();
    }
}

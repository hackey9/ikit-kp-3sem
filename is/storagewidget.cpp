#include "storagewidget.h"
#include "ui_storagewidget.h"
#include "storageeditdialog.h"

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

#include "storageswindow.h"
#include "ui_storageswindow.h"
#include "storagewidget.h"
#include "storagecreatedialog.h"
#include "mainwindow.h"

StoragesWindow::StoragesWindow(Database &db, User user, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StoragesWindow),
    db(db),
    user(user)
{
    ui->setupUi(this);

    updateItems();
}

StoragesWindow::~StoragesWindow()
{
    delete ui;
}

void StoragesWindow::updateItems()
{
    while (auto item = ui->StoragesAreaContent->layout()->itemAt(0)) {
        ui->StoragesAreaContent->layout()->removeItem(item);
        item->widget()->deleteLater();
    }

    QVector<Store> storages = db.storages.All();

    for (Store &store : storages)
    {
        StorageWidget *widget = new StorageWidget(db, store);
        ui->StoragesAreaContent->layout()->addWidget(widget);

        QObject::connect(widget, &StorageWidget::onStorageChanged, [=](){ updateItems(); });
    }

    ui->StoragesAreaContent->layout()->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

void StoragesWindow::on_CreateStoreButton_clicked()
{
    StorageCreateDialog *dialog = new StorageCreateDialog(db);
    dialog->show();

    QObject::connect(dialog, &StorageCreateDialog::onStoreCreated, [=](){ updateItems(); });
}

void StoragesWindow::on_CloseButton_clicked()
{
    close();
    deleteLater();

    MainWindow *window = new MainWindow(db, user);
    window->show();
}

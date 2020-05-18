#include "constructorwindow.h"
#include "ui_constructorwindow.h"
#include <QMessageBox>
#include "constructordetailwidget.h"

ConstructorWindow::ConstructorWindow(Database &db, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConstructorWindow),
    db(db)
{
    ui->setupUi(this);

    setWindowModality(Qt::WindowModality::ApplicationModal);

    storedDetails = db.details.All();

    for (const auto &store : db.storages.All())
    {
        ui->StoreSelect->addItem(store.address);
    }

    updateItems();
}

ConstructorWindow::~ConstructorWindow()
{
    delete ui;
}

void ConstructorWindow::on_BuildButton_clicked()
{
    QString product_code = ui->CodeInput->text();
    QString product_name = ui->NameInput->text();
    int store_index = ui->StoreSelect->currentIndex();

    auto storages = db.storages.All();

    if (store_index < 0 || store_index >= storages.length())
    {
        QMessageBox message;
        message.setText("Выберите склад");
        message.exec();
        return;
    }

    Store store = storages[store_index];

    if (product_code.length() < 2)
    {
        QMessageBox message;
        message.setText("Код изделия - минимум 2 символа");
        message.exec();
        return;
    }

    if (product_name.length() < 2)
    {
        QMessageBox message;
        message.setText("Наименование изделия - минимум 2 символа");
        message.exec();
        return;
    }

    if (selectedDetails.length() < 2)
    {
        QMessageBox message;
        message.setText("Хотя-бы 2 детали в изделии");
        message.exec();
        return;
    }

    if (!db.products.Insert(Product(product_code, product_name, store.id, selectedDetails.toList())))
    {
        QMessageBox message;
        message.setText("Не удалось создать изделие");
        message.exec();
        return;
    }

    for (const auto &detail : selectedDetails)
    {
        db.details.Delete(detail);
    }

    emit onProductBuilt();

    close();
    deleteLater();
}

void ConstructorWindow::updateItems()
{
    // stored

    while (auto item = ui->StoredScrollAreaContent->layout()->itemAt(0)) {
        ui->StoredScrollAreaContent->layout()->removeItem(item);
        item->widget()->deleteLater();
    }

    for (const auto &detail : storedDetails)
    {
        ConstructorDetailWidget *widget = new ConstructorDetailWidget(detail, CtorDirection::AddToDetail, this);
        ui->StoredScrollAreaContent->layout()->addWidget(widget);

        QObject::connect(widget, &ConstructorDetailWidget::onDetailSelected, [=](QUuid detail_id, CtorDirection direction)
        {
            for (auto it = storedDetails.begin(); it != storedDetails.end(); it++)
            {
                if (it->id == detail_id)
                {
                    selectedDetails.push_back(*it);
                    storedDetails.erase(it);

                    updateItems();
                    return;
                }
            }
        });
    }

    ui->StoredScrollAreaContent->layout()->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    // selected

    while (auto item = ui->SelectedScrollAreaContent->layout()->itemAt(0)) {
        ui->SelectedScrollAreaContent->layout()->removeItem(item);
        item->widget()->deleteLater();
    }

    QVector<Company> companies = db.companies.All();

    for (const auto &detail : selectedDetails)
    {
        ConstructorDetailWidget *widget = new ConstructorDetailWidget(detail, CtorDirection::RemoveToStore, this);
        ui->SelectedScrollAreaContent->layout()->addWidget(widget);

        QObject::connect(widget, &ConstructorDetailWidget::onDetailSelected, [=](QUuid detail_id, CtorDirection direction)
        {
            for (auto it = selectedDetails.begin(); it != selectedDetails.end(); it++)
            {
                if (it->id == detail_id)
                {
                    storedDetails.push_back(*it);
                    selectedDetails.erase(it);

                    updateItems();
                    return;
                }
            }
        });
    }

    ui->SelectedScrollAreaContent->layout()->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

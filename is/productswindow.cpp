#include "productswindow.h"
#include "ui_productswindow.h"
#include "productwidget.h"
#include "mainwindow.h"
#include "constructorwindow.h"

ProductsWindow::ProductsWindow(Database &db, const User &user, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProductsWindow),
    db(db),
    user(user)
{
    ui->setupUi(this);

    updateItems();
}

void ProductsWindow::updateItems()
{
    while (auto item = ui->ScrollAreaContent->layout()->itemAt(0)) {
        ui->ScrollAreaContent->layout()->removeItem(item);
        item->widget()->deleteLater();
    }

    QVector<Product> products = db.products.All();

    for (const auto &product : products)
    {
        ProductWidget *widget = new ProductWidget(db, product, this);
        ui->ScrollAreaContent->layout()->addWidget(widget);
    }

    ui->ScrollAreaContent->layout()->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding));
}

ProductsWindow::~ProductsWindow()
{
    delete ui;
}

void ProductsWindow::on_CloseButton_clicked()
{
    close();
    deleteLater();

    MainWindow *window = new MainWindow(db, user);
    window->show();
}

void ProductsWindow::on_CreateStoreButton_clicked()
{
    ConstructorWindow *window = new ConstructorWindow(db);
    window->show();

    QObject::connect(window, &ConstructorWindow::onProductBuilt, [=]() { updateItems(); });
}

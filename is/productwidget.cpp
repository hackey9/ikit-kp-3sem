#include "productwidget.h"
#include "ui_productwidget.h"
#include "productdetailwidget.h"

ProductWidget::ProductWidget(Database &db, const Product &product, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductWidget),
    db(db),
    product(product)
{
    ui->setupUi(this);

    ui->CodeLabel->setText(product.code);
    ui->NameLabel->setText(product.name);

    for (const Detail &detail : product.details)
    {
        ProductDetailWidget *widget = new ProductDetailWidget(db, detail, this);
        ui->ScrollAreaContent->layout()->addWidget(widget);
    }

    ui->ScrollAreaContent->layout()->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

ProductWidget::~ProductWidget()
{
    delete ui;
}

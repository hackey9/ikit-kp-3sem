#include "productdetailwidget.h"
#include "ui_productdetailwidget.h"

ProductDetailWidget::ProductDetailWidget(Database &db, const Detail &detail, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductDetailWidget),
    db(db),
    detail(detail)
{
    ui->setupUi(this);

    ui->CodeLabel->setText(detail.code);
    ui->NameLabel->setText(detail.name);
}

ProductDetailWidget::~ProductDetailWidget()
{
    delete ui;
}

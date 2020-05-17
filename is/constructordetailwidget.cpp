#include "constructordetailwidget.h"
#include "ui_constructordetailwidget.h"

ConstructorDetailWidget::ConstructorDetailWidget(const Detail &detail, CtorDirection direction, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConstructorDetailWidget),
    detail(detail),
    direction(direction)
{
    ui->setupUi(this);

    if (direction == AddToDetail) {
        ui->SelectButton->setText("Добавить");
    } else {
        ui->SelectButton->setText("Убрать");
    }

    ui->CodeLabel->setText(detail.code);
    ui->NameLabel->setText(detail.name);
}

ConstructorDetailWidget::~ConstructorDetailWidget()
{
    delete ui;
}

void ConstructorDetailWidget::on_SelectButton_clicked()
{
    emit onDetailSelected(detail.id, direction);
}

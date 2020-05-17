#pragma once

#include <QWidget>
#include "../database/database.h"

namespace Ui {
class ProductDetailWidget;
}

class ProductDetailWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProductDetailWidget(Database &db, const Detail &detail, QWidget *parent = nullptr);
    ~ProductDetailWidget();

private:
    Ui::ProductDetailWidget *ui;
    Database &db;
    Detail detail;
};

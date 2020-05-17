#pragma once

#include <QWidget>
#include "../database/database.h"

namespace Ui {
class ProductWidget;
}

class ProductWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProductWidget(Database &db, const Product &product, QWidget *parent = nullptr);
    ~ProductWidget();

private:
    Ui::ProductWidget *ui;
    Database &db;
    Product product;
};


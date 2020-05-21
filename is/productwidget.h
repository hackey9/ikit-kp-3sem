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

signals:
    void onProductUpdated();

private slots:
    void on_DeconstructButton_clicked();

private:
    Ui::ProductWidget *ui;
    Database &db;
    Product product;
};


#pragma once

#include <QWidget>
#include "../database/database.h"

namespace Ui {
class DetailWidget;
}

class DetailWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DetailWidget(Database &db, Detail detail, QWidget *parent = nullptr);
    ~DetailWidget();

signals:
    void onDetailChanged(DetailWidget *sender);

private:
    Ui::DetailWidget *ui;
    Database &db;
    Detail detail;
};


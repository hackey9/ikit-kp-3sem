#pragma once

#include <QWidget>
#include "../database/database.h"

namespace Ui {
class ConstructorDetailWidget;
}

enum CtorDirection : bool
{
    AddToDetail = false,
    RemoveToStore = true,
};

class ConstructorDetailWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConstructorDetailWidget(const Detail &detail, CtorDirection direction, QWidget *parent = nullptr);
    ~ConstructorDetailWidget();

signals:
    void onDetailSelected(QUuid detail_id, CtorDirection direction);

private slots:
    void on_SelectButton_clicked();

private:
    Ui::ConstructorDetailWidget *ui;
    Detail detail;
    CtorDirection direction;
};


#pragma once

#include <QMainWindow>
#include "../database/database.h"

namespace Ui {
class DetailsWindow;
}

class DetailsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DetailsWindow(Database &db, const User &user, QWidget *parent = nullptr);
    ~DetailsWindow();

private slots:
    void on_CloseButton_clicked();

    void on_ResetSearchButton_clicked();

    void on_SearchInput_textChanged(const QString &arg1);

    void on_SortSelect_currentIndexChanged(int index);

private:
    Ui::DetailsWindow *ui;
    Database &db;
    User user;
    QVector<Detail> details;

    void updateItems();
};


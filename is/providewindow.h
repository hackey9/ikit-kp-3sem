#pragma once

#include <QMainWindow>
#include "../database/database.h"

namespace Ui {
class ProvideWindow;
}

class ProvideWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProvideWindow(Database &db, const User &user, QWidget *parent = nullptr);
    ~ProvideWindow();

private slots:
    void on_CloseButton_clicked();

    void on_ProviderSelect_currentIndexChanged(int index);

    void on_ProvideButton_clicked();

private:
    Ui::ProvideWindow *ui;
    Database &db;
    User user;

    QUuid company_id;
};


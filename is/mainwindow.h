#pragma once

#include <QMainWindow>
#include "../model/user.h"
#include "../database/database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Database &db, User user, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ChangePasswordButton_clicked();

    void on_UsersButton_clicked();

    void on_StoragesButton_clicked();

    void on_ProvidersButton_clicked();

    void on_DetailsButton_clicked();

    void on_LogoutButton_clicked();

    void on_ProductsButton_clicked();

    void on_ProvideButton_clicked();

private:
    Ui::MainWindow *ui;
    Database &db;
    User user;
};


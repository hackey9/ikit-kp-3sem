#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "changepassworddialog.h"
#include "userswindow.h"
#include "storageswindow.h"
#include "detailswindow.h"
#include "companieswindow.h"
#include "loginwindow.h"
#include "productswindow.h"
#include "providewindow.h"

MainWindow::MainWindow(Database &db, User user, QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow),
    db(db),
    user(user)
{
    ui->setupUi(this);

    if (user.group == Admin) {
        ui->UsersButton->setEnabled(true);
        ui->StoragesButton->setEnabled(true);
        ui->ProvidersButton->setEnabled(true);

        ui->DetailsButton->setEnabled(true);
        ui->ProductsButton->setEnabled(true);
    }

    if (user.group == Dispatcher) {
        ui->DetailsButton->setEnabled(true);
        ui->ProductsButton->setEnabled(true);
        ui->ProvidersButton->setEnabled(true);
    }

    if (user.group == Provider) {
        ui->ProvideButton->setEnabled(true);
    }

    ui->UsernameLabel->setText(user.username);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ChangePasswordButton_clicked()
{
    ChangePasswordDialog *dialog = new ChangePasswordDialog(db, user);
    dialog->show();
}

void MainWindow::on_UsersButton_clicked()
{
    close();
    deleteLater();

    UsersWindow *window = new UsersWindow(db, user);
    window->show();
}

void MainWindow::on_StoragesButton_clicked()
{
    close();
    deleteLater();

    StoragesWindow *window = new StoragesWindow(db, user);
    window->show();
}

void MainWindow::on_ProvidersButton_clicked()
{
    close();
    deleteLater();

    CompaniesWindow *window = new CompaniesWindow(db, user);
    window->show();
}

void MainWindow::on_DetailsButton_clicked()
{
    close();
    deleteLater();

    DetailsWindow *window = new DetailsWindow(db, user);
    window->show();
}

void MainWindow::on_LogoutButton_clicked()
{
    close();
    deleteLater();

    LoginWindow *window = new LoginWindow(db);
    window->show();
}

void MainWindow::on_ProductsButton_clicked()
{
    close();
    deleteLater();

    ProductsWindow *window = new ProductsWindow(db, user);
    window->show();
}

void MainWindow::on_ProvideButton_clicked()
{
    close();
    deleteLater();

    ProvideWindow *window = new ProvideWindow(db, user);
    window->show();
}

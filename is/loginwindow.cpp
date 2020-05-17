#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
#include "mainwindow.h"

LoginWindow::LoginWindow(Database &db, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow),
    db(db)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_pushButton_clicked()
{
    QString username = ui->UsernameInput->text();
    QString password = ui->PasswordInput->text();

    QUuid id = db.users.FindByUsername(username);
    if (id.isNull()) {
        QMessageBox message;
        message.setText("Неправильное имя пользователя (1)");
        message.exec();
        return;
    }

    if (!db.users.Exists(id)) {
        QMessageBox message;
        message.setText("Неправильное имя пользователя (2)");
        message.exec();
        return;
    }

    User user = db.users.Get(id);

    if (!user.CheckPassword(password)) {
        QMessageBox message;
        message.setText("Неверный пароль");
        message.exec();
        return;
    }

    close();
    deleteLater();

    MainWindow *window = new MainWindow(db, user);
    window->show();
}

void LoginWindow::on_ResetDatabaseButton_clicked()
{
    ui->UsernameInput->setText("admin");
    ui->PasswordInput->setText("admin");

    // Users

    db.users.Clear();
    User u_admin("admin", "admin", Admin);
    User u_dispatcher("dispatcher", "dispatcher", Dispatcher);
    User u_provider("provider", "provider", Provider);

    db.users.Insert(u_admin);
    db.users.Insert(u_dispatcher);
    db.users.Insert(u_provider);

    // Storages

    db.storages.Clear();
    Store store("Борисова 24");
    db.storages.Insert(store);

    // Providers

    db.companies.Clear();
    Company provider("Магазин \"АвтоМотоВелоФото\"", u_provider.id, store.id);

    db.companies.Insert(provider);

    // Details

    db.details.Clear();
    Detail koleso_pered("koleso", "Колесо '13 вело", store.id, provider.id);
    Detail koleso_zad("kolesoz", "Колесо заднее '13 вело", store.id, provider.id);
    Detail rama("rama", "Рама стальная", store.id, provider.id);
    Detail rul("rul", "Руль велосипедный", store.id, provider.id);
    Detail tsep("tsep", "Цепь для велосипеда", store.id, provider.id);
    Detail pedali("pedali", "Педали для велосипеда", store.id, provider.id);
    Detail accum("accum", "Аккумулятор 5V 40A", store.id, provider.id);
    Detail engine("engine", "Двигатель электрический", store.id, provider.id);
    Detail provodka("engine", "Проводка в асс.", store.id, provider.id);
    Detail controller("engine", "Контроллер для двигателя", store.id, provider.id);
    Detail krilo("krilo", "Крыло самолёт. 4м длин.", store.id, provider.id);

    db.details.Insert(koleso_pered);
    db.details.Insert(koleso_zad);
    db.details.Insert(rama);
    db.details.Insert(rul);
    db.details.Insert(tsep);
    db.details.Insert(pedali);
    db.details.Insert(accum);
    db.details.Insert(engine);
    db.details.Insert(provodka);
    db.details.Insert(controller);
    db.details.Insert(krilo);

    // Products

    db.products.Clear();
    Product samolet("TY24", "Экспериментальный самолёт", store.id, {
                        Detail("TY24", "Крыло (лев.)", store.id, provider.id),
                        Detail("TY24", "Крыло (пр.)", store.id, provider.id),
                        Detail("TY24", "Борт", store.id, provider.id),
                        Detail("TY24", "Двигатель", store.id, provider.id),
                        Detail("TY24", "Винт", store.id, provider.id),
                        Detail("TY24", "Шасси", store.id, provider.id),
                        Detail("TY24", "Фюзеляж", store.id, provider.id),
                    });

    Product bolt("BOLT", "Болт с гайкой", store.id, {
                        Detail("BOLT", "Болт", store.id, provider.id),
                        Detail("BOLT", "Гайка", store.id, provider.id),
                    });

    db.products.Insert(samolet);
    db.products.Insert(bolt);
}

#include "userswindow.h"
#include "ui_userswindow.h"
#include "userwidget.h"
#include "usercreatedialog.h"
#include "mainwindow.h"

UsersWindow::UsersWindow(Database &db, User user, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UsersWindow),
    db(db),
    user(user)
{
    ui->setupUi(this);

    updateList();
}

UsersWindow::~UsersWindow()
{
    delete ui;
}

void UsersWindow::updateList()
{
    while (auto item = ui->UsersListContent->layout()->itemAt(0)) {
        ui->UsersListContent->layout()->removeItem(item);
        item->widget()->deleteLater();
    }

    QVector<User> users = db.users.All();

    for (User &user : users)
    {
        UserWidget *widget = new UserWidget(db, user);
        ui->UsersListContent->layout()->addWidget(widget);

        QObject::connect(widget, &UserWidget::onUserUpdated, [=](){ updateList(); });
    }

    ui->UsersListContent->layout()->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

void UsersWindow::on_NewUserButton_clicked()
{
    UserCreateDialog *dialog = new UserCreateDialog(db);
    dialog->show();

    QObject::connect(dialog, &UserCreateDialog::onUserCreated, [=](){ updateList(); });
}

void UsersWindow::on_CloseButton_clicked()
{
    close();
    deleteLater();

    MainWindow *window = new MainWindow(db, user);
    window->show();
}

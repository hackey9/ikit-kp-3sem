#include "usercreatedialog.h"
#include "ui_usercreatedialog.h"
#include <QMessageBox>

UserCreateDialog::UserCreateDialog(Database &db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserCreateDialog),
    db(db)
{
    ui->setupUi(this);

    setWindowModality(Qt::WindowModality::ApplicationModal);
}

UserCreateDialog::~UserCreateDialog()
{
    delete ui;
}

void UserCreateDialog::on_CreateUserButton_clicked()
{
    QString username = ui->UsernameInput->text().trimmed();
    QString password = ui->PasswordInput->text().trimmed();
    QString password_confirm = ui->PasswordConfirmInput->text();
    UserGroup group = (UserGroup)ui->GroupDropdown->currentIndex();

    if (username.length() < 2)
    {
        QMessageBox message;
        message.setText("Имя пользователя должно содержать минимум 2 символа.");
        message.exec();
        return;
    }

    if (password != password_confirm)
    {
        QMessageBox message;
        message.setText("Пароли не совпадают.");
        message.exec();
        return;
    }

    if (password.length() < 6)
    {
        QMessageBox message;
        message.setText("Пароль должен содержать минимум 6 символов.");
        message.exec();
        return;
    }

    User user(username, password, group);

    if (db.users.Insert(user))
    {
        emit onUserCreated();

        QMessageBox message;
        message.setText("Пользователь добавлен.");
        message.exec();

        close();
    }
    else
    {
        QMessageBox message;
        message.setText("Не удалось добавить пользователя.");
        message.setDetailedText("Возможно, в системе уже есть пользователь с таким именем.");
        message.exec();
    }
}

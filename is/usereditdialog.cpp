#include "usereditdialog.h"
#include "ui_usereditdialog.h"
#include <QMessageBox>

UserEditDialog::UserEditDialog(Database &db, User user, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserEditDialog),
    db(db),
    user(user)
{
    ui->setupUi(this);

    setWindowModality(Qt::WindowModality::ApplicationModal);

    ui->UsernameInput->setText(user.username);
    ui->CurrentUsernameInput->setText(user.username);

    auto getUserGroupName = [](UserGroup group) {
        switch (group) {
        case Admin: return "Администратор";
        case Dispatcher: return "Диспетчер";
        case Provider: return "Поставщик";
        }
        return "Не определена";
    };

    ui->CurrentUserGroupInput->setText(getUserGroupName(user.group));
}

UserEditDialog::~UserEditDialog()
{
    delete ui;
}

void UserEditDialog::on_UsernameButton_clicked()
{
    QString username = ui->UsernameInput->text().trimmed();
    User updated_user = user;
    updated_user.username = username;

    if (username.length() < 2) {
        QMessageBox message;
        message.setText("Минимум 2 символа.");
        message.exec();
        return;
    }

    if (db.users.Update(updated_user))
    {
        emit onUserUpdated();

        QMessageBox message;
        message.setText("Изменения применены.");
        message.exec();
        close();
    }
    else
    {
        QMessageBox message;
        message.setText("Не удалось изменить имя пользователя");
        message.setInformativeText("Возможно, в системе уже есть пользователь с таким именем");
        message.exec();
    }
}

void UserEditDialog::on_GroupButton_clicked()
{
    UserGroup group = (UserGroup)ui->GroupDropdown->currentIndex();

    User updated_user = user;
    updated_user.group = group;

    if (db.users.Update(updated_user))
    {
        emit onUserUpdated();

        QMessageBox message;
        message.setText("Изменения применены.");
        message.exec();
        close();
    }
    else
    {
        QMessageBox message;
        message.setText("Не удалось изменить группу пользователя");
        message.exec();
    }
}

void UserEditDialog::on_PasswordButton_clicked()
{
    QString password = ui->PasswordInput->text().trimmed();
    QString password_confirm = ui->PasswordConfirmInput->text();

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
        message.setText("Пароль должен быть больше 6 символов.");
        message.exec();
        return;
    }

    User updated_user = user;
    updated_user.SetPassword(password);

    if (db.users.Update(updated_user))
    {
        emit onUserUpdated();

        QMessageBox message;
        message.setText("Изменения применены.");
        message.exec();

        close();
    }
    else
    {
        QMessageBox message;
        message.setText("Не удалось изменить пароль пользователя");
        message.exec();
    }
}

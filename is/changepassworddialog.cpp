#include "changepassworddialog.h"
#include "ui_changepassworddialog.h"
#include <QMessageBox>

ChangePasswordDialog::ChangePasswordDialog(Database &db, User user, QWidget *parent) : QDialog(parent),
    ui(new Ui::ChangePasswordDialog),
    db(db),
    user(user)
{
    ui->setupUi(this);

    setWindowModality(Qt::WindowModality::ApplicationModal);
}

ChangePasswordDialog::~ChangePasswordDialog()
{
    delete ui;
}

void ChangePasswordDialog::on_ChangeButton_clicked()
{
    QString password = ui->PasswordInput->text().trimmed();
    QString password_confirm = ui->PasswordConfirmInput->text();

    if (password != password_confirm)
    {
        QMessageBox message;
        message.setText("Пароли не совпадают");
        message.exec();
        return;
    }

    if (password.length() < 6)
    {
        QMessageBox message;
        message.setText("Пароль длиной не менее 6 символов");
        message.exec();
        return;
    }

    user.SetPassword(password);
    db.users.Update(user);

    close();
    deleteLater();
}

#include "userwidget.h"
#include "ui_userwidget.h"
#include "usereditdialog.h"

UserWidget::UserWidget(Database &db, User user, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserWidget),
    db(db),
    user(user)
{
    ui->setupUi(this);

    ui->UsernameLabel->setText(user.username);
    ui->GroupLabel->setText(groupToText(user.group));
}

UserWidget::~UserWidget()
{
    delete ui;
}

void UserWidget::on_EditButton_clicked()
{
    UserEditDialog *dialog = new UserEditDialog(db, user);
    dialog->show();

    QObject::connect(dialog, &UserEditDialog::onUserUpdated, [=](){ emit onUserUpdated(); });
}

QString UserWidget::groupToText(UserGroup group)
{
    if (group == Admin) return "Администратор";
    if (group == Dispatcher) return "Диспетчер";
    if (group == Provider) return "Поставщик";

    return "Группа не определена";
}

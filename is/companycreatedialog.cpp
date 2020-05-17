#include "companycreatedialog.h"
#include "ui_companycreatedialog.h"
#include <QMessageBox>

CompanyCreateDialog::CompanyCreateDialog(Database &db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CompanyCreateDialog),
    db(db)
{
    ui->setupUi(this);

    setWindowModality(Qt::WindowModality::ApplicationModal);

    for (const User &user : db.users.All())
    {
        if (user.group == Provider)
        {
            providers.push_back(user);
            ui->UserSelectInput->addItem(user.username);
        }
    }

    storages = db.storages.All();

    for (const Store &store : db.storages.All())
    {
        ui->StorageSelect->addItem(store.address);
    }
}

CompanyCreateDialog::~CompanyCreateDialog()
{
    delete ui;
}

void CompanyCreateDialog::on_CreateCompanyButton_clicked()
{
    QString name = ui->NameInput->text();

    int store_index = ui->StorageSelect->currentIndex();
    if (store_index < 0 || store_index >= storages.length())
    {
        QMessageBox message;
        message.setText("Выберите склад");
        message.exec();
        return;
    }
    Store store = storages[store_index];

    QString username = ui->UserSelectInput->currentText();

    QUuid user_id = db.users.FindByUsername(username);

    if (!db.users.Exists(user_id))
    {
        QMessageBox message;
        message.setText("Пользователь не найден");
        message.exec();
        return;
    }

    User user = db.users.Get(user_id);
    if (user.group != Provider)
    {
        QMessageBox message;
        message.setText("Пользователь не является поставщиком");
        message.exec();
        return;
    }

    if(!db.companies.Insert(Company(name, user.id, store.id)))
    {
        QMessageBox message;
        message.setText("Не удалось добавить поставщика");
        message.setInformativeText("Возможно, уже существует поставщик с таким названием");
        message.exec();
        return;
    }

    emit onCompanyCreated();

    close();
    deleteLater();
}

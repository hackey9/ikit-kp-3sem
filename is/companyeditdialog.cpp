#include "companyeditdialog.h"
#include "ui_companyeditdialog.h"
#include <QMessageBox>

CompanyEditDialog::CompanyEditDialog(Database &db, const Company &company, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CompanyEditDialog),
    db(db),
    company(company)
{
    ui->setupUi(this);

    setWindowModality(Qt::WindowModality::ApplicationModal);

    ui->InitialNameInput->setText(company.title);

    if(db.users.Exists(company.user_id))
    {
        User user = db.users.Get(company.user_id);
        ui->InitialStoreInput->setText(user.username);
    }

    for (const User &user : db.users.All())
    {
        if (user.group == Provider)
        {
            ui->UsernameInputSelect->addItem(user.username);
        }
    }

    if (db.storages.Exists(company.store_id))
    {
        Store store = db.storages.Get(company.store_id);
        ui->InitialStoreInput->setText(store.address);
    }

    for (const Store &store : db.storages.All())
    {
        ui->StoreSelect->addItem(store.address);
    }
}

CompanyEditDialog::~CompanyEditDialog()
{
    delete ui;
}

void CompanyEditDialog::on_ChangeNameButton_clicked()
{
    QString new_name = ui->NewNameInput->text().trimmed();

    if (new_name.length() < 2)
    {
        QMessageBox message;
        message.setText("Минимум 2 символа");
        message.exec();
        return;
    }

    Company updated_company = company;
    updated_company.title = new_name;

    if (!db.companies.Update(updated_company))
    {
        QMessageBox message;
        message.setText("Не удалось обновить поставщика");
        message.setInformativeText("Возможно, поставщик с таким названием уже есть");
        message.exec();
        return;
    }

    emit onCompanyEdited();
    close();
    deleteLater();
}

void CompanyEditDialog::on_ChangeUsernameButton_clicked()
{
    QString new_username = ui->UsernameInputSelect->currentText();

    QUuid user_id = db.users.FindByUsername(new_username);

    if(!db.users.Exists(user_id))
    {
        QMessageBox message;
        message.setText("Пользователь не найден");
        message.exec();
        return;
    }

    User new_user = db.users.Get(user_id);

    if (new_user.group != Provider)
    {
        QMessageBox message;
        message.setText("Пользователь не является поставщиком");
        message.exec();
        return;
    }

    Company updated_company = company;
    updated_company.user_id = new_user.id;

    if (!db.companies.Update(updated_company))
    {
        QMessageBox message;
        message.setText("Не удалось обновить поставщика");
        message.exec();
        return;
    }

    emit onCompanyEdited();
    close();
    deleteLater();
}

void CompanyEditDialog::on_ChangeStoreButton_clicked()
{
    int store_index = ui->StoreSelect->currentIndex();

    auto storages = db.storages.All();
    if (store_index < 0 || store_index >= storages.length())
    {
        QMessageBox message;
        message.setText("Выберите поставщика");
        message.exec();
        return;
    }

    Store store = storages[store_index];

    Company updated_company = company;
    updated_company.store_id = store.id;

    if (!db.companies.Update(updated_company))
    {
        QMessageBox message;
        message.setText("Не удалось обновить склад");
        message.exec();
        return;
    }

    emit onCompanyEdited();
    close();
    deleteLater();
}

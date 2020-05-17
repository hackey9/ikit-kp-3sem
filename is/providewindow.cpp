#include "providewindow.h"
#include "ui_providewindow.h"
#include <QMessageBox>
#include "mainwindow.h"

ProvideWindow::ProvideWindow(Database &db, const User &user, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProvideWindow),
    db(db),
    user(user),
    company_id(QUuid())
{
    ui->setupUi(this);

    for(const auto &company : db.companies.FindByUserId(user.id))
    {
        ui->ProviderSelect->addItem(company.title);
    }
}

ProvideWindow::~ProvideWindow()
{
    delete ui;
}

void ProvideWindow::on_CloseButton_clicked()
{
    close();
    deleteLater();

    MainWindow *window = new MainWindow(db, user);
    window->show();
}

void ProvideWindow::on_ProviderSelect_currentIndexChanged(int index)
{
    const auto providers = db.companies.FindByUserId(user.id);

    if (index < 0 || index >= providers.length())
    {
        company_id = QUuid();

        ui->ProvideBox->setEnabled(false);

        ui->AddressInput->setText("не указан");
        ui->ProviderInput->setText("не указан");
        ui->DetailCountCounter->setValue(1);

        ui->DetailCodeInput->setText("");
        ui->DetailNameInput->setText("");
        return;
    }

    Company company = providers[index];
    company_id = company.id;

    if (db.storages.Exists(company.store_id))
    {
        Store store = db.storages.Get(company.store_id);
        ui->AddressInput->setText(store.address);
    }
    else
    {
        ui->AddressInput->setText("не указан");
    }
    ui->ProviderInput->setText(company.title);
    ui->DetailCountCounter->setValue(1);

    ui->DetailCodeInput->setText("");
    ui->DetailNameInput->setText("");

    ui->ProvideBox->setEnabled(true);
}

void ProvideWindow::on_ProvideButton_clicked()
{
    if (!db.companies.Exists(company_id))
        return;

    QString detail_code = ui->DetailCodeInput->text().trimmed();
    QString detail_name = ui->DetailNameInput->text().trimmed();

    if (detail_code.length() < 2)
    {
        QMessageBox message;
        message.setText("Код детали - минимум 2 символа");
        message.exec();
        return;
    }

    if (detail_name.length() < 2)
    {
        QMessageBox message;
        message.setText("Наименование детали - минимум 2 символа");
        message.exec();
        return;
    }

    Company company = db.companies.Get(company_id);

    if(!db.details.Insert(Detail(detail_code, detail_name, company.store_id, company.id)))
    {
        QMessageBox message;
        message.setText("Не удалось добавить деталь");
        message.exec();
        return;
    }

    QMessageBox message;
    message.setText("Деталь добавлена на склад");
    message.exec();

    ui->DetailCountCounter->setValue(1);

    ui->DetailCodeInput->setText("");
    ui->DetailNameInput->setText("");
}

#include "companywidget.h"
#include "ui_companywidget.h"
#include "companyeditdialog.h"

CompanyWidget::CompanyWidget(Database &db, Company company,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CompanyWidget),
    db(db),
    company(company)
{
    ui->setupUi(this);

    ui->CompanyLabel->setText(company.title);

    if (db.users.Exists(company.user_id))
    {
        User user = db.users.Get(company.user_id);

        ui->UsernameLabel->setText(user.username);
    }
    else
    {
        ui->UsernameLabel->setText("(отсутствует)");
    }
}

CompanyWidget::~CompanyWidget()
{
    delete ui;
}

void CompanyWidget::on_EditButton_clicked()
{
    CompanyEditDialog *dialog = new CompanyEditDialog(db, company);
    dialog->show();

    QObject::connect(dialog, &CompanyEditDialog::onCompanyEdited, [=]() { emit onCompanyChanged(this); });
}

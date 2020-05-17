#include "companieswindow.h"
#include "ui_companieswindow.h"
#include "companywidget.h"
#include "mainwindow.h"
#include "companycreatedialog.h"

CompaniesWindow::CompaniesWindow(Database &db, const User &user, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CompaniesWindow),
    db(db),
    user(user)
{
    ui->setupUi(this);

    updateItems();
}



CompaniesWindow::~CompaniesWindow()
{
    delete ui;
}

void CompaniesWindow::updateItems()
{
    while (auto item = ui->ScrollAreaContent->layout()->itemAt(0)) {
        ui->ScrollAreaContent->layout()->removeItem(item);
        item->widget()->deleteLater();
    }

    QVector<Company> companies = db.companies.All();

    for (Company &company : companies)
    {
        CompanyWidget *widget = new CompanyWidget(db, company, this);
        ui->ScrollAreaContent->layout()->addWidget(widget);

        QObject::connect(widget, &CompanyWidget::onCompanyChanged, [=](){ updateItems(); });
    }

    ui->ScrollAreaContent->layout()->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

void CompaniesWindow::on_CloseButton_clicked()
{
    close();
    deleteLater();

    MainWindow *window = new MainWindow(db, user);
    window->show();
}

void CompaniesWindow::on_CreateStoreButton_clicked()
{
    CompanyCreateDialog *dialog = new CompanyCreateDialog(db);
    dialog->show();

    QObject::connect(dialog, &CompanyCreateDialog::onCompanyCreated, [=]() { updateItems(); });
}

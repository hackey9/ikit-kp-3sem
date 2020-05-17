#include "detailswindow.h"
#include "ui_detailswindow.h"
#include "detailwidget.h"
#include "mainwindow.h"

DetailsWindow::DetailsWindow(Database &db, const User &user, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DetailsWindow),
    db(db),
    user(user)
{
    ui->setupUi(this);

    updateItems();
}

void DetailsWindow::updateItems()
{
    while (auto item = ui->DetailsAreaContent->layout()->itemAt(0)) {
        ui->DetailsAreaContent->layout()->removeItem(item);
        item->widget()->deleteLater();
    }

    QVector<Detail> details = db.details.All();

    for (Detail &detail : details)
    {
        DetailWidget *widget = new DetailWidget(db, detail, this);
        ui->DetailsAreaContent->layout()->addWidget(widget);

        QObject::connect(widget, &DetailWidget::onDetailChanged, [=](){ updateItems(); });
    }

    ui->DetailsAreaContent->layout()->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

DetailsWindow::~DetailsWindow()
{
    delete ui;
}

void DetailsWindow::on_CloseButton_clicked()
{
    close();
    deleteLater();

    MainWindow *window = new MainWindow(db, user);
    window->show();
}

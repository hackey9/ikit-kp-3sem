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

    QVector<Detail> details;
    QString search = ui->SearchInput->text().trimmed();
    if (search == "") {
        details = db.details.All();
    } else {
        details = db.details.Search(search);
    }

    if (ui->SortSelect->currentIndex() == 1)
    {
        qSort(details.begin(), details.end(), [](const Detail &left, const Detail &right) {

            return QString::localeAwareCompare(left.name, right.name) < 0;
        });
    }
    else if (ui->SortSelect->currentIndex() == 2)
    {
        qSort(details.begin(), details.end(), [](const Detail &left, const Detail &right) {
            return QString::localeAwareCompare(left.code, right.code) < 0;
        });
    }

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

void DetailsWindow::on_ResetSearchButton_clicked()
{
    ui->SearchInput->setText("");
}

void DetailsWindow::on_SearchInput_textChanged(const QString &)
{
    updateItems();
}

void DetailsWindow::on_SortSelect_currentIndexChanged(int index)
{
    updateItems();
}

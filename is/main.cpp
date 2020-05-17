#include <QApplication>
#include <QVector>
#include "loginwindow.h"
#include "../database/database.h"
#include "../model/user.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Database db;

    LoginWindow *window = new LoginWindow(db);
    window->show();

    return a.exec();
}

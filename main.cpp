#include "displaywindow.h"
#include "mainmenu.h"
#include "findbooksdialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(":/style.qss");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString stylesheet = file.readAll();
        a.setStyleSheet(stylesheet);
    }

    MainMenu w;
    w.show();
    return a.exec();
}

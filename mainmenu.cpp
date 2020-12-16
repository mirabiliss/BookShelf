#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    this->setWindowTitle("BookShelf");

    this->displayWindow = new DisplayWindow;
    connect(displayWindow, SIGNAL(displaywindow(QVector<Book*>, QRect)), this, SLOT(showDisplayWindow(QVector<Book*>, QRect)));
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::showDisplayWindow(QVector<Book*>, QRect size)
{
    this->setGeometry(size);
    this->show();
}

void MainMenu::on_view_pushButton_clicked()
{
    displayWindow->setSizePolicy(this->sizePolicy());
    displayWindow->setGeometry(this->geometry());
    displayWindow->show();
    this->close();
}

void MainMenu::on_intro_pushButton_clicked()
{
    QMessageBox intro(QMessageBox::NoIcon, tr("About"), \
                      tr("We are glad to welcome you in our app!\nTo start, click on \"Get started!\" button. \n\
To find all provided options you should open context menues in the opened window. \n\
For more details read user guide."), QMessageBox::Ok);
    intro.setFont(QFont("Serif", 14, QFont::StyleItalic));
    intro.exec();
}

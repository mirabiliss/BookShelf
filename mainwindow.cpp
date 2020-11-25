#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

// set app icon

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::writeToFile(const Book& book)
{
    QString filename = "books.txt";
    QFile file(filename);
    file.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Text);
    if (!file.isOpen()){
        qDebug() << "file isn't open\n";
        return;
    }
    QTextStream streamFile(&file);

    streamFile << book.author()->name() << " " << book.author()->surname() << " \"" \
               << book.title() << "\" " << book.yearOfPublishment() << " " << book.pages() \
               << " " << book.ISBN() << " " << book.illustrations() << " " << book.hardCover() \
               << book.editionSize() << "\n";

    file.close();
}

void MainWindow::readFromFile()
{
    if (!this->bookList.isEmpty()){
        this->bookList.clear();
    }
    QString filename = "books.txt";
    QFile file(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    if (!file.isOpen()){
        qDebug() << "file isn't open\n";
        return;
    }

    Book book;


//    while (!file.atEnd()){
//        QByteArray line = file.readLine();
//        QList<QByteArray> l = line.split(' ');
//        QString* dataAsQString;
//        for (int i = 0; )
//        QTextCodec::codecForMib(1015)->toUnicode(l[0]);
//        Author* author(QString(l[1]), QString(l[0]));
////        QString n, s;
//        QString title;
//        int yearOfPublishment;
//        unsigned pages;
//        QString ISBN;
//        bool illustrations;
//        bool hardCover;
//        unsigned editionSize;
//    }
//    file.close();
}

// add showAll button

void MainWindow::on_actionClose_triggered()
{
    close();
}

void MainWindow::on_actionAdd_triggered()
{
    //
}

void MainWindow::on_actionFind_triggered()
{
    //
}

void MainWindow::on_actionEdit_triggered()
{
    // open window as for addaction with all fields filled in, may be edited in there & saved
}

void sort(QString sortBy)
{
    enum parameters {
        Author,
        Title,
        YearOfPublishment,
        NumberOfPages,
        ISBN,
        Illustrations,
        HardCover,
        EditionSize
    };

    // how to assign a parameter to sortBy?

//    switch (sortBy) {
//        case ()
//    }

}

void MainWindow::on_actionSort_by_triggered()
{
    // QInputDialog with combobox
    bool ok;
    QString sortBy = QInputDialog::getText(this, "Choose parameter to be sorted by",\
                                           "Sort by: ", QLineEdit::Normal, "", &ok);


    if (ok && !sortBy.isEmpty())
    {
//        sort(sortBy);
    }
}

void MainWindow::on_actionRemove_triggered()
{
    // or choose from list with setting a checkbox
}


    // all individual tasks in find action, find by all parameters

    // similar ui to findbooksdialog may be used for adding

void MainWindow::on_sort_by_comboBox_currentTextChanged(const QString &arg1)
{
    //
}

void MainWindow::on_clear_pushButton_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);

    Book b;
    b.setAuthor(new Author("Jane", "Hutson"));
    b.setTitle("Title");
    b.setYearOfPublishment(2004);
    b.setPages(389);
    b.setISBN("ISBN401-080-0562-00-4");
    b.setIllustrations(false);
    b.setHardCover(true);
    b.setEditionSize(560);
    writeToFile(b);
}

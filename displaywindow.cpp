#include "displaywindow.h"
#include "ui_displaywindow.h"

DisplayWindow::DisplayWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DisplayWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("BookShelf");

    this->setFixedSize(this->size());

    findDialog = new FindBooksDialog(this->books);
    connect(findDialog, SIGNAL(finddialog(QRect)), this, SLOT(showFindDialog(QRect)));
}

DisplayWindow::~DisplayWindow()
{
    delete ui;
}


void DisplayWindow::showDisplayWindow(QRect size)
{
    this->setGeometry(size);
    this->show();
}

void DisplayWindow::writeToFile(const Book& book)
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
               << " " << book.editionSize() << "\n";

    file.close();
}

void DisplayWindow::readFromFile()
{
    if (!this->books.isEmpty()){
        this->books.clear();
    }
    QString filename = "books.txt";
    QFile file(filename);

    file.open(QIODevice::ReadOnly | QIODevice::Text);
    if (!file.isOpen()){
        qDebug() << "file isn't open\n";
        return;
    }


    Book book;

    while (!file.atEnd()){
        QByteArray line = file.readLine();
        QTextStream input(&line);

        input >> book;

        this->books.push_back(&book);
    }
    file.close();
}

void DisplayWindow::sort()
{
    // getting from user parameter to be sorted by
    QInputDialog qDialog ;

    QStringList items;
    items << "Author";
    items << "Title";
    items << "Year of publishment";
    items << "Number of pages";
    items << "ISBN";
    items << "Have illustrations";
    items << "Have hard cover";
    items << "Edition size";

    qDialog.setOptions(QInputDialog::UseListViewForComboBoxItems);
    qDialog.setComboBoxItems(items);
    qDialog.setWindowTitle("Choose parameter");

    QObject::connect(&qDialog, SIGNAL(textValueChanged(const QString &)), \
               this, SLOT(onCompute(const QString &)));

    qDialog.exec();



}


//    // QInputDialog with combobox
//    bool ok;
//    QString sortBy = QInputDialog::getText(this, "Choose parameter to be sorted by",\
//                                           "Sort by: ", QLineEdit::Normal, "", &ok);


//    if (ok && !sortBy.isEmpty())
//    {
////        sort(sortBy);
//    }





    // all individual tasks in find action, find by all parameters

    // similar ui to findbooksdialog may be used for adding



//    Book b;
//    b.setAuthor(new Author("Jane", "Hutson"));
//    b.setTitle("Title");
//    b.setYearOfPublishment(2004);
//    b.setPages(389);
//    b.setISBN("ISBN401-080-0562-00-4");
//    b.setIllustrations(false);
//    b.setHardCover(true);
//    b.setEditionSize(560);
//    writeToFile(b);



void DisplayWindow::on_actionSave_triggered()
{

}

void DisplayWindow::on_actionSave_as_triggered()
{

}

void DisplayWindow::on_actionClose_triggered()
{
    close();
}

void DisplayWindow::on_actionAdd_triggered()
{

}

void DisplayWindow::on_actionRemove_triggered()
{

}

void DisplayWindow::on_actionFind_triggered()
{
    this->close();
    findDialog->setSizePolicy(this->sizePolicy());
    findDialog->setGeometry(this->geometry());
    findDialog->show();
    // glue them together
}

void DisplayWindow::on_actionSort_by_triggered()
{
    sort();
}

void DisplayWindow::on_actionClear_triggered()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);
}

void DisplayWindow::on_actionGet_books_from_file_triggered()
{
    readFromFile();
}

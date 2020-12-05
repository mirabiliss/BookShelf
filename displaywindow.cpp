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
    connect(findDialog, SIGNAL(finddialog(QVector<Book*>, QRect)), this, SLOT(showFindDialog(QVector<Book*>, QRect)));
}

DisplayWindow::~DisplayWindow()
{
    delete ui;
}

void DisplayWindow::showFindDialog(QVector<Book*> books, QRect size)
{
    // bboooookkkksss
    this->setGeometry(size);
    this->show();
}

void displaywindow(QVector<Book*>, QRect)
{
    // impement this
}

void DisplayWindow::display(QVector<Book*> vec)
{
    ui->tableWidget->clearContents();

    ui->tableWidget->setRowCount(vec.size());
    ui->tableWidget->setColumnCount(8);

    for (int i = 0; i < vec.size(); i++) {
        Book* book = vec[i];
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(book->author()->name() + QString(" ") + book->author()->surname()));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(*book->title()));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(book->yearOfPublishment()));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(book->pages()));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(*book->ISBN()));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(book->illustrations()));
        ui->tableWidget->setItem(i, 6, new QTableWidgetItem(book->hardCover()));
        ui->tableWidget->setItem(i, 7, new QTableWidgetItem(book->editionSize()));
    }
}

void DisplayWindow::writeToFile(Book& book)
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

bool DisplayWindow::readFromFile()
{
    if (!this->books.isEmpty()){
        this->books.clear();
    }
    QString filename = QDir::currentPath() + "/" + "books.txt";
    QFile file(filename);

    file.open(QIODevice::ReadOnly | QIODevice::Text);
    if (!file.isOpen()){
        qDebug() << "file isn't open\n";
        return false;
    }

    while (!file.atEnd()){
        Book book;
        QByteArray line = file.readLine();
        QTextStream input(&line);

        input >> book;

        this->books.push_back(&book);
    }
    file.close();
    return true;
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
    if (readFromFile())
        display(this->books);
}

void DisplayWindow::on_actionBiggest_amount_of_pages_triggered()
{

}

void DisplayWindow::on_actionSmallest_amount_of_pages_biggest_edition_size_triggered()
{

}

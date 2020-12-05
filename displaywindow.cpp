#include "displaywindow.h"
#include "ui_displaywindow.h"

DisplayWindow::DisplayWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DisplayWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("BookShelf");

    this->setFixedSize(this->size());

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

DisplayWindow::~DisplayWindow()
{
    delete ui;
}

void DisplayWindow::showFindDialog(QVector<Book*> books, QRect size)
{
    if (books.isEmpty())
    {
        QMessageBox::information(this, "Ooooops...", "Books with given parameters were not found");
    }

    this->setGeometry(size);
    this->show();

    this->foundBooks = books;
    display(this->foundBooks);
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
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(book->yearOfPublishment())));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(book->pages())));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(*book->ISBN()));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(book->illustrations() == true ? "yes" : "no"));
        ui->tableWidget->setItem(i, 6, new QTableWidgetItem(book->hardCover() == true ? "yes" : "no"));
        ui->tableWidget->setItem(i, 7, new QTableWidgetItem(QString::number(book->editionSize())));
    }
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 1; j < 8; j++)
        {
            ui->tableWidget->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }

    QStringList horHeaders;
    horHeaders << "Author";
    horHeaders << "Title";
    horHeaders << "Year of\npublishment";
    horHeaders << "Number of\npages";
    horHeaders << "ISBN";
    horHeaders << "Illustrations";
    horHeaders << "Hard cover";
    horHeaders << "Edition";

    ui->tableWidget->setHorizontalHeaderLabels(horHeaders);
}

void DisplayWindow::writeToFile(Book& book)
{
    QString filename = "books.txt";
    QFile file(filename);
    file.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Text);
    if (!file.isOpen())
    {
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
    QString filename = QDir::home().filePath("books.txt");
    QFile file(filename);

    file.open(QIODevice::ReadOnly | QIODevice::Text);
    if (!file.isOpen()){
        qDebug() << "file isn't open\n";
        return false;
    }

    while (!file.atEnd()){
        Book *book = new Book;
        QByteArray line = file.readLine();
        QTextStream input(&line);

        input >> *book;

        this->books.push_back(book);
    }
    file.close();
    return true;
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
    findDialog = new FindBooksDialog(this->books);
    connect(findDialog, SIGNAL(finddialog(QVector<Book*>, QRect)), this, SLOT(showFindDialog(QVector<Book*>, QRect)));

//    this->foundBooks.clear();
    this->close();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);

    findDialog->setSizePolicy(this->sizePolicy());
    findDialog->setGeometry(this->geometry());
    findDialog->show();
    // glue them together
}

bool byAuthor(Book* first, Book* second)
{
    return (first->author()->surname()->toStdString() < second->author()->surname()->toStdString());
}

bool byTitle(Book* first, Book* second)
{
    return (first->title()->toStdString() < second->title()->toStdString());
}

bool byISBN(Book* first, Book* second)
{
    return (first->ISBN()->toStdString() < second->ISBN()->toStdString());
}

bool byYearOfPublishment(Book* first, Book* second)
{
    return (first->yearOfPublishment() < second->yearOfPublishment());
}

bool byPages(Book* first, Book* second)
{
    return (first->pages() < second->pages());
}

bool byIllustrations(Book* first, Book* second)
{
    return (first->illustrations() >= second->illustrations());
}

bool byCover(Book* first, Book* second)
{
    return (first->hardCover() >= second->hardCover());
}

bool byEditionSize(Book* first, Book* second)
{
    return (first->editionSize() < second->editionSize());
}

QString DisplayWindow::getParameter()
{
    // getting from user parameter to be sorted by
    QStringList items;
    items << "Author";
    items << "Title";
    items << "Year of publishment";
    items << "Number of pages";
    items << "ISBN";
    items << "Have illustrations";
    items << "Have hard cover";
    items << "Edition size";

    return QInputDialog::getItem(this, "Choose parameter", "Choose parameter to be sorted by:", items);
}

void DisplayWindow::on_actionSort_by_triggered()
{
    this->foundBooks = this->books;

    QString parameter = getParameter();

    if (foundBooks.isEmpty())
    {
        qDebug() << "found nothing";
        return;
    }

    if (parameter == "Author")
    {
        std::sort(foundBooks.begin(), foundBooks.end(), byAuthor);
        display(this->foundBooks);
    }
    else if (parameter == "Title")
    {
        std::sort(foundBooks.begin(), foundBooks.end(), byTitle);
        display(this->foundBooks);
    }
    else if (parameter == "Year of publishment")
    {
        std::sort(foundBooks.begin(), foundBooks.end(), byYearOfPublishment);
        display(this->foundBooks);
    }
    else if (parameter == "Number of pages")
    {
        std::sort(foundBooks.begin(), foundBooks.end(), byPages);
        display(this->foundBooks);
    }
    else if (parameter == "ISBN")
    {
        std::sort(foundBooks.begin(), foundBooks.end(), byISBN);
        display(this->foundBooks);
    }
    else if (parameter == "Have illustrations")
    {
        std::sort(foundBooks.begin(), foundBooks.end(), byIllustrations);
        display(this->foundBooks);
    }
    else if (parameter == "Have hard cover")
    {
        std::sort(foundBooks.begin(), foundBooks.end(), byCover);
        display(this->foundBooks);
    }
    else if (parameter == "Edition size")
    {
        std::sort(foundBooks.begin(), foundBooks.end(), byEditionSize);
        display(this->foundBooks);
    }
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

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
    ui->tableWidget->horizontalHeader()->stretchLastSection();

//    QPixmap newpix("new.png");
//    QPixmap openpix("../coursework_oop/folder.png");
//    QPixmap quitpix("quit.png");

//    QToolBar *toolbar = addToolBar("main toolbar");
//    QAction *add = toolbar->addAction(QIcon(newpix), "Add...");
//    QAction *getFromFile = toolbar->addAction(QIcon(openpix), "Get from file");
//    toolbar->addSeparator();
//    QAction *quit = toolbar->addAction(QIcon(quitpix), "Quit");

//    connect(quit, &QAction::triggered, qApp, &QApplication::quit);
//    connect(add, &QAction::triggered, qApp, SLOT(on_actionAdd_triggered));
//    connect(getFromFile, &QAction::triggered, qApp, SLOT(on_actionGet_books_from_file_triggered));
}

DisplayWindow::~DisplayWindow()
{
    delete ui;
}

void DisplayWindow::showFindDialog(QVector<Book*> books, QRect size)
{
    if (books.isEmpty())
    {
        QMessageBox::warning(this, "Ooooops...", "Books with given parameters were not found");
        display(this->books);
    }
    else
    {
        this->foundBooks = books;
        display(this->foundBooks);
    }

    this->setGeometry(size);
    this->show();
}

void DisplayWindow::showAddDialog(Book *book)
{
    if (!book)
        QMessageBox::warning(this, "Ooooops...", "Book was not added");
    else
        this->books.push_back(book);

    this->show();
    display(this->books);
    this->foundBooks = this->books;
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
    try {
        if (!this->books.isEmpty()){
            this->books.clear();
        }
        QString filename = QDir::home().filePath("books.txt");
        QFile file(filename);

        file.open(QIODevice::ReadOnly | QIODevice::Text);
        if (!file.isOpen()){
            throw FileNotOpenException();
        }

        while (!file.atEnd()){
            Book *book = new Book;
            QByteArray line = file.readLine();
            QTextStream input(&line);

            input >> *book;

            this->books.push_back(book);
        }
        file.close();
        this->foundBooks = this->books;

        return true;

    }  catch (FileNotOpenException& e) {
        qDebug() << e.what();
        QMessageBox::warning(this, "Ooooops...", e.what());
    }
    return false;
}

void DisplayWindow::on_actionSave_triggered()
{
    try {

        bool saved = true;

        QString filename = QDir::home().filePath("books.txt");
        QFile file(filename);

        file.open(QIODevice::WriteOnly | QIODevice::Text);
        if (!file.isOpen())
        {
            saved = false;
            throw FileNotOpenException();
        }

        QTextStream output(&file);

        for (int i = 0; i < this->books.size(); i++)
        {
            output << *books[i];
        }

        file.close();

        if (!saved) throw SaveException();
    }  catch (SaveException& e) {
        qDebug() << e.what();
        QMessageBox::warning(this, "Ooooops...", "Seems like we couldn't save books to file\nPlease try again.");
    }
}

void DisplayWindow::on_actionClose_triggered()
{
    close();
}

void DisplayWindow::on_actionAdd_triggered()
{
    addBookDialog = new AddBookDialog();
    connect(addBookDialog, SIGNAL(addbookdialog(Book*)), this, SLOT(showAddDialog(Book*)));

    addBookDialog->show();
}

void DisplayWindow::on_actionRemove_triggered()
{
    try {
        if (this->books.isEmpty())
            throw NoBooksException();
        this->posToDelete = QInputDialog::getInt(this, "Delete book", \
                                                 "Enter position of the book you want to delete:\n", \
                                                 0, 1, this->books.size()) - 1;
        removeBook();
    }  catch (NoBooksException& e) {
        qDebug() << e.what();
        QMessageBox::warning(this, "Ooooops...", "Seems like no books are available\nPlease add some books first.");
    }
}

void DisplayWindow::on_actionFind_triggered()
{
    try {
        if (this->books.isEmpty())
        {
            throw NoBooksException();
        }

        findDialog = new FindBooksDialog(this->books);
        connect(findDialog, SIGNAL(finddialog(QVector<Book*>, QRect)), this, SLOT(showFindDialog(QVector<Book*>, QRect)));

        this->close();
        ui->tableWidget->clear();
        ui->tableWidget->setRowCount(0);
        ui->tableWidget->setColumnCount(0);

        findDialog->setSizePolicy(this->sizePolicy());
        findDialog->setGeometry(this->geometry());
        findDialog->show();

    }  catch (NoBooksException& e) {
        qDebug() << e.what();
        QMessageBox::warning(this, "Ooooops...", "Seems like no books are available\nPlease add some books first.");
    }
}


// comparators

bool byAuthor(Book* first, Book* second)
{
    return (first->author()->surname()->toStdString() < second->author()->surname()->toStdString());
}

struct byAuthorPred {
    bool operator()(Author *lhs, Author *rhs) {
        return *lhs < *rhs;
    }
};

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
    QStringList items;
    items << "Author";
    items << "Title";
    items << "Year of publishment";
    items << "Number of pages";
    items << "ISBN";
    items << "Have illustrations";
    items << "Have hard cover";
    items << "Edition size";

    // if cancel was clicked - do not return a value
    return QInputDialog::getItem(this, "Choose parameter", "Choose parameter to be sorted by:", items);
}

void DisplayWindow::on_actionSort_by_triggered()
{
    try {
        if (this->books.isEmpty())
            throw NoBooksException();

        // getting parameter from user to be sorted by
        QString parameter = getParameter();

        // check if valid
        if (foundBooks.isEmpty())
        {
            qDebug() << "No books were found";
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
    }  catch (NoBooksException& e) {
        qDebug() << e.what();
        QMessageBox::warning(this, "Ooooops...", "Seems like no books are available\nPlease add some books first.");
    }
}

void DisplayWindow::on_actionClear_triggered()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);
    this->books.clear();
    this->foundBooks.clear();
}

void DisplayWindow::on_actionGet_books_from_file_triggered()
{
    if (readFromFile())
        display(this->books);
}

void DisplayWindow::on_actionBiggest_amount_of_pages_triggered()
{
    try {
        if (this->books.isEmpty())
            throw NoBooksException();

        QVector<Book*> tmp = this->books;
        QVector<Book*> res;

        // sort by pages
        std::sort(tmp.begin(), tmp.end(), byPages);

        // check from the books with biggest number of pages to smallest if they have illustrations
        for (int i = tmp.size()-1; i >= 0; i--)
        {
            if (tmp[i]->illustrations() == true)
            {
                if (res.isEmpty())
                    res.push_back(tmp[i]);
                else
                    if (tmp[i]->pages() == res[0]->pages())
                        res.push_back(tmp[i]);
            }
            else
                if (!res.isEmpty())
                    break; // if we've found something already & next book either does not have pics or has less pages
        }

        this->foundBooks = res;
        display(this->foundBooks);
    }  catch (NoBooksException& e) {
        qDebug() << e.what();
        QMessageBox::warning(this, "Ooooops...", "Seems like no books are available\nPlease add some books first.");
    }
}

void DisplayWindow::on_actionSmallest_amount_of_pages_biggest_edition_size_triggered()
{
    try {
        if (this->books.isEmpty())
            throw NoBooksException();

        QVector<Book*> tmp = this->books;
        QVector<Book*> byPagesAscending;
        QVector<Book*> byEdDescending;
        QVector<Book*> res;
        QMap<Book*, int> bookPriority;

        int year = 99999;
        if ((year = QInputDialog::getInt(this, "Enter year of publishment", \
                    "Among books of which year of publishment to look for?", 0, -999999, 2020)) > 2020)
            return;

        // find books of given year
        QVector<int> posToRemove;

        for (int i = 0; i < tmp.size(); i++)
        {
            if (tmp[i]->yearOfPublishment() != year)
                posToRemove.push_back(i);
        }

        int k = 0;
        for (int i = 0; i < tmp.size(); i++)
        {
            if (k < posToRemove.size())
            {
                if (i != posToRemove[k])
                {
                    res.push_back(tmp[i]);
                }
                else
                    k++;
            }
            else
                res.push_back(tmp[i]);
        }

        tmp = res;
        res.clear();

        // sort by pages
        std::sort(tmp.begin(), tmp.end(), byPages);
        byPagesAscending = tmp;

        for (int i = 0; i < byPagesAscending.size(); i++)
        {
            bookPriority[byPagesAscending[i]] = i;
        }

        // sort by edition
        std::sort(tmp.begin(), tmp.end(), byEditionSize);
        byEdDescending = tmp;

        for (int i = 0; i < byEdDescending.size(); i++)
        {
            bookPriority[byPagesAscending[i]] += i;
        }

        int min = tmp.size() * 2;
        // finding book with least value - biggest priority
        for (auto el = bookPriority.begin(); el != bookPriority.end(); el++)
        {
            if (el.value() < min)
            {
                min = el.value();
            }
        }
        // saving book with biggest priority
        for (auto el = bookPriority.begin(); el != bookPriority.end(); el++)
        {
            if (el.value() == min)
            {
                res.push_back(el.key());
                break;
            }
        }

        this->foundBooks = res;
        display(this->foundBooks);

    }  catch (NoBooksException& e) {
        qDebug() << e.what();
        QMessageBox::warning(this, "Ooooops...", "Seems like no books are available\nPlease add some books first.");
    }

}

void DisplayWindow::removeBook()
{
    this->books.remove(this->posToDelete);
    this->foundBooks.remove(this->posToDelFromFound);
    display(this->books);
}

void DisplayWindow::on_tableWidget_cellDoubleClicked(int row, int)
{
    QMessageBox* box = new QMessageBox(QMessageBox::Question,
                                           "Delete book",
                                           "Are you sure you want to delete this book?",
                                           QMessageBox::Yes | QMessageBox::No,
                                           this);
    this->posToDelFromFound = row;

    for (int i = 0; i < this->books.size(); i++)
    {
        if (this->books[i] == this->foundBooks[row])
        {
            posToDelete = i;
            break;
        }
    }

    QObject::connect(box->button(QMessageBox::Yes), &QAbstractButton::clicked, this, &DisplayWindow::removeBook);
    box->show();
}

void DisplayWindow::on_actionGroup_by_authors_triggered()
{
    std::map<Author*, QVector<Book*>, byAuthorPred> authorsBooks;
    QVector<Book*> res;

    for (int i = 0; i < this->books.size(); i++)
    {
        authorsBooks[books[i]->author()].push_back(books[i]);
    }

    for (auto el = authorsBooks.begin(); el != authorsBooks.end(); el++)
    {
        std::sort(el->second.begin(), el->second.end(), byPages);
    }

    for (auto el = authorsBooks.begin(); el != authorsBooks.end(); el++)
    {
        res += el->second;
    }

    this->foundBooks = res;
    display(this->foundBooks);
}

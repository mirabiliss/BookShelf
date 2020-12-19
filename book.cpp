#include "book.h"

Book::Book()
{
    this->setAuthor(new Author(new QString(""), new QString("")));
    this->setTitle(new QString(""));
    this->setYearOfPublishment(0);
    this->setPages(0);
    this->setISBN(new QString(""));
    this->setIllustrations(false);
    this->setHardCover(false);
    this->setEditionSize(0);
}

Book::Book(Author* _author, QString* _title, int _year, unsigned _pages, QString* _isbn, bool _illustrations, bool _hardCover, unsigned _edition)
{
    this->setAuthor(_author);
    this->setTitle(_title);
    this->setYearOfPublishment(_year);
    this->setPages(_pages);
    this->setISBN(_isbn);
    this->setIllustrations(_illustrations);
    this->setHardCover(_hardCover);
    this->setEditionSize(_edition);
}

Book::Book(Book &other)
{
    *this = other;
}

Book &Book::operator=(Book &other)
{
    if (this != &other)
    {
        this->setAuthor(other.author());
        this->setTitle(other.title());
        this->setYearOfPublishment(other.yearOfPublishment());
        this->setPages(other.pages());
        this->setISBN(other.ISBN());
        this->setIllustrations(other.illustrations());
        this->setHardCover(other.hardCover());
        this->setEditionSize(other.editionSize());
    }
    return *this;
}

Author *Book::author() const
{
    return author_;
}

void Book::setAuthor(Author *author)
{
    author_ = author;
}

QString* Book::title()
{
    return title_;
}

void Book::setTitle(QString* title)
{
    title_ = title;
}

int Book::yearOfPublishment() const
{
    return yearOfPublishment_;
}

void Book::setYearOfPublishment(int yearOfPublishment)
{
    yearOfPublishment_ = yearOfPublishment;
}

unsigned Book::pages() const
{
    return pages_;
}

void Book::setPages(const unsigned pages)
{
    pages_ = pages;
}

QString* Book::ISBN()
{
    return ISBN_;
}

void Book::setISBN(QString* ISBN)
{
    ISBN_ = ISBN;
}

bool Book::illustrations() const
{
    return illustrations_;
}

void Book::setIllustrations(bool illustrations)
{
    illustrations_ = illustrations;
}

bool Book::hardCover() const
{
    return hardCover_;
}

void Book::setHardCover(bool hardCover)
{
    hardCover_ = hardCover;
}

unsigned Book::editionSize() const
{
    return editionSize_;
}

void Book::setEditionSize(const unsigned editionSize)
{
    editionSize_ = editionSize;
}

QTextStream& operator<<(QTextStream& output, Book& book)
{
    output << *book.author_->name() << " " << *book.author_->surname() << " \"" << \
              *book.title() << "\" " << book.yearOfPublishment() << " " << book.pages() << \
              " " << *book.ISBN() << " " << book.illustrations() << \
              " " << book.hardCover() << " " << book.editionSize() << "\n";
    return output;
}

QTextStream& operator>>(QTextStream& input, Book& book)
{
    QString *name = new QString(""), *surname = new QString(""), *title = new QString(""), *isbn = new QString("");
    int year, illustrations, covers;
    unsigned pages, edSize;

    input >> *name;
    input >> *surname;

    char c;

    bool reading = false;
    while (true) {
        input >> c;
        if (reading) {
            if (c == '\"')
            {
                reading = false;
                break;
            }
            else (*title) += c;
        }
        else {
            if (c == '\"') reading = true;
        }
    }

    input >> year >> pages >> *isbn >> illustrations >> covers >> edSize;

    Book b(new Author(name, surname), title, year, pages, isbn, illustrations, covers, edSize);
    book = b;

    return input;
}

bool operator==(const Book& first, const Book& second)
{
    return ((first.author() == second.author()) && ((*first.title_) == (*second.title_)) && \
            (first.yearOfPublishment() == second.yearOfPublishment()) &&\
            (first.pages() == second.pages()) && ((*first.ISBN_) == (*second.ISBN_)) && \
            (first.pages() == second.pages()) && (first.illustrations() == second.illustrations()) && \
            (first.hardCover() == second.hardCover()));
}

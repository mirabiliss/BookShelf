#include "book.h"

Book::Book()
{
    this->setAuthor(new Author("", ""));
    this->setTitle("");
    this->setYearOfPublishment(0);
    this->setPages(0);
    this->setISBN("");
    this->setIllustrations(false);
    this->setHardCover(false);
    this->setEditionSize(0);
}

Book::Book(Author* _author, QString _title, int _year, unsigned _pages, QString _isbn, bool _illustrations, bool _hardCover, unsigned _edition)
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

Book &Book::operator=(const Book &other)
{
//    if (*this != other)
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

QString Book::title() const
{
    return title_;
}

void Book::setTitle(const QString &title)
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

void Book::setPages(const unsigned &pages)
{
    pages_ = pages;
}

QString Book::ISBN() const
{
    return ISBN_;
}

void Book::setISBN(const QString &ISBN)
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

void Book::setEditionSize(const unsigned &editionSize)
{
    editionSize_ = editionSize;
}

QTextStream& operator<<(QTextStream& output, const Book& book)
{
    output << book.author_->name() << " " << book.author_->surname() << ":\t'" << \
              book.title() << "'\t" << book.yearOfPublishment() << "y.\t" << book.pages() << \
            "pgs\tISBN: " << book.ISBN() << "\thas pics - " << book.illustrations() << \
            "\thard cover - " << book.hardCover() << "\ted. size = " << book.editionSize() << "\n";
    return output;
}

QTextStream& operator>>(QTextStream& input, Book& book)
{
    QString name, surname, tmpStr;
    int tmpNum;
/*    if (!input.Ok)*/ {
        input >> name;
        input >> surname;
        book.setAuthor(new Author(name, surname));
        input >> tmpStr;
        book.setTitle(tmpStr);
        input >> tmpNum;
        book.setYearOfPublishment(tmpNum);
        input >> tmpNum;
        book.setPages(tmpNum);
        input >> tmpStr;
        book.setISBN(tmpStr);
        input >> tmpNum;
        book.setIllustrations(tmpNum);
        input >> tmpNum;
        book.setHardCover(tmpNum);
        input >> tmpNum;
        book.setEditionSize(tmpNum);
    }
    return input;
}

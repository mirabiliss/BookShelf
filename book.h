#ifndef BOOK_H
#define BOOK_H

#include "author.h"
#include <QString>
#include <QTextStream>


class Book
{
public:
    Book();
    Book(Author* _author, QString* _title = new QString(""), int _year = 0, unsigned _pages = 0, \
         QString* _isbn = new QString("ISBN000-000-0000-00-0"), bool _illustrations = false, bool _hardCover = false,\
         unsigned _edition = 0);
    Book(Book& other);

    friend QTextStream &operator<<(QTextStream& output, Book& book);
    friend QTextStream &operator>>(QTextStream& input, Book& book);
    Book& operator=(Book& other);

    Author *author() const;
    void setAuthor(Author *author);

    QString* title();
    void setTitle(QString* title);

    int yearOfPublishment() const;
    void setYearOfPublishment(int yearOfPublishment);

    unsigned pages() const;
    void setPages(const unsigned pages);

    QString* ISBN();
    void setISBN(QString* ISBN);

    bool illustrations() const;
    void setIllustrations(bool illustrations);

    bool hardCover() const;
    void setHardCover(bool hardCover);

    unsigned editionSize() const;
    void setEditionSize(const unsigned editionSize);

private:
    Author* author_;
    QString* title_;
    int yearOfPublishment_;
    unsigned pages_;
    QString* ISBN_;
    bool illustrations_;
    bool hardCover_;
    unsigned editionSize_; // number of books published
};

#endif // BOOK_H

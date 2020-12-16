#ifndef BOOKEXCEPTION_H
#define BOOKEXCEPTION_H

#include <QException>
#include <QString>

#include "author.h"
#include "book.h"

class BookException : public QException
{
    static const QString defaultExceptionMessage;

public:
    BookException();
    BookException(const QString& what);

    const char* what() const noexcept override { return what_.toLocal8Bit().data(); };

protected:
    QString what_;
};

// trown when operating with empty vector of books
class NoBooksException : public BookException
{
public:
    const char* what() const noexcept override
    {
        return "Seems like no books are available \nPlease add some books first.";
    }
};

// thrown when file didn't open correctly
class FileNotOpenException : public BookException
{
public:
    const char * what() const noexcept
    {
        return "Cannot open file! Please, try again.";
    }
};

// thrown when can't save to file
class SaveException : public BookException
{
public:
    const char * what() const noexcept
    {
        return "Cannot save books to file! \nPlease, try again.";
    }
};

#endif // BOOKEXCEPTION_H

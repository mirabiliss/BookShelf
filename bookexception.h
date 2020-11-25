#ifndef BOOKEXCEPTION_H
#define BOOKEXCEPTION_H

#include <QException>
#include <QString>

class BookException : public QException
{
    static const QString defaultExceptionMessage;

public:
    BookException();
    BookException(const QString& what);

protected:
    QString _what;

};


// wrong year exception

// trown when operating with empty list
class EmptyBookListException : BookException
{

};

// thrown when file didn't open correctly?
class LoadingFromFileException : public BookException
{
    //
};

// thrown when setting data of different type (when setting from user input)
class InvalidDataPassedException : public BookException
{
    //
};

// thrown when can't save to file?
class SaveException : public BookException
{

};

#endif // BOOKEXCEPTION_H

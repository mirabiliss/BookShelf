#include "bookexception.h"

const QString BookException::defaultExceptionMessage = "exception";
BookException::BookException()
{
    _what = defaultExceptionMessage;
}

BookException::BookException(const QString &msg) :
    _what(msg)
{
}


#include "bookexception.h"

const QString BookException::defaultExceptionMessage = "exception";
BookException::BookException()
{
    what_ = "";
}

BookException::BookException(const QString &what)
{
    what_ = what;
}

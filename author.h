#ifndef AUTHOR_H
#define AUTHOR_H

#include <QString>

class Author
{
public:
    Author();
    Author(QString* name, QString* surname);
    Author(Author& other);

    friend bool operator==(const Author& first, const Author& second);

    QString* name();
    void setName(QString* name);

    QString* surname();
    void setSurname(QString* surname);

private:
    QString *name_;
    QString *surname_;
};

#endif // AUTHOR_H

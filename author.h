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
    friend bool operator<(const Author& first, const Author& second);
    QString* name() const;
    void setName(QString* name);

    QString* surname() const;
    void setSurname(QString* surname);

private:
    QString *name_;
    QString *surname_;
};

#endif // AUTHOR_H

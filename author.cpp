#include "author.h"

Author::Author()
{
    this->setName("");
    this->setSurname("");
}

Author::Author(QString name, QString surname)
{
    this->setName(name);
    this->setSurname(surname);
}

Author::Author(Author &other)
{
    this->setName(other.name());
    this->setSurname(other.surname());
}

QString Author::name() const
{
    return name_;
}

void Author::setName(const QString &name)
{
    name_ = name;
}

QString Author::surname() const
{
    return surname_;
}

void Author::setSurname(const QString &surname)
{
    surname_ = surname;
}

bool operator==(const Author& first, const Author& second)
{
    if (first.name() == second.name() && first.surname() == second.surname())
        return true;
    return false;
}

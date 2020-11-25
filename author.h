#ifndef AUTHOR_H
#define AUTHOR_H

#include <QString>

class Author
{
public:
    Author();
    Author(QString _name, QString _surname);
    Author(Author& other);

    friend bool operator==(const Author& first, const Author& second);

    QString name() const;
    void setName(const QString &name);

    QString surname() const;
    void setSurname(const QString &surname);

private:
    QString name_;
    QString surname_;
};

#endif // AUTHOR_H

#ifndef DISPLAYWINDOW_H
#define DISPLAYWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QDebug>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QSpinBox>
#include <QInputDialog>
#include <QFile>
#include <QTextStream>
#include <QDir>

#include "book.h"
#include "findbooksdialog.h"

namespace Ui {
class DisplayWindow;
}

class DisplayWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DisplayWindow(QWidget *parent = nullptr);
    ~DisplayWindow();

signals:
    void displaywindow(QVector<Book*>, QRect);

private slots:
    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionClose_triggered();

    void on_actionAdd_triggered();

    void on_actionRemove_triggered();

    void on_actionFind_triggered();

    void on_actionSort_by_triggered();

    void on_actionClear_triggered();


    void showFindDialog(QVector<Book*>, QRect size);

    void on_actionGet_books_from_file_triggered();

    void on_actionBiggest_amount_of_pages_triggered();

    void on_actionSmallest_amount_of_pages_biggest_edition_size_triggered();

private:
    void writeToFile(Book &book);
    bool readFromFile();
    void sort();
    void display(QVector<Book*> vec);

private:
    Ui::DisplayWindow *ui;
    QVector<Book*> books;
    QVector<Book*> foundBooks;
    FindBooksDialog *findDialog;
};

#endif // DISPLAYWINDOW_H

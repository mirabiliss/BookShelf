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
    void finddialog(QVector<Book> found, QRect);
    // "add" dialog

private slots:
    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionClose_triggered();

    void on_actionAdd_triggered();

    void on_actionRemove_triggered();

    void on_actionFind_triggered();

    void on_actionSort_by_triggered();

    void on_actionClear_triggered();


    void showDisplayWindow(QRect size);

    void on_actionGet_books_from_file_triggered();

private:
    void writeToFile(const Book &book);
    void readFromFile();
    void sort();

private:
    Ui::DisplayWindow *ui;
    QVector<Book*> books;
    QVector<Book*> foundBooks;
    FindBooksDialog *findDialog;
};

#endif // DISPLAYWINDOW_H

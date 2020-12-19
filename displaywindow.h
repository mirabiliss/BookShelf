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
#include <algorithm>
#include <QAbstractButton>
#include <QToolBar>

#include "book.h"
#include "findbooksdialog.h"
#include "addbookdialog.h"
#include "bookexception.h"

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

    void on_actionClose_triggered();

    void on_actionAdd_triggered();

    void on_actionRemove_triggered();

    void on_actionFind_triggered();

    void on_actionSort_by_triggered();

    void on_actionClear_triggered();

    void on_actionGet_books_from_file_triggered();

    void on_actionBiggest_amount_of_pages_triggered();

    void on_actionSmallest_amount_of_pages_biggest_edition_size_triggered();

    void on_tableWidget_cellDoubleClicked(int row, int column);

    void showFindDialog(QVector<Book*>, QRect size);
    void showAddDialog(Book *book);


    void on_actionGroup_by_authors_triggered();

private:
    void writeToFile(Book &book);
    bool readFromFile();
    void display(QVector<Book*> vec);
    QString getParameter();
    void removeBook();

private:
    Ui::DisplayWindow *ui;
    QVector<Book*> books;
    QVector<Book*> foundBooks;
    FindBooksDialog *findDialog;
    AddBookDialog *addBookDialog;
    int posToDelete;
    int posToDelFromFound;
};

#endif // DISPLAYWINDOW_H

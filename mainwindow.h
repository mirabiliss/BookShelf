#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include <QTextCodec>
#include "book.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionClose_triggered();

    void on_actionAdd_triggered();

    void on_actionFind_triggered();

    void on_actionEdit_triggered();

    void on_actionSort_by_triggered();

    void on_actionRemove_triggered();

    void on_sort_by_comboBox_currentTextChanged(const QString &arg1);

    void on_clear_pushButton_clicked();


    void writeToFile(const Book &book);
    void readFromFile();


private:
    Ui::MainWindow *ui;
    QList<Book> bookList;
};
#endif // MAINWINDOW_H

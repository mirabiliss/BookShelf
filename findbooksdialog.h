#ifndef FINDBOOKSDIALOG_H
#define FINDBOOKSDIALOG_H

#include <QMessageBox>

#include "author.h"
#include "book.h"
//#include <displaywindow.h>

namespace Ui {
class FindBooksDialog;
}

class FindBooksDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindBooksDialog(QVector<Book*> books, QWidget *parent = nullptr);
    ~FindBooksDialog();

signals:
   // void displaywindow(QVector<Book*>, QRect);
    void finddialog(QVector<Book*> found, QRect);

private slots:
    void on_author_checkBox_stateChanged(int arg1);
    
    void on_title_checkBox_stateChanged(int arg1);

    void on_year_checkBox_stateChanged(int arg1);

    void on_pages_checkBox_stateChanged(int arg1);

    void on_isbn_checkBox_stateChanged(int arg1);

    void on_illustrations_checkBox_stateChanged(int arg1);

    void on_hard_covers_checkBox_stateChanged(int arg1);

    void on_edition_size_checkBox_stateChanged(int arg1);

    void on_find_pushButton_clicked();

    void on_cancel_pushButton_clicked();


    void showFindDialod(QRect size);


    bool supplied();
    void find();
    
private:
    Ui::FindBooksDialog *ui;
    QMap<QPair<int, QCheckBox*>, QPair<QWidget*, QWidget*> > checkboxes;
    QVector<Book*> toFind;
//    DisplayWindow *d;
};

#endif // FINDBOOKSDIALOG_H

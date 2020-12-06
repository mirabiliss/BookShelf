#ifndef ADDBOOKDIALOG_H
#define ADDBOOKDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "book.h"

namespace Ui {
class AddBookDialog;
}

class AddBookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddBookDialog(QWidget *parent = nullptr);
    ~AddBookDialog();

signals:
    void addbookdialog(Book* book);

private slots:
    void on_add_pushButton_clicked();

    void on_cancel_pushButton_clicked();

private:
    Ui::AddBookDialog *ui;
};

#endif // ADDBOOKDIALOG_H

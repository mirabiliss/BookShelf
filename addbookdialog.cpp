#include "addbookdialog.h"
#include "ui_addbookdialog.h"

AddBookDialog::AddBookDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddBookDialog)
{
    ui->setupUi(this);
}

AddBookDialog::~AddBookDialog()
{
    delete ui;
}

//bool isWidgetEmpty(QWidget* w)
//{
//    if (w->metaObject()->className() == QString("QWidget"))
//        return false;
//    if (w->metaObject()->className() == QString("QLineEdit"))
//    {
//        return static_cast<QLineEdit*>(w)->text().isEmpty();
//    }
//    return false;
//}

void AddBookDialog::on_add_pushButton_clicked()
{
    if (ui->author_name_lineEdit->text().isEmpty() || ui->author_surname_lineEdit->text().isEmpty() \
            || ui->title_lineEdit->text().isEmpty() || ui->isbn_lineEdit->text().isEmpty())
    {
        QMessageBox::warning(this, tr("Not all fields filled"),
            tr("Please supply all information."), QMessageBox::Ok);
    }
    else
    {
        Book* book = new Book;
        book->setAuthor(new Author(new QString(ui->author_name_lineEdit->text()), new QString(ui->author_surname_lineEdit->text())));
        book->setTitle(new QString(ui->title_lineEdit->text()));
        book->setYearOfPublishment(ui->year_spinBox->value());
        book->setISBN(new QString(ui->isbn_lineEdit->text()));
        book->setPages(ui->pages_spinBox->value());
        book->setEditionSize(ui->editionSize_spinBox->value());
        book->setIllustrations(ui->yes_illustrations_radioButton->isChecked() ? true : false);
        book->setHardCover(ui->yes_hard_covers_radioButton->isChecked() ? true : false);

        this->close();
        emit addbookdialog(book);
    }
}

void AddBookDialog::on_cancel_pushButton_clicked()
{
    this->close();
}

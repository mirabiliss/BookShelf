#include "findbooksdialog.h"
#include "ui_findbooksdialog.h"

FindBooksDialog::FindBooksDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindBooksDialog)
{
    ui->setupUi(this);
    ui->author_name_lineEdit->setVisible(false);
    ui->author_surname_lineEdit->setVisible(false);
    ui->title_lineEdit->setVisible(false);
    ui->year_lineEdit->setVisible(false);
    ui->min_pages_spinBox->setVisible(false);
    ui->max_pages_spinBox->setVisible(false);
    ui->isbn_lineEdit->setVisible(false);
    ui->yes_illustrations_radioButton->setVisible(false);
    ui->no_illustrations_radioButton->setVisible(false);
    ui->yes_hard_covers_radioButton->setVisible(false);
    ui->no_hard_covers_radioButton->setVisible(false);
    ui->min_edition_size_spinBox->setVisible(false);
    ui->max_edition_size_spinBox->setVisible(false);
}

FindBooksDialog::~FindBooksDialog()
{
    delete ui;
}

void FindBooksDialog::on_author_checkBox_stateChanged(int arg1)
{
    if (arg1 == 2) // checked
    {
        ui->author_name_lineEdit->setVisible(true);
        ui->author_surname_lineEdit->setVisible(true);

    } else if (arg1 == 0) // unchecked
    {
        ui->author_name_lineEdit->setVisible(false);
        ui->author_surname_lineEdit->setVisible(false);
    }
}

void FindBooksDialog::on_title_checkBox_stateChanged(int arg1)
{
    if (arg1 == 2) // checked
    {
        ui->title_lineEdit->setVisible(true);
        ui->title_lineEdit->setVisible(true);

    } else if (arg1 == 0) // unchecked
    {
        ui->title_lineEdit->setVisible(false);
        ui->title_lineEdit->setVisible(false);
    }
}

void FindBooksDialog::on_year_checkBox_stateChanged(int arg1)
{
    if (arg1 == 2) // checked
    {
        ui->year_lineEdit->setVisible(true);
        ui->year_lineEdit->setVisible(true);

    } else if (arg1 == 0) // unchecked
    {
        ui->year_lineEdit->setVisible(false);
        ui->year_lineEdit->setVisible(false);
    }
}

void FindBooksDialog::on_pages_checkBox_stateChanged(int arg1)
{
    if (arg1 == 2) // checked
    {


    } else if (arg1 == 0) // unchecked
    {

    }
}

void FindBooksDialog::on_isbn_checkBox_stateChanged(int arg1)
{
    if (arg1 == 2) // checked
    {
        ui->isbn_lineEdit->setVisible(true);
        ui->isbn_lineEdit->setVisible(true);

    } else if (arg1 == 0) // unchecked
    {
        ui->isbn_lineEdit->setVisible(false);
        ui->isbn_lineEdit->setVisible(false);
    }
}

void FindBooksDialog::on_illustrations_checkBox_stateChanged(int arg1)
{

}

void FindBooksDialog::on_hard_covers_checkBox_stateChanged(int arg1)
{

}

void FindBooksDialog::on_edition_size_checkBox_stateChanged(int arg1)
{

}

void FindBooksDialog::on_find_pushButton_clicked()
{

}

void FindBooksDialog::on_cancel_pushButton_clicked()
{

}

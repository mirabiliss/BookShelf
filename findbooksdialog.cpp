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
    
    connect(ui->find_pushButton, SIGNAL(clicked()), this, SLOT(find()));
    
}

FindBooksDialog::~FindBooksDialog()
{
    delete ui;
}

bool FindBooksDialog::checkIfFilled()
{
    if (ui->author_name_lineEdit->text().isEmpty() || ui->author_surname_lineEdit->text().isEmpty() \
            || ui->title_lineEdit->text().isEmpty() || ui->year_lineEdit->text().isEmpty() \
            || (ui->min_pages_spinBox->text().isEmpty() || ui->max_pages_spinBox->text().isEmpty()) \
            || (ui->min_edition_size_spinBox->text().isEmpty() || ui->max_edition_size_spinBox->text().isEmpty()) \
            || ui->isbn_lineEdit->text().isEmpty()  \
            || (ui->yes_illustrations_radioButton->isChecked() || ui->no_illustrations_radioButton->isChecked()) \
            || (ui->yes_hard_covers_radioButton->isChecked() || ui->no_hard_covers_radioButton->isChecked()))
        return false;
    return true;
    
}

void FindBooksDialog::find()
{
    if (checkIfFilled())
        (void) QMessageBox::information(this, tr("Not all checked values filled"),
            tr("Please supply all chosen information."), QMessageBox::Cancel);
    else
    {
        // check which checkboxes are checked and create parameters
    }
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

    } else if (arg1 == 0) // unchecked
    {
        ui->title_lineEdit->setVisible(false);
    }
}

void FindBooksDialog::on_year_checkBox_stateChanged(int arg1)
{
    if (arg1 == 2) // checked
    {
        ui->year_lineEdit->setVisible(true);
    } else if (arg1 == 0) // unchecked
    {
        ui->year_lineEdit->setVisible(false);
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

void FindBooksDialog::on_pages_checkBox_stateChanged(int arg1)
{
    if (arg1 == 2) // checked
    {
        ui->min_pages_spinBox->setVisible(true);
        ui->max_pages_spinBox->setVisible(true);
        ui->pages_label->setVisible(true);
    } else if (arg1 == 0) // unchecked
    {
        ui->min_pages_spinBox->setVisible(false);
        ui->max_pages_spinBox->setVisible(false);
        ui->pages_label->setVisible(false);
    }
}

void FindBooksDialog::on_illustrations_checkBox_stateChanged(int arg1)
{
    if (arg1 == 2) // checked
    {
        ui->yes_illustrations_radioButton->setVisible(true);
        ui->no_illustrations_radioButton->setVisible(true);
    } else if (arg1 == 0) // unchecked
    {
        ui->yes_illustrations_radioButton->setVisible(false);
        ui->no_illustrations_radioButton->setVisible(false);
    }
}

void FindBooksDialog::on_hard_covers_checkBox_stateChanged(int arg1)
{
    if (arg1 == 2) // checked
    {
        ui->yes_hard_covers_radioButton->setVisible(true);
        ui->no_hard_covers_radioButton->setVisible(true);
    } else if (arg1 == 0) // unchecked
    {
        ui->yes_hard_covers_radioButton->setVisible(false);
        ui->no_hard_covers_radioButton->setVisible(false);
    }
}

void FindBooksDialog::on_edition_size_checkBox_stateChanged(int arg1)
{
    if (arg1 == 2) // checked
    {
        ui->min_edition_size_spinBox->setVisible(true);
        ui->max_edition_size_spinBox->setVisible(true);
        ui->edSize_label->setVisible(true);
    } else if (arg1 == 0) // unchecked
    {
        ui->min_edition_size_spinBox->setVisible(false);
        ui->max_edition_size_spinBox->setVisible(false);
        ui->edSize_label->setVisible(false);
    }
}

void FindBooksDialog::on_find_pushButton_clicked()
{

}

void FindBooksDialog::on_cancel_pushButton_clicked()
{

}

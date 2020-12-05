#include "findbooksdialog.h"
#include "ui_findbooksdialog.h"

FindBooksDialog::FindBooksDialog(QVector<Book*> books, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindBooksDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("BookShelf");

    // temporary books to work with
    this->toFind = books;

    // all given info
    checkboxes = {
        {{0, ui->author_checkBox}, {ui->author_name_lineEdit, ui->author_surname_lineEdit}},
        {{1, ui->title_checkBox}, {ui->title_lineEdit, new QWidget()}},
        {{2, ui->year_checkBox}, {ui->year_spinBox, new QWidget()}},
        {{3, ui->pages_checkBox}, {ui->min_pages_spinBox, ui->max_pages_spinBox}},
        {{4, ui->isbn_checkBox}, {ui->isbn_lineEdit, new QWidget()}},
        {{5, ui->illustrations_checkBox}, {ui->yes_illustrations_radioButton, ui->no_illustrations_radioButton}},
        {{6, ui->hard_covers_checkBox}, {ui->yes_hard_covers_radioButton, ui->no_hard_covers_radioButton}},
        {{7, ui->edition_size_checkBox}, {ui->min_edition_size_spinBox, ui->max_edition_size_spinBox}}
    };

    for (auto &it : checkboxes)
    {
        it.first->setVisible(false);
        it.second->setVisible(false);
    }
    ui->pages_label->setVisible(false);
    ui->edSize_label->setVisible(false);
}

FindBooksDialog::~FindBooksDialog()
{
    delete ui;
}

bool isWidgetEmpty(QWidget* w)
{
    if (w->metaObject()->className() == QString("QWidget"))
        return false;
    if (w->metaObject()->className() == QString("QLineEdit"))
    {
        return static_cast<QLineEdit*>(w)->text().isEmpty();
    }
    return false;
}

bool FindBooksDialog::supplied()
{
    // check if parameter checkbox is checked & then is info supplied
    for (auto it = checkboxes.begin(); it != checkboxes.end(); it++)
    {
        auto checkbox = it.key();
        auto values = it.value();

        if (checkbox.second->isChecked())
        {
            if (isWidgetEmpty(values.first) && isWidgetEmpty(values.second))
                return false;
        }
    }
    return true;
}

void FindBooksDialog::find()
{
    if (!supplied())
    {
        (void) QMessageBox::information(this, tr("Not all checked values filled"),
            tr("Please supply all chosen information."), QMessageBox::Cancel);
        return;
    }
    else
    {
        // if current parameter is checked
        for (auto it = checkboxes.begin(); it != checkboxes.end(); it++)
        {
            auto checkbox = it.key();

            if (checkbox.second->isChecked())
            {
                switch (checkbox.first) {

                // author
                case 0:
                {
                    // read val
                    Author* author = new Author(new QString(ui->author_name_lineEdit->text()), new QString(ui->author_surname_lineEdit->text()));

                    // delete what doesn't fit
                    for (int i = 0; i < toFind.size(); i++)
                    {
                        if ((toFind[i]->author()->name() != author->name()) || (toFind[i]->author()->surname() != author->surname()))
                            toFind.remove(i);
                    }
                    break;
                }

                // title
                case 1:
                {
                    QString title = ui->title_lineEdit->text();
                    QVector<int> posToRemove;
                    QVector<Book*> tmp;

                    for (int i = 0; i < toFind.size(); i++)
                    {
                        if (toFind[i]->title() != title)
                            posToRemove.push_back(i);
                    }
                    // store what satisfies the condition
                    int k = 0;
                    for (int i = 0; i < toFind.size(); i++)
                    {
                        if (i != posToRemove[k])
                        {
                            tmp.push_back(toFind[i]);
                        }
                        else
                            k++;
                    }

                    toFind = tmp;

                    break;
                }

                // year of publishment
                case 2:
                {
                    int year = ui->year_spinBox->value();
                    QVector<int> posToRemove;
                    QVector<Book*> tmp;

                    for (int i = 0; i < toFind.size(); i++)
                    {
                        if (toFind[i]->yearOfPublishment() != year)
                            posToRemove.push_back(i);
                    }
                    // store what satisfies the condition
                    int k = 0;
                    for (int i = 0; i < toFind.size(); i++)
                    {
                        if (i != posToRemove[k])
                        {
                            tmp.push_back(toFind[i]);
                        }
                        else
                            k++;
                    }

                    toFind = tmp;


                    break;
                }

                // pages
                case 3:
                {
                    unsigned int min = ui->min_pages_spinBox->value();
                    unsigned int max = ui->max_pages_spinBox->value();
                    QVector<int> posToRemove;
                    QVector<Book*> tmp;

                    for (int i = 0; i < toFind.size(); i++)
                    {
                        if ((toFind[i]->pages() < min) || (toFind[i]->pages() > max))
                            posToRemove.push_back(i);
                    }
                    // store what satisfies the condition
                    int k = 0;
                    for (int i = 0; i < toFind.size(); i++)
                    {
                        if (i != posToRemove[k])
                        {
                            tmp.push_back(toFind[i]);
                        }
                        else
                            k++;
                    }

                    toFind = tmp;

                    break;
                }

                // isbn
                case 4:
                {
                    QString isbn = ui->isbn_lineEdit->text();
                    QVector<int> posToRemove;
                    QVector<Book*> tmp;

                    for (int i = 0; i < toFind.size(); i++)
                    {
                        if ((toFind[i]->ISBN() != isbn))
                            posToRemove.push_back(i);
                    }
                    // store what satisfies the condition
                    int k = 0;
                    for (int i = 0; i < toFind.size(); i++)
                    {
                        if (i != posToRemove[k])
                        {
                            tmp.push_back(toFind[i]);
                        }
                        else
                            k++;
                    }

                    toFind = tmp;

                    break;
                }

                // illustrations
                case 5:
                {
                    bool img = ui->yes_illustrations_radioButton->isChecked() ? true : false;
                    QVector<int> posToRemove;
                    QVector<Book*> tmp;

                    for (int i = 0; i < toFind.size(); i++)
                    {
                        if (toFind[i]->illustrations() != img)
                            posToRemove.push_back(i);
                    }
                    // store what satisfies the condition
                    int k = 0;
                    for (int i = 0; i < toFind.size(); i++)
                    {
                        if (i != posToRemove[k])
                        {
                            tmp.push_back(toFind[i]);
                        }
                        else
                            k++;
                    }

                    toFind = tmp;

                    break;
                }

                // hard covers
                case 6:
                {
                    bool cov = ui->yes_hard_covers_radioButton->isChecked() ? true : false;
                    QVector<int> posToRemove;
                    QVector<Book*> tmp;

                    for (int i = 0; i < toFind.size(); i++)
                    {
                        if (toFind[i]->hardCover() != cov)
                            posToRemove.push_back(i);
                    }
                    // store what satisfies the condition
                    int k = 0;
                    for (int i = 0; i < toFind.size(); i++)
                    {
                        if (i != posToRemove[k])
                        {
                            tmp.push_back(toFind[i]);
                        }
                        else
                            k++;
                    }

                    toFind = tmp;

                    break;
                }

                // edition size
                case 7:
                {
                    unsigned int min = ui->min_edition_size_spinBox->value();
                    unsigned int max = ui->max_edition_size_spinBox->value();
                    QVector<int> posToRemove;
                    QVector<Book*> tmp;

                    for (int i = 0; i < toFind.size(); i++)
                    {
                        if ((toFind[i]->editionSize() < min) || (toFind[i]->editionSize() > max))
                            posToRemove.push_back(i);
                    }
                    // store what satisfies the condition
                    int k = 0;
                    for (int i = 0; i < toFind.size(); i++)
                    {
                        if (i != posToRemove[k])
                        {
                            tmp.push_back(toFind[i]);
                        }
                        else
                            k++;
                    }

                    toFind = tmp;

                    break;
                }

                }
            }
        }
        // return toSort to displaywindow & display it
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
        ui->year_spinBox->setVisible(true);
    } else if (arg1 == 0) // unchecked
    {
        ui->year_spinBox->setVisible(false);
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
    this->find();
    this->close();
    emit finddialog(this->toFind, this->geometry());
}

void FindBooksDialog::on_cancel_pushButton_clicked()
{
    this->find();
    this->close();
    // toFind has to be empty
    emit finddialog(this->toFind, this->geometry());
}

void FindBooksDialog::showFindDialod(QRect size)
{
    this->setGeometry(size);
    this->show();
}

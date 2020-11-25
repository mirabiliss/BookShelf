#ifndef FINDBOOKSDIALOG_H
#define FINDBOOKSDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class FindBooksDialog;
}

class FindBooksDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindBooksDialog(QWidget *parent = nullptr);
    ~FindBooksDialog();

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

    
    bool checkIfFilled();
    void find();
    
private:
    Ui::FindBooksDialog *ui;
};

#endif // FINDBOOKSDIALOG_H

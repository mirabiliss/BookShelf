#ifndef FINDBOOKSDIALOG_H
#define FINDBOOKSDIALOG_H

#include <QDialog>

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
    
private:
    Ui::FindBooksDialog *ui;
};

#endif // FINDBOOKSDIALOG_H

#ifndef MAINMENU_H
#define MAINMENU_H

#include "displaywindow.h"
#include "findbooksdialog.h"

namespace Ui {
class MainMenu;
}

class MainMenu : public QDialog
{
    Q_OBJECT

signals:
    void displaywindow(QRect); // implement?

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

private slots:
    void on_view_pushButton_clicked();

    void on_intro_pushButton_clicked();

private:
    Ui::MainMenu *ui;
    DisplayWindow *displayWindow;
};

#endif // MAINMENU_H

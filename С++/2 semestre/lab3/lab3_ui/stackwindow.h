#ifndef STACKWINDOW_H
#define STACKWINDOW_H
#include <stdexcept>
#include "Collections/Stack.hpp"

#include <QDialog>

namespace Ui {
class StackWindow;
}

class StackWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StackWindow(QWidget *parent = nullptr);
    ~StackWindow();

private:
    Ui::StackWindow *ui;
    void Label_update();
    lab3::Stack<long long int> main_stack;

private slots:
    void digit_numbers();
    void plus_minus();
    void on_Button_Clear_clicked();
    void on_Button_BackSpace_clicked();
    void on_Button_GetSize_clicked();
    void on_Button_Push_clicked();
    void on_Button_Peek_clicked();
    void on_Button_Pop_clicked();
};

#endif // STACKWINDOW_H

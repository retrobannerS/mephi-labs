#ifndef DEQUEWINDOW_H
#define DEQUEWINDOW_H

#include <QDialog>
#include "Collections/Deque.hpp"

namespace Ui {
class DequeWindow;
}

class DequeWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DequeWindow(QWidget *parent = nullptr);
    ~DequeWindow();

private:
    Ui::DequeWindow *ui;
    lab3::Deque<long long int> main_deque;
    void Label_update();

private slots:
    void digit_numbers();
    void plus_minus();
    void on_Button_Clear_clicked();
    void on_Button_BackSpace_clicked();
    void on_Button_GetSize_clicked();
    void on_Button_PushBack_clicked();
    void on_Button_Front_clicked();
    void on_Button_Back_clicked();
    void on_Button_PushFront_clicked();
    void on_Button_PopFront_clicked();
    void on_Button_PopBack_clicked();
};

#endif // DEQUEWINDOW_H

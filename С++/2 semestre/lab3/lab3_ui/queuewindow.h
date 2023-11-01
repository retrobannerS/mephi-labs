#ifndef QUEUEWINDOW_H
#define QUEUEWINDOW_H

#include <QDialog>
#include "Collections/Queue.hpp"

namespace Ui {
class QueueWindow;
}

class QueueWindow : public QDialog
{
    Q_OBJECT

public:
    explicit QueueWindow(QWidget *parent = nullptr);
    ~QueueWindow();

private:
    Ui::QueueWindow *ui;
    lab3::Queue<long long int> main_queue;
    void Label_update();

private slots:
    void digit_numbers();
    void plus_minus();
    void on_Button_Clear_clicked();
    void on_Button_BackSpace_clicked();
    void on_Button_GetSize_clicked();
    void on_Button_Push_clicked();
    void on_Button_Front_clicked();
    void on_Button_Back_clicked();
    void on_Button_Pop_clicked();
};

#endif // QUEUEWINDOW_H

#ifndef PRIORITYQUEUEWINDOW_H
#define PRIORITYQUEUEWINDOW_H

#include <QDialog>
#include "Collections/PriorityQueue.hpp"

namespace Ui {
class PriorityQueueWindow;
}

class PriorityQueueWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PriorityQueueWindow(QWidget *parent = nullptr);
    ~PriorityQueueWindow();

private:
    Ui::PriorityQueueWindow *ui;
    lab3::PriorityQueue<long long int> main_queue;
    void Label_update();

private slots:
    void digit_numbers();
    void plus_minus();
    void on_Button_Clear_clicked();
    void on_Button_BackSpace_clicked();
    void on_Button_GetSize_clicked();
    void on_Button_Push_clicked();
    void on_Button_Top_clicked();
    void on_Button_Bottom_clicked();
    void on_Button_Pop_clicked();
    void on_Button_ToPriority_clicked();
};

#endif // PRIORITYQUEUEWINDOW_H

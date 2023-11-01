#ifndef LAB2_H
#define LAB2_H

#include <QMainWindow>
#include "ArraySequence.hpp"
#include "ListSequence.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class lab2; }
QT_END_NAMESPACE

class SequenceWindow : public QMainWindow
{
    Q_OBJECT

public:
    SequenceWindow(QWidget *parent = nullptr);
    ~SequenceWindow();

private:
    Ui::lab2 *ui;
    lab2::ArraySequence<long long int> MainArr;
    lab2::ListSequence<long long int> MainList;
    void Label_update();

private slots:
    void digit_numbers();
    void plus_minus();
    void on_Button_Clear_clicked();
    void on_Button_BackSpace_clicked();
    void on_Button_Tests_clicked();
    void on_Button_ToIndex_clicked();
    void on_Button_GetSize_clicked();
    void on_ChooseButton_currentIndexChanged(int index);
    void on_Button_PushBack_clicked();
    void on_Button_Get_clicked();
    void on_Button_Set_clicked();
    void on_Button_PopFrom_clicked();
    void on_Button_InsertAt_clicked();
    void on_Button_GetFirst_clicked();
    void on_Button_GetLast_clicked();
    void on_Button_PushFront_clicked();
    void on_Button_PopFront_clicked();
    void on_Button_PopBack_clicked();
};
#endif // LAB2_H

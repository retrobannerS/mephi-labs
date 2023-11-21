#ifndef LAB1_H
#define LAB1_H

#include <QMainWindow>
#include "SmartArraySequence.hpp"
#include "SmartListSequence.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class lab1; }
QT_END_NAMESPACE

class lab1 : public QMainWindow
{
    Q_OBJECT

public:
    lab1(QWidget *parent = nullptr);
    ~lab1();

private:
    Ui::lab1 *ui;
    sem3::SmartArraySequence<long long int> MainArr;
    sem3::SmartListSequence<long long int> MainList;
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
#endif // LAB1_H

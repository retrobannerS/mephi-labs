#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "trees/N_ary_tree.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    lab4::N_ary_tree<int> *main_tree = new lab4::N_ary_tree<int>(5, 5);
    void Label_update();

private slots:
    void digit_numbers();
    void plus_minus();
    void on_Button_Clear_clicked();
    void on_Button_BackSpace_clicked();
    void on_Button_Contains_clicked();
    void on_Button_Add_clicked();
    void on_Button_Size_clicked();
    void on_Button_SubTrees_clicked();
    void on_Button_Arity_clicked();
    void on_Button_Height_clicked();
    void on_Button_Delete_clicked();
    void on_Button_Value_clicked();
    void on_Button_Set_clicked();
    void on_Button_Traverse_clicked();
};
#endif // MAINWINDOW_H

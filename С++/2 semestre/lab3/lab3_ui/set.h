#ifndef SET_H
#define SET_H

#include <QDialog>
#include "Collections/Set.hpp"

namespace Ui {
class Set;
}

namespace mynamespace {
    class Set : public QDialog
    {
        Q_OBJECT

    public:
        explicit Set(QWidget *parent = nullptr);
        ~Set();

    private:
        Ui::Set *ui;
        lab3::Set<long long int> set1;
        lab3::Set<long long int> set2;
        void Label_update();

    private slots:
        void digit_numbers();
        void plus_minus();
        void on_Button_Clear_clicked();
        void on_Button_BackSpace_clicked();
        void on_Button_Power_clicked();
        void on_ChooseButton_currentIndexChanged(int index);
        void on_Button_Add_clicked();
        void on_Button_Remove_clicked();
        void on_Button_Union_clicked();
        void on_Button_Insertion_clicked();
        void on_Button_Difference_clicked();
    };
}



#endif // SET_H

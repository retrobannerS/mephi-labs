#include "set.h"
#include "ui_set.h"
#include <QMessageBox>
#include <QString>
#include <stdexcept>
#include "Collections/Set.hpp"

using namespace lab2;
using namespace std;
using namespace mynamespace;

Set::Set(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Set)
{
    ui->setupUi(this);
    Label_update();
    connect(ui->Button_0, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->Button_1, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->Button_2, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->Button_3, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->Button_4, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->Button_5, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->Button_6, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->Button_7, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->Button_8, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->Button_9, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->Button_PlusMinus, SIGNAL(clicked()), this, SLOT(plus_minus()));
}

Set::~Set()
{
    delete ui;
}

void Set::Label_update() {
    QString str = "{ ";
    if(ui->ChooseButton->currentIndex() == 0){
        if(set1.empty()) {
            ui->ShowSet->setText("{ }");
            return;
        }
        for(auto item : set1) {
            str += QString::number(item) + ", ";
        }
    } else if (ui->ChooseButton->currentIndex() == 1) {
        if(set2.empty()) {
            ui->ShowSet->setText("{ }");
            return;
        }
        for(auto item : set2) {
            str += QString::number(item) + ", ";
        }
    }
    str.removeLast();
    str.removeLast();
    str += " }";
    ui->ShowSet->setText(str);
}

void Set::digit_numbers() {
    QPushButton *num = (QPushButton *)sender();
    QString nextNum = ui->Main_label->text() + num->text();
    if (nextNum.length() > 15) {
        return;
    }
    long long int now_in_line = nextNum.toLongLong();
    QString to_show = QString::number(now_in_line, 'g', 15);
    ui->Main_label->setText(to_show);
}

void Set::plus_minus() {
    QString nextNum = ui->Main_label->text();
    long long int now_in_line = nextNum.toLongLong();
    now_in_line *= -1;
    QString to_show = QString::number(now_in_line, 'g', 15);
    ui->Main_label->setText(to_show);
}



void Set::on_Button_Clear_clicked()
{
    if(ui->ChooseButton->currentIndex() == 0) {
        this->set1.clear();
    } else if(ui->ChooseButton->currentIndex() == 1){
        this->set2.clear();
    }
    Label_update();
}


void Set::on_Button_BackSpace_clicked()
{
    QString nextNum = ui->Main_label->text().removeLast();
    ui->Main_label->setText(nextNum);
}

void Set::on_Button_Power_clicked()
{
    if(ui->ChooseButton->currentIndex() == 0)
        ui->Main_label->setText(QString::number(this->set1.power()));
    else
        ui->Main_label->setText(QString::number(this->set2.power()));
}

void Set::on_ChooseButton_currentIndexChanged(int index)
{
    Label_update();
}

void Set::on_Button_Add_clicked()
{
    if(ui->Main_label->text().isEmpty()) {
        return;
    }
    long long int item = ui->Main_label->text().toLongLong();
    try {
        if(ui->ChooseButton->currentIndex() == 0)
            this->set1.add(item);
        else
            this->set2.add(item);
        Label_update();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}

void Set::on_Button_Remove_clicked()
{
    if(ui->Main_label->text().isEmpty()) {
        return;
    }
    long long int item = ui->Main_label->text().toLongLong();
    try {
        if(ui->ChooseButton->currentIndex() == 0)
            this->set1.remove(item);
        else
            this->set2.remove(item);
        Label_update();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}



void Set::on_Button_Union_clicked()
{
    if(ui->ChooseButton->currentIndex() == 0)
        set1 = set1.union_with(set2);
    else
        set2 = set2.union_with(set1);
    Label_update();
}




void Set::on_Button_Insertion_clicked()
{
    if(ui->ChooseButton->currentIndex() == 0)
        set1 = set1.intersection_with(set2);
    else
        set2 = set2.intersection_with(set1);
    Label_update();
}




void Set::on_Button_Difference_clicked()
{
    if(ui->ChooseButton->currentIndex() == 0)
        set1 = set1.difference_with(set2);
    else
        set2 = set2.difference_with(set1);
    Label_update();
}


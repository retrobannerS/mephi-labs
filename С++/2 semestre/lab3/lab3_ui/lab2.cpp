#include "lab2.h"
#include "ui_lab2.h"
#include <QString>
#include <stdexcept>
#include <QMessageBox>
#include "ArraySequence.hpp"
#include "ListSequence.hpp"

SequenceWindow::SequenceWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::lab2)
{
    ui->setupUi(this);
    ui->Index_label->setText("0");

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

SequenceWindow::~SequenceWindow()
{
    delete ui;
}

void SequenceWindow::Label_update() {
    QString str = "[ ";
    int size = 0;
    if(ui->ChooseButton->currentIndex() == 0){
        size = this->MainArr.GetSize();
    } else if (ui->ChooseButton->currentIndex() == 1) {
        size = this->MainList.GetSize();
    }

    for(int i = 0; i != size; ++i){
        if(ui->ChooseButton->currentIndex() == 0){
            str += QString::number(this->MainArr.Get(i));
        } else if (ui->ChooseButton->currentIndex() == 1) {
            str += QString::number(this->MainList.Get(i));
        }
        if(i != size - 1) {
            str += ", ";
        }
    }
    str += " ]";
    ui->ShowSequence->setText(str);
}

void SequenceWindow::digit_numbers() {
    QPushButton *num = (QPushButton *)sender();
    QString nextNum = ui->Main_label->text() + num->text();
    if (nextNum.length() > 15) {
        return;
    }
    long long int now_in_line = nextNum.toLongLong();
    QString to_show = QString::number(now_in_line, 'g', 15);
    ui->Main_label->setText(to_show);
}

void SequenceWindow::plus_minus() {
    QString nextNum = ui->Main_label->text();
    long long int now_in_line = nextNum.toLongLong();
    now_in_line *= -1;
    QString to_show = QString::number(now_in_line, 'g', 15);
    ui->Main_label->setText(to_show);
}



void SequenceWindow::on_Button_Clear_clicked()
{
    if(ui->ChooseButton->currentIndex() == 0) {
        this->MainArr.Clear();
    } else if(ui->ChooseButton->currentIndex() == 1){
        this->MainList.Clear();
    }
    Label_update();
}


void SequenceWindow::on_Button_BackSpace_clicked()
{
    QString nextNum = ui->Main_label->text().removeLast();
    ui->Main_label->setText(nextNum);
}


void SequenceWindow::on_Button_Tests_clicked()
{

}


void SequenceWindow::on_Button_ToIndex_clicked()
{
    if(ui->Main_label->text().toInt() < 0) {
        QMessageBox::warning(this, "Invalid index", "Index mightn`t be under zero!");
        return;
    }
    size_t len = ui->Main_label->text().length();
    if(0 < len and len < 11) {
        ui->Index_label->setText(ui->Main_label->text());
        ui->Main_label->clear();
    }
    if(len > 10) {
        QMessageBox::warning(this, "Index warning", "Index is too large");
    }
}


void SequenceWindow::on_Button_GetSize_clicked()
{
    if(ui->ChooseButton->currentIndex() == 0)
        ui->Main_label->setText(QString::number(this->MainArr.GetSize()));
    else
        ui->Main_label->setText(QString::number(this->MainList.GetSize()));
}


void SequenceWindow::on_ChooseButton_currentIndexChanged(int index)
{
    Label_update();
}


void SequenceWindow::on_Button_Get_clicked()
{
    int index = ui->Index_label->text().toInt();
    long long int value;
    try {
        if(ui->ChooseButton->currentIndex() == 0)
            value = this->MainArr.Get(index);
        else
            value = this->MainList.Get(index);
        ui->Main_label->setText(QString::number(value));
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}


void SequenceWindow::on_Button_Set_clicked()
{
    if(ui->Main_label->text().isEmpty()) {
        return;
    }
    int index = ui->Index_label->text().toInt();
    long long int item = ui->Main_label->text().toLongLong();
    try {
        if(ui->ChooseButton->currentIndex() == 0)
            this->MainArr.Set(index, item);
        else
            this->MainList.Set(index, item);
        Label_update();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}


void SequenceWindow::on_Button_PopFrom_clicked()
{
    int index = ui->Index_label->text().toInt();
    try {
        if(ui->ChooseButton->currentIndex() == 0)
            this->MainArr.PopFrom(index);
        else
            this->MainList.PopFrom(index);
        Label_update();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}


void SequenceWindow::on_Button_InsertAt_clicked()
{
    if(ui->Main_label->text().isEmpty()) {
        return;
    }
    int index = ui->Index_label->text().toInt();
    long long int item = ui->Main_label->text().toLongLong();
    try {
        if(ui->ChooseButton->currentIndex() == 0)
            this->MainArr.InsertAt(index, item);
        else
            this->MainList.InsertAt(index, item);
        Label_update();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}


void SequenceWindow::on_Button_GetFirst_clicked()
{
    long long int value;
    try {
        if(ui->ChooseButton->currentIndex() == 0)
            value = this->MainArr.GetFirst();
        else
            value = this->MainList.GetFirst();
        ui->Main_label->setText(QString::number(value));
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}




void SequenceWindow::on_Button_GetLast_clicked()
{
    long long int value;
    try {
        if(ui->ChooseButton->currentIndex() == 0)
            value = this->MainArr.GetLast();
        else
            value = this->MainList.GetLast();
        ui->Main_label->setText(QString::number(value));
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}




void SequenceWindow::on_Button_PushFront_clicked()
{
    if(ui->Main_label->text().isEmpty()) {
        return;
    }
    long long int item = ui->Main_label->text().toLongLong();
    try {
        if(ui->ChooseButton->currentIndex() == 0)
            this->MainArr.PushFront(item);
        else
            this->MainList.PushFront(item);
        Label_update();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}

void SequenceWindow::on_Button_PushBack_clicked()
{
    if(ui->Main_label->text().isEmpty()) {
        return;
    }
    long long int item = ui->Main_label->text().toLongLong();
    try {
        if(ui->ChooseButton->currentIndex() == 0)
            this->MainArr.PushBack(item);
        else
            this->MainList.PushBack(item);
        Label_update();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}






void SequenceWindow::on_Button_PopFront_clicked()
{
    try {
        if(ui->ChooseButton->currentIndex() == 0)
            this->MainArr.PopFront();
        else
            this->MainList.PopFront();
        Label_update();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}




void SequenceWindow::on_Button_PopBack_clicked()
{
    try {
        if(ui->ChooseButton->currentIndex() == 0)
            this->MainArr.PopBack();
        else
            this->MainList.PopBack();
        Label_update();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}


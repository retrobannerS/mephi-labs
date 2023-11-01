#include "dequewindow.h"
#include "ui_dequewindow.h"
#include <QString>
#include <stdexcept>
#include <QMessageBox>
#include "Collections/Deque.hpp"

DequeWindow::DequeWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DequeWindow)
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

DequeWindow::~DequeWindow()
{
    delete ui;
}

void DequeWindow::Label_update() {
    QString str = "";

    for(const auto item : main_deque) {
        str.append("<p style='text-align: center; margin-top: 0; margin-bottom: 0;'>" + QString::number(item) + "</p>");
    }
    str.removeLast();
    ui->ShowDeque->setText(str);
    ui->ShowDeque->setAlignment(Qt::AlignCenter);
}

void DequeWindow::digit_numbers() {
    QPushButton *num = (QPushButton *)sender();
    QString nextNum = ui->Main_label->text() + num->text();
    if (nextNum.length() > 10) {
        return;
    }
    long long int now_in_line = nextNum.toLongLong();
    QString to_show = QString::number(now_in_line, 'g', 15);
    ui->Main_label->setText(to_show);
}

void DequeWindow::plus_minus() {
    QString nextNum = ui->Main_label->text();
    long long int now_in_line = nextNum.toLongLong();
    now_in_line *= -1;
    QString to_show = QString::number(now_in_line, 'g', 15);
    ui->Main_label->setText(to_show);
}

void DequeWindow::on_Button_Clear_clicked()
{
    this->main_deque.clear();
    Label_update();
}

void DequeWindow::on_Button_BackSpace_clicked()
{
    QString nextNum = ui->Main_label->text().removeLast();
    ui->Main_label->setText(nextNum);
}

void DequeWindow::on_Button_GetSize_clicked()
{
    ui->Main_label->setText(QString::number(main_deque.size()));
}

void DequeWindow::on_Button_Front_clicked()
{
    try {
        ui->Main_label->setText(QString::number(main_deque.front()));
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}




void DequeWindow::on_Button_Back_clicked()
{
    try {
        ui->Main_label->setText(QString::number(main_deque.back()));
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}




void DequeWindow::on_Button_PushFront_clicked()
{
    if(ui->Main_label->text().isEmpty()) {
        return;
    }
    long long int item = ui->Main_label->text().toLongLong();
    this->main_deque.pushFront(item);
    Label_update();
}

void DequeWindow::on_Button_PushBack_clicked()
{
    if(ui->Main_label->text().isEmpty()) {
        return;
    }
    long long int item = ui->Main_label->text().toLongLong();
    this->main_deque.pushBack(item);
    Label_update();
}






void DequeWindow::on_Button_PopFront_clicked()
{
    try {
        long long int value = this->main_deque.popFront();
        ui->Main_label->setText(QString::number(value));
        Label_update();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}




void DequeWindow::on_Button_PopBack_clicked()
{
    try {
        long long int value = this->main_deque.popBack();
        ui->Main_label->setText(QString::number(value));
        Label_update();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}

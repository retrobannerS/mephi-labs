#include "stackwindow.h"
#include "ui_stackwindow.h"

#include <QString>
#include <stdexcept>
#include <QMessageBox>
#include "Collections/Stack.hpp"

StackWindow::StackWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StackWindow)
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

StackWindow::~StackWindow()
{
    delete ui;
}

void StackWindow::Label_update() {
    QString str = "";

    for(const auto item : main_stack) {
        str.prepend("<p style='text-align: center; margin-top: 0; margin-bottom: 0;'>" + QString::number(item) + "</p>");
    }
    str.removeLast();
    ui->ShowStack->setText(str);
    ui->ShowStack->setAlignment(Qt::AlignCenter);
}

void StackWindow::digit_numbers() {
    QPushButton *num = (QPushButton *)sender();
    QString nextNum = ui->Main_label->text() + num->text();
    if (nextNum.length() > 10) {
        return;
    }
    long long int now_in_line = nextNum.toLongLong();
    QString to_show = QString::number(now_in_line, 'g', 15);
    ui->Main_label->setText(to_show);
}

void StackWindow::plus_minus() {
    QString nextNum = ui->Main_label->text();
    long long int now_in_line = nextNum.toLongLong();
    now_in_line *= -1;
    QString to_show = QString::number(now_in_line, 'g', 15);
    ui->Main_label->setText(to_show);
}

void StackWindow::on_Button_Clear_clicked()
{
    this->main_stack.clear();
    Label_update();
}

void StackWindow::on_Button_BackSpace_clicked()
{
    QString nextNum = ui->Main_label->text().removeLast();
    ui->Main_label->setText(nextNum);
}

void StackWindow::on_Button_GetSize_clicked()
{
    ui->Main_label->setText(QString::number(this->main_stack.size()));
}

void StackWindow::on_Button_Peek_clicked()
{
    try {
        long long int value = main_stack.peek();
        ui->Main_label->setText(QString::number(value));
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}

void StackWindow::on_Button_Push_clicked()
{
    if(ui->Main_label->text().isEmpty()) {
        return;
    }
    long long int item = ui->Main_label->text().toLongLong();
    try {
        this->main_stack.push(item);
        Label_update();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}

void StackWindow::on_Button_Pop_clicked()
{
    try {
        long long value = this->main_stack.pop();
        Label_update();
        ui->Main_label->setText(QString::number(value));
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}

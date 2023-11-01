#include "priorityqueuewindow.h"
#include "ui_priorityqueuewindow.h"
#include <QString>
#include <QMessageBox>
#include <stdexcept>
#include "Collections/PriorityQueue.hpp"

PriorityQueueWindow::PriorityQueueWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PriorityQueueWindow)
{
    ui->setupUi(this);
    ui->Priority_label->setText("1");
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

PriorityQueueWindow::~PriorityQueueWindow()
{
    delete ui;
}

void PriorityQueueWindow::Label_update() {
    QString str = "";

    for(const auto item : main_queue) {
        str.append("<p style='text-align: center; margin-top: 0; margin-bottom: 0;'>{" + QString::number(item.first) +
                   ", " + QString::number(item.second) + "}</p>\n");
    }
    str.removeLast();
    ui->ShowPriorityQueue->setText(str);
    ui->ShowPriorityQueue->setAlignment(Qt::AlignCenter);
}

void PriorityQueueWindow::digit_numbers() {
    QPushButton *num = (QPushButton *)sender();
    QString nextNum = ui->Main_label->text() + num->text();
    if (nextNum.length() > 10) {
        return;
    }
    long long int now_in_line = nextNum.toLongLong();
    QString to_show = QString::number(now_in_line, 'g', 15);
    ui->Main_label->setText(to_show);
}

void PriorityQueueWindow::plus_minus() {
    QString nextNum = ui->Main_label->text();
    long long int now_in_line = nextNum.toLongLong();
    now_in_line *= -1;
    QString to_show = QString::number(now_in_line, 'g', 15);
    ui->Main_label->setText(to_show);
}

void PriorityQueueWindow::on_Button_Clear_clicked()
{
    this->main_queue.clear();
    Label_update();
}

void PriorityQueueWindow::on_Button_BackSpace_clicked()
{
    QString nextNum = ui->Main_label->text().removeLast();
    ui->Main_label->setText(nextNum);
}

void PriorityQueueWindow::on_Button_GetSize_clicked()
{
    ui->Main_label->setText(QString::number(this->main_queue.size()));
}

void PriorityQueueWindow::on_Button_Top_clicked()
{
    try {
        long long int value = main_queue.top().first;
        int priority = main_queue.top().second;
        ui->Main_label->setText(QString::number(value));
        ui->Priority_label->setText(QString::number(priority));
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}

void PriorityQueueWindow::on_Button_Bottom_clicked()
{
    try {
        long long int value = main_queue.bottom().first;
        int priority = main_queue.bottom().second;
        ui->Main_label->setText(QString::number(value));
        ui->Priority_label->setText(QString::number(priority));
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}

void PriorityQueueWindow::on_Button_Push_clicked()
{
    if(ui->Main_label->text().isEmpty()) {
        return;
    }
    long long int item = ui->Main_label->text().toLongLong();
    int priority = ui->Priority_label->text().toInt();
    try {
        this->main_queue.push(item, priority);
        Label_update();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}

void PriorityQueueWindow::on_Button_Pop_clicked()
{
    try {
        long long value = this->main_queue.pop();
        Label_update();
        ui->Main_label->setText(QString::number(value));
        ui->Priority_label->clear();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}

void PriorityQueueWindow::on_Button_ToPriority_clicked()
{
    if(ui->Main_label->text().toInt() < 1) {
        QMessageBox::warning(this, "Invalid priority", "Priority mightn`t be under one!");
        return;
    }
    size_t len = ui->Main_label->text().length();
    if(0 < len and len < 6) {
        ui->Priority_label->setText(ui->Main_label->text());
        ui->Main_label->clear();
    }
    if(len > 5) {
        QMessageBox::warning(this, "Priority warning", "Priority is too large");
    }
}


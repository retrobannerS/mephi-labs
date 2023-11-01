#include "queuewindow.h"
#include "ui_queuewindow.h"
#include <QString>
#include <QMessageBox>
#include <stdexcept>
#include "Collections/Queue.hpp"

QueueWindow::QueueWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QueueWindow)
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

QueueWindow::~QueueWindow()
{
    delete ui;
}

void QueueWindow::Label_update() {
    QString str = "";

    for(const auto item : main_queue) {
        str.append("<p style='text-align: center; margin-top: 0; margin-bottom: 0;'>"
                   + QString::number(item) + "</p>\n");
    }
    str.removeLast();
    ui->ShowQueue->setText(str);
    ui->ShowQueue->setAlignment(Qt::AlignCenter);
}

void QueueWindow::digit_numbers() {
    QPushButton *num = (QPushButton *)sender();
    QString nextNum = ui->Main_label->text() + num->text();
    if (nextNum.length() > 10) {
        return;
    }
    long long int now_in_line = nextNum.toLongLong();
    QString to_show = QString::number(now_in_line, 'g', 15);
    ui->Main_label->setText(to_show);
}

void QueueWindow::plus_minus() {
    QString nextNum = ui->Main_label->text();
    long long int now_in_line = nextNum.toLongLong();
    now_in_line *= -1;
    QString to_show = QString::number(now_in_line, 'g', 15);
    ui->Main_label->setText(to_show);
}

void QueueWindow::on_Button_Clear_clicked()
{
    this->main_queue.clear();
    Label_update();
}

void QueueWindow::on_Button_BackSpace_clicked()
{
    QString nextNum = ui->Main_label->text().removeLast();
    ui->Main_label->setText(nextNum);
}

void QueueWindow::on_Button_GetSize_clicked()
{
    ui->Main_label->setText(QString::number(this->main_queue.size()));
}

void QueueWindow::on_Button_Front_clicked()
{
    try {
        long long int value = main_queue.front();
        ui->Main_label->setText(QString::number(value));
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}

void QueueWindow::on_Button_Back_clicked()
{
    try {
        long long int value = main_queue.back();
        ui->Main_label->setText(QString::number(value));
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}

void QueueWindow::on_Button_Push_clicked()
{
    if(ui->Main_label->text().isEmpty()) {
        return;
    }
    long long int item = ui->Main_label->text().toLongLong();
    try {
        this->main_queue.push(item);
        Label_update();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}

void QueueWindow::on_Button_Pop_clicked()
{
    try {
        long long value = this->main_queue.pop();
        Label_update();
        ui->Main_label->setText(QString::number(value));
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}

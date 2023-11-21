#include "lab1.h"
#include "ui_lab1.h"
#include <QString>
#include <stdexcept>
#include <QMessageBox>
#include <QProcess>
#include <QThread>

lab1::lab1(QWidget *parent) : QMainWindow(parent), ui(new Ui::lab1)
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

lab1::~lab1()
{
    delete ui;
}

void lab1::Label_update() {
    QString str = "[ ";
    int size = 0;
    if(ui->ChooseButton->currentIndex() == 0){
        size = this->MainArr.getSize();
    } else if (ui->ChooseButton->currentIndex() == 1) {
        size = this->MainList.getSize();
    }

    for(int i = 0; i != size; ++i){
        if(ui->ChooseButton->currentIndex() == 0){
            str += QString::number(this->MainArr.get(i));
        } else if (ui->ChooseButton->currentIndex() == 1) {
            str += QString::number(this->MainList.get(i));
        }
        if(i != size - 1) {
            str += ", ";
        }
    }
    str += " ]";
    ui->ShowSequence->setText(str);
}

void lab1::digit_numbers() {
    QPushButton *num = (QPushButton *)sender();
    QString nextNum = ui->Main_label->text() + num->text();
    if (nextNum.length() > 15) {
        return;
    }
    long long int now_in_line = nextNum.toLongLong();
    QString to_show = QString::number(now_in_line, 'g', 15);
    ui->Main_label->setText(to_show);
}

void lab1::plus_minus() {
    QString nextNum = ui->Main_label->text();
    long long int now_in_line = nextNum.toLongLong();
    now_in_line *= -1;
    QString to_show = QString::number(now_in_line, 'g', 15);
    ui->Main_label->setText(to_show);
}



void lab1::on_Button_Clear_clicked()
{
    if(ui->ChooseButton->currentIndex() == 0) {
        this->MainArr.clear();
    } else if(ui->ChooseButton->currentIndex() == 1){
        this->MainList.clear();
    }
    Label_update();
}


void lab1::on_Button_BackSpace_clicked()
{
    QString nextNum = ui->Main_label->text().removeLast();
    ui->Main_label->setText(nextNum);
}

void lab1::on_Button_Tests_clicked()
{

}


void lab1::on_Button_ToIndex_clicked()
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


void lab1::on_Button_GetSize_clicked()
{
    if(ui->ChooseButton->currentIndex() == 0)
        ui->Main_label->setText(QString::number(this->MainArr.getSize()));
    else
        ui->Main_label->setText(QString::number(this->MainList.getSize()));
}


void lab1::on_ChooseButton_currentIndexChanged(int index)
{
    Label_update();
}


void lab1::on_Button_Get_clicked()
{
    int index = ui->Index_label->text().toInt();
    long long int value;
    try {
        if(ui->ChooseButton->currentIndex() == 0)
            value = this->MainArr.get(index);
        else
            value = this->MainList.get(index);
        ui->Main_label->setText(QString::number(value));
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}


void lab1::on_Button_Set_clicked()
{
    if(ui->Main_label->text().isEmpty()) {
        return;
    }
    int index = ui->Index_label->text().toInt();
    long long int item = ui->Main_label->text().toLongLong();
    try {
        if(ui->ChooseButton->currentIndex() == 0)
            this->MainArr.set(index, item);
        else
            this->MainList.set(index, item);
        Label_update();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}


void lab1::on_Button_PopFrom_clicked()
{
    int index = ui->Index_label->text().toInt();
    try {
        if(ui->ChooseButton->currentIndex() == 0)
            this->MainArr.removeAt(index);
        else
            this->MainList.removeAt(index);
        Label_update();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}


void lab1::on_Button_InsertAt_clicked()
{
    if(ui->Main_label->text().isEmpty()) {
        return;
    }
    int index = ui->Index_label->text().toInt();
    long long int item = ui->Main_label->text().toLongLong();
    try {
        if(ui->ChooseButton->currentIndex() == 0)
            this->MainArr.insertAt(index, item);
        else
            this->MainList.insertAt(index, item);
        Label_update();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}


void lab1::on_Button_GetFirst_clicked()
{
    long long int value;
    try {
        if(ui->ChooseButton->currentIndex() == 0)
            value = this->MainArr.getFirst();
        else
            value = this->MainList.getFirst();
        ui->Main_label->setText(QString::number(value));
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}




void lab1::on_Button_GetLast_clicked()
{
    long long int value;
    try {
        if(ui->ChooseButton->currentIndex() == 0)
            value = this->MainArr.getLast();
        else
            value = this->MainList.getLast();
        ui->Main_label->setText(QString::number(value));
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}




void lab1::on_Button_PushFront_clicked()
{
    if(ui->Main_label->text().isEmpty()) {
        return;
    }
    long long int item = ui->Main_label->text().toLongLong();
    try {
        if(ui->ChooseButton->currentIndex() == 0)
            this->MainArr.prepend(item);
        else
            this->MainList.prepend(item);
        Label_update();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}

void lab1::on_Button_PushBack_clicked()
{
    if(ui->Main_label->text().isEmpty()) {
        return;
    }
    long long int item = ui->Main_label->text().toLongLong();
    try {
        if(ui->ChooseButton->currentIndex() == 0)
            this->MainArr.append(item);
        else
            this->MainList.append(item);
        Label_update();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}


void lab1::on_Button_PopFront_clicked()
{
    try {
        if(ui->ChooseButton->currentIndex() == 0)
            this->MainArr.removeFirst();
        else
            this->MainList.removeFirst();
        Label_update();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}




void lab1::on_Button_PopBack_clicked()
{
    try {
        if(ui->ChooseButton->currentIndex() == 0)
            this->MainArr.removeLast();
        else
            this->MainList.removeLast();
        Label_update();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}


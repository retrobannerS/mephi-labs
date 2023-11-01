#include "primenumbers.h"
#include "ui_primenumbers.h"
#include "Algos/PrimeNumbers/PrimeNumbers.h"
#include "ArraySequence.hpp"
#include <utility>
#include <QString>
#include <QMessageBox>

PrimeNumbers::PrimeNumbers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrimeNumbers)
{
    ui->setupUi(this);
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
}

PrimeNumbers::~PrimeNumbers()
{
    delete ui;
}

void PrimeNumbers::digit_numbers() {
    QPushButton *num = (QPushButton *)sender();
    QString nextNum = ui->Main_label->text() + num->text();
    if (nextNum.length() > 15) {
        return;
    }
    long long int now_in_line = nextNum.toLongLong();
    QString to_show = QString::number(now_in_line, 'g', 15);
    ui->Main_label->setText(to_show);
}

void PrimeNumbers::on_Button_Clear_clicked()
{
    ui->Main_label->clear();
}

void PrimeNumbers::on_Button_BackSpace_clicked()
{
    QString nextNum = ui->Main_label->text().removeLast();
    ui->Main_label->setText(nextNum);
}



void PrimeNumbers::on_Button_IsPrime_clicked()
{
    bool is_prime = lab3::isPrime(ui->Main_label->text().toInt());
    if(is_prime) {
        QMessageBox::information(this, "Is prime", "YES");
    } else {
        QMessageBox::information(this, "Is prime", "NO");
    }
}


void PrimeNumbers::on_Button_Factorize_clicked()
{
    int value = ui->Main_label->text().toLongLong();
    ArraySequence<std::pair<int, int>> factorized = lab3::factorize(value);
    QString multipliers;
    QString count;
    for(int i = 0; i != factorized.GetSize(); ++i) {
        std::pair<int, int> pair = factorized[i];
        multipliers += "<p style='text-align: center; margin-top: 0; margin-bottom: 0;'>" + QString::number(pair.first) + "</p>\n";
        count +=  "<p style='text-align: center; margin-top: 0; margin-bottom: 0;'>" + QString::number(pair.second) + "</p>\n";
    }
    multipliers.removeLast();
    count.removeLast();
    ui->ShowMultipliers->setText(multipliers);
    ui->ShowCount->setText(count);
}


void PrimeNumbers::on_Button_EratospheneSieve_clicked()
{
    QString message = "";
    ArraySequence<bool> sieve_array = lab3::sieveOfEratosthenes(ui->Main_label->text().toInt());
    for (int i = 0; i < sieve_array.GetSize(); ++i) {
        if (sieve_array[i]) {
            message += "<font size='5'>" + QString::number(i) + "</font>  ";;
        } else {
            message += "<font size='5'><s style='text-decoration-thickness: 2px; text-decoration-color: red;'>" + QString::number(i) + "</s></font>\n";
        }
        if(i % 20 == 0 && i != 0) {
            message += "\n";
        }
    }
    QMessageBox::information(this, "Eratosphene sieve", message);
}


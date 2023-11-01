#include "hanoi.h"
#include "ui_hanoi.h"
#include <QKeyEvent>
#include <QTimer>
#include "Collections/Stack.hpp"
#include "Algos/hanoi/hanoi.h"
#define STACK(n) ((n) == 1 ? stack1 : ((n) == 2 ? stack2 : stack3))
#define TO_CHAR(N) ((N) == 1 ? '1' : ((N) == 2 ? '2' : '3'))


Hanoi::Hanoi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Hanoi)
{
    ui->setupUi(this);
}

Hanoi::~Hanoi()
{
    delete ui;
}

void Hanoi::hanoi(int n, Stack<int> &from, Stack<int> &to, Stack<int> &aux, int speed) {
    speed = std::max(speed, 1);
    if (n == 1) {
        to.push(from.pop());
        diskMoved();
        return;
    } else {
        hanoi(n - 1, from, aux, to, speed);
        to.push(from.pop());
        diskMoved();
        QTimer::singleShot(speed, this, [&] { hanoi(n - 1, aux, to, from, speed); });
    }
}

void Hanoi::diskMoved() {
    QString str = "";

    for(const auto item : stack1) {
        str.append("<p style='text-align: center; margin-top: 0; margin-bottom: 0;'>" + QString::number(item) + "</p>");
    }
    str.removeLast();
    ui->ShowStack->setText(str);
    ui->ShowStack->setAlignment(Qt::AlignCenter);

    str.clear();

    for(const auto item : stack2) {
        str.append("<p style='text-align: center; margin-top: 0; margin-bottom: 0;'>" + QString::number(item) + "</p>");
    }
    str.removeLast();
    ui->ShowStack_2->setText(str);
    ui->ShowStack_2->setAlignment(Qt::AlignCenter);

    str.clear();

    for(const auto item : stack3) {
        str.append("<p style='text-align: center; margin-top: 0; margin-bottom: 0;'>" + QString::number(item) + "</p>");
    }
    str.removeLast();
    ui->ShowStack_3->setText(str);
    ui->ShowStack_3->setAlignment(Qt::AlignCenter);
}

void Hanoi::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        stack1.clear();
        stack2.clear();
        stack3.clear();
        int from = ui->spinFrom->value();
        int to = ui->spinTo->value();
        int aux = 6 - from - to;
        int N = ui->spinN->value();
        int animation = ui->Animation_time->value();
        for(int i = 1; i <= N; i++) {
            STACK(from).push(i);
        }
        hanoi(N, STACK(from), STACK(to), STACK(aux), animation);
    } else {
        int from = ui->spinFrom->value();
        int to = ui->spinTo->value();
        int aux = 6 - from - to;
        int N = ui->spinN->value();
        for(int i = 1; i <= N; i++) {
            STACK(from).push(i);
        }
        lab3::hanoi2(N, TO_CHAR(from), TO_CHAR(to), TO_CHAR(aux));
        QWidget::keyPressEvent(event);
    }
}

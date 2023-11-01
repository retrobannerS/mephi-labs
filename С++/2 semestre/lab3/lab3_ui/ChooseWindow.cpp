#include "ChooseWindow.h"
#include "ui_ChooseWindow.h"
#include "sequencewindow.h"
#include "stackwindow.h"
#include "dequewindow.h"
#include "queuewindow.h"
#include "priorityqueuewindow.h"
#include "primenumbers.h"
#include "hanoi.h"
#include "set.h"


ChooseWindow::ChooseWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChooseWindow)
{
    ui->setupUi(this);
}

ChooseWindow::~ChooseWindow()
{
    delete ui;
}


void ChooseWindow::on_Choose_button_clicked()
{
    if(ui->buttonGroup->checkedButton() == nullptr) {
        return;
    }

    QString current_button = ui->buttonGroup->checkedButton()->text();
    if(current_button == "Sequence") {
        SequenceWindow window;
        window.setModal(true);
        window.exec();
    } else if(current_button == "Stack") {
        StackWindow window;
        window.setModal(true);
        window.exec();
    } else if(current_button == "Deque") {
        DequeWindow window;
        window.setModal(true);
        window.exec();
    } else if(current_button == "Queue") {
        QueueWindow window;
        window.setModal(true);
        window.exec();
    } else if(current_button == "PriorityQueue") {
        PriorityQueueWindow window;
        window.setModal(true);
        window.exec();
    } else if(current_button == "Set") {
        mynamespace::Set window;
        window.setModal(true);
        window.exec();
    } else if(current_button == "PrimeNumbers") {
        PrimeNumbers window;
        window.setModal(true);
        window.exec();
    } else if(current_button == "Hanoi") {
        Hanoi window;
        window.setModal(true);
        window.exec();
    } else {}
}


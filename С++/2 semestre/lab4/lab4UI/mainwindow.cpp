#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "trees/N_ary_tree.hpp"
#include <string>
#include <QString>
#include <QMessageBox>
#include "Sequence.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    main_tree->add_subtree(4);
    main_tree->add_subtree(7);
    main_tree->add_subtree(8);
    main_tree->add_subtree(11);
    main_tree->add_subtree(2);
    (*main_tree)[0].add_subtree(4);
    (*main_tree)[0].add_subtree(6);
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

MainWindow::~MainWindow()
{
    delete ui;
    delete main_tree;
}

void MainWindow::Label_update() {
    std::string str = main_tree->to_string_for_ui();
    QString str2 = QString::fromStdString(str);
    ui->ShowSequence->setText(str2);
}

void MainWindow::digit_numbers() {
    QPushButton *num = (QPushButton *)sender();
    QString nextNum = ui->Main_label->text() + num->text();
    if (nextNum.length() > 15) {
        return;
    }
    long long int now_in_line = nextNum.toLongLong();
    QString to_show = QString::number(now_in_line, 'g', 15);
    ui->Main_label->setText(to_show);
}

void MainWindow::plus_minus() {
    QString nextNum = ui->Main_label->text();
    long long int now_in_line = nextNum.toLongLong();
    now_in_line *= -1;
    QString to_show = QString::number(now_in_line, 'g', 15);
    ui->Main_label->setText(to_show);
}



void MainWindow::on_Button_Clear_clicked()
{
    ui->Main_label->clear();
}


void MainWindow::on_Button_BackSpace_clicked()
{
    QString nextNum = ui->Main_label->text().removeLast();
    ui->Main_label->setText(nextNum);
}

void MainWindow::on_Button_Contains_clicked()
{
    int value = ui->Main_label->text().toInt();
    if(main_tree->contains(value)) {
        QMessageBox::information(this, "Contains", "Yes!");
    } else {
        QMessageBox::information(this, "Contains", "No!");
    }
}




void MainWindow::on_Button_Add_clicked()
{
    try {
        main_tree->add_subtree(ui->Main_label->text().toInt());
        Label_update();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}




void MainWindow::on_Button_Size_clicked()
{
    ui->Main_label->setText(QString::number(main_tree->size()));
}


void MainWindow::on_Button_SubTrees_clicked()
{
    ui->Main_label->setText(QString::number(main_tree->current_subtrees()));
}




void MainWindow::on_Button_Arity_clicked()
{
    ui->Main_label->setText(QString::number(main_tree->arity()));
}




void MainWindow::on_Button_Height_clicked()
{
    ui->Main_label->setText(QString::number(main_tree->height()));
}




void MainWindow::on_Button_Delete_clicked()
{
    int index = ui->Main_label->text().toInt();
    try {
        main_tree->delete_subtree(index);
        Label_update();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Something went wrong", e.what());
    }
}



void MainWindow::on_Button_Value_clicked()
{
    ui->Main_label->setText(QString::number(main_tree->value()));
}




void MainWindow::on_Button_Set_clicked()
{
    main_tree->set(ui->Main_label->text().toInt());
    Label_update();
}




void MainWindow::on_Button_Traverse_clicked()
{
//    lab4::N_ary_tree<int>::TraverseType type;
//    switch(ui->Main_label->text().toInt()) {
//    case(1):
//        Sequence<int> *seq = main_tree->traverse(lab4::N_ary_tree<int>::TraverseType::NLR);
//        break;
//    case(2):
//        Sequence<int> *seq = main_tree->traverse(lab4::N_ary_tree<int>::TraverseType::NRL);
//        break;
//    case(3):
//        Sequence<int> *seq = main_tree->traverse(lab4::N_ary_tree<int>::TraverseType::LRN);
//        break;
//    case(4):
//        Sequence<int> *seq = main_tree->traverse(lab4::N_ary_tree<int>::TraverseType::RLN);
//        break;
//    }

//    try {
//        Sequence<int> *seq = main_tree->traverse(());
//        Label_update();
//    } catch (const std::exception &e) {
//        QMessageBox::warning(this, "Something went wrong", e.what());
//    }
}


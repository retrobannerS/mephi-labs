#ifndef HANOI_H
#define HANOI_H

#include <QDialog>
#include "Collections/Stack.hpp"
#include <QTimer>
using namespace lab3;

namespace Ui {
class Hanoi;
}

class Hanoi : public QDialog
{
    Q_OBJECT
    QTimer timer;
public:
    explicit Hanoi(QWidget *parent = nullptr);
    ~Hanoi();

private:
    Ui::Hanoi *ui;std::function<void()> pendingAction;
    void keyPressEvent(QKeyEvent *event);
    lab3::Stack<int> stack1;
    lab3::Stack<int> stack2;
    lab3::Stack<int> stack3;
    void hanoi(int n, Stack<int> &from, Stack<int> &to, Stack<int> &aux, int speed);
    void hanoi(int n, Stack<int> &from, Stack<int> &to, Stack<int> &aux);
    void diskMoved();
public slots:
    void executePendingAction() {
        if (pendingAction) {
            auto action = pendingAction;
            pendingAction = {};
            action();
        }
    }
};

#endif // HANOI_H

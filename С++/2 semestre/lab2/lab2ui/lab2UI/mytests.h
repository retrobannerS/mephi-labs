#ifndef MYTESTS_H
#define MYTESTS_H

#include <QDialog>

namespace Ui {
class MyTests;
}

class MyTests : public QDialog
{
    Q_OBJECT

public:
    explicit MyTests(QWidget *parent = nullptr);
    ~MyTests();

private:
    Ui::MyTests *ui;
};

#endif // MYTESTS_H

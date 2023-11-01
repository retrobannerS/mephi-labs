#ifndef PRIMENUMBERS_H
#define PRIMENUMBERS_H

#include <QDialog>

namespace Ui {
class PrimeNumbers;
}

class PrimeNumbers : public QDialog
{
    Q_OBJECT

public:
    explicit PrimeNumbers(QWidget *parent = nullptr);
    ~PrimeNumbers();

private:
    Ui::PrimeNumbers *ui;

private slots:
    void digit_numbers();
    void on_Button_Clear_clicked();
    void on_Button_BackSpace_clicked();
    void on_Button_IsPrime_clicked();
    void on_Button_Factorize_clicked();
    void on_Button_EratospheneSieve_clicked();
};

#endif // PRIMENUMBERS_H

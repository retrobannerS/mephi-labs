#include "mytests.h"
#include "ui_mytests.h"
#include <iostream>
#include <streambuf>

MyTests::MyTests(QWidget *parent) :
    QDialog(parent)
{
    ui = new Ui::MyTests;
    ui->setupUi(this);
    plainTextEdit = ui->plainTextEdit; // Здесь plainTextEdit - имя вашего Plain Text Edit на форме

}

MyTests::~MyTests()
{
    delete ui;
}

class StdoutRedirector : public std::basic_streambuf<char> {
public:
    explicit StdoutRedirector(QPlainTextEdit *textEdit)
        : textEdit(textEdit) {}

protected:
    virtual int_type overflow(int_type c) override {
        if (c != traits_type::eof()) {
            QChar ch = c;
            textEdit->insertPlainText(ch);
        }
        return c;
    }

    virtual std::streamsize xsputn(const char *s, std::streamsize n) override {
        QString str(s, static_cast<int>(n));
        textEdit->insertPlainText(str);
        return n;
    }

private:
    QPlainTextEdit *textEdit;
};

#include <functional>
#include <Qt>
#include "QMessageBox"
#include "QString"
#include "QStringRef"
#include "QRegExp"
#include "QValidator"
#include "QVector"
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "spaceroperation.h"
#include "sumoperation.h"
#include "subtractoperation.h"
#include "multiplyoperation.h"
#include "divideoperation.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QRegExp validInput("(\\d+\\h002E?\\d*\\s?)+");
    QRegExpValidator validator(validInput, this);
    ui->inputFirst->setValidator(&validator);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearInput()
{
    ui -> inputFirst -> clear();
}

/*bool MainWindow::inputIsValid(QString input)
{
    QRegExp wrongInput("[^\\d\\s\\x002E]");
    if (input.contains(wrongInput))
    {
        QMessageBox::information(0, "Ошибка", "Введен неверный символ!");
        return false;
    }
    return true;
}
*/


void MainWindow::readOperand()
{
    this -> operand = ui -> inputFirst -> text().toDouble();
    this -> values.append(this -> operand);
    this -> clearInput();
}

void MainWindow::setOperation(std::function<double(QVector<double>)> operation)
{
    this -> opFunc = operation;
}

void MainWindow::checkOperandAvailability()
{
    if (ui -> inputFirst -> text().isEmpty())
    {
        return;
    }
    else
    {
        readOperand();
    }
}

void MainWindow::checkLastOperation()
{
    if (!(this -> opFunc))
    {
        return;
    }
    else
    {
        this -> values.first() = opFunc(values);
        this -> values.removeLast();
    }
}

void MainWindow::on_plusButton_clicked()
{
    checkOperandAvailability();
    checkLastOperation();
    setOperation(&SumOperation);
}

void MainWindow::on_minusButton_clicked()
{
    checkOperandAvailability();
    checkLastOperation();
    setOperation(&SubtractOperation);
}

void MainWindow::on_multiplyButton_clicked()
{
    checkOperandAvailability();
    checkLastOperation();
    setOperation(&MultiplyOperation);
}

void MainWindow::on_divideButton_clicked()
{
    checkOperandAvailability();
    checkLastOperation();
    setOperation(&DivideOperation);
}

void MainWindow::on_inputFirst_inputRejected()
{
    QMessageBox::information(0, "Ошибка", "Некорректный ввод данных!");
    clearInput();
}

void MainWindow::on_equalsButton_clicked()
{
    if (this ->opFunc == nullptr)
    {
        return;
    }
    else
    {
        checkOperandAvailability();
        this -> result = opFunc(this -> values);
        QString tmp;
        tmp.setNum(result);
        ui -> inputFirst -> setText(tmp);
        this -> values.clear();
        opFunc = nullptr;

    }

}

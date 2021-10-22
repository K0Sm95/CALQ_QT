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
    validator.setNotation(QDoubleValidator::StandardNotation);
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
        while (this -> values.length() > 1)
        {
            this -> values.first() = opFunc(values);
            this -> values.removeLast();
        }
    }

}

void MainWindow::printIntermediateResult()
{
    QString tmp;
    tmp.setNum(values.first());
    ui -> intermediateResult -> setText(tmp);
}

void MainWindow::on_plusButton_clicked()
{
    checkOperandAvailability();
    checkLastOperation();
    printIntermediateResult();
    setOperation(&SumOperation);
    ui -> operatorLabel -> setText("+");
}

void MainWindow::on_minusButton_clicked()
{
    checkOperandAvailability();
    checkLastOperation();
    printIntermediateResult();
    setOperation(&SubtractOperation);
    ui -> operatorLabel -> setText("-");
}

void MainWindow::on_multiplyButton_clicked()
{
    checkOperandAvailability();
    checkLastOperation();
    printIntermediateResult();
    setOperation(&MultiplyOperation);
    ui -> operatorLabel -> setText("x");
}

void MainWindow::on_divideButton_clicked()
{
    checkOperandAvailability();
    checkLastOperation();
    printIntermediateResult();
    setOperation(&DivideOperation);
    ui -> operatorLabel -> setText("/");
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
        while (this -> values.length() >= 1)
        {
            this -> result = opFunc(this -> values);
            QString tmp;
            tmp.setNum(result);
            ui -> output -> setText(tmp);
            ui -> intermediateResult ->setText("Промежут.");
            ui -> operatorLabel ->clear();
            this -> values.clear();
            opFunc = nullptr;

        }
    }
}

void MainWindow::on_inputFirst_inputRejected()
{
    QMessageBox::information(0, "Ошибка", "Некорректный ввод данных!");
    clearInput();
}

void MainWindow::on_inputFirst_editingFinished()
{
    ui -> output -> clear();
}

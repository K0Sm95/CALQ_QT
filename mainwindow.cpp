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
#include "sqrtoperation.h"


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
    if (ui -> inputFirst -> text().isEmpty())
    {
        return;
    }
    else
    {
        this -> operand = ui -> inputFirst -> text().toDouble();
        this -> values.append(this -> operand);
        this -> clearInput();
    }
}

void MainWindow::handleLastOperation()
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

void MainWindow::OpButtonClickRoutine(std::function<double(QVector<double>)> operation, QString sign)
{
    ui -> inputFirst ->setFocus();
    readOperand();
    if (!values.isEmpty())
    {
        handleLastOperation();
        printIntermediateResult();
        this -> opFunc = operation;
        ui -> operatorLabel -> setText(sign);
    }
    else
    {
        ui -> inputFirst ->setFocus();
    }
}

void MainWindow::on_plusButton_clicked()
{
    OpButtonClickRoutine(&SumOperation, "+");
}

void MainWindow::on_minusButton_clicked()
{
    OpButtonClickRoutine(&SubtractOperation, "-");
}

void MainWindow::on_multiplyButton_clicked()
{
    OpButtonClickRoutine(&MultiplyOperation, "x");
}

void MainWindow::on_divideButton_clicked()
{
    OpButtonClickRoutine(&DivideOperation, "/");
}

void MainWindow::on_equalsButton_clicked()
{
    if (this ->opFunc == nullptr)
    {
        return;
    }
    else
    {
        readOperand();
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

void MainWindow::on_sqrtButton_clicked()
{

}

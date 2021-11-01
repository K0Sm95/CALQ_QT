#include <functional>
#include <Qt>
#include "QWidget"
#include "QLocale"
#include "QMessageBox"
#include "QString"
#include "QStringRef"
#include "QRegExp"
#include "QValidator"
#include "QVector"
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "binaryoperations.h"
#include "unaryoperations.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui -> setupUi(this);
    ui -> output -> setReadOnly(true);
    ui -> input ->setClearButtonEnabled(true);

    QLocale C(QLocale::C);
    C.setNumberOptions(QLocale::RejectGroupSeparator);
    validator.setLocale(C);
    validator.setNotation(QDoubleValidator::StandardNotation);
    ui -> input->setValidator(&validator);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::printNumber(double value, QLineEdit* widget)
{
    QString tmp;
    tmp.setNum(value);
    widget -> setText(tmp);
}

void MainWindow::printNumber(double value, QLabel* widget)
{
    QString tmp;
    tmp.setNum(value);
    widget -> setText(tmp);
}

void MainWindow::clearInput()
{
    ui -> input -> clear();
}

void MainWindow::readOperand()
{
    if (ui -> input -> text().isEmpty())
    {
        return;
    }
    else
    {
        operand = ui -> input -> text().toDouble();
        values.append(operand);
        clearInput();
    }
}

void MainWindow::handleLastOperation()
{
    if (!binaryFunc)
    {
        return;
    }
    else
    {
        while (values.length() > 1)
        {
            values.first() = binaryFunc(values);
            values.removeLast();
        }
    }
}

void MainWindow::BinaryOpButtonClickRoutine(BinaryOperation operation, QChar sign)
{
    ui -> input ->setFocus();
    readOperand();
    if (!values.isEmpty())
    {
        handleLastOperation();
        printNumber(values.first(), ui -> intermediateResult);
        binaryFunc = operation;
        ui -> operatorLabel -> setText(sign);
    }
    else
    {
        ui -> input ->setFocus();
    }
}

void MainWindow::UnaryOpButtonClickRoutine(UnaryOperation operation)
{
    unaryFunc = operation;
    if (ui -> input -> text().isEmpty())
    {
        if (values.length() > 0)
        {
            values.first() = unaryFunc(values.first());
            printNumber(values.first(), ui -> intermediateResult);
        }
    }
    else
    {
        operand = ui -> input -> text().toDouble();
        operand = unaryFunc(operand);
        printNumber(operand, ui -> input);
    }
    ui -> input ->setFocus();
}

void MainWindow::on_plusButton_clicked()
{
    BinaryOpButtonClickRoutine(&sumOperation, '+');
}

void MainWindow::on_minusButton_clicked()
{
    BinaryOpButtonClickRoutine(&subtractOperation, '-');
}

void MainWindow::on_multiplyButton_clicked()
{
    BinaryOpButtonClickRoutine(&multiplyOperation, 'x');
}

void MainWindow::on_divideButton_clicked()
{
    BinaryOpButtonClickRoutine(&divideOperation, '/');
}

void MainWindow::on_sqrtButton_clicked()
{
    UnaryOpButtonClickRoutine(&sqrtOperation);
}

void MainWindow::on_squareButton_clicked()
{
    UnaryOpButtonClickRoutine(&squareOperation);
}

void MainWindow::on_absButton_clicked()
{
    UnaryOpButtonClickRoutine(&absOperation);
}

void MainWindow::on_sinButton_clicked()
{
    UnaryOpButtonClickRoutine(&sinOperation);
}


void MainWindow::on_cosButton_clicked()
{
    UnaryOpButtonClickRoutine(&cosOperation);
}


void MainWindow::on_equalsButton_clicked()
{
    double result;
    if (binaryFunc == nullptr)
    {
        result = ui -> input ->text().toDouble();
    }
    else
    {
        readOperand();
        if (values.length() > 0)
        {
            result = binaryFunc(values);
        }
    }
    printNumber(result, ui -> output);
    ui -> intermediateResult ->setText("Промежут.");
    ui -> input -> clear();
    ui -> operatorLabel ->clear();
    values.clear();
    binaryFunc = nullptr;
}

void MainWindow::on_input_inputRejected()
{
    QMessageBox::information(0, "Ошибка", "Некорректный ввод данных!");
    clearInput();
}

void MainWindow::on_input_editingFinished()
{
    ui -> output -> clear();
}


#include <functional>
#include <Qt>
#include "QMessageBox"
#include "QString"
#include "QStringRef"
#include "QStringList"
#include "QRegExp"
#include "QValidator"
#include "QVector"
#include "mainwindow.h"
#include "./ui_mainwindow.h"
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
void MainWindow::calculate(std::function<double(QVector<double>)> func)
{
    QVector<double> values;
    QString input = ui -> inputFirst -> text();
    QStringList sepInput = input.split(QLatin1Char(' '));
    for (int i = 0; i < sepInput.size(); ++i)
    {
        QString number = sepInput[i];
        values.append(number.toDouble());
    }
    double result = func(values);
    QString tmp;
    tmp.setNum(result);
    ui -> inputFirst -> setText(tmp);
}

void MainWindow::on_plusButton_clicked()
{
    calculate(&SumOperation);
}

void MainWindow::on_minusButton_clicked()
{
    calculate(&SubtractOperation);
}

void MainWindow::on_multiplyButton_clicked()
{
    calculate(&MultiplyOperation);
}


void MainWindow::on_divideButton_clicked()
{
    calculate(&DivideOperation);
}

void MainWindow::on_inputFirst_inputRejected()
{
    QMessageBox::information(0, "Ошибка", "Некорректный ввод данных!");
    clearInput();
}

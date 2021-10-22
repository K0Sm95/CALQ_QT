#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <functional>
#include <QMainWindow>
#include "QVector"
#include "QDoubleValidator"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_plusButton_clicked();

    void on_minusButton_clicked();

    void on_multiplyButton_clicked();

    void on_divideButton_clicked();

    void on_inputFirst_inputRejected();

    void on_equalsButton_clicked();

    void on_inputFirst_editingFinished();

private:
    Ui::MainWindow *ui;

    QDoubleValidator validator;

    double operand, result;

    QVector<double> values;

    std::function<double(QVector<double>)> opFunc;

    void readOperand();

    void checkOperandAvailability();

    void setOperation(std::function<double(QVector<double>)> operation);

    void checkLastOperation();

    void printIntermediateResult();

    void clearInput();

};
#endif // MAINWINDOW_H

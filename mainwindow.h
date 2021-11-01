#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <functional>
#include <QMainWindow>
#include "QVector"
#include "QDoubleValidator"
#include "QLineEdit"
#include "QLabel"

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

    void on_input_inputRejected();

    void on_equalsButton_clicked();

    void on_input_editingFinished();

    void on_sqrtButton_clicked();

    void on_squareButton_clicked();

    void on_absButton_clicked();

    void on_sinButton_clicked();

    void on_cosButton_clicked();

private:
    typedef std::function<double(QVector<double>)> BinaryOperation;

    typedef std::function<double(double)> UnaryOperation;

    void printNumber(double value, QLineEdit *widget);

    void printNumber(double value, QLabel *widget);

    Ui::MainWindow *ui;

    QDoubleValidator validator;

    double operand;

    bool isLastOpUnary;

    QVector<double> values;

    BinaryOperation binaryFunc;

    UnaryOperation unaryFunc;

    void readOperand();

    void handleLastOperation();

    void printIntermediateResult();

    void clearInput();

    void BinaryOpButtonClickRoutine(BinaryOperation operation, QChar sign);

    void UnaryOpButtonClickRoutine(UnaryOperation operation);

};
#endif // MAINWINDOW_H

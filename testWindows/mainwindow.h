#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


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
    void digits_numbers();



    void unaryOperations();
    void double_operation();
    void reverse();
    void dot();

    void equal();

    void clear();
    void clear_all_label();

    void ERROR();
private:
    Ui::MainWindow *ui;

    QString m_pending_operation;
    bool calculate(double operand, const QString& operation);

    QString m_radical_sign = QChar(0x221A);
    QString m_squere_sign = "х^2";
    QString m_raciprocal_sign = "1/x";

    QString m_plus_sign = "+";
    QString m_minus_sign = "-";
    QString m_multiply_sign = "*";
    QString m_dot_sign = ".";
    QString m_division_sing = QChar(0x000000F7);





};
#endif // MAINWINDOW_H

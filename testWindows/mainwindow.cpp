#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include <QDebug>
#include <QtMath>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ввод чисел
    connect(ui -> pushButton_0,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui -> pushButton_1,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui -> pushButton_2,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui -> pushButton_3,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui -> pushButton_4,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui -> pushButton_5,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui -> pushButton_6,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui -> pushButton_7,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui -> pushButton_8,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui -> pushButton_9,SIGNAL(clicked()), this, SLOT(digits_numbers()));



    //унарные операции
    connect(ui -> pushButton_radical,SIGNAL(clicked()), this,         SLOT(unaryOperations()));
    connect(ui -> pushButton_square, SIGNAL(clicked()), this,         SLOT(unaryOperations()));
    connect(ui -> pushButton_unar_division, SIGNAL(clicked()), this,  SLOT(unaryOperations()));

    //двойные, обычные операции
    connect(ui -> pushButton_minus,SIGNAL(clicked()),           SLOT(double_operation()));
    connect(ui -> pushButton_pluse,SIGNAL(clicked()), this,     SLOT(double_operation()));
    connect(ui -> pushButton_division,SIGNAL(clicked()), this,  SLOT(double_operation()));
    connect(ui -> pushButton_multiply,SIGNAL(clicked()), this,  SLOT(double_operation()));


    connect(ui -> pushButton_reverse,SIGNAL(clicked()), this, SLOT(reverse()));
    connect(ui -> pushButton_dot,SIGNAL(clicked()), this, SLOT(dot()));

    connect(ui -> pushButton_equally,SIGNAL(clicked()), this, SLOT(equal()));


    connect(ui -> pushButton_clear,SIGNAL(clicked()), this, SLOT(clear()));
    connect(ui -> pushButton_clear_all, SIGNAL(clicked()), this, SLOT(clear_all_label()));




}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::digits_numbers()
{

    QPushButton* button = dynamic_cast<QPushButton*>( sender() );
    double number;
    QString new_result;



    number = (ui -> label_result -> text() + button -> text()).toDouble();

    new_result = QString::number(number);

    ui -> label_result -> setText(new_result);
}

void MainWindow::clear(){
    ui -> label_result->clear();
}

void MainWindow::clear_all_label(){
    ui -> label_result -> clear();
    ui -> label_previous -> clear();
    ui -> label_operation -> clear();
}

void MainWindow::unaryOperations(){
    QPushButton* button = dynamic_cast<QPushButton*>( sender() );
    QString operation = button -> text();


    double result = 0.0;
    double operand = ui -> label_result -> text().toDouble();
    qDebug()<< operation;
    if(operation == m_radical_sign){
        if(operand < 0.0){
            ERROR();
            return;
        }

        result = std::sqrt(operand);

    }else if(operation == m_squere_sign){

        result = std::pow(operand, 2.0);


    }else if(operation == m_raciprocal_sign){
        if(operand == 0.0){
            ERROR();
            return;
        }
        result = 1.0 / operand;

    }
    ui -> label_operation -> setText(operation);
    ui -> label_result -> setText(QString::number(result));

}

void MainWindow::dot(){
    if(!ui -> label_result -> text().contains('.')){
        ui -> label_result -> setText(ui -> label_result -> text() + '.');
    }
}

void MainWindow::equal(){
    double operand = ui -> label_result -> text().toDouble();
    if(!m_pending_operation.isEmpty()){
            if(!calculate(operand, m_pending_operation)){
                ERROR();
                return;
            }
            m_pending_operation.clear();
         }

    ui -> label_result->setText(ui -> label_previous -> text());
    ui -> label_previous ->clear();
    ui -> label_operation -> clear();
}

void MainWindow::double_operation(){
    QPushButton* button = dynamic_cast<QPushButton*>( sender() );
    QString operation = button -> text();

    double operand = ui -> label_result -> text().toDouble();

    if(ui -> label_result ->text() == '0')
        return;

    ui -> label_operation -> setText(operation);

    if(ui -> label_result -> text() == "")
        return;

     ui -> label_result -> clear();

     if(!m_pending_operation.isEmpty()){
        if(!calculate(operand, m_pending_operation)){
            ERROR();
            return;
        }
        m_pending_operation.clear();
     }else {
         ui -> label_previous -> setText(QString::number(operand));
     }
     m_pending_operation = operation;
}


void MainWindow::reverse()
{
    QPushButton* button = dynamic_cast<QPushButton*>( sender() );
    double number;
    QString new_result;


        if(button -> text() == "+/-")
        {

            number = ui -> label_result -> text().toDouble();

            number = number * -1;

            new_result = QString::number(number);
            ui -> label_result -> setText(new_result);
        }



}
void MainWindow::ERROR()
{
    ui -> label_previous ->clear();
    ui -> label_operation -> clear();
    ui -> label_result -> setText("ERROR");
}

bool MainWindow::calculate(double operand, const QString &operation)
{
        double temp_total = ui -> label_previous -> text().toDouble();

        if(operation == m_plus_sign){
            temp_total += operand;
        }else if(operation == m_minus_sign){
            temp_total -= operand;
        }else if(operation == m_multiply_sign){
            temp_total *= operand;
        }else if(operation == m_division_sing){
            if(operand == 0.0){
                return false;
            }
            temp_total /= operand;
        }

        ui -> label_previous -> setText(QString::number(temp_total));
        return true;

}









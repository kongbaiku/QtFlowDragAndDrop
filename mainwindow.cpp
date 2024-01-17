#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->wContainer->appendWidget(new QLabel("any text"));
    ui->wContainer->appendWidget(new QPushButton("any button"));
    ui->wContainer->appendWidget(new QSpinBox);
    ui->wContainer->appendWidget(new QDateTimeEdit);
    ui->wContainer->appendWidget(new QTextEdit("any big text"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

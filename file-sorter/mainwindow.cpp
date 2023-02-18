#include "mainwindow.hpp"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_outputDestination_pressed()
{
    mOutputDestination = QFileDialog::getExistingDirectory(this, "Open Output Destination");
    ui->lineEdit->setText(mOutputDestination);
}


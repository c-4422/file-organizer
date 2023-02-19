#include "mainwindow.hpp"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString str("test");
    ui->pictureFileExtList->
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pictureDestination_pressed()
{
    sFileOp.SetOutputDestinantion(QFileDialog::getExistingDirectory(this, "Open Picture Output Destination"));
    ui->pictureDestinationField->setText(sFileOp.GetOutputDestinantion());
}


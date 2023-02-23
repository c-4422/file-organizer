#include "mainwindow.hpp"
#include "./ui_mainwindow.h"
#include <QListWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString str("test");
    for(auto extension : sFileOp.GetPicturesFileExt()) {
        ui->picturExtList->addItem(extension);
    }
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


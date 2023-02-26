#include "mainwindow.hpp"
#include "./ui_mainwindow.h"
#include <QListWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    UpdatePictureFileExtList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UpdatePictureFileExtList() {
  ui->picturExtList->clear();
  for(auto extension : sFileOp.GetPicturesFileExt()) {
      ui->picturExtList->addItem(extension);
  }
}

void MainWindow::on_pictureDestination_pressed()
{
    sFileOp.SetOutputDestinantion(QFileDialog::getExistingDirectory(this, "Open Picture Output Destination"));
    ui->pictureDestinationField->setText(sFileOp.GetOutputDestinantion());
}


void MainWindow::on_addPictureFileExtButton_pressed()
{
    const auto extInput = ui->pictureFileExtEdit->text();
    if (!extInput.isEmpty()) {
      sFileOp.AddFileExt(FileOperation::Category::Picture, extInput);
      UpdatePictureFileExtList();
    }
}


void MainWindow::on_removePictureFileExt_pressed()
{
  sFileOp.RemoveFileExt(FileOperation::Category::Picture, ui->picturExtList->currentIndex().row());
  UpdatePictureFileExtList();
}


void MainWindow::on_isPictureAllFiles_toggled(bool checked)
{
  sFileOp.SetAllFileTypes(FileOperation::Category::Picture, checked);
  ui->picturExtList->setDisabled(checked);
  ui->addPictureFileExtButton->setDisabled(checked);
  ui->removePictureFileExt->setDisabled(checked);
  ui->pictureFileExtEdit->setDisabled(checked);
}


void MainWindow::on_isPictureDateSorted_toggled(bool checked)
{
  sFileOp.SetDateSorted(FileOperation::Category::Picture, checked);
}


void MainWindow::on_isPictureFileComments_toggled(bool checked)
{
  sFileOp.SetFileComment(FileOperation::Category::Picture, checked);
}


void MainWindow::on_pictureInputButton_pressed()
{
  sFileOp.SetOutputDestinantion(QFileDialog::getExistingDirectory(this, "Open Picture Output Destination"));
}


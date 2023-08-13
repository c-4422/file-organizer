/**************************************************************
 * File Organizer Pictures
 *
 * This should only contain UI layer logic for pictures.
 *
 *************************************************************/

#include "../mainwindow.hpp"
#include "../ui_mainwindow.h"
#include <QListWidget>

void MainWindow::UpdatePictureFileExtList() {
  ui->pictureExtList->clear();
  for (auto extension : sFileOp.GetFileExt(FileOperation::Category::Picture)) {
    ui->pictureExtList->addItem(extension);
  }
}

void MainWindow::UpdatePictureInputList() {
  ui->pictureInputPaths->clear();
  for (auto path :
       sFileOp.GetInputDirectories(FileOperation::Category::Picture)) {
    ui->pictureInputPaths->addItem(path.mFolderInput);
  }
}

void MainWindow::on_pictureDestination_pressed() {
  sFileOp.SetOutputDestinantion(FileOperation::Category::Picture,
                                QFileDialog::getExistingDirectory(
                                    this, "Open Picture Output Destination"));
  ui->pictureDestinationField->setText(
      sFileOp.GetOutputDestinantion(FileOperation::Category::Picture));
}

void MainWindow::on_addPictureFileExtButton_pressed() {
  const auto extInput = ui->pictureFileExtEdit->text();
  if (!extInput.isEmpty()) {
    sFileOp.AddFileExt(FileOperation::Category::Picture, extInput);
    UpdatePictureFileExtList();
  }
}

void MainWindow::on_removePictureFileExt_pressed() {
  sFileOp.RemoveFileExt(FileOperation::Category::Picture,
                        ui->pictureExtList->currentIndex().row());
  UpdatePictureFileExtList();
}

void MainWindow::on_isPictureAllFiles_toggled(bool checked) {
  sFileOp.SetAllFileTypes(FileOperation::Category::Picture, checked);
  ui->pictureExtList->setDisabled(checked);
  ui->addPictureFileExtButton->setDisabled(checked);
  ui->removePictureFileExt->setDisabled(checked);
  ui->pictureFileExtEdit->setDisabled(checked);
}

void MainWindow::on_isPictureDateSorted_toggled(bool checked) {
  sFileOp.SetDateSorted(FileOperation::Category::Picture, checked);
}

void MainWindow::on_isPictureFileComments_toggled(bool checked) {
  sFileOp.SetFileComment(FileOperation::Category::Picture, checked);
}

void MainWindow::on_pictureInputButton_pressed() {
  sFileOp.AddFileInputPath(FileOperation::Category::Picture,
                           QFileDialog::getExistingDirectory(
                               this, "Open Picture Output Destination"));
  UpdatePictureInputList();
}

void MainWindow::on_pictureInputRemove_pressed() {
  sFileOp.RemoveFileInputPath(FileOperation::Category::Picture,
                              ui->pictureInputPaths->currentIndex().row());
  UpdatePictureInputList();
}

void MainWindow::on_isPictureMultiDestination_toggled(bool checked) {
  ui->pictureOutputDestinationList->setDisabled(!checked);
  ui->addPictureDestination->setDisabled(!checked);
  ui->removePictureDestination->setDisabled(!checked);
  sFileOp.SetMultiDestination(FileOperation::Category::Picture,
                              ui->pictureInputPaths->currentIndex().row(),
                              checked);
}

void MainWindow::UpdatePictureOutputList() {
  ui->pictureInputPaths->clear();
  for (auto path : sFileOp.GetOutputDirectories(
           FileOperation::Category::Picture,
           ui->pictureOutputDestinationList->currentIndex().row())) {
    ui->pictureInputPaths->addItem(path);
  }
}

void MainWindow::on_addPictureDestination_pressed() {
  // Specific destination per input path
  sFileOp.AddSpecificOuputPath(
      FileOperation::Category::Picture,
      ui->pictureOutputDestinationList->currentIndex().row(),
      QFileDialog::getExistingDirectory(this,
                                        "Open Picture Output Destination"));
}

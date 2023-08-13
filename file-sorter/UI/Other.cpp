/**************************************************************
 * File Organizer Others
 *
 * This should only contain UI layer logic for other files.
 *
 *************************************************************/

#include "../mainwindow.hpp"
#include "../ui_mainwindow.h"
#include <QListWidget>

void MainWindow::UpdateOtherFileExtList() {
  ui->otherExtList->clear();
  for (auto extension : sFileOp.GetFileExt(FileOperation::Category::Other)) {
    ui->otherExtList->addItem(extension);
  }
}

void MainWindow::UpdateOtherInputList() {
  ui->otherInputPaths->clear();
  for (auto path :
       sFileOp.GetInputDirectories(FileOperation::Category::Other)) {
    ui->otherInputPaths->addItem(path.mFolderInput);
  }
}

void MainWindow::on_otherDestination_pressed() {
  sFileOp.SetOutputDestinantion(
      FileOperation::Category::Other,
      QFileDialog::getExistingDirectory(this, "Open Other Output Destination"));
  ui->otherDestinationField->setText(
      sFileOp.GetOutputDestinantion(FileOperation::Category::Other));
}

void MainWindow::on_addOtherFileExtButton_pressed() {
  const auto extInput = ui->otherFileExtEdit->text();
  if (!extInput.isEmpty()) {
    sFileOp.AddFileExt(FileOperation::Category::Other, extInput);
    UpdateOtherFileExtList();
  }
}

void MainWindow::on_removeOtherFileExt_pressed() {
  sFileOp.RemoveFileExt(FileOperation::Category::Other,
                        ui->otherExtList->currentIndex().row());
  UpdateOtherFileExtList();
}

void MainWindow::on_isOtherAllFiles_toggled(bool checked) {
  sFileOp.SetAllFileTypes(FileOperation::Category::Other, checked);
  ui->otherExtList->setDisabled(checked);
  ui->addOtherFileExtButton->setDisabled(checked);
  ui->removeOtherFileExt->setDisabled(checked);
  ui->otherFileExtEdit->setDisabled(checked);
}

void MainWindow::on_isOtherDateSorted_toggled(bool checked) {
  sFileOp.SetDateSorted(FileOperation::Category::Other, checked);
}

void MainWindow::on_isOtherFileComments_toggled(bool checked) {
  sFileOp.SetFileComment(FileOperation::Category::Other, checked);
}

void MainWindow::on_otherInputButton_pressed() {
  sFileOp.AddFileInputPath(
      FileOperation::Category::Other,
      QFileDialog::getExistingDirectory(this, "Open Other Output Destination"));
  UpdateOtherInputList();
}

void MainWindow::on_otherInputRemove_pressed() {
  sFileOp.RemoveFileInputPath(FileOperation::Category::Other,
                              ui->otherInputPaths->currentIndex().row());
  UpdateOtherInputList();
}

void MainWindow::on_isOtherMultiDestination_toggled(bool checked) {
  ui->otherOutputDestinationList->setVisible(!checked);
  ui->addOtherDestination->setVisible(!checked);
  ui->removeOtherDestination->setVisible(!checked);
  sFileOp.SetMultiDestination(FileOperation::Category::Other,
                              ui->otherInputPaths->currentIndex().row(),
                              checked);
}

void MainWindow::UpdateOtherOutputList() {
  ui->otherInputPaths->clear();
  for (auto path : sFileOp.GetOutputDirectories(
           FileOperation::Category::Other,
           ui->otherOutputDestinationList->currentIndex().row())) {
    ui->otherInputPaths->addItem(path);
  }
}

void MainWindow::on_addOtherDestination_pressed() {
  // Specific destination per input path
  sFileOp.AddSpecificOuputPath(
      FileOperation::Category::Other,
      ui->otherOutputDestinationList->currentIndex().row(),
      QFileDialog::getExistingDirectory(this,
                                        "Open Other Files Output Destination"));
}
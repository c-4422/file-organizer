/**************************************************************
 * File Organizer Videos
 *
 * This should only contain UI layer logic for videos.
 *
 *************************************************************/

#include "../mainwindow.hpp"
#include "../ui_mainwindow.h"
#include <QListWidget>

void MainWindow::UpdateVideoFileExtList() {
  ui->videoExtList->clear();
  for (auto extension : sFileOp.GetFileExt(FileOperation::Category::Video)) {
    ui->videoExtList->addItem(extension);
  }
}

void MainWindow::UpdateVideoInputList() {
  ui->videoInputPaths->clear();
  for (auto path :
       sFileOp.GetInputDirectories(FileOperation::Category::Video)) {
    ui->videoInputPaths->addItem(path.mFolderInput);
  }
}

void MainWindow::on_videoDestination_pressed() {
  sFileOp.SetOutputDestinantion(
      FileOperation::Category::Video,
      QFileDialog::getExistingDirectory(this, "Open Video Output Destination"));
  ui->videoDestinationField->setText(
      sFileOp.GetOutputDestinantion(FileOperation::Category::Video));
}

void MainWindow::on_addVideoFileExtButton_pressed() {
  const auto extInput = ui->videoFileExtEdit->text();
  if (!extInput.isEmpty()) {
    sFileOp.AddFileExt(FileOperation::Category::Video, extInput);
    UpdateVideoFileExtList();
  }
}

void MainWindow::on_removeVideoFileExt_pressed() {
  sFileOp.RemoveFileExt(FileOperation::Category::Video,
                        ui->videoExtList->currentIndex().row());
  UpdateVideoFileExtList();
}

void MainWindow::on_isVideoAllFiles_toggled(bool checked) {
  sFileOp.SetAllFileTypes(FileOperation::Category::Video, checked);
  ui->videoExtList->setDisabled(checked);
  ui->addVideoFileExtButton->setDisabled(checked);
  ui->removeVideoFileExt->setDisabled(checked);
  ui->videoFileExtEdit->setDisabled(checked);
}

void MainWindow::on_isVideoDateSorted_toggled(bool checked) {
  sFileOp.SetDateSorted(FileOperation::Category::Video, checked);
}

void MainWindow::on_isVideoFileComments_toggled(bool checked) {
  sFileOp.SetFileComment(FileOperation::Category::Video, checked);
}

void MainWindow::on_videoInputButton_pressed() {
  sFileOp.AddFileInputPath(
      FileOperation::Category::Video,
      QFileDialog::getExistingDirectory(this, "Open Video Output Destination"));
  UpdateVideoInputList();
}

void MainWindow::on_videoInputRemove_pressed() {
  sFileOp.RemoveFileInputPath(FileOperation::Category::Video,
                              ui->videoInputPaths->currentIndex().row());
  UpdateVideoInputList();
}

void MainWindow::on_isVideoMultiDestination_toggled(bool checked) {
  ui->videoOutputDestinationList->setVisible(!checked);
  ui->addVideoDestination->setVisible(!checked);
  ui->removeVideoDestination->setVisible(!checked);
  sFileOp.SetMultiDestination(FileOperation::Category::Video,
                              ui->videoInputPaths->currentIndex().row(),
                              checked);
}

void MainWindow::UpdateVideoOutputList() {
  ui->videoInputPaths->clear();
  for (auto path : sFileOp.GetOutputDirectories(
           FileOperation::Category::Video,
           ui->videoOutputDestinationList->currentIndex().row())) {
    ui->videoInputPaths->addItem(path);
  }
}

void MainWindow::on_addVideoDestination_pressed() {
  // Specific destination per input path
  sFileOp.AddSpecificOuputPath(
      FileOperation::Category::Video,
      ui->videoOutputDestinationList->currentIndex().row(),
      QFileDialog::getExistingDirectory(this, "Open Video Output Destination"));
}

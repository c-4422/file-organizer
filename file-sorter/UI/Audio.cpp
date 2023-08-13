/**************************************************************
 * File Organizer Audios
 *
 * This should only contain UI layer logic for audio.
 *
 *************************************************************/

#include "../mainwindow.hpp"
#include "../ui_mainwindow.h"
#include <QListWidget>

void MainWindow::UpdateAudioFileExtList() {
  ui->audioExtList->clear();
  for (auto extension : sFileOp.GetFileExt(FileOperation::Category::Audio)) {
    ui->audioExtList->addItem(extension);
  }
}

void MainWindow::UpdateAudioInputList() {
  ui->audioInputPaths->clear();
  for (auto path :
       sFileOp.GetInputDirectories(FileOperation::Category::Audio)) {
    ui->audioInputPaths->addItem(path.mFolderInput);
  }
}

void MainWindow::on_audioDestination_pressed() {
  sFileOp.SetOutputDestinantion(
      FileOperation::Category::Audio,
      QFileDialog::getExistingDirectory(this, "Open Audio Output Destination"));
  ui->audioDestinationField->setText(
      sFileOp.GetOutputDestinantion(FileOperation::Category::Audio));
}

void MainWindow::on_addAudioFileExtButton_pressed() {
  const auto extInput = ui->audioFileExtEdit->text();
  if (!extInput.isEmpty()) {
    sFileOp.AddFileExt(FileOperation::Category::Audio, extInput);
    UpdateAudioFileExtList();
  }
}

void MainWindow::on_removeAudioFileExt_pressed() {
  sFileOp.RemoveFileExt(FileOperation::Category::Audio,
                        ui->audioExtList->currentIndex().row());
  UpdateAudioFileExtList();
}

void MainWindow::on_isAudioAllFiles_toggled(bool checked) {
  sFileOp.SetAllFileTypes(FileOperation::Category::Audio, checked);
  ui->audioExtList->setDisabled(checked);
  ui->addAudioFileExtButton->setDisabled(checked);
  ui->removeAudioFileExt->setDisabled(checked);
  ui->audioFileExtEdit->setDisabled(checked);
}

void MainWindow::on_isAudioDateSorted_toggled(bool checked) {
  sFileOp.SetDateSorted(FileOperation::Category::Audio, checked);
}

void MainWindow::on_isAudioFileComments_toggled(bool checked) {
  sFileOp.SetFileComment(FileOperation::Category::Audio, checked);
}

void MainWindow::on_audioInputButton_pressed() {
  sFileOp.AddFileInputPath(
      FileOperation::Category::Audio,
      QFileDialog::getExistingDirectory(this, "Open Audio Output Destination"));
  UpdateAudioInputList();
}

void MainWindow::on_audioInputRemove_pressed() {
  sFileOp.RemoveFileInputPath(FileOperation::Category::Audio,
                              ui->audioInputPaths->currentIndex().row());
  UpdateAudioOutputList();
}

void MainWindow::on_isAudioMultiDestination_toggled(bool checked) {
  ui->audioOutputDestinationList->setVisible(!checked);
  ui->addAudioDestination->setVisible(!checked);
  ui->removeAudioDestination->setVisible(!checked);
  sFileOp.SetMultiDestination(FileOperation::Category::Audio,
                              ui->audioInputPaths->currentIndex().row(),
                              checked);
}

void MainWindow::UpdateAudioOutputList() {
  ui->audioInputPaths->clear();
  for (auto path : sFileOp.GetOutputDirectories(
           FileOperation::Category::Audio,
           ui->audioOutputDestinationList->currentIndex().row())) {
    ui->audioInputPaths->addItem(path);
  }
}

void MainWindow::on_addAudioDestination_pressed() {
  // Specific destination per input path
  sFileOp.AddSpecificOuputPath(
      FileOperation::Category::Audio,
      ui->audioOutputDestinationList->currentIndex().row(),
      QFileDialog::getExistingDirectory(this, "Open Audio Output Destination"));
}
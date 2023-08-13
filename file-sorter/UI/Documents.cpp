/**************************************************************
 * File Organizer Documents
 *
 * This should only contain UI layer logic for documents.
 *
 *************************************************************/

#include "../mainwindow.hpp"
#include "../ui_mainwindow.h"
#include <QListWidget>

void MainWindow::UpdateDocumentFileExtList() {
  ui->documentExtList->clear();
  for (auto extension : sFileOp.GetFileExt(FileOperation::Category::Document)) {
    ui->documentExtList->addItem(extension);
  }
}

void MainWindow::UpdateDocumentInputList() {
  ui->documentInputPaths->clear();
  for (auto path :
       sFileOp.GetInputDirectories(FileOperation::Category::Document)) {
    ui->documentInputPaths->addItem(path.mFolderInput);
  }
}

void MainWindow::on_documentDestination_pressed() {
  sFileOp.SetOutputDestinantion(FileOperation::Category::Document,
                                QFileDialog::getExistingDirectory(
                                    this, "Open Document Output Destination"));
  ui->documentDestinationField->setText(
      sFileOp.GetOutputDestinantion(FileOperation::Category::Document));
}

void MainWindow::on_addDocumentFileExtButton_pressed() {
  const auto extInput = ui->documentFileExtEdit->text();
  if (!extInput.isEmpty()) {
    sFileOp.AddFileExt(FileOperation::Category::Document, extInput);
    UpdateDocumentFileExtList();
  }
}

void MainWindow::on_removeDocumentFileExt_pressed() {
  sFileOp.RemoveFileExt(FileOperation::Category::Document,
                        ui->documentExtList->currentIndex().row());
  UpdateDocumentFileExtList();
}

void MainWindow::on_isDocumentAllFiles_toggled(bool checked) {
  sFileOp.SetAllFileTypes(FileOperation::Category::Document, checked);
  ui->documentExtList->setDisabled(checked);
  ui->addDocumentFileExtButton->setDisabled(checked);
  ui->removeDocumentFileExt->setDisabled(checked);
  ui->documentFileExtEdit->setDisabled(checked);
}

void MainWindow::on_isDocumentDateSorted_toggled(bool checked) {
  sFileOp.SetDateSorted(FileOperation::Category::Document, checked);
}

void MainWindow::on_isDocumentFileComments_toggled(bool checked) {
  sFileOp.SetFileComment(FileOperation::Category::Document, checked);
}

void MainWindow::on_documentInputButton_pressed() {
  sFileOp.AddFileInputPath(FileOperation::Category::Document,
                           QFileDialog::getExistingDirectory(
                               this, "Open Document Output Destination"));
  UpdateDocumentInputList();
}

void MainWindow::on_documentInputRemove_pressed() {
  sFileOp.RemoveFileInputPath(FileOperation::Category::Document,
                              ui->pictureInputPaths->currentIndex().row());
  UpdateDocumentInputList();
}

void MainWindow::on_isDocumentMultiDestination_toggled(bool checked) {
  ui->documentOutputDestinationList->setVisible(!checked);
  ui->addDocumentDestination->setVisible(!checked);
  ui->removeDocumentDestination->setVisible(!checked);
  sFileOp.SetMultiDestination(FileOperation::Category::Document,
                              ui->documentInputPaths->currentIndex().row(),
                              checked);
}

void MainWindow::UpdateDocumentOutputList() {
  ui->documentInputPaths->clear();
  for (auto path : sFileOp.GetOutputDirectories(
           FileOperation::Category::Document,
           ui->documentOutputDestinationList->currentIndex().row())) {
    ui->documentInputPaths->addItem(path);
  }
}

void MainWindow::on_addDocumentDestination_pressed() {
  // Specific destination per input path
  sFileOp.AddSpecificOuputPath(
      FileOperation::Category::Document,
      ui->documentOutputDestinationList->currentIndex().row(),
      QFileDialog::getExistingDirectory(this,
                                        "Open Document Output Destination"));
  // Update
}

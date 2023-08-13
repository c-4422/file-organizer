/**************************************************************
 * File Organizer Main Window
 *
 * This should only contain UI layer logic. UI methods for
 * the file categories have been split into seperate files,
 * pictures, video, documents etc.
 *
 *************************************************************/

#include "mainwindow.hpp"
#include "./ui_mainwindow.h"
#include <QListWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  UpdatePictureFileExtList();
  UpdatePictureInputList();
  on_isPictureMultiDestination_toggled(false);
  UpdateAudioFileExtList();
  UpdateAudioInputList();
  on_isAudioMultiDestination_toggled(false);
  UpdateDocumentFileExtList();
  UpdateDocumentInputList();
  on_isDocumentMultiDestination_toggled(false);
  UpdateOtherFileExtList();
  UpdateOtherInputList();
  on_isOtherMultiDestination_toggled(false);
  UpdateVideoFileExtList();
  UpdateVideoInputList();
  on_isVideoMultiDestination_toggled(false);
}

void MainWindow::on_clearUnifiedOutput_pressed() {
  sFileOp.SetOutputDestinantion(QString{});
  ui->unifiedOutputField->setText(QString{});
}

void MainWindow::on_outputDestination_pressed() {
  sFileOp.SetOutputDestinantion(
      QFileDialog::getExistingDirectory(this, "Open Output Destination"));
  ui->unifiedOutputField->setText(sFileOp.GetOutputDestinantion());
}

MainWindow::~MainWindow() { delete ui; }

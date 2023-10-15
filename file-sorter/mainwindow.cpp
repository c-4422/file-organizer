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
#include <QStringBuilder>

static FileOperation::Category TabIndexToCategory(const int aIndex) {
  switch (aIndex) {
  case 0:
    return FileOperation::Category::Picture;
  case 1:
    return FileOperation::Category::Video;
  case 2:
    return FileOperation::Category::Document;
  case 3:
    return FileOperation::Category::Audio;
  case 4:
    return FileOperation::Category::Other;
  default:
    return FileOperation::Category::Invalid;
  }
}

static QString GetCategoryString(const FileOperation::Category aCategory) {
  switch (aCategory) {
  case FileOperation::Category::Picture:
    return "Picture";
  case FileOperation::Category::Video:
    return "Video";
  case FileOperation::Category::Document:
    return "Documents";
  case FileOperation::Category::Audio:
    return "Audio";
  case FileOperation::Category::Other:
    return "Other";
  default:
    return "";
  }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  mTabBar = new QTabBar;
  // Set up tabs
  for (auto category : FileOperation::AllCategories) {
    mTabBar->addTab(GetCategoryString(category));
  }
  ui->tab_layout->layout()->addWidget(mTabBar);
  UpdateInterface();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::UpdateInterface() {
  // TODO: Need ui->tabWidget->currentIndex()
  mCurrentCategory = TabIndexToCategory(0);
  UpdateFileExtensionList();
  UpdateInputList();
  on_IsMultiDestination_toggled(ui->IsMultiDestination->isChecked());
}

void MainWindow::UpdateFileExtensionList() {
  ui->ExtensionList->clear();
  for (auto extension : sFileOp.GetFileExt(mCurrentCategory)) {
    ui->ExtensionList->addItem(extension);
  }
}

void MainWindow::UpdateInputList() {
  ui->InputPaths->clear();
  for (auto path : sFileOp.GetInputDirectories(mCurrentCategory)) {
    ui->InputPaths->addItem(path.mFolderInput);
  }
}

void MainWindow::on_Destination_pressed() {
  QString categoryString = GetCategoryString(mCurrentCategory);
  QStringBuilder openDirectoryString =
      "Open " % categoryString % " Output Destination";
  sFileOp.SetOutputDestinantion(
      mCurrentCategory,
      QFileDialog::getExistingDirectory(this, openDirectoryString));
  ui->DestinationField->setText(
      sFileOp.GetOutputDestinantion(mCurrentCategory));
}

void MainWindow::on_AddFileExtension_pressed() {
  const auto extInput = ui->FileExtensionEdit->text();
  if (!extInput.isEmpty()) {
    sFileOp.AddFileExt(mCurrentCategory, extInput);
    UpdateFileExtensionList();
  }
}

void MainWindow::on_RemoveFileExtension_pressed() {
  sFileOp.RemoveFileExt(mCurrentCategory,
                        ui->ExtensionList->currentIndex().row());
  UpdateFileExtensionList();
}

void MainWindow::on_IsAllFileExtensions_toggled(bool checked) {
  sFileOp.SetAllFileTypes(mCurrentCategory, checked);
  ui->ExtensionList->setDisabled(checked);
  ui->AddFileExtension->setDisabled(checked);
  ui->RemoveFileExtension->setDisabled(checked);
  ui->FileExtensionEdit->setDisabled(checked);
}

void MainWindow::on_IsDateSorted_toggled(bool checked) {
  sFileOp.SetDateSorted(mCurrentCategory, checked);
}

void MainWindow::on_IsFileComments_toggled(bool checked) {
  sFileOp.SetFileComment(mCurrentCategory, checked);
}

void MainWindow::on_AddInputDirectory_pressed() {
  QString categoryString = GetCategoryString(mCurrentCategory);
  QStringBuilder inputDirectoryString =
      "Open " % categoryString % " Input Directory";
  sFileOp.AddFileInputPath(mCurrentCategory, QFileDialog::getExistingDirectory(
                                                 this, inputDirectoryString));
  UpdateInputList();
}

void MainWindow::on_RemoveInputDirectory_pressed() {
  sFileOp.RemoveFileInputPath(mCurrentCategory,
                              ui->InputPaths->currentIndex().row());
  UpdateInputList();
}

void MainWindow::on_IsMultiDestination_toggled(bool checked) {
  ui->OutputDestinationList->setDisabled(!checked);
  ui->AddDestination->setDisabled(!checked);
  ui->RemoveDestination->setDisabled(!checked);
  sFileOp.SetMultiDestination(mCurrentCategory,
                              ui->InputPaths->currentIndex().row(), checked);
}

void MainWindow::UpdateOutputList() {
  ui->InputPaths->clear();
  for (auto path : sFileOp.GetOutputDirectories(
           mCurrentCategory, ui->OutputDestinationList->currentIndex().row())) {
    ui->InputPaths->addItem(path);
  }
}

void MainWindow::on_AddDestination_pressed() {
  // Specific destination per input path
  QString categoryString = GetCategoryString(mCurrentCategory);
  QStringBuilder inputDirectoryString =
      "Open " % categoryString % " Input Destination";
  sFileOp.AddSpecificOuputPath(
      mCurrentCategory, ui->OutputDestinationList->currentIndex().row(),
      QFileDialog::getExistingDirectory(this, inputDirectoryString));
}

void MainWindow::on_InputPaths_currentRowChanged(int currentRow) {
  ui->IsMultiDestination->setDisabled(
      currentRow < sFileOp.GetInputDirectories(mCurrentCategory).size());
}

void MainWindow::on_ClearUnifiedOutput_pressed() {
  sFileOp.SetOutputDestinantion(QString{});
  ui->UnifiedOutputField->setText(QString{});
}

void MainWindow::on_OutputDestination_pressed() {
  sFileOp.SetOutputDestinantion(
      QFileDialog::getExistingDirectory(this, "Open Output Destination"));
  ui->UnifiedOutputField->setText(sFileOp.GetOutputDestinantion());
}

void MainWindow::on_tabWidget_currentChanged(int index) {
  // Get ready for some hokey code...
  // I don't think you can set multiple tabs to a singular layout (or at the
  // very least I can't find anything in the documentation which suggests that).

  // In order to get around this we will delete all of the widgets in the
  // picture tab, reconstruct all of the widgets and push them over into
  // whatever tab is selected changing the file operation category in the
  // process.

  // This allows us to reuse the same layout for every tab without having to
  // actually construct a layout for each of them. This allows us to reuse the
  // widget slots and therefore cuts down on code needed and other headaches.

  // This is where I got the idea from:
  // https://stackoverflow.com/questions/1891961/how-do-you-move-a-widget-from-one-tab-to-another-and-keep-a-layout
  // mCurrentCategory = TabIndexToCategory(index);
  // QLayout *layout = ui->tabWidget->widget(index)->layout();
  // layout->removeWidget(ui->tabWidget->widget(index));
  // delete layout;
  // layout = new QVBoxLayout;
  // layout->addWidget(ui->tabWidget->);
  // ui->tabWidget->widget(index)->setLayout(layout);
}

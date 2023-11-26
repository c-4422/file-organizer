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
  if (aIndex < FileOperation::AllCategories.size()) {
    return *(FileOperation::AllCategories.begin() + aIndex);
  }
  return FileOperation::Category::Invalid;
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
  // Set up tabs
  mTabBar = new QTabBar;
  connect(mTabBar, &QTabBar::currentChanged, [this](int index) {
    mCurrentCategory = TabIndexToCategory(index);
    UpdateInterface();
  });
  for (auto category : FileOperation::AllCategories) {
    mTabBar->addTab(GetCategoryString(category));
  }
  ui->tab_layout->layout()->addWidget(mTabBar);
  UpdateInterface();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::UpdateInterface() {
  UpdateFileExtensionList();
  UpdateInputList();
  UpdateOutputList();
  on_IsMultiDestination_toggled(ui->IsMultiDestination->isChecked());
  ui->IsDateSorted->setChecked(sFileOp.IsDateSort(mCurrentCategory));
  ui->IsFileComments->setChecked(sFileOp.IsFileComment(mCurrentCategory));
  ui->IsAllFileExtensions->setChecked(sFileOp.IsAllFileTypes(mCurrentCategory));
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
  if (auto currentRow = ui->OutputDestinationList->currentIndex().row();
      currentRow < sFileOp.GetInputDirectories(mCurrentCategory).size()) {
    for (auto path :
         sFileOp.GetOutputDirectories(mCurrentCategory, currentRow)) {
      ui->InputPaths->addItem(path);
    }
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
  UpdateOutputList();
}

void MainWindow::on_InputPaths_currentRowChanged(int currentRow) {
  ui->IsMultiDestination->setDisabled(
      sFileOp.IsMultiDestination(mCurrentCategory, currentRow));
  UpdateOutputList();
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

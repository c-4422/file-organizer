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
#include <limits>

static constexpr size_t InvalidVectorIndex = std::numeric_limits<size_t>::max();

static FileOperation::Category TabIndexToCategory(const int aIndex) {
  if (aIndex < FileOperation::AllCategories.size()) {
    return *(FileOperation::AllCategories.begin() + aIndex);
  }
  return FileOperation::Category::Invalid;
}

static size_t ConvertToSizeT(const int aIndex) {
  // Row indexes can be negative when row is invalid, convert to size_t.
  return aIndex >= 0 ? static_cast<size_t>(aIndex) : InvalidVectorIndex;
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
    mTabBar->addTab(FileOperation::GetCategoryString(category));
  }
  ui->tab_layout->layout()->addWidget(mTabBar);
  UpdateInterface();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::UpdateInterface() {
  const size_t inputListRow =
      ConvertToSizeT(ui->InputPaths->currentIndex().row());

  UpdateFileExtensionList();
  UpdateInputList();
  UpdateOutputList();
  on_IsMultiDestination_toggled(ui->IsMultiDestination->isChecked());
  ui->IsDateSorted->setEnabled(
      inputListRow < sFileOp.GetInputDirectories(mCurrentCategory).size());
  ui->IsDateSorted->setChecked(
      sFileOp.IsDateSort(mCurrentCategory, inputListRow));
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
  QString categoryString = FileOperation::GetCategoryString(mCurrentCategory);
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
  sFileOp.SetDateSorted(mCurrentCategory, ui->InputPaths->currentIndex().row(),
                        checked);
}

void MainWindow::on_IsFileComments_toggled(bool checked) {
  sFileOp.SetFileComment(mCurrentCategory, checked);
}

void MainWindow::on_AddInputDirectory_pressed() {
  QString categoryString = FileOperation::GetCategoryString(mCurrentCategory);
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
  ui->OutputDestinationList->clear();

  if (auto *const outputDirectories = sFileOp.GetOutputDirectories(
          mCurrentCategory,
          ConvertToSizeT(ui->InputPaths->currentIndex().row()));
      outputDirectories) {
    for (const auto path : *outputDirectories) {
      ui->OutputDestinationList->addItem(path);
    }
  }
}

void MainWindow::on_AddDestination_pressed() {
  // Specific destination per input path
  QString categoryString = FileOperation::GetCategoryString(mCurrentCategory);
  QStringBuilder inputDirectoryString =
      "Open " % categoryString % " Specific Output Directory";
  sFileOp.AddSpecificOuputPath(
      mCurrentCategory, ConvertToSizeT(ui->InputPaths->currentIndex().row(),
      QFileDialog::getExistingDirectory(this, inputDirectoryString));
  UpdateOutputList();
}

void MainWindow::on_InputPaths_currentRowChanged(int currentRow) {
  const size_t index = ConvertToSizeT(currentRow);
  ui->IsMultiDestination->setDisabled(
      sFileOp.IsMultiDestination(mCurrentCategory, index));
  ui->IsDateSorted->setEnabled(true);
  ui->IsDateSorted->setChecked(sFileOp.IsDateSort(mCurrentCategory, index));
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

void MainWindow::on_actionSave_triggered() {
  const QString savePath = sFileOp.GetConfigurationFilePath();
  sFileOp.SaveConfiguration(
      savePath.isEmpty()
          ? QFileDialog::getSaveFileName(this, "Save Configuration", QString(),
                                         QString("Json (*.json)"))
          : savePath);
}

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "FileOperation.hpp"
#include <QFileDialog>
#include <QMainWindow>
#include <QTabBar>

// There should only ever be one file operation object.
// This will make it easier to save configurations since
// we can jsonify the object itself.
static FileOperation sFileOp;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_OutputDestination_pressed();
  void on_ClearUnifiedOutput_pressed();
  void on_Destination_pressed();
  void on_AddFileExtension_pressed();
  void on_RemoveFileExtension_pressed();
  void on_IsAllFileExtensions_toggled(bool checked);
  void on_IsDateSorted_toggled(bool checked);
  void on_IsFileComments_toggled(bool checked);
  void on_AddInputDirectory_pressed();
  void on_RemoveInputDirectory_pressed();
  void on_IsMultiDestination_toggled(bool checked);
  void on_AddDestination_pressed();
  void on_InputPaths_currentRowChanged(int currentRow);

private:
  void UpdateInterface();
  void UpdateFileExtensionList();
  void UpdateInputList();
  void UpdateOutputList();

  FileOperation::Category mCurrentCategory;
  Ui::MainWindow *ui;
  QTabBar *mTabBar = nullptr;
};
#endif // MAINWINDOW_HPP

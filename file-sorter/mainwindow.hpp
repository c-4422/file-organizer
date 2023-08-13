#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "FileOperation.hpp"
#include <QFileDialog>
#include <QMainWindow>

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
  void on_outputDestination_pressed();
  void on_clearUnifiedOutput_pressed();

  // Picture controls
  void on_pictureDestination_pressed();
  void on_addPictureFileExtButton_pressed();
  void on_removePictureFileExt_pressed();
  void on_isPictureAllFiles_toggled(bool checked);
  void on_isPictureDateSorted_toggled(bool checked);
  void UpdatePictureFileExtList();
  void UpdatePictureInputList();
  void on_isPictureFileComments_toggled(bool checked);
  void on_pictureInputButton_pressed();
  void on_pictureInputRemove_pressed();
  void on_isPictureMultiDestination_toggled(bool checked);
  void UpdatePictureOutputList();
  void on_addPictureDestination_pressed();
  // Audio Controls
  void on_audioDestination_pressed();
  void on_addAudioFileExtButton_pressed();
  void on_removeAudioFileExt_pressed();
  void on_isAudioAllFiles_toggled(bool checked);
  void on_isAudioDateSorted_toggled(bool checked);
  void UpdateAudioFileExtList();
  void UpdateAudioInputList();
  void on_isAudioFileComments_toggled(bool checked);
  void on_audioInputButton_pressed();
  void on_audioInputRemove_pressed();
  void on_isAudioMultiDestination_toggled(bool checked);
  void UpdateAudioOutputList();
  void on_addAudioDestination_pressed();
  // Document Controls
  void on_documentDestination_pressed();
  void on_addDocumentFileExtButton_pressed();
  void on_removeDocumentFileExt_pressed();
  void on_isDocumentAllFiles_toggled(bool checked);
  void on_isDocumentDateSorted_toggled(bool checked);
  void UpdateDocumentFileExtList();
  void UpdateDocumentInputList();
  void on_isDocumentFileComments_toggled(bool checked);
  void on_documentInputButton_pressed();
  void on_documentInputRemove_pressed();
  void on_isDocumentMultiDestination_toggled(bool checked);
  void UpdateDocumentOutputList();
  void on_addDocumentDestination_pressed();
  // Other File Controls
  void on_otherDestination_pressed();
  void on_addOtherFileExtButton_pressed();
  void on_removeOtherFileExt_pressed();
  void on_isOtherAllFiles_toggled(bool checked);
  void on_isOtherDateSorted_toggled(bool checked);
  void UpdateOtherFileExtList();
  void UpdateOtherInputList();
  void on_isOtherFileComments_toggled(bool checked);
  void on_otherInputButton_pressed();
  void on_otherInputRemove_pressed();
  void on_isOtherMultiDestination_toggled(bool checked);
  void UpdateOtherOutputList();
  void on_addOtherDestination_pressed();
  // Video Controls
  void on_videoDestination_pressed();
  void on_addVideoFileExtButton_pressed();
  void on_removeVideoFileExt_pressed();
  void on_isVideoAllFiles_toggled(bool checked);
  void on_isVideoDateSorted_toggled(bool checked);
  void UpdateVideoFileExtList();
  void UpdateVideoInputList();
  void on_isVideoFileComments_toggled(bool checked);
  void on_videoInputButton_pressed();
  void on_videoInputRemove_pressed();
  void on_isVideoMultiDestination_toggled(bool checked);
  void UpdateVideoOutputList();
  void on_addVideoDestination_pressed();

private:
  Ui::MainWindow *ui;
};
#endif // MAINWINDOW_HPP

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QFileDialog>
#include <QMainWindow>
#include "FileOperation.hpp"

// There should only ever be one file operation object.
// This will make it easier to save configurations since
// we can jsonify the object itself.
static FileOperation sFileOp;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pictureDestination_pressed();

    void on_addPictureFileExtButton_pressed();

    void on_removePictureFileExt_pressed();

    void on_isPictureAllFiles_toggled(bool checked);

    void on_isPictureDateSorted_toggled(bool checked);

    void UpdatePictureFileExtList();
    void UpdatePictureInputList();

    void on_isPictureFileComments_toggled(bool checked);

    void on_pictureInputButton_pressed();

    void on_outputDestination_pressed();

    void on_clearUnifiedOutput_pressed();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_HPP

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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_HPP

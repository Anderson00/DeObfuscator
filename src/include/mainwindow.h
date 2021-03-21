#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QDialog>
#include <QFileDialog>
#include "subwindows/programheader.h"

#include <retdec/fileformat/format_factory.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void fileChoosed(retdec::fileformat::FileFormat* file);

private slots:
    void on_actionExit_triggered();

    void on_actionOpen_triggered();

    void on_actionProgram_header_toggled(bool arg1);

    void on_actionFullscreen_triggered();

private:
    Ui::MainWindow *ui;

    //SubWindows
    ProgramHeader *pHeader;
    //end

    std::unique_ptr<retdec::fileformat::FileFormat> file;

};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QFileDialog>

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

private:
    Ui::MainWindow *ui;
    std::unique_ptr<retdec::fileformat::FileFormat> file;

};
#endif // MAINWINDOW_H

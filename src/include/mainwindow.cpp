#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "programheader.h"

#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->mdiArea->tileSubWindows();
    ui->mdiArea->addSubWindow(new ProgramHeader(this));
    ui->mdiArea->addSubWindow(new ProgramHeader(this));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::exit();
}

void MainWindow::on_actionOpen_triggered()
{
    QUrl fileUrl = QFileDialog::getOpenFileUrl(this, tr("File"), tr(""),"Supported files (*.exe *.dll)");

    QFile file(fileUrl.toLocalFile());

    qDebug() << file.size();
    qDebug() <<"Testando" << file.exists();

    this->ui->label->setText(fileUrl.fileName().append(" ").append("size: ").append(std::to_string(file.size()/1024).c_str()).append("KB"));

}

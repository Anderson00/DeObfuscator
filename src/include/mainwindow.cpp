#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "programheader.h"
#include <QDebug>
#include <QLabel>
#include <sstream>
#include <iomanip>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->mdiArea->tileSubWindows();
    ProgramHeader *pHeader = new ProgramHeader(this);
    ui->mdiArea->addSubWindow(pHeader);

    //QObject::connect(this, SIGNAL(fileChoosed(retdec::fileformat::FileFormat*)), pHeader, SLOT(on_fileChoosed(retdec::fileformat::FileFormat*)));
    QObject::connect(this, &MainWindow::fileChoosed, pHeader, &ProgramHeader::on_fileIsChoosed);
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
    if(fileUrl.isValid()){
        QFile file(fileUrl.toLocalFile());
        QFileInfo info(file);

        this->file = retdec::fileformat::createFileFormat(fileUrl.toLocalFile().toStdString());

        this->ui->fileName->setText(info.completeBaseName()+'.'+info.completeSuffix());
        this->ui->fileSize->setText(QString::number(file.size() / 1024)+" KB");

        emit fileChoosed(this->file.get());
        std::string header;
        this->file->getHexBytes(header, 0x00, 2);
        qDebug() << QString::fromStdString(header);
    }

}
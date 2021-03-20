#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "subwindows/programheader.h"
#include "subwindows/debuggermain.h"
#include "utils.h"
#include <QMessageBox>
#include <QDebug>
#include <QLabel>
#include <sstream>
#include <iomanip>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ui->mdiArea->tileSubWindows();
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

        if(this->file->isUnknownArch() || !this->file->isInValidState()){
            QMessageBox::warning(this, "File error", "File is invalid for some reason");
        }else{
            this->ui->fieldArch->setText(MyUtils::architectureEnumToQString(this->file->getTargetArchitecture()));
            emit fileChoosed(this->file.get());
        }
    }

}

void MainWindow::on_actionProgram_header_toggled(bool arg1)
{
    if(arg1){
        pHeader = new ProgramHeader(this);
        sub = ui->mdiArea->addSubWindow(pHeader);
        pHeader->show();

        QObject::connect(this, &MainWindow::fileChoosed, pHeader, &ProgramHeader::on_fileIsChoosed);
        QObject::connect(sub, &QMdiSubWindow::destroyed, [=](){
            ui->actionProgram_header->setChecked(false);
        });
    }else{
        if(pHeader){
            ui->mdiArea->removeSubWindow(sub);
        }
    }


}

void MainWindow::on_actionFullscreen_triggered()
{
    if(!this->isFullScreen()){
        ui->actionFullscreen->setIcon(QIcon(":/icons/fullscreen-exit.svg"));
        this->showFullScreen();
    }else{
        ui->actionFullscreen->setIcon(QIcon(":/icons/fullscreen.svg"));
        this->showNormal();
    }
}

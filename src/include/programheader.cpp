#include "programheader.h"
#include "ui_programheader.h"

ProgramHeader::ProgramHeader(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProgramHeader)
{
    ui->setupUi(this);
    this->setWindowTitle("Program Header");
}

ProgramHeader::~ProgramHeader()
{
    delete ui;
}

#include "programheadertabs.h"
#include "ui_programheadertabs.h"

ProgramHeaderTabs::ProgramHeaderTabs(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProgramHeaderTabs)
{
    ui->setupUi(this);
}

ProgramHeaderTabs::~ProgramHeaderTabs()
{
    delete ui;
}

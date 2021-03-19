#include "debuggermain.h"
#include "ui_debuggermain.h"

DebuggerMain::DebuggerMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DebuggerMain)
{
    ui->setupUi(this);
}

DebuggerMain::~DebuggerMain()
{
    delete ui;
}

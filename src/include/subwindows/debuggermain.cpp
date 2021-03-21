#include "debuggermain.h"
#include "ui_debuggermain.h"

DebuggerMain::DebuggerMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DebuggerMain)
{
    ui->setupUi(this);

    ui->splitter_3->setSizes(QList<int>({1, 1}));
}

DebuggerMain::~DebuggerMain()
{
    delete ui;
}

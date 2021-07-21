#ifndef DEBUGGERMAIN_H
#define DEBUGGERMAIN_H

#include <QMainWindow>

#include "qmlwindow.h"
#include "qmlmdisubwindow.h"

class DebuggerMain : public QMLMdiSubWindow
{
    Q_OBJECT

public:
    explicit DebuggerMain(QWidget *parent = nullptr);
    ~DebuggerMain();
};

#endif // DEBUGGERMAIN_H

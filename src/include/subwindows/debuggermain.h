#ifndef DEBUGGERMAIN_H
#define DEBUGGERMAIN_H

#include <QMainWindow>

#include "qmlwindow.h"

class DebuggerMain : public QMLWindow
{
    Q_OBJECT

public:
    explicit DebuggerMain(QWidget *parent = nullptr);
    ~DebuggerMain();
};

#endif // DEBUGGERMAIN_H

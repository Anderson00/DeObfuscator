#ifndef DEBUGGERMAIN_H
#define DEBUGGERMAIN_H

#include <QMainWindow>

class DebuggerMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit DebuggerMain(QWidget *parent = nullptr);
    ~DebuggerMain();
};

#endif // DEBUGGERMAIN_H

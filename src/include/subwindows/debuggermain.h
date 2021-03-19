#ifndef DEBUGGERMAIN_H
#define DEBUGGERMAIN_H

#include <QMainWindow>

namespace Ui {
class DebuggerMain;
}

class DebuggerMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit DebuggerMain(QWidget *parent = nullptr);
    ~DebuggerMain();

private:
    Ui::DebuggerMain *ui;
};

#endif // DEBUGGERMAIN_H

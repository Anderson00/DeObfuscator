#ifndef PROGRAMHEADERTABS_H
#define PROGRAMHEADERTABS_H

#include <QMainWindow>

namespace Ui {
class ProgramHeaderTabs;
}

class ProgramHeaderTabs : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProgramHeaderTabs(QWidget *parent = nullptr);
    ~ProgramHeaderTabs();

private:
    Ui::ProgramHeaderTabs *ui;
};

#endif // PROGRAMHEADERTABS_H

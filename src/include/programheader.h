#ifndef PROGRAMHEADER_H
#define PROGRAMHEADER_H

#include <QMainWindow>

namespace Ui {
class ProgramHeader;
}

class ProgramHeader : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProgramHeader(QWidget *parent = nullptr);
    ~ProgramHeader();

private:
    Ui::ProgramHeader *ui;
};

#endif // PROGRAMHEADER_H

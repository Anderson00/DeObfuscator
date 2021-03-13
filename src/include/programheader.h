#ifndef PROGRAMHEADER_H
#define PROGRAMHEADER_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <retdec/fileformat/format_factory.h>
#include <QList>
#include "programfieldsmodel.h"


namespace Ui {
class ProgramHeader;
}

class ProgramHeader : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProgramHeader(QWidget *parent = nullptr);
    ~ProgramHeader();

public slots:
    void on_fileIsChoosed(retdec::fileformat::FileFormat* file);

private slots:
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
    void onMzHeaderItemClicked(QTreeWidgetItem *item, int column);
    void onPeHeaderItemClicked(QTreeWidgetItem *item, int column);

    void insertProgramFieldsModelListinFieldsRow(const QList<ProgramFieldsModel>& list);

private:
    Ui::ProgramHeader *ui;
    retdec::fileformat::FileFormat *file;

    QString initialItem = "MZ Header";
    QString currentItem = "";
    const QList<ProgramFieldsModel>* currentFields;
};

#endif // PROGRAMHEADER_H

#include "programheader.h"
#include "./ui_programheader.h"
#include <QDebug>
#include <QTreeWidgetItem>

#include "programfieldsmodel.h"
#include "utils.h"


ProgramHeader::ProgramHeader(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProgramHeader)
{
    ui->setupUi(this);
    this->setWindowTitle("Program Header");
}

ProgramHeader::~ProgramHeader()
{
    delete ui;
}

void ProgramHeader::on_fileIsChoosed(retdec::fileformat::FileFormat *file)
{
    this->file = file;
    this->ui->centralwidget->setEnabled(true);
}

void ProgramHeader::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    QString itemClicked = item->text(0);
    qDebug() << "item clicked: " << itemClicked;
    if(itemClicked == "MZ Header"){
        onMzHeaderItemClicked(item, column);
    }else if(itemClicked == "PE Header"){
        onPeHeaderItemClicked(item, column);
    }
}

void ProgramHeader::onMzHeaderItemClicked(QTreeWidgetItem *item, int column)
{
    if(this->currentItem == "MZ Header")
        return;

    this->currentItem = "MZ Header";
    this->insertProgramFieldsModelListinFieldsRow(MyUtils::getDosFieldsList(file->getTargetArchitecture()));
}

void ProgramHeader::onPeHeaderItemClicked(QTreeWidgetItem *item, int column)
{
    if(this->currentItem == "PE Header")
        return;
    this->currentItem = "PE Header";;
    this->insertProgramFieldsModelListinFieldsRow(MyUtils::getPEHeaderFieldsList(this->file->getTargetArchitecture()));
}

void ProgramHeader::insertProgramFieldsModelListinFieldsRow(const QList<ProgramFieldsModel> &list)
{
    this->currentFields = &list;
    this->ui->fieldsTable->clear();
    this->ui->fieldsTable->setHorizontalHeaderLabels({"Field", "Value", "Desc"});
    this->ui->fieldsTable->setRowCount(list.size());


    int i = 0;
    for(ProgramFieldsModel fields : list){

        std::string result;
        this->file->getHexBytes(result, fields.getOffset(), fields.getSizeBytes());
        fields.setValue(QString::fromStdString(result));

        this->ui->fieldsTable->setItem(i, 0, new QTableWidgetItem(fields.getField()));
        this->ui->fieldsTable->setItem(i, 1, new QTableWidgetItem(fields.getValue()));
        this->ui->fieldsTable->setItem(i, 2, new QTableWidgetItem(fields.getDesc()));

        this->ui->fieldsTable->setVerticalHeaderItem(i, new QTableWidgetItem(fields.getHexOffset()));
        i++;
    }
}

#include "programheader.h"
#include "./ui_programheader.h"
#include <QDebug>
#include <QTreeWidgetItem>

#include "programfieldsmodel.h"
#include "utils.h"
#include "retdec/pelib/PeLibInc.h"


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
    }else if(itemClicked == "File Header"){
        onFileHeaderItemClicked(item, column);
    }
}

void ProgramHeader::onMzHeaderItemClicked(QTreeWidgetItem *item, int column)
{
    if(this->currentItem == "MZ Header")
        return;

    this->currentItem = "MZ Header";
    this->insertProgramFieldsModelListinFieldsRow(MyUtils::getDosFieldsList(file->getTargetArchitecture()), 0);
    this->hexTableShowMemory(0, 0x3c, 6);
}

void ProgramHeader::onPeHeaderItemClicked(QTreeWidgetItem *item, int column)
{
    if(this->currentItem == "PE Header")
        return;
    this->currentItem = "PE Header";
    this->insertProgramFieldsModelListinFieldsRow(MyUtils::getPEHeaderFieldsList(this->file->getTargetArchitecture()), 0xF8);

    this->hexTableShowMemory(0xF8, MyUtils::getNtHeaderSize(this->file->getTargetArchitecture()));
}

void ProgramHeader::onFileHeaderItemClicked(QTreeWidgetItem *item, int column)
{
    if(this->currentItem == "File Header")
        return;
    this->currentItem = "File Header";;
    this->insertProgramFieldsModelListinFieldsRow(MyUtils::getFileHeaderFieldsList(this->file->getTargetArchitecture()), 0xF8 + 0x04);
    this->hexTableShowMemory(0xF8+4, MyUtils::getNtHeaderSize(this->file->getTargetArchitecture()));
}

void ProgramHeader::insertProgramFieldsModelListinFieldsRow(const QList<ProgramFieldsModel> &list, size_t baseAddress)
{
    this->currentFields = &list;
    this->ui->fieldsTable->clear();
    this->ui->fieldsTable->setHorizontalHeaderLabels({"Field", "Value", "Desc"});
    this->ui->fieldsTable->setRowCount(list.size());


    int i = 0;
    for(ProgramFieldsModel fields : list){

        std::string result;
        this->file->getHexBytes(result, baseAddress+fields.getOffset(), fields.getSizeBytes());
        fields.setValue(QString::fromStdString(result));

        this->ui->fieldsTable->setItem(i, 0, new QTableWidgetItem(fields.getField()));
        this->ui->fieldsTable->setItem(i, 1, new QTableWidgetItem(fields.getValue()));
        this->ui->fieldsTable->setItem(i, 2, new QTableWidgetItem(fields.getDesc()));

        this->ui->fieldsTable->setVerticalHeaderItem(i, new QTableWidgetItem(fields.getHexOffset()));
        i++;
    }
}

void ProgramHeader::hexTableShowMemory(size_t baseAddress, size_t size, int bytesPerRow)
{
    this->ui->hexTable->clear();
    this->ui->hexTable->setRowCount((size/bytesPerRow) + 1);
    this->ui->hexTable->setColumnCount(bytesPerRow);

    size_t endAddress = baseAddress + size;

    for(size_t i = 0, newBaseAddress = baseAddress; newBaseAddress <= endAddress ;i++, newBaseAddress = baseAddress+i*bytesPerRow){


        for(int j = 0; j < bytesPerRow; j++){
            std::string result;
            this->file->getHexBytes(result, newBaseAddress+j, 1);
            QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(result));
            item->setTextAlignment(Qt::AlignmentFlag::AlignCenter);
            this->ui->hexTable->setItem(i, j, item);
        }

        this->ui->hexTable->setVerticalHeaderItem(i, new QTableWidgetItem(MyUtils::convertToHex(newBaseAddress, 4)));
    }

    this->ui->hexTable->resizeColumnsToContents();
    this->ui->hexTable->horizontalHeader()->setVisible(false);
}

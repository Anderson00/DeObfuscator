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

    QObject::connect(this->ui->fieldsTable->verticalHeader(), &QHeaderView::sectionClicked, this, &ProgramHeader::on_vertical_sectionClicked);
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
    }else if(itemClicked == "Optional Header"){
        onOptionalHeaderItemClicked(item, column);
    }
}

void ProgramHeader::on_vertical_sectionClicked(int index)
{
    //qDebug() << index;

    auto field = this->currentFields->at(index);
    //qDebug() << this->currentBaseAddressHexTable << field.getSizeBytes();

    //this->ui->hexTable->setRangeSelected({1,0,1,1}, true);
    this->ui->hexTable->verticalHeaderItem(0)->text();
    int colCount = this->ui->hexTable->columnCount();
    int rowCount = this->ui->hexTable->rowCount();
    size_t fieldAddress = this->currentBaseAddressHexTable + field.getOffset();

    int col = fieldAddress % this->currentBytesPerRowHexTable;
    int row = ((fieldAddress - this->currentBaseAddressHexTable) / this->currentBytesPerRowHexTable) % rowCount;
    int rrow = (((fieldAddress - this->currentBaseAddressHexTable) + field.getSizeBytes() - 1)/ this->currentBytesPerRowHexTable) % rowCount;

    this->ui->hexTable->clearSelection();

    if(rrow != row){

        this->ui->hexTable->setRangeSelected({row,col,row, colCount - 2}, true);
        for(int i = 1, byteCount = field.getSizeBytes() - (col - colCount - 2); i <= (rrow - row); i++){

            int next = (byteCount - colCount) - 1;
            int nextClamp = MyUtils::Math::clamp(next, 0, colCount - 2);
            this->ui->hexTable->setRangeSelected({row + i, 0, row + i, nextClamp}, true);

            //qDebug() << ">>> " << next << nextClamp << " " << byteCount;
            byteCount -= nextClamp;
        }
    }else{
        this->ui->hexTable->setRangeSelected({row,col,row, col + field.getSizeBytes() - 1}, true);
    }

    this->ui->hexTable->scrollToItem(this->ui->hexTable->selectedItems()[0]);

    //qDebug() << row << " " << col << " " << rrow;
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

    std::uint64_t res = 0;
    this->file->get4ByteOffset(0x3c, res);

    this->insertProgramFieldsModelListinFieldsRow(MyUtils::getPEHeaderFieldsList(this->file->getTargetArchitecture()), res);
    this->hexTableShowMemory(res, MyUtils::getNtHeaderSize(this->file->getTargetArchitecture()));
}

void ProgramHeader::onFileHeaderItemClicked(QTreeWidgetItem *item, int column)
{
    if(this->currentItem == "File Header")
        return;
    this->currentItem = "File Header";

    std::uint64_t res = 0;
    this->file->get4ByteOffset(0x3c, res);

    this->insertProgramFieldsModelListinFieldsRow(MyUtils::getFileHeaderFieldsList(this->file->getTargetArchitecture()), res + 0x04);
    this->hexTableShowMemory(res + 0x04, MyUtils::getNtHeaderSize(this->file->getTargetArchitecture()));
}

void ProgramHeader::onOptionalHeaderItemClicked(QTreeWidgetItem *item, int column)
{
    if(this->currentItem == "Optional Header")
        return;
    this->currentItem = "Optional Header";

    std::uint64_t res = 0;
    this->file->get4ByteOffset(0x3c, res);

    size_t offset = res + 0x4 + sizeof(PeLib::PELIB_IMAGE_FILE_HEADER);
    if(this->file->getTargetArchitecture() == retdec::fileformat::Architecture::X86){
        offset += sizeof(PeLib::PELIB_IMAGE_OPTIONAL_HEADER32);
    }else{
        offset += sizeof(PeLib::PELIB_IMAGE_OPTIONAL_HEADER64);
    }


    this->insertProgramFieldsModelListinFieldsRow(MyUtils::getOptionalHeaderFieldsList(this->file->getTargetArchitecture()), offset);
    this->hexTableShowMemory(offset, MyUtils::getNtHeaderSize(this->file->getTargetArchitecture()));

}

void ProgramHeader::insertProgramFieldsModelListinFieldsRow(const QList<ProgramFieldsModel> &list, size_t baseAddress)
{
    this->currentFields = &list;
    this->ui->fieldsTable->clear();
    this->ui->fieldsTable->setHorizontalHeaderLabels({"Field", "Value", "Desc"});
    this->ui->fieldsTable->setRowCount(list.size());
    this->ui->fieldsTable->scrollToTop();

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
    this->currentBaseAddressHexTable = baseAddress;
    this->currentBytesPerRowHexTable = bytesPerRow;

    this->ui->hexTable->clear();
    this->ui->hexTable->setRowCount((size/bytesPerRow) + 1);
    this->ui->hexTable->setColumnCount(bytesPerRow + 1);
    this->ui->hexTable->scrollToTop();

    size_t endAddress = baseAddress + size;

    for(size_t i = 0, newBaseAddress = baseAddress; newBaseAddress <= endAddress ;i++, newBaseAddress = baseAddress+i*bytesPerRow){


        for(int j = 0; j < bytesPerRow; j++){
            std::string result;
            this->file->getHexBytes(result, newBaseAddress+j, 1);
            QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(result));
            item->setTextAlignment(Qt::AlignmentFlag::AlignCenter);
            this->ui->hexTable->setItem(i, j, item);
            this->file->getString(result, newBaseAddress, bytesPerRow);
            this->ui->hexTable->setItem(i, j + 1, new QTableWidgetItem(QString::fromStdString(result)));
        }

        this->ui->hexTable->setVerticalHeaderItem(i, new QTableWidgetItem(MyUtils::convertToHex(newBaseAddress, 4)));
    }

    this->ui->hexTable->resizeColumnsToContents();
    this->ui->hexTable->horizontalHeader()->setVisible(false);
}

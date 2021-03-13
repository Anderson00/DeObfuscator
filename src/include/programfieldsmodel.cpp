#include "programfieldsmodel.h"
#include <iomanip>
#include <sstream>

ProgramFieldsModel::ProgramFieldsModel(const int& offset, size_t sizeBytes, const QString& field, const QString& value, const QString& desc)
    : offset(offset), field(field), value(value), desc(desc), sizeBytes(sizeBytes)
{

}

QString ProgramFieldsModel::getField() const
{
    return field;
}

void ProgramFieldsModel::setField(const QString &value)
{
    field = value;
}

QString ProgramFieldsModel::getValue() const
{
    return value;
}

void ProgramFieldsModel::setValue(const QString &value)
{
    this->value = value;
}

QString ProgramFieldsModel::getDesc() const
{
    return desc;
}

void ProgramFieldsModel::setDesc(const QString &value)
{
    desc = value;
}

int ProgramFieldsModel::getOffset() const
{
    return offset;
}

void ProgramFieldsModel::setOffset(int value)
{
    offset = value;
}

QString ProgramFieldsModel::getHexOffset() const
{
    std::stringstream stream;
    stream << "0x" << std::setfill('0') << std::setw(2) << std::hex << this->offset;

    return QString::fromStdString(stream.str());
}

int ProgramFieldsModel::getSizeBytes() const
{
    return sizeBytes;
}

void ProgramFieldsModel::setSizeBytes(int value)
{
    sizeBytes = value;
}

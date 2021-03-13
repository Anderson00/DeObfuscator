#ifndef PROGRAMFIELDSMODEL_H
#define PROGRAMFIELDSMODEL_H

#include <QString>

class ProgramFieldsModel
{
public:
    ProgramFieldsModel(const int& offset, size_t sizeBytes, const QString& field, const QString& value, const QString& desc);


    QString getField() const;
    void setField(const QString &value);

    QString getValue() const;
    void setValue(const QString &value);

    QString getDesc() const;
    void setDesc(const QString &value);

    int getOffset() const;
    void setOffset(int value);

    QString getHexOffset() const;

    int getSizeBytes() const;
    void setSizeBytes(int value);

private:
    QString field, value, desc;
    int offset, sizeBytes;
};

#endif // PROGRAMFIELDSMODEL_H

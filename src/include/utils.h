#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QList>
#include "programfieldsmodel.h"

#include <retdec/fileformat/fftypes.h>

namespace MyUtils {

    const QList<ProgramFieldsModel> &getDosFieldsList(retdec::fileformat::Architecture arch);
    const QList<ProgramFieldsModel> &getPEHeaderFieldsList(retdec::fileformat::Architecture arch);
    const QList<ProgramFieldsModel> &getFileHeaderFieldsList(retdec::fileformat::Architecture arch);
    const QList<ProgramFieldsModel> &getOptionalHeaderFieldsList(retdec::fileformat::Architecture arch);

    QString convertToHex(size_t value, int w);
    QString architectureEnumToQString(retdec::fileformat::Architecture arch);
    size_t getNtHeaderSize(retdec::fileformat::Architecture arch);


    namespace Math {
        int clamp(int val, int min, int max);
    }

};

#endif // UTILS_H

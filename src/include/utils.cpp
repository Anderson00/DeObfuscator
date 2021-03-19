#include "utils.h"

#include <iomanip>
#include <sstream>

#include "retdec/pelib/PeLibInc.h"

const QList<ProgramFieldsModel> &MyUtils::getDosFieldsList(retdec::fileformat::Architecture arch)
{
    if(arch == retdec::fileformat::Architecture::X86){
        //return x86 fields
__SameThing:
        static QList<ProgramFieldsModel> dosFields = {
            ProgramFieldsModel(0x00, 2, "e_magic", "", "MZ Header signature"),
            ProgramFieldsModel(0x02, 2, "e_cblp", "", "Bytes on last page of file"),
            ProgramFieldsModel(0x04, 2, "e_cp", "", "Pages in file"),
            ProgramFieldsModel(0x06, 2, "e_crlc", "", "Relocations"),
            ProgramFieldsModel(0x08, 2, "e_cparhdr", "", "Size of header in paragraphs"),
            ProgramFieldsModel(0x0a, 2, "e_minalloc", "", "Minimum extra paragraphs needed"),
            ProgramFieldsModel(0x0c, 2, "e_maxalloc", "", "Maximum extra paragraphs needed"),
            ProgramFieldsModel(0x0e, 2, "e_ss", "", "Initial (relative) SS value"),
            ProgramFieldsModel(0x10, 2, "e_sp", "", "Initial SP value"),
            ProgramFieldsModel(0x12, 2, "e_csum", "", "Checksum"),
            ProgramFieldsModel(0x14, 2, "e_ip", "", "Initial IP value"),
            ProgramFieldsModel(0x16, 2, "e_cs", "", "Initial (relative) CS value"),
            ProgramFieldsModel(0x18, 2, "e_lfarlc", "", "File address of relocation table"),
            ProgramFieldsModel(0x1a, 2, "e_ovno", "", "Overlay number"),
            ProgramFieldsModel(0x1c, 4, "e_res", "", "Reserved words"),
            ProgramFieldsModel(0x24, 2, "e_oemid", "", "OEM identifier (for e_oeminfo)"),
            ProgramFieldsModel(0x26, 2, "e_oeminfo", "", "OEM information; e_oemid specific"),
            ProgramFieldsModel(0x28, 10, "e_res2", "", "Reserved words"),
            ProgramFieldsModel(0x3c, 4, "e_lfanew", "", "Offset to extended header")
        };

        return dosFields;
    }else if(arch == retdec::fileformat::Architecture::X86_64){
        //return x64 fields
        goto __SameThing;// In Mz header x86 and x64 is equal
    }else{
        //throw exception
        //No Architecture supported
        assert(false);
    }
}

const QList<ProgramFieldsModel> &MyUtils::getPEHeaderFieldsList(retdec::fileformat::Architecture arch)
{
    if(arch == retdec::fileformat::Architecture::X86){
        //return x86 fields
__SameThing:
        static QList<ProgramFieldsModel> peFields = {
            ProgramFieldsModel(0x00, 4, "Signature",  "", "")
        };

        return peFields;
    }else if(arch == retdec::fileformat::Architecture::X86_64){
        //return x64 fields
        goto __SameThing;
    }else{
        //throw exception
        //No Architecture supported
        assert(false);
    }
}

const QList<ProgramFieldsModel> &MyUtils::getFileHeaderFieldsList(retdec::fileformat::Architecture arch)
{
    if(arch == retdec::fileformat::Architecture::X86){
        //return x86 fields
__SameThing:
        static QList<ProgramFieldsModel> peFields = {
            ProgramFieldsModel(0x00, 2, "Machine",  "", ""),
            ProgramFieldsModel(0x02, 2, "NumberOfSections",  "", ""),
            ProgramFieldsModel(0x04, 4, "TimeDateStamp",  "", ""),
            ProgramFieldsModel(0x08, 4, "PointerToSymbolTable",  "", ""),
            ProgramFieldsModel(0x0C, 4, "NumberOfSymbols",  "", ""),
            ProgramFieldsModel(0x0E, 2, "SizeOfOptionalHeader",  "", ""),
            ProgramFieldsModel(0x10, 2, "Characteristics",  "", ""),
        };

        return peFields;
    }else if(arch == retdec::fileformat::Architecture::X86_64){
        //return x64 fields
        goto __SameThing;
    }else{
        //throw exception
        //No Architecture supported
        assert(false);
    }
}

const QList<ProgramFieldsModel> &MyUtils::getOptionalHeaderFieldsList(retdec::fileformat::Architecture arch)
{
    if(arch == retdec::fileformat::Architecture::X86){
        //return x86 fields
        static QList<ProgramFieldsModel> peFields = {
            ProgramFieldsModel(0x00, 2, "Magic", "", ""),
            ProgramFieldsModel(0x02, 1, "MajorLinkerVersion", "", ""),
            ProgramFieldsModel(0x03, 1, "MinorLinkerVersion", "", ""),
            ProgramFieldsModel(0x04, 4, "SizeOfCode", "", ""),
            ProgramFieldsModel(0x08, 4, "SizeOfInitializedData", "", ""),
            ProgramFieldsModel(0x0C, 4, "SizeOfUninitializedData", "", ""),
            ProgramFieldsModel(0x10, 4, "AddressOfEntryPoint", "", ""),
            ProgramFieldsModel(0x14, 4, "BaseOfCode", "", ""),
            ProgramFieldsModel(0x18, 4, "BaseOfData", "", ""),
            ProgramFieldsModel(0x1C, 4, "ImageBase", "", ""),
            ProgramFieldsModel(0x20, 4, "SectionAlignment", "", ""),
            ProgramFieldsModel(0x24, 4, "FileAlignment", "", ""),
            ProgramFieldsModel(0x26, 2, "MajorOperatingSystemVersion", "", ""),
            ProgramFieldsModel(0x28, 2, "MinorOperatingSystemVersion", "", ""),
            ProgramFieldsModel(0x2A, 2, "MajorImageVersion", "", ""),
            ProgramFieldsModel(0x2C, 2, "MinorImageVersion", "", ""),
            ProgramFieldsModel(0x2E, 2, "MajorSubsystemVersion", "", ""),
            ProgramFieldsModel(0x30, 2, "MinorSubsystemVersion", "", ""),
            ProgramFieldsModel(0x32, 4, "Win32VersionValue", "", ""),
            ProgramFieldsModel(0x36, 4, "SizeOfImage", "", ""),
            ProgramFieldsModel(0x3A, 4, "SizeOfHeaders", "", ""),
            ProgramFieldsModel(0x3E, 4, "CheckSum", "", ""),
            ProgramFieldsModel(0x42, 2, "Subsystem", "", ""),
            ProgramFieldsModel(0x44, 2, "DllCharacteristics", "", ""),
            ProgramFieldsModel(0x46, 4, "SizeOfStackReserve", "", ""),
            ProgramFieldsModel(0x4A, 4, "SizeOfStackCommit", "", ""),
            ProgramFieldsModel(0x4E, 4, "SizeOfHeapReserve", "", ""),
            ProgramFieldsModel(0x52, 4, "SizeOfHeapCommit", "", ""),
            ProgramFieldsModel(0x56, 4, "LoaderFlags", "", ""),
            ProgramFieldsModel(0x5A, 4, "NumberOfRvaAndSizes", "", ""),
            ProgramFieldsModel(0x5E, PeLib::PELIB_IMAGE_NUMBEROF_DIRECTORY_ENTRIES, "DataDirectory", "", "")
        };

        return peFields;
    }else if(arch == retdec::fileformat::Architecture::X86_64){
        //return x64 fields
        static QList<ProgramFieldsModel> peFields = {
            ProgramFieldsModel(0x00, 2, "Magic", "", ""),
            ProgramFieldsModel(0x02, 1, "MajorLinkerVersion", "", ""),
            ProgramFieldsModel(0x03, 1, "MinorLinkerVersion", "", ""),
            ProgramFieldsModel(0x04, 4, "SizeOfCode", "", ""),
            ProgramFieldsModel(0x08, 4, "SizeOfInitializedData", "", ""),
            ProgramFieldsModel(0x0C, 4, "SizeOfUninitializedData", "", ""),
            ProgramFieldsModel(0x10, 4, "AddressOfEntryPoint", "", ""),
            ProgramFieldsModel(0x14, 4, "BaseOfCode", "", ""),
            ProgramFieldsModel(0x18, 4, "BaseOfData", "", ""),
            ProgramFieldsModel(0x1C, 8, "ImageBase", "", ""),
            ProgramFieldsModel(0x24, 4, "SectionAlignment", "", ""),
            ProgramFieldsModel(0x28, 4, "FileAlignment", "", ""),
            ProgramFieldsModel(0x2C, 2, "MajorOperatingSystemVersion", "", ""),
            ProgramFieldsModel(0x2E, 2, "MinorOperatingSystemVersion", "", ""),
            ProgramFieldsModel(0x30, 2, "MajorImageVersion", "", ""),
            ProgramFieldsModel(0x32, 2, "MinorImageVersion", "", ""),
            ProgramFieldsModel(0x34, 2, "MajorSubsystemVersion", "", ""),
            ProgramFieldsModel(0x36, 2, "MinorSubsystemVersion", "", ""),
            ProgramFieldsModel(0x38, 4, "Win32VersionValue", "", ""),
            ProgramFieldsModel(0x3C, 4, "SizeOfImage", "", ""),
            ProgramFieldsModel(0x40, 4, "SizeOfHeaders", "", ""),
            ProgramFieldsModel(0x44, 4, "CheckSum", "", ""),
            ProgramFieldsModel(0x48, 2, "Subsystem", "", ""),
            ProgramFieldsModel(0x4A, 2, "DllCharacteristics", "", ""),
            ProgramFieldsModel(0x4C, 8, "SizeOfStackReserve", "", ""),
            ProgramFieldsModel(0x54, 8, "SizeOfStackCommit", "", ""),
            ProgramFieldsModel(0x5C, 8, "SizeOfHeapReserve", "", ""),
            ProgramFieldsModel(0x64, 8, "SizeOfHeapCommit", "", ""),
            ProgramFieldsModel(0x6C, 4, "LoaderFlags", "", ""),
            ProgramFieldsModel(0x70, 4, "NumberOfRvaAndSizes", "", ""),
            ProgramFieldsModel(0x74, PeLib::PELIB_IMAGE_NUMBEROF_DIRECTORY_ENTRIES, "DataDirectory", "", "")
        };

        return peFields;
    }else{
        //throw exception
        //No Architecture supported
        assert(false);
    }
}

QString MyUtils::convertToHex(size_t value, int w = 2)
{
    std::stringstream stream;
    stream << "0x" << std::setfill('0') << std::setw(w) << std::uppercase << std::hex << value;

    return QString::fromStdString(stream.str());
}

size_t MyUtils::getNtHeaderSize(retdec::fileformat::Architecture arch)
{
    if(arch == retdec::fileformat::Architecture::UNKNOWN){
        assert(false);
    }

    static size_t sizeOfPeHeader = 4 + sizeof(PeLib::PELIB_IMAGE_FILE_HEADER)
            + ((arch == retdec::fileformat::Architecture::X86) ?
                  sizeof(PeLib::PELIB_IMAGE_OPTIONAL_HEADER32)://true
                  sizeof(PeLib::PELIB_IMAGE_OPTIONAL_HEADER64) //false
              );

    return sizeOfPeHeader;
}

QString MyUtils::architectureEnumToQString(retdec::fileformat::Architecture arch)
{
    switch(arch){
    case retdec::fileformat::Architecture::ARM:
        return "ARM";
    case retdec::fileformat::Architecture::X86:
        return "X86";
    case retdec::fileformat::Architecture::X86_64:
        return "x64";
    case retdec::fileformat::Architecture::POWERPC:
        return "PowerPC";
    case retdec::fileformat::Architecture::MIPS:
        return "Mips";
    default:
        return "Unknow";
    }
}


int MyUtils::Math::clamp(int val, int min, int max)
{
    assert(min <= max);
    if(val >= min && val <= max){
        return val;
    }else if(val < min){
        return min;
    }else{
        return max;
    }
}

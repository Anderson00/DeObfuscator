#include "utils.h"

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

        };

        return peFields;
    }else if(arch == retdec::fileformat::Architecture::X86_64){
        //return x64 fields
        static QList<ProgramFieldsModel> peFields = {

        };

        return peFields;
    }else{
        //throw exception
        //No Architecture supported
        assert(false);
    }
}

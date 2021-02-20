#include <unicorn/unicorn.h>
#include <capstone/capstone.h>
#include <iostream>
#include <fstream>
#include <curses.h>
#include <panel.h>

#include "include/curses/CursesSingleton.h"
#include "include/curses/window.h"
#include "include/curses/text.h"
#include "include/curses/borderpane.h"
#include "include/curses/scrollpane.h"

void capstone_printf(uint64_t address, byte *buffer, size_t size)
{
    csh handle;
    cs_insn *insn;
    size_t count;

    if (cs_open(CS_ARCH_X86, CS_MODE_32, &handle) != CS_ERR_OK)
    {
        std::cout << "Erro in capstone open: " << cs_strerror(cs_errno(handle)) << std::endl;
        return;
    }
    count = cs_disasm(handle, buffer, size, address, 0, &insn);
    if (count > 0)
    {
        for (size_t i = 0; i < count; i++)
        {
            std::cout << "0x" << std::hex << insn[i].address << " " << insn[i].bytes << "\t " << insn[i].op_str << std::endl;
        }

        cs_free(insn, count);
    }

    cs_close(&handle);
}

int main(int argc, char **argv)
{

    CursesSingleton *cursesInstance = CursesSingleton::instance();
    noecho();
    cbreak();

    
    BorderPane *pane = new BorderPane(COLS, LINES, 0, 0);


    refresh();

    getch();
    
    delete pane;
    delete cursesInstance;

    return 0;
}
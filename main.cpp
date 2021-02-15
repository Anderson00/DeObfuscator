#include <unicorn/unicorn.h>
#include <capstone/capstone.h>
#include <iostream>
#include <fstream>
#include <curses.h>
#include <panel.h>

#define DLL "codex.dll"
#define ADDRESS 0x10000000
#define STACK_ADDR 0x0
#define STACK_SIZE 1024*1024

uc_engine *engine;
int64_t r_esp = STACK_ADDR + STACK_SIZE - 1;

void capstone_printf(uint64_t address, byte * buffer, size_t size){
    csh handle;
    cs_insn *insn;
	size_t count;

    if(cs_open(CS_ARCH_X86, CS_MODE_32, &handle) != CS_ERR_OK){
        std::cout << "Erro in capstone open: " << cs_strerror(cs_errno(handle)) << std::endl;
        return;
    }
    count = cs_disasm(handle, buffer, size, address, 0, &insn);
    if(count > 0){
        for(size_t i = 0; i < count; i++){
            std::cout << "0x" << std::hex << insn[i].address << " " << insn[i].bytes << "\t " << insn[i].op_str << std::endl;
        }

        cs_free(insn, count);
    }


    cs_close(&handle);
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{	
    WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	wborder(local_win, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
	wrefresh(local_win);
	return local_win;
}

void destroy_win(WINDOW *local_win)
{	
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wrefresh(local_win);
	delwin(local_win);
}

int main(int argc, char **argv){

    WINDOW *local_win, *local_win2, *local_win3;	
	initscr();
    noecho();
    start_color();
	init_pair(1, COLOR_RED, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    wbkgd(stdscr, COLOR_PAIR(1));
    refresh();
    
	local_win = create_newwin(LINES-6, COLS/2 - 2, 1, 1);
    local_win2 = create_newwin(LINES-6, COLS/2 - 1, 1, COLS/2);
    local_win3 = create_newwin(5, COLS-2, LINES-5, 1);

    wbkgd(local_win, COLOR_PAIR(1));

    wattron(local_win, COLOR_PAIR(1));
    wmove(local_win, 1, 1);
    wprintw(local_win, "Testando !");
    wmove(local_win, 2, 1);
    wprintw(local_win, "H=%d W=%d", LINES, COLS);
    wmove(local_win3, 1, 1);
    wprintw(local_win3, "has colors: %d %d", has_colors(), can_change_color());
    wattroff(local_win, COLOR_PAIR(1));

    wrefresh(local_win);
    wrefresh(local_win3);
	getch();
	destroy_win(local_win);
	refresh();
	endwin();

    uc_err err = uc_open(UC_ARCH_X86, UC_MODE_32, &engine);
    if(err == UC_ERR_OK){
        err = uc_mem_map(engine, ADDRESS, 2 * 1024 * 1024, UC_PROT_ALL);
        if(err != UC_ERR_OK){
            std::cout << "Error2: " << uc_strerror(err) << std::endl;
            return err;
        }
        err = uc_mem_map(engine, STACK_ADDR, STACK_SIZE, UC_PROT_READ | UC_PROT_WRITE);
        if(err != UC_ERR_OK){
            std::cout << "Stack mem map: " << uc_strerror(err) << std::endl;
            return err;
        }

        std::ifstream file(DLL, std::ifstream::binary);
        if(file){
            file.seekg (0, file.end);
            int length = file.tellg();
            file.seekg (0, file.beg);
            std::cout << "File:" << DLL << ", Size: " << length << std::endl;
            
            char * buffer = new char[length];
            file.read(buffer, length);

            if(file){
                std::cout << DLL << " read successfully" << std::endl;
            }else{
                std::cout << "error: only " << file.gcount() << " could be read" << std::endl;
                return -1;
            }

            err = uc_mem_write(engine, ADDRESS, buffer, length);
            if(err != UC_ERR_OK){
                std::cout << "Error 3: " << uc_strerror(err) << std::endl;
                return err;
            }

            

            byte *dllEntry = new byte[0x1E9];
            err = uc_mem_read(engine, ADDRESS + 0x18bd0, dllEntry, 0x1E9);

            //capstone_printf(ADDRESS, dllEntry, 0x1E9);


            uc_reg_write(engine, UC_X86_REG_ESP, &r_esp);
            uc_emu_start(engine, ADDRESS + 0x18bdb, 0, 0, 0);

            int64_t value = 0;
            uc_reg_read(engine, UC_X86_REG_ESP, &value);
            std::cout << "ESP = 0x" << std::hex << value << std::endl; 
            uc_reg_read(engine, UC_X86_REG_EAX, &value);
            std::cout << "EAX = 0x" << std::hex << value << std::endl; 
            uc_reg_read(engine, UC_X86_REG_EBX, &value);
            std::cout << "EBX = 0x" << std::hex << value << std::endl; 
            uc_reg_read(engine, UC_X86_REG_ESI, &value);
            std::cout << "ESI = 0x" << std::hex << value << std::endl; 
            uc_reg_read(engine, UC_X86_REG_EIP, &value);
            std::cout << "EIP = 0x" << std::hex << value << std::endl; 
            

            //Write deobfuscated file
            byte *bb = new byte[length];
            err = uc_mem_read(engine, ADDRESS, bb, length);
            if(err != UC_ERR_OK){
                std::cout << "Error leitura: " << uc_strerror(err) << std::endl;
                return err;
            }
            std::cout << "testando" << std::endl;
            
            std::ofstream output("codex22.dll", std::ofstream::binary);
            if(output){
                output.write((char*)bb, length);
                output.flush();
            }
            output.close();
            //end

            delete[] dllEntry;
            delete[] bb;
            delete[] buffer;
        }
    }else{
        std::cout << "Error: " << uc_strerror(err) << std::endl;
    }

    uc_close(engine);

    return 0;
}
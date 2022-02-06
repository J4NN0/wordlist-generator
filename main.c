// Copyright 2017 Federico Gianno
//
// This file is part of wordlist.
//
// wordlist is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// wordlist is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with wordlist.  If not, see <http://www.gnu.org/licenses/>.

#include <stdio.h>
#include "Wordlist/wordlist.h"
#include "More/more.h"
#include "System/system.h"

void intro();

int main() {
    char cmd = ' ';

    intro();

    #ifdef _WIN32
    system("color 02");
    #endif

    while(cmd != '0'){

        fprintf(stdout,"__          __           _ _ _     _                                     _             \n"
                       "\\ \\        / /          | | (_)   | |                                   | |            \n"
                       " \\ \\  /\\  / /__  _ __ __| | |_ ___| |_    __ _  ___ _ __   ___ _ __ __ _| |_ ___  _ __ \n"
                       "  \\ \\/  \\/ / _ \\| '__/ _` | | / __| __|  / _` |/ _ \\ '_ \\ / _ \\ '__/ _` | __/ _ \\| '__|\n"
                       "   \\  /\\  / (_) | | | (_| | | \\__ \\ |_  | (_| |  __/ | | |  __/ | | (_| | || (_) | |   \n"
                       "    \\/  \\/ \\___/|_|  \\__,_|_|_|___/\\__|  \\__, |\\___|_| |_|\\___|_|  \\__,_|\\__\\___/|_|   \n"
                       "                                          __/ |                                        \n"
                       "                                         |___/                                         \n"
                       "\n"
               " [1] Wordlist with whole alphabet [a-zA-Z]\n"
               " [2] Wordlist with only numbers [0-9]\n"
               " [3] Wordlist with strings, character and numbers\n"
               " [4] Guided wordlist\n"
               " [5] Wordlist from data file\n"
               " [6] Dictionary wordlist\n"
               " [7] More info\n"
               " [0] Exit\n\n");

        fprintf(stdout, ">> ");
        fflush(stdin);
        fscanf(stdin, "%1s", &cmd);

        switch(cmd){
            case '0':
                fprintf(stdout, "\nGoodbye!\n");
                break;
            case '1':
                wl_alphabet();
                break;
            case '2':
                wl_numbers();
                break;
            case '3':
                wl_str();
                break;
            case '4':
                wl_guided();
                break;
            case '5':
                wl_file();
                break;
            case '6':
                wl_dictionary();
                break;
            case '7':
                info();
                break;
            default:
                fprintf(stdout, "Function not supported, you fucking know it.\n");
                fprintf(stdout, "Press enter to continue...");
                fflush(stdin);
                getc(stdin);
                clear();
                break;
        }
    }

    return 0;
}

void intro() {
    fprintf(stdout, "This program is free software: you can redistribute it and/or modify\n"
                    "it under the terms of the GNU General Public License as published by\n"
                    "the Free Software Foundation, either version 3 of the License, or\n"
                    "(at your option) any later version.\n\n"

                    "This program is distributed in the hope that it will be useful,\n"
                    "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
                    "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
                    "GNU General Public License for more details.\n\n"

                    "You should have received a copy of the GNU General Public License\n"
                    "along with this program. If not, see <http://www.gnu.org/licenses/>.\n\n");

    fprintf(stdout, "Developed by Federico Gianno (J4NN0).\n\n");

    pause();
    clear();
}

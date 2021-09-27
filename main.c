/*  Copyright 2017 Federico Gianno

    This file is part of wordlist.

    wordlist is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    wordlist is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with wordlist.  If not, see <http://www.gnu.org/licenses/>.

    Developed by Federico Gianno */

#include <stdio.h>
#include <stdlib.h>
#include "Wordlist/wordlist.h"

int main()
{
    char oper=' ';

    intro();

    #ifdef _WIN32
    system("color 02");
    #endif

    while(oper!='0'){
        fprintf(stdout, "\t\t\t ==== WORDLIST GENERATOR ==== \n\n"
               " [1] Wordlist with whole alphabet (a-zA-Z)\n"
               " [2] Wordlist with only numbers (0-9)\n"
               " [3] Wordlist with strings, character and numbers\n"
               " [4] Guided wordlist\n"
               " [5] Wordlist from data file\n"
               " [6] Dictionary wordlist\n"
               " [7] More info\n"
               " [0] Exit\n");
        fprintf(stdout, "\n>> ");
        fflush(stdin);
        fscanf(stdin, "%1s", &oper);
        switch(oper){
            case '0':
                fprintf(stdout, "\nGoodbye!\n");
                break;
            case '1':
                wl_alpha();
                break;
            case '2':
                wl_numb();
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
                #ifdef _WIN32
                system("CLS");
                #endif //win
                #ifdef linux
                system("clear");
                #endif // linux
                break;
        }
    }

    return 0;
}

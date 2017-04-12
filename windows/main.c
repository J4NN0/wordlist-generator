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

    Developed by Nindo */

#include <stdio.h>
#include <stdlib.h>
#include "wordlist.h"

int main()
{
    system("title Wordlist");

    char oper=' ';

    intro();

    system("color 02");
    while(oper!='0'){
        fprintf(stdout, "\t\t\t\4 MAKE WORDLIST \4\t[patch 1.01]\n\n"
               " [1] Generate a wordlist with whole alphabet (a-z)|(A-Z);\n"
               " [2] Generate a wordlist with only numbers (0-9);\n"
               " [3] Generate a customized wordlist (char);\n"
               " [4] Generate a wordlist with strings, character and numbers;\n"
               " [5] Guided wordlist (Alphabet | Number | Special Characters);\n"
               " [6] Generate a wordlist from data file;\n"
               " [7] More info;\n"
               " [0] Exit;\n");
        fprintf(stdout, "\n>> ");
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
                wl_custom();
                break;
            case '4':
                wl_str();
                break;
            case '5':
                wl_guided();
                break;
            case '6':
                wl_file();
                break;
            case '7':
                info();
                break;
            default:
                fprintf(stdout, "Function not supported, you fucking know it.\n");
                fprintf(stdout, "Press enter to continue...");
                fflush(stdin);
                getc(stdin);
                system("CLS");
                break;
        }
    }

    return 0;
}

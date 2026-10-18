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
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "wordlist.h"
#include "Util/util.h"
#include "../More/more.h"
#include "../System/system.h"

/* Global var */
static unsigned long long count=0;

/* Arrangements engine, shared by Alphabet [1], Numbers [2], Str [3], Guided [4] and File [5] */
static void arrangements(FILE *fp_out, int pos, char **tok, int *sol, int *mark, int n_tok, int min_len, int max_len, unsigned long long tot);
static void print_sol(FILE *fp_out, const int *sol, char **tok, int dim);
/* Dictionary [6] */
static void create_dic(FILE *fp_out, int start, char *str, char *sol, int n, unsigned long long tot);

/// === Alphabet ===
void wl_alphabet() {
    FILE *fp=NULL;
    char *v=NULL, **tok=NULL, oper=' ';
    int *sol=NULL, min_size=0, max_size=0, dim=0;
    unsigned long long tot;

    explication();
    fflush(stdin);

    while(oper!='1' && oper!='2' && oper!='3'){
        fprintf(stdout, "[1] Uppercase;\n"
                        "[2] Lowercase;\n"
                        "[3] Both (1 and 2);\n"
                        ">> ");
        fscanf(stdin, " %c", &oper);
        switch(oper){
            case '1':
                v = init_alphabet_uppercase(v);
                dim = A;
                break;
            case '2':
                v = init_alphabet_lowercase(v);
                dim = A;
                break;
            case '3':
                v = init_alphabet_uppercase_and_lowercase(v);
                dim = A + A;
                break;
            default:
                fprintf(stdout, "Come on please, seriously.\n");
                pause();
                clear();
                break;
        }
    }

    sol = manage_size(&min_size, &max_size, sol);
    fp = manage_file();
    tok = chars_to_tokens(v, dim);

    tot = tot_arrangements_rep(min_size, max_size, dim);
    arrangements(fp, 0, tok, sol, NULL, dim, min_size, max_size, tot);

    end(min_size, max_size);
    count = 0;

    fclose(fp);
    free(v);
    free(sol);
    free_char_tokens(tok);
}

/// === Number ===
void wl_numbers() {
    FILE *fp=NULL;
    char **tok=NULL;
    int *sol=NULL, min_size=0, max_size=0;
    unsigned long long tot;

    explication();
    fflush(stdin);

    sol = manage_size(&min_size, &max_size, sol);
    fp = manage_file();
    tok = chars_to_tokens("0123456789", N);

    tot = tot_arrangements_rep(min_size, max_size, N);
    arrangements(fp, 0, tok, sol, NULL, N, min_size, max_size, tot);

    end(min_size, max_size);
    count = 0;

    fclose(fp);
    free(sol);
    free_char_tokens(tok);
}

/// === Str & Numb ===
void wl_str() {
    FILE *fp=NULL;
    int *sol=NULL, *mark=NULL;
    char **str=NULL, trash;
    int i, dim=0, n_rip, ok=0;
    unsigned long long tot;

    explication();
    fflush(stdin);

    str = init_str(str, &dim);

    while(!ok) {
        fprintf(stdout, "\nHow many times (from 1 to 9) a string must be repeated? (Suggested 1) -> ");
        trash = getc(stdin);
        fflush(stdin);
        if(isdigit(trash) && trash != '0'){
            n_rip = trash - '0';
            if(n_rip > 0) {
                ok = 1;
            }
        }
        else {
            fprintf(stderr, "Are you trying to trolling me? Please, try again.\n");
        }
    }

    mark = malloc(dim*sizeof(int));
    if(mark == NULL) {
        err_pointer(-10);
    }

    for(i=0; i<dim; i++) {
        mark[i] = n_rip;
    }

    sol = malloc((dim * n_rip) * sizeof(int));
    if(sol == NULL) {
        err_pointer(-9);
    }

    fp = manage_file();

    tot = tot_arrangements(dim * n_rip, dim * n_rip);

    arrangements(fp, 0, str, sol, mark, dim, 1, dim * n_rip, tot);
    fprintf(stdout, "\nAll the possible strings generated!\n");
    count=0;
    fprintf(stdout, "Use it wisely!\n");

    pause();

    fclose(fp);
    free(sol);
    free(mark);
    // free 2d:
    for(i=0; i<dim; i++)
        free(str[i]);
    free(str);

    clear();
}

/// === Guided ===
void wl_guided() {
    FILE *fp=NULL;
    char *v=NULL, **tok=NULL;
    char oper=' ';
    int *sol=NULL, min_size=0, max_size=0, dim=0;
    unsigned long long tot;

    explication();
    fflush(stdin);

    // Alphabet
    while(oper!='1' && oper!='2'){
        fprintf(stdout, "Do you want insert some or all alphabet characters?\n"
                        "[1] Yes - [2] No\n"
                        ">> ");
        fscanf(stdin, " %c", &oper);
        switch(oper){
            case '1':
                v = insert_alphabet_chars(v, &dim);
                break;
            case '2':
                break;
            default:
                fprintf(stdout, "Are you trolling?\n");
                break;
        }
    }
    oper=' ';

    // Numbers
    while(oper!='1' && oper!='2'){
        fprintf(stdout, "\nDo you want insert some number?\n"
                        "[1] Yes - [2] No\n"
                        ">> ");
        fscanf(stdin, " %c", &oper);
        switch(oper){
            case '1':
                v = insert_numbers(v, &dim);
                break;
            case '2':
                break;
            default:
                fprintf(stdout, "Are you trolling?\n");
                break;
        }
    }
    oper=' ';

    // Special characters
    while(oper!='1' && oper!='2'){
        fprintf(stdout, "\nDo you want insert some (or all) special characters?\n"
                        "[1] Yes - [2] No\n"
                        ">> ");
        fscanf(stdin, " %c", &oper);
        switch(oper){
            case '1':
                v = insert_special_chars(v, &dim);
                break;
            case '2':
                break;
            default:
                fprintf(stdout, "Are you confused?\n");
                break;
        }
    }

    sol = manage_size(&min_size, &max_size, sol);

    fp = manage_file();

    tok = chars_to_tokens(v, dim);

    tot = tot_arrangements_rep(min_size, max_size, dim);
    arrangements(fp, 0, tok, sol, NULL, dim, min_size, max_size, tot);

    end(min_size, max_size);
    count = 0;

    fclose(fp);
    free(v);
    free(sol);
    free_char_tokens(tok);
}

/// === Dictionary ===
void wl_dictionary() {
    FILE *fp=NULL;
    char str[S], *sol=NULL;
    int len;
    unsigned long long tot;

    explication();
    fflush(stdin);

    fprintf(stdout, "Insert string to modify for dictionary attack: ");
    fscanf(stdin, "%49s", str);

    fp = manage_file();
    tot = tot_dic(str);

    sol = malloc((strlen(str)+1)*sizeof(char));
    if(sol == NULL) {
        err_pointer(-24);
    }
    strcpy(sol, str);

    len = (int)strlen(str);
    create_dic(fp, 0, str, sol, len, tot);

    end(len, len);
    count = 0;

    fclose(fp);
    free(sol);
}

static void create_dic(FILE *fp_out, int start, char *str, char *sol, int n, unsigned long long tot) {
    int i;
    char dic=' ';

    if(start >= n) {
        return;
    }

    for(i=start; i<n; i++){
        dic = get_dic(str[i]);
        if(dic != ' '){
            sol[i] = dic;
            //print_count(++count, tot);
            fprintf(fp_out, "%s\n", sol);
            create_dic(fp_out, i+1, str, sol, n, tot);
            sol[i] = str[i];
        }
    }
}

/// === File ===
void wl_file() {
    FILE *fp;
    char filename[FILENAME_MAX];
    char str[S], **matr=NULL, **tmp=NULL;
    int *mark=NULL, *sol=NULL;
    int i=0, ok=0, dim_file=0;
    unsigned long long tot=0;

    explication();
    fflush(stdin);

    while(!ok){
        fprintf(stdout, "Insert file name: ");
        fscanf(stdin, "%s", filename);
        fp = fopen(filename, "r");
        if(fp==NULL){
            fprintf(stdout, "\nError opening file %s.\n", filename);
            fprintf(stdout, "Enter a valid name.\n\n");
        }
        else
            ok=1;
    }

    fprintf(stdout, "\n");

    dim_file = 20; // arbitrary;
    matr = malloc(dim_file*sizeof(char*));
    if(matr == NULL) {
        err_pointer(-19);
    }

    fprintf(stdout, "Reading file %s...\n", filename);
    while(fgets(str, S, fp)!=NULL){
        matr[i] = malloc((strlen(str)+1)*sizeof(char));
        if(matr[i] == NULL){
            err_pointer(-20);
        }
        strcpy_format(matr[i], str);

        i++;
        if(i==dim_file){
            tmp = realloc(matr, (2*dim_file)*sizeof(char*));
            if(tmp == NULL) {
                err_pointer(-21);
            }
            matr = tmp;
            dim_file = 2*dim_file;
        }
    }
    dim_file = i;
    fclose(fp);

    // Empty input file
    if(dim_file == 0) {
        fprintf(stdout, "File %s is empty. Nothing to generate.\n", filename);
        free(matr);
        pause();
        clear();
        return;
    }

    sol = malloc(dim_file*sizeof(int));
    if(sol == NULL) {
        err_pointer(-22);
    }

    // Each line can be used once: arrangements without repetition
    mark = malloc(dim_file*sizeof(int));
    if(mark == NULL) {
        err_pointer(-23);
    }

    for(i=0; i<dim_file; i++) {
        mark[i] = 1;
    }

    tot = tot_arrangements(dim_file, dim_file);
    fp = manage_file();
    arrangements(fp, 0, matr, sol, mark, dim_file, 1, dim_file, tot);
    fprintf(stdout, "\nAll the possible strings generated!\n");
    count=0;
    fprintf(stdout, "Use it wisely!\n");

    pause();

    fclose(fp);
    free(sol);
    free(mark);
    for(i=0; i<dim_file; i++) {
        free(matr[i]);
    }
    free(matr);

    clear();
}

// Shorter prefixes are still walked through (they are the root of the longer
// strings) but only the ones reaching min_len are written to the wordlist.
static void arrangements(FILE *fp_out, int pos, char **tok, int *sol, int *mark, int n_tok, int min_len, int max_len, unsigned long long tot) {
    int i;

    if(pos >= max_len) {
        return;
    }

    for(i=0; i<n_tok; i++){
        if(mark != NULL){
            if(mark[i] <= 0) {
                continue;
            }
            mark[i]--;
        }

        sol[pos] = i;
        if(pos + 1 >= min_len){
            print_sol(fp_out, sol, tok, pos + 1);
            print_count(++count, tot);
        }
        arrangements(fp_out, pos + 1, tok, sol, mark, n_tok, min_len, max_len, tot);

        if(mark != NULL) {
            mark[i]++;
        }
    }
}

static void print_sol(FILE *fp_out, const int *sol, char **tok, int dim) {
    for(int t=0; t<dim; t++) {
        fprintf(fp_out, "%s", tok[sol[t]]);
    }
    fprintf(fp_out, "\n");
}

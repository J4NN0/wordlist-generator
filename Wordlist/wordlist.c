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
static int count=0;

/* Numbers [2] */
static void arrangements_rep_numb(FILE *fp_out, int pos, int *val, int *sol, int n, int tot);
static void print_sol_numb(FILE *fp_out, int *sol, int dim);
/* Strings and Numbers [3] */
static void arrangements_str(FILE *fp_out, int pos, char **str, int *sol, int *mark, int dim, long int tot);
static void print_sol_str(FILE *fp_out, int *sol, char **str, int dim);
/* Alphabet and Guided [1 & 4] */
static void arrangements_rep_alphabet(FILE *fp_out, int pos, char *val, int *sol, int n, int dim, long int tot);
static void print_sol_alphabet(FILE *fp_out, int *sol, char *val, int dim);
/* File [5] */
static void arrangements_file(FILE *fp_out, int pos, char **matr, int *sol, int *mark, int dim, long int tot);
static void print_sol_file(FILE *fp_out, int *sol, char **matr, int dim);
/* Dictionary [6] */
static void create_dic(FILE *fp_out, int start, char *str, char *sol, int n, long int tot);
static char get_dic(char ch);

/// === Alphabet ===
void wl_alphabet() {
    FILE *fp=NULL;
    char *v=NULL, oper=' ';
    int *sol=NULL, size=0;
    long int tot;

    explication();
    fflush(stdin);

    while(oper!='1' && oper!='2' && oper!='3'){
        fprintf(stdout, "[1] Uppercase;\n"
                        "[2] Lowercase;\n"
                        "[3] Both (1 and 2);\n"
                        ">> ");
        fscanf(stdin, "%1s", &oper);
        switch(oper){
            case '1':
                v = init_alphabet_uppercase(v);
                sol = manage_size(&size, sol);
                fp = manage_file();
                tot = tot_arrangements_rep(size, A);
                arrangements_rep_alphabet(fp, 0, v, sol, size, A, tot);
                break;
            case '2':
                v = init_alphabet_lowercase(v);
                sol = manage_size(&size, sol);
                fp = manage_file();
                tot = tot_arrangements_rep(size, A);
                arrangements_rep_alphabet(fp, 0, v, sol, size, A, tot);
                break;
            case '3':
                v = init_alphabet_uppercase_and_lowercase(v);
                sol = manage_size(&size, sol);
                fp = manage_file();
                tot = tot_arrangements_rep(size, A + A);
                arrangements_rep_alphabet(fp, 0, v, sol, size, A + A, tot);
                break;
            default:
                fprintf(stdout, "Come on please, seriously.\n");
                pause();
                clear();
                break;
        }
    }

    end(size);
    count = 0;

    fclose(fp);
    free(v);
    free(sol);
}

static void arrangements_rep_alphabet(FILE *fp_out, int pos, char *val, int *sol, int n, int dim, long int tot) {
    if(pos >= n) {
        return;
    }

    for(int i=0; i<dim; i++){
        sol[pos] = i;
        print_sol_alphabet(fp_out, sol, val, pos + 1);
        print_count(++count, tot);
        arrangements_rep_alphabet(fp_out, pos + 1, val, sol, n, dim, tot);
    }
}

static void print_sol_alphabet(FILE *fp_out, int *sol, char *val, int dim) {
    for(int t=0; t<dim; t++) {
        fprintf(fp_out, "%c", val[sol[t]]);
    }
    fprintf(fp_out, "\n");
}

/// === Number ===
void wl_numbers() {
    FILE *fp=NULL;
    int *v=NULL, *sol=NULL;
    int size=0;
    long int tot;

    explication();
    fflush(stdin);

    v = malloc(N*sizeof(int));
    if(v == NULL) {
        err_pointer(-3);
    }

    v = init_numbers(v);

    sol = manage_size(&size, sol);
    if(sol == NULL) {
        err_pointer(-4);
    }

    fp = manage_file();

    tot = tot_arrangements_rep(size, N);
    arrangements_rep_numb(fp, 0, v, sol, size, tot);

    end(size);
    count = 0;

    fclose(fp);
    free(v);
    free(sol);
}

static void arrangements_rep_numb(FILE *fp_out, int pos, int *val, int *sol, int n, int tot) {
    int i;

    if(pos >= n) {
        return;
    }

    for(i=0; i<N; i++){
        sol[pos] = val[i];
        print_sol_numb(fp_out, sol, pos + 1);
        print_count(++count, tot);
        arrangements_rep_numb(fp_out, pos + 1, val, sol, n, tot);
    }
}

static void print_sol_numb(FILE *fp_out, int *sol, int dim)
{
    int t=0;

    for(t=0; t<dim; t++)
        fprintf(fp_out, "%d", sol[t]);
    fprintf(fp_out, "\n");
}

/// === Str & Numb ===
void wl_str() {
    FILE *fp=NULL;
    int *sol=NULL, *mark=NULL;
    char **str=NULL, trash;
    int i, dim=0, n_rip, ok=0;
    long int tot;

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

    arrangements_str(fp, 0, str, sol, mark, dim * n_rip, tot);
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

static void arrangements_str(FILE *fp_out, int pos, char **str, int *sol, int *mark, int dim, long int tot) {
    int i;

    if(pos >= dim) {
        return;
    }

    for(i=0; i<dim; i++){
        if(mark[i]>0){
            mark[i]--;
            sol[pos] = i;
            print_sol_str(fp_out, sol, str, pos + 1);
            print_count(++count, tot);
            arrangements_str(fp_out, pos + 1, str, sol, mark, dim, tot);
            mark[i]++;
        }
    }
}

static void print_sol_str(FILE *fp_out, int *sol, char **str, int dim) {
    for(int t=0; t<dim; t++) {
        fprintf(fp_out, "%s", str[sol[t]]);
    }
    fprintf(fp_out, "\n");
}

/// === Guided ===
void wl_guided() {
    FILE *fp=NULL;
    char *v=NULL;
    char oper=' ';
    int *sol=NULL, size=0, dim=0;
    long int tot;

    explication();
    fflush(stdin);

    // Alphabet
    while(oper!='1' && oper!='2'){
        fprintf(stdout, "Do you want insert some or all alphabet characters?\n"
                        "[1] Yes - [2] No\n"
                        ">> ");
        fscanf(stdin, "%1s", &oper);
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
        fscanf(stdin, "%1s", &oper);
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
        fscanf(stdin, "%1s", &oper);
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

    sol = manage_size(&size, sol);

    fp = manage_file();

    tot = tot_arrangements_rep(size, dim);
    arrangements_rep_alphabet(fp, 0, v, sol, size, dim, tot);

    end(size);
    count = 0;

    fclose(fp);
    free(v);
    free(sol);
}

/// === Dictionary ===
void wl_dictionary() {
    FILE *fp=NULL;
    char str[S], *sol=NULL;
    long int tot;

    explication();
    fflush(stdin);

    fprintf(stdout, "Insert string to modify for dictionary attack: ");
    fscanf(stdin, "%49s", str);

    fp = manage_file();
    tot = tot_dic(str);

    sol = malloc((strlen(str)+1)*sizeof(char));
    strcpy(sol, str);
    if(sol == NULL) {
        err_pointer(-24);
    }

    create_dic(fp, 0, str, sol, strlen(str), tot);

    end(strlen(str));
    count = 0;

    fclose(fp);
    free(sol);
}

static void create_dic(FILE *fp_out, int start, char *str, char *sol, int n, long int tot) {
    int i;
    char dic=' ';

    if(i >= n) {
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

static char get_dic(char ch) {
    char dic=' ';

    switch(ch){
        case 'o':
            dic = 0 + '0';
            break;
        case 'i':
            dic = 1 + '0';
            break;
        case 'e':
            dic = 3 + '0';
            break;
        case 'a':
            dic = 4 + '0';
            break;
        case 's':
            dic = 5 + '0';
            break;
        case 'g':
            dic = 6 + '0';
            break;
        case 't':
            dic = 7 + '0';
            break;
        case 'b':
            dic = 8 + '0';
            break;
        case 'O':
            dic = 0 + '0';
            break;
        case 'I':
            dic = 1 + '0';
            break;
        case 'E':
            dic = 3 + '0';
            break;
        case 'A':
            dic = 4 + '0';
            break;
        case 'S':
            dic = 5 + '0';
            break;
        case 'G':
            dic = 6 + '0';
            break;
        case 'T':
            dic = 7 + '0';
            break;
        case 'B':
            dic = 8 + '0';
            break;
        default:
            dic=' ';
            break;
    }

    return dic;
}

/// === File ===
void wl_file() {
    FILE *fp;
    char filename[FILENAME_MAX];
    char str[S], **matr=NULL;
    int *mark=NULL, *sol=NULL;
    int i=0, ok=0, dim_file=0;
    long int tot=0;

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
        if(i==dim_file-1){
            matr = realloc(matr, (2*dim_file)*sizeof(char));
            if(matr == NULL) {
                err_pointer(-21);
            }
        }
    }
    dim_file = i;
    fclose(fp);

    sol = malloc(dim_file*sizeof(int));
    if(sol == NULL) {
        err_pointer(-22);
    }

    mark = calloc(dim_file, sizeof(int));
    if(mark == NULL) {
        err_pointer(-23);
    }

    tot = tot_arrangements(dim_file, dim_file);
    fp = manage_file();
    arrangements_file(fp, 0, matr, sol, mark, dim_file, tot);
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

    clear();
}

void arrangements_file(FILE *fp_out, int pos, char **matr, int *sol, int *mark, int dim, long int tot) {
    int i;

    if(pos >= dim) {
        return;
    }

    for(i=0; i<dim; i++){
        if(mark[i]==0){
            mark[i]=1;
            sol[pos] = i;
            print_sol_file(fp_out, sol, matr, pos + 1);
            print_count(++count, tot);
            arrangements_file(fp_out, pos + 1, matr, sol, mark, dim, tot);
            mark[i]=0;
        }
    }
}

void print_sol_file(FILE *fp_out, int *sol, char **matr, int dim) {
    for(int t=0; t<dim; t++) {
        fprintf(fp_out, "%s", matr[sol[t]]);
    }
    fprintf(fp_out, "\n");
}

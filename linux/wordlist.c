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
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <signal.h>

#include "wordlist.h"
#include "more.h"

#define A 26 //Size alphabet
#define N 10 //Numbers 0 to 9
#define S 50 //Max string size
#define X 26 //Special characters

/* Signal */
void sigHand(int signo);

/*more.h*/
void info();

/* Global var */
static int count=0;

/* Alpha [1] */
static char *init_up(char *v); //_[5]
static char *init_low(char *v); //_[5]
static char *init_both(char *v); //_[5]
/* Numb [2] */
static int *init_numb(int *v);
static void disprip_numb(FILE *fp_out, int pos, int *val, int *sol, int n, int tot);
static void printSol_numb(FILE *fp_out, int *sol, int dim);
/* Custom [3] */
static char *init_custom(char *v, int *dim);
//Alpha, Numb and Custom [1 & 2 & 3]:
static int *manage_size(int *size, int *sol);
/* Str and Numb [4] */
static char **init_str(char **str, int *dim);
static void disp_str(FILE *fp_out, int pos, char **str, int *sol, int *mark, int dim, long int tot);
static void printstr(FILE *fp_out, int *sol, char **str, int dim);
/* Guided [5] */
static char *insertalpha(char *v, int *dim);
static char *delalpha(char *del, int dim, int *dim_tmp);
static int control_saved(char *saved, int dimsaved, int pos, char ch);
static char *bubblesort(char *v, int dim);
static char *convUp(char *v, int dim);
static char *convLow(char *v, int dim);
static char *insertnumb(char *v, int *dim);
static char *insertspl(char *v, int *dim);
//Alpha and Custom [1 & 3 & 5]:
static void disprip_char(FILE *fp_out, int pos, char *val, int *sol, int n, int dim, long int tot);
static void printSol(FILE *fp_out, int *sol, char *val, int dim);
/* File [6] */
static void strcpy_format(char str1[], char str2[]);
static void disp_ffile(FILE *fp_out, int pos, char **matr, int *sol, int *mark, int dim, long int tot);
static void print_ffile(FILE *fp_out, int *sol, char **matr, int dim);
/* All */
void intro();
static void explication(); //Signal handler inside
static FILE *manage_file();
static void pause();
static void errPointer(int err);
static void printcount(int count, long int tot);
static void end(int size);
/* Combinatorics */
static long int totDispRip(int size, int base); //[1 & 2 & 3]
static long int totDisp(int n, int k); //[4]
static int factorial(int num); //_[4]

///more.h-->
void info()
{
    system("clear");
    fflush(stdin);

    char oper=' ';

    while(oper!='0'){
        fprintf(stdout, "INFO\n\n"
               " [1] WEP - Wired Equivalent Privacy;\n"
               " [2] WPA - Wi-Fi Protected Access;\n"
               " [3] CC - Creative Commons;\n"
               " [4] Wordlist;\n"
               " [5] Developer;\n"
               " [0] Exit;\n\n");
        fprintf(stdout, ">> ");
        fscanf(stdin, "%1s", &oper);
        fflush(stdin);
        switch(oper){
            case '0':
                system("clear");
                break;
            case '1':
                info_wep();
                system("clear");
                break;
            case '2':
                info_wpa();
                system("clear");
                break;
            case '3':
                info_cc();
                system("clear");
                break;
            case '4':
                info_wl();
                system("clear");
            case '5':
                develop();
                system("clear");
            default:
                fprintf(stdout, "Hilarious.\n");
                pause();
                system("clear");
                break;
        }
    }
}

///Alpha-->
void wl_alpha()
{
    FILE *fp=NULL;
    char *v=NULL, oper=' ';
    int *sol=NULL, size =0;
    long int tot=0;

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
                v = init_up(v);
                sol = manage_size(&size, sol);
                fp = manage_file();
                tot = totDispRip(size, A);
                disprip_char(fp, 0, v, sol, size, A, tot);
                break;
            case '2':
                v = init_low(v);
                sol = manage_size(&size, sol);
                fp = manage_file();
                tot = totDispRip(size, A);
                disprip_char(fp, 0, v, sol, size, A, tot);
                break;
            case '3':
                v = init_both(v);
                sol = manage_size(&size, sol);
                fp = manage_file();
                tot = totDispRip(size, A+A);
                disprip_char(fp, 0, v, sol, size, A+A, tot);
                break;
            default:
                fprintf(stdout, "Come on please serious.\n");
                pause();
                system("clear");
                break;
        }
    }

    end(size);

    fclose(fp);
    free(v);
    free(sol);
}

static int *manage_size(int *size, int *sol)
{
    int ok=0;
    char trash;

    while(!ok){
        fprintf(stdout, "\nEnter maximum size string to generate: ");
        fscanf(stdin, "%1s", &trash);
        fflush(stdin);
        if(isdigit(trash))
            ok=1;
    }

    (*size) = trash -'0';
    sol = malloc((*size)*sizeof(int));
    if(sol==NULL)
        errPointer(-2);

    return sol;
}

static char *init_up(char *v)
{
    int i=0;

    v = malloc(A*sizeof(char));
    if(v==NULL)
        errPointer(-1);

    for(i=0; i<A; i++)
        v[i]='A'+i;

    return v;
}

static char *init_low(char *v)
{
    int i=0;

    v = malloc(A*sizeof(char));
    if(v==NULL)
        errPointer(-1);

    for(i=0; i<A; i++)
        v[i]='a'+i;

    return v;
}

static char *init_both(char *v)
{
    int i=0, bck=0;

    v = malloc((A+A)*sizeof(char));
    if(v==NULL)
        errPointer(-1);

    for(i=0; i<A; i++)
        v[i]='A'+i;
    bck = i;

    for(i=0; i<A; i++, bck++)
        v[bck]='a'+i;

    return v;
}

static void disprip_char(FILE *fp_out, int pos, char *val, int *sol, int n, int dim, long int tot)
{
    int i=0;

    if(pos>=n)
        return;

    for(i=0; i<dim; i++){
        sol[pos] = i;
        printSol(fp_out, sol, val, pos+1);
        printcount(++count, tot);
        disprip_char(fp_out, pos+1, val, sol, n, dim, tot);
    }
}

static void printSol(FILE *fp_out, int *sol, char *val, int dim)
{
    int t=0;

    for(t=0; t<dim; t++)
        fprintf(fp_out, "%c", val[sol[t]]);
    fprintf(fp_out, "\n");
}

///Number-->
void wl_numb()
{
    FILE *fp=NULL;
    int *v=NULL, *sol=NULL;
    int size=0;
    long int tot=0;

    explication();
    fflush(stdin);

    v = malloc(N*sizeof(int));
    if(v==NULL)
        errPointer(-3);

    v = init_numb(v);

    sol = manage_size(&size, sol);

    sol = malloc(size*sizeof(int));
    if(sol==NULL)
        errPointer(-4);

    fp = manage_file();

    tot = totDispRip(size, N);
    disprip_numb(fp, 0, v, sol, size, tot);

    end(size);

    fclose(fp);
    free(v);
    free(sol);
}

static int *init_numb(int *v)
{
    int i=0;

    for(i=0; i<N; i++)
        v[i] = i;

    return v;
}

static void disprip_numb(FILE *fp_out, int pos, int *val, int *sol, int n, int tot)
{
    int i=0;

    if(pos>=n)
        return;

    for(i=0; i<N; i++){
        sol[pos] = val[i];
        printSol_numb(fp_out, sol, pos+1);
        printcount(++count, tot);
        disprip_numb(fp_out, pos+1, val, sol, n, tot);
    }
}

static void printSol_numb(FILE *fp_out, int *sol, int dim)
{
    int t=0;

    for(t=0; t<dim; t++)
        fprintf(fp_out, "%d", sol[t]);
    fprintf(fp_out, "\n");
}

///Custom-->
void wl_custom()
{
    FILE *fp=NULL;
    char *v=NULL;
    int *sol=NULL, dim=0, size=0;
    long int tot=0;

    explication();
    fflush(stdin);

    dim = 10; //arbitrary
    v = malloc(dim*sizeof(char));
    if(v==NULL)
        errPointer(-5);

    v = init_custom(v, &dim);

    sol = manage_size(&size, sol);

    fp = manage_file();

    tot = totDispRip(size, dim);
    disprip_char(fp, 0, v, sol, size, dim, tot);

    end(size);

    fclose(fp);
    free(v);
    free(sol);
}

static char *init_custom(char *v, int *dim)
{
    int i=0, bugfix;
    char trash[3];

    fprintf(stdout, "Insert '!quit' when you want to end.\n\n");

    for(i=0; i<(*dim); i++){
        fprintf(stdout, "Insert character %d: ", i+1);
        bugfix = i; //bug fix
        fscanf(stdin, "%3s", trash);

        if((strcmp(trash, "!quit"))==0){
            (*dim) = i;
            return v;
        }

        v[i] = trash[0];

        if(i==(*dim)-1){
            v = realloc(v, (2*(*dim))*sizeof(char));
            if(v==NULL) errPointer(-5);
            (*dim) = 2*(*dim);
        }
    }

    return v;
}

///Str & Numb-->
void wl_str()
{
    FILE *fp=NULL;
    int *sol=NULL, *mark=NULL;
    char **str=NULL, trash;
    int i=0, dim=0, nrip=0, ok=0;
    long int tot=0;

    explication();
    fflush(stdin);

    str = init_str(str, &dim);

    while(!ok){
        fprintf(stdout, "\nHow much time [1-9] every strings must be repeated? ");
        trash=getc(stdin);
        fflush(stdin);
        if(isdigit(trash) && trash!='0'){
            nrip = trash-'0';
            if(nrip>0)
                ok=1;
        }
        else
            fprintf(stderr, "Error. Try again.\n");
    }

    mark = malloc(dim*sizeof(int));
    if(mark==NULL) errPointer(-10);
    for(i=0; i<dim; i++)
        mark[i]=nrip;

    sol = malloc((dim*nrip)*sizeof(int));
    if(sol==NULL)
        errPointer(-9);

    fp = manage_file();

    tot = totDisp(dim*nrip, dim*nrip);

    disp_str(fp, 0, str, sol, mark, dim*nrip, tot);
    fprintf(stdout, "\nAll the possible strings generated!\n");
    count=0;
    fprintf(stdout, "Use it wisely!\n");

    pause();

    fclose(fp);
    free(sol);
    free(mark);
    //free 2d:
    for(i=0; i<dim; i++)
        free(str[i]);
    free(str);

    system("clear");
}

static char **init_str(char **str, int *dim)
{
    int i=0;
    char str_tmp[S];

    (*dim)=10; //arbitrary;
    str = malloc((*dim)*sizeof(char*));
    if(str==NULL)
        errPointer(-7);

    fprintf(stdout, "\nInsert '!quit' when you want to end.\n\n");
    for(i=0; i<(*dim); i++){
        fprintf(stdout, "String n %d: ", i+1);
        fscanf(stdin, "%49s", str_tmp);

        if((strcmp(str_tmp, "!quit"))==0){
            (*dim) = i;
            break;
        }

        str[i] = malloc((strlen(str_tmp)+1)*sizeof(char));
        if(str[i]==NULL) errPointer(i);
        strcpy(str[i], str_tmp);

        if(i==(*dim)-1){
            str = realloc(str, (2*(*dim))*sizeof(char));
            if(str==NULL) errPointer(-7);
            (*dim) = 2*(*dim);
        }
    }

    fflush(stdin);

    return str;
}

static void disp_str(FILE *fp_out, int pos, char **str, int *sol, int *mark, int dim, long int tot)
{
    int i=0;

    if(pos>=dim)
        return;

    for(i=0; i<dim; i++){
        if(mark[i]>0){
            mark[i]--;
            sol[pos] = i;
            printstr(fp_out, sol, str, pos+1);
            printcount(++count, tot);
            disp_str(fp_out, pos+1, str, sol, mark, dim, tot);
            mark[i]++;
        }
    }
}

static void printstr(FILE *fp_out, int *sol, char **str, int dim)
{
    int t=0;

    for(t=0; t<dim; t++)
        fprintf(fp_out, "%s", str[sol[t]]);
    fprintf(fp_out, "\n");
}

///Guided-->
void wl_guided()
{
    FILE *fp=NULL;
    char *v=NULL;
    char oper=' ';
    int *sol=NULL, size=0, dim=0;
    long int tot=0;

    explication();
    fflush(stdin);

    //Alphabet:
    while(oper!='1' && oper!='2'){
        fprintf(stdout, "Do you want insert some (or all) alphabet characters?\n"
                "[1] Yes - [2] No\n"
                ">> ");
        fscanf(stdin, "%1s", &oper);
        switch(oper){
            case '1':
                v = insertalpha(v, &dim);
                break;
            case '2':
                break;
            default:
                fprintf(stdout, "Are you confused?\n");
                pause();
                system("clear");
                break;
        }
    }
    oper=' ';

    //Number:
    while(oper!='1' && oper!='2'){
        fprintf(stdout, "\nDo you want insert some number?\n"
                "[1] Yes - [2] No\n"
                ">> ");
        fscanf(stdin, "%1s", &oper);
        switch(oper){
            case '1':
                v = insertnumb(v, &dim);
                break;
            case '2':
                break;
            default:
                fprintf(stdout, "Are you confused?\n");
                pause();
                system("clear");
                break;
        }
    }
    oper=' ';

    //Special character:
    while(oper!='1' && oper!='2'){
        fprintf(stdout, "\nDo you want insert some (or all) special characters?\n"
                "[1] Yes - [2] No\n"
                ">> ");
        fscanf(stdin, "%1s", &oper);
        switch(oper){
            case '1':
                v = insertspl(v, &dim);
                break;
            case '2':
                break;
            default:
                fprintf(stdout, "Are you confused?\n");
                pause();
                system("clear");
                break;
            }
    }

    sol = manage_size(&size, sol);

    fp = manage_file();

    tot = totDispRip(size, dim);
    disprip_char(fp, 0, v, sol, size, dim, tot);

    end(size);

    fclose(fp);
    free(v);
    free(sol);
}

static char *insertalpha(char *v, int *dim)
{
    int UoL=0; //UoL=Upper_case or Lower_case
    char *del=NULL, oper=' ';
    int i=0, bck=0, dim_tmp=0;

    //Set UoL:
    while(oper!='1' && oper!='2' && oper!='3'){
        fprintf(stdout, "\n[1] Uppercase;\n"
                "[2] Lowercase;\n"
                "[3] Both (1 and 2);\n"
                ">> ");
        fscanf(stdin, "%1s", &oper);
        switch(oper){
            case '1'://Uppercase
                UoL = 1;
                break;
            case '2'://Lowercase
                UoL = 2;
                break;
            case '3':
                UoL = 3;//Both
                break;
            default:
                fprintf(stdout, "Come on please serious.\n");
                pause();
                system("clear");
                break;
        }
    }
    oper=' ';

    while(oper!='1' && oper!='2'){
        fprintf(stdout, "\nDo you want insert all alphabet or not?\n"
                "[1] All - [2] Some\n"
                ">> ");
        fscanf(stdin, "%1s", &oper);
        switch(oper){
            case '1': //All alphabet
                if(UoL==1){ //Uppercase (all)
                    v = init_up(v);
                    (*dim) = A;
                }
                if(UoL==2){ //Lowercase (all)
                    v = init_low(v);
                    (*dim) = A;
                }
                if(UoL==3){ //Both (all)
                    v = init_both(v);
                    (*dim) = A+A;
                }
                break;
            case '2': //Some characters of alphabet
                del = delalpha(del, A, &dim_tmp);
                if(UoL==1){ //Uppercase (some)
                    del = convUp(del, dim_tmp);
                    v = malloc((A-dim_tmp)*sizeof(char));
                    if(v==NULL) errPointer(-12);
                    for(i=0, bck=0; i<A-dim_tmp; i++){
                        if(i<dim_tmp){
                            if(del[i]!='A'+i){
                                v[bck] = 'A'+i;
                                bck++;
                            }
                        }
                        else{
                            v[bck] = 'A'+i;
                            bck++;
                        }
                    }
                    (*dim) = A-dim_tmp;
                }
                if(UoL==2){ //Lowercase (some)
                    del = convLow(del, dim_tmp);
                    v = malloc((A-dim_tmp)*sizeof(char));
                    if(v==NULL) errPointer(-13);
                    for(i=0, bck=0; i<A-dim_tmp; i++){
                        if(i<dim_tmp){
                            if(del[i]!='a'+i){
                                v[bck] = 'a'+i;
                                bck++;
                            }
                        }
                        else{
                            v[bck] = 'a'+i;
                            bck++;
                        }
                    }
                    (*dim) = A-dim_tmp;
                }
                if(UoL==3){ //Both (some)
                    v = malloc(((A+A)-dim_tmp)*sizeof(char));
                    if(v==NULL) errPointer(-14);
                    for(i=0, bck=0; i<A-dim_tmp; i++){
                        if(i<dim_tmp){
                            if(del[i]!='A'+i){
                                v[bck] = 'A'+i;
                                bck++;
                            }
                        }
                        else{
                            v[bck] = 'A'+i;
                            bck++;
                        }
                    }
                    del = convLow(del, dim_tmp);
                    for(i=0; i<A-dim_tmp; i++){
                        if(i<dim_tmp){
                            if(del[i]!='a'+i){
                                v[bck] = 'a'+i;
                                bck++;
                            }
                        }
                        else{
                            v[bck] = 'a'+i;
                            bck++;
                        }
                    }
                    (*dim) = (A+A)-dim_tmp;
                }
                break;
            default:
                fprintf(stdout, "Not supported.\n");
                pause();
                system("clear");
                break;
        }
    }

    return v;
}

static char *delalpha(char *del, int dim, int *dim_tmp)
{
    int i=0, pos=0, dimsaved=0;
    char *saved=NULL, trash;

    fprintf(stdout, "Insert characters you want to delete.\n"
            "Insert '0' (zero) to end.\n\n");

    del = malloc(dim*sizeof(char));
    if(del==NULL)
        errPointer(-11);

    saved = malloc(dim*sizeof(char));
    if(saved==NULL)
        errPointer(-22);

    for(i=0; i<dim; i++){
        fprintf(stdout, "Insert characters %d: ", i+1);
        fscanf(stdin, "%1s", &trash);
        if(trash=='0'){
            (*dim_tmp) = i;
            break;
        }
        else{
            if(control_saved(saved, dimsaved, pos, trash)){
                del[pos]=trash;
                pos++;
                dimsaved++;
            }
            else
                fprintf(stdout, "Characters %c just removed.\n", trash);
        }
    }

    del = bubblesort(del, (*dim_tmp));

    free(saved);

    return del;
}

static int control_saved(char *saved, int dimsaved, int pos, char ch)
{
    int i=0, flag=0;

    for(i=0; i<dimsaved && flag==0; i++)
        if(ch==saved[i])
            flag=1;

    if(flag==0){
        saved[pos]=ch;
        return 1;
    }

    return 0;
}

static char *bubblesort(char *v, int dim)
{
    int i=0, j=0;
    int val=0;

    for(i=0; i<dim-1; i++) {
        for(j=0; j<dim-1-i; j++) {
            if(v[j]>v[j+1]) {
               val = v[j];
               v[j] = v[j+1];
               v[j+1] = val;
            }
        }
    }

    return v;
}

static char *convUp(char *v, int dim)
{
    int i=0;

    for(i=0; i<dim; i++)
        v[i] = toupper(v[i]);

    return v;
}

static char *convLow(char *v, int dim)
{
    int i=0;

    for(i=0; i<dim; i++)
        v[i] = tolower(v[i]);

    return v;
}

static char *insertnumb(char *v, int *dim)
{
    int *vnumb=NULL, bugfix;
    char trash;
    int i=0, dim_tmp=0, tmp=0;

    dim_tmp=15; //arbitrary
    vnumb = malloc(dim_tmp*sizeof(int));
    if(vnumb==NULL)
        errPointer(-15);

    fprintf(stdout, "\nInsert 'q' when you want to end.\n\n");

    for(i=0; i<dim_tmp; i++){
        fprintf(stdout, "Insert number %d: ", i+1);
        bugfix = dim_tmp; //bug fix
        fscanf(stdin, "%1s", &trash);

        if(trash=='q'){
            dim_tmp = i;
            break;
        }

        if(isdigit(trash)){
            vnumb[i] = trash-'0';
            if(i==dim_tmp-1){
                vnumb = realloc(vnumb, (2*dim_tmp)*sizeof(int));
                if(vnumb==NULL) errPointer(-16);
                dim_tmp = dim_tmp*2;
            }
        }
        else{
            printf("Error: %c is not a number. Try again.\n", trash);
            i--;
        }
    }

    v = realloc(v, ((*dim)+dim_tmp)*sizeof(char));
    if(v==NULL)
        errPointer(-17);

    tmp = (*dim);
    (*dim) = (*dim)+dim_tmp;

    for(i=0; i<dim_tmp; i++, tmp++)
        v[tmp] = vnumb[i]+'0';

    return v;
}

static char *insertspl(char *v, int *dim)
{
    char spl[X] = {'"', '#', '$', '%', '&', '(', ')', '*', '+', ',', '-', '.', '/',
                  ':', ';', '<', '>', '=', '?', '@', '[', ']', '^', '_', '`', '~'};
                  //Missing: '', '§', '|', '÷', '\', ''';
    int i=0, j=0, cnt=0, dimsaved=0, pos=0, flag=0, tmp=0, tmpX=X;
    int del[X]={-1};
    char *saved=NULL, trash;

    saved = malloc(X*sizeof(char));
    if(saved==NULL)
        errPointer(-22);

    for(i=0; i<X; i++)
        fprintf(stdout, "%d:%c  ", i, spl[i]);

    fprintf(stdout, "\n\nInsert the character's number you want to delete.\n\n");
    fprintf(stdout, "\nInsert 'q' when you want to end.\n\n");

    for(i=0; i<X; i++){
        fprintf(stdout, "Remove n %d: ", i+1);
        fscanf(stdin, "%1s", &trash);

        if(trash=='q')
            break;

        if(isdigit(trash)){
            if(control_saved(saved, dimsaved, pos, trash)){
                del[pos] = trash-'0';
                pos++;
                dimsaved++;
                cnt++;
            }
            else
                fprintf(stdout, "Characters %c just removed.\n", trash);
        }
        else{
            fprintf(stdout, "Error: %c is not a number. Try again.\n", trash);
            i--;
        }
    }

    v = realloc(v, ((*dim)+(tmpX-cnt))*sizeof(char));
    if(v==NULL)
        errPointer(-18);

    tmp = (*dim);
    (*dim) = (*dim)+(tmpX-cnt);

    for(i=0; i<X; i++){
        flag=0;
        for(j=0; j<cnt && flag==0; j++)
            if(i==del[j])
                flag=1;
        if(flag==0){
            v[tmp] = spl[i];
            tmp++;
        }
    }

    free(saved);

    return v;
}

///File-->
void wl_file()
{
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
            pause();
            system("clear");
        }
        else
            ok=1;
    }

    fprintf(stdout, "\n");

    dim_file = 20; //arbitrary;
    matr = malloc(dim_file*sizeof(char*));
    if(matr==NULL)
        errPointer(-19);

    fprintf(stdout, "Reading file %s...\n", filename);
    while(fgets(str, S, fp)!=NULL){
        matr[i] = malloc((strlen(str)+1)*sizeof(char));
        if(matr[i]==NULL) errPointer(-20);
        strcpy_format(matr[i], str);

        i++;
        if(i==dim_file-1){
            matr = realloc(matr, (2*dim_file)*sizeof(char));
            if(matr==NULL) errPointer(-21);
        }
    }
    dim_file = i;
    fclose(fp);

    sol = malloc(dim_file*sizeof(int));
    if(sol==NULL)
        errPointer(-22);

    mark = calloc(dim_file, sizeof(int));
    if(mark==NULL)
        errPointer(-23);

    tot = totDisp(dim_file, dim_file);
    fp = manage_file();
    disp_ffile(fp, 0, matr, sol, mark, dim_file, tot);
    fprintf(stdout, "\nAll the possible strings generated!\n");
    count=0;
    fprintf(stdout, "Use it wisely!\n");

    pause();

    fclose(fp);
    free(sol);
    free(mark);
    for(i=0; i<dim_file; i++)
        free(matr[i]);

    system("clear");
}

static void strcpy_format(char str1[], char str2[])
{
    int i=0, dim=0;

    dim = strlen(str2);

    for(i=dim-1; i<dim; i++)
        if(str2[i]=='\n')
            str2[i]='\0';

    strcpy(str1, str2);
}

void disp_ffile(FILE *fp_out, int pos, char **matr, int *sol, int *mark, int dim, long int tot)
{
    int i=0;

    if(pos>=dim)
        return;

    for(i=0; i<dim; i++){
        if(mark[i]==0){
            mark[i]=1;
            sol[pos] = i;
            print_ffile(fp_out, sol, matr, pos+1);
            printcount(++count, tot);
            disp_ffile(fp_out, pos+1, matr, sol, mark, dim, tot);
            mark[i]=0;
        }
    }
}

void print_ffile(FILE *fp_out, int *sol, char **matr, int dim)
{
    int t=0;

    for(t=0; t<dim; t++)
        fprintf(fp_out, "%s", matr[sol[t]]);
    fprintf(fp_out, "\n");
}

///All-->
void intro()
{
    fprintf(stdout, "This program is free software: you can redistribute it and/or modify\n"
                    "it under the terms of the GNU General Public License as published by\n"
                    "the Free Software Foundation, either version 3 of the License, or\n"
                    "(at your option) any later version.\n\n"

                    "This program is distributed in the hope that it will be useful,\n"
                    "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
                    "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
                    "GNU General Public License for more details.\n\n"

                    "You should have received a copy of the GNU General Public License\n"
                    "along with this program.  If not, see <http://www.gnu.org/licenses/>.\n\n");

    fprintf(stdout, "Developed by Nindo.\n\n");

    pause();
    system("clear");
}

void explication()
{
    system("clear");

    fprintf(stdout, "\5 Remember:\n\n"
           "\4 Creating a wordlist of large size, probably it will need some hours!\n"
           "\4 You can put the extensions when insert the filename (.txt, .dat, etc..).\n"
           "\4 The maximum string size can be 50.\n");

    fprintf(stdout, "\n");
    pause();
    system("clear");

    //Signal handler
    if(signal(SIGINT, sigHand)==SIG_ERR || signal(SIGABRT, sigHand)==SIG_ERR || signal(SIGTERM, sigHand)==SIG_ERR){
        fprintf(stderr, "An error occurred while setting a signal handler.\n");
        pause();
        exit(EXIT_FAILURE);
    }
}

FILE *manage_file()
{
    int flag=0;
    char name[S], oper=' ';
    FILE *fp=NULL;

    while(flag==0){
        fprintf(stdout, "\nEnter file name to save the wordlist: ");
        scanf("%49s", name);
        fp = fopen(name, "r");
        if(fp==NULL){
            fprintf(stdout, "No such file with this name. Creating file %s.\n", name);
            fp = fopen(name, "w");
            flag=1;
        }
        else{
            fprintf(stdout, "\nThere is a file with the same name.\n"
                   "Do you want to (1)overwrite or (2)create a new one? ");
            scanf("%1s", &oper);
            switch(oper){
                case '1':
                    fp = fopen(name, "w");
                    flag=1;
                    break;
                case '2':
                    break;
                default:
                    fprintf(stdout, "Are you kidding me? Come on please serious.\n");
                    pause();
                    system("clear");
                    break;
            }
        }
    }

    fprintf(stdout, "\n");

    return fp;
}

void pause()
{
    fflush(stdin);
    fprintf(stdout, "Press enter to continue...");
    getc(stdin);
    fflush(stdin);
}

void errPointer(int err)
{
    fprintf(stderr, "Can't allocate memory.\nError %d\n", err);
    pause();
    exit(EXIT_FAILURE);
}

void printcount(int count, long int tot)
{
    fprintf(stdout, "Wait: %d to %li\r", count, tot);
}

void end(int size)
{
    fprintf(stdout, "\nAll the possible strings of size %d generated!\n", size);
    count=0;
    fprintf(stdout, "Use it wisely!\n\n");

    pause();

    fprintf(stdout, "Memory deallocation...\n");

    system("clear");
}

///Signal-->
void sigHand(int signo)
{
    //Interrupt:
    if(signo==SIGINT){
        fprintf(stderr, "\nReceived signal %d (Interrupt).\n"
                "Interactive attention request sent to the program.\n", signo);
        fprintf(stderr, "Impossible to deallocate memory.\n"
                "Possible Memory Leak.\n\n");
        fprintf(stderr, "Exiting...\n");
        exit(EXIT_FAILURE);
    }

    //Abort:
    if(signo==SIGABRT){
        fprintf(stderr, "\nReceived signal %d (Abort).\n"
                "Abnormal termination.", signo);
        fprintf(stderr, "Impossible to deallocate memory.\n"
                "Possible Memory Leak.\n\n");
        fprintf(stderr, "Exiting...\n");
        exit(EXIT_FAILURE);
    }

    //Terminate:
    if(signo==SIGTERM){
        fprintf(stderr, "\nReceived signal %d (Terminate).\n"
                "Termination request sent to the program.\n", signo);
        fprintf(stderr, "Impossible to deallocate memory.\n"
                "Possible Memory Leak.\n\n");
        fprintf(stderr, "Exiting...\n");
        exit(EXIT_FAILURE);
    }
}

///Combinatorics-->
long int totDispRip(int size, int base)
{
    int i=0, j=0;
    long int tot=0, tmp=1;

    for(i=1; i<=size; i++){
        for(j=1; j<=i; j++){
            tmp = (long int) base*tmp;
        }
        tot += tmp;
        tmp=1;
    }

    if(tot<=0) //overflow
        return INT_MAX;
    else
        return tot;
}

static long int totDisp(int n, int k)
{
    int i=0, fact_n=0, fact_k=0;
    long int tot=0;

    fact_n = factorial(n);

    for(i=0; i<n; i++){
        fact_k = factorial(n-k);
        tot += (long int) (fact_n/fact_k);
        k--;
    }

    return tot;
}

static int factorial(int num)
{
    int i=0, fact=num;

    if(num==0)
        return 1;

    for(i=1; i<num; i++)
        fact = fact*i;

    return fact;
}

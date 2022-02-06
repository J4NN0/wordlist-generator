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
#include <limits.h>
#include <signal.h>
#include "util.h"
#include "../../System/system.h"

/* Signal */
static void sig_hand(int signo);

/* Guided [4] */
static int control_saved(char *saved, int dim_saved, int pos, char ch);
static char *bubble_sort(char *v, int dim);
static char *conv_to_uppercase(char *v, int dim);
static char *conv_to_lowercase(char *v, int dim);

/* All */
static int factorial(int num);

/// Alphabet [1]
char *init_alphabet_uppercase(char *v) {
    v = malloc(A*sizeof(char));
    if(v == NULL) {
        err_pointer(-1);
    }

    for(int i=0; i<A; i++) {
        v[i] = 'A' + i;
    }

    return v;
}

char *init_alphabet_lowercase(char *v) {
    v = malloc(A*sizeof(char));
    if(v == NULL) {
        err_pointer(-1);
    }

    for(int i=0; i<A; i++) {
        v[i] = 'a' + i;
    }

    return v;
}

char *init_alphabet_uppercase_and_lowercase(char *v) {
    int i, bck;

    v = malloc((A+A)*sizeof(char));
    if(v == NULL) {
        err_pointer(-1);
    }

    for(i=0; i<A; i++) {
        v[i] = 'A' + i;
    }
    bck = i;

    for(i=0; i<A; i++, bck++) {
        v[bck] = 'a' + i;
    }

    return v;
}

/// Numbers [2]
int *init_numbers(int *v) {
    for(int i=0; i<N; i++) {
        v[i] = i;
    }

    return v;
}

/// Alphabet and Numbers [1 & 2]:
int *manage_size(int *size, int *sol) {
    int ok=0;
    char tmp_size_char;

    while(!ok){
        fprintf(stdout, "\nEnter maximum size string to generate: ");
        fscanf(stdin, "%1s", &tmp_size_char);
        fflush(stdin);
        if(isdigit(tmp_size_char)) {
            ok=1;
        }
    }

    (*size) = tmp_size_char - '0';
    sol = malloc((*size)*sizeof(int));
    if(sol == NULL) {
        err_pointer(-2);
    }

    return sol;
}

/// Str (Strings and Numbers) [3]
char **init_str(char **str, int *dim) {
    int i;
    char str_tmp[S];

    (*dim)=10; // arbitrary;
    str = malloc((*dim)*sizeof(char*));
    if(str==NULL) {
        err_pointer(-7);
    }

    fprintf(stdout, "\nInsert '!quit' when you want to end.\n\n");
    for(i=0; i<(*dim); i++){
        fprintf(stdout, "String n %d: ", i+1);
        fscanf(stdin, "%49s", str_tmp);

        if((strcmp(str_tmp, "!quit"))==0){
            (*dim) = i;
            break;
        }

        str[i] = malloc((strlen(str_tmp)+1)*sizeof(char));
        if(str[i] == NULL){
            err_pointer(i);
        }
        strcpy(str[i], str_tmp);

        if(i==(*dim)-1){
            str = realloc(str, (2*(*dim))*sizeof(char));
            if(str == NULL){
                err_pointer(-7);
            }
            (*dim) = 2*(*dim);
        }
    }

    fflush(stdin);

    return str;
}

/// Guided [4]
char *insert_alphabet_chars(char *v, int *dim) {
    int up_low_case=0;
    char *del=NULL, oper=' ';
    int i, bck, dim_tmp=0;

    //Set up_low_case:
    while(oper!='1' && oper!='2' && oper!='3'){
        fprintf(stdout, "\n[1] Uppercase;\n"
                        "[2] Lowercase;\n"
                        "[3] Both (1 and 2);\n"
                        ">> ");
        fscanf(stdin, "%1s", &oper);
        switch(oper){
            case '1': // Uppercase
                up_low_case = 1;
                break;
            case '2': // Lowercase
                up_low_case = 2;
                break;
            case '3': // Both
                up_low_case = 3;
                break;
            default:
                fprintf(stdout, "Come on please, seriously.\n");
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
                if(up_low_case == 1){ //Uppercase (all)
                    v = init_alphabet_uppercase(v);
                    (*dim) = A;
                }
                if(up_low_case == 2){ //Lowercase (all)
                    v = init_alphabet_lowercase(v);
                    (*dim) = A;
                }
                if(up_low_case == 3){ //Both (all)
                    v = init_alphabet_uppercase_and_lowercase(v);
                    (*dim) = A+A;
                }
                break;
            case '2': //Some characters of alphabet
                del = delete_alphabet_chars(del, A, &dim_tmp);
                if(up_low_case == 1){ //Uppercase (some)
                    del = conv_to_uppercase(del, dim_tmp);
                    v = malloc((A-dim_tmp)*sizeof(char));
                    if(v==NULL) err_pointer(-12);
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
                if(up_low_case == 2){ //Lowercase (some)
                    del = conv_to_lowercase(del, dim_tmp);
                    v = malloc((A-dim_tmp)*sizeof(char));
                    if(v==NULL) err_pointer(-13);
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
                if(up_low_case == 3){ //Both (some)
                    v = malloc(((A+A)-dim_tmp)*sizeof(char));
                    if(v==NULL) err_pointer(-14);
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
                    del = conv_to_lowercase(del, dim_tmp);
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
                break;
        }
    }

    return v;
}

char *delete_alphabet_chars(char *del, int dim, int *dim_tmp) {
    int i, pos=0, dim_saved=0;
    char *saved=NULL, trash;

    fprintf(stdout, "Insert characters you want to delete.\n"
                    "Insert '0' (zero) to end.\n\n");

    del = malloc(dim*sizeof(char));
    if(del == NULL) {
        err_pointer(-11);
    }

    saved = malloc(dim*sizeof(char));
    if(saved == NULL) {
        err_pointer(-22);
    }

    for(i=0; i<dim; i++){
        fprintf(stdout, "Insert characters %d: ", i+1);
        fscanf(stdin, "%1s", &trash);
        if(trash=='0'){
            (*dim_tmp) = i;
            break;
        }
        else{
            if(control_saved(saved, dim_saved, pos, trash)){
                del[pos]=trash;
                pos++;
                dim_saved++;
            }
            else {
                fprintf(stdout, "Characters %c just removed.\n", trash);
            }
        }
    }

    del = bubble_sort(del, (*dim_tmp));

    free(saved);

    return del;
}

static int control_saved(char *saved, int dim_saved, int pos, char ch) {
    int flag=0;

    for(int i=0; i<dim_saved && flag==0; i++) {
        if(ch == saved[i]) {
            flag=1;
        }
    }

    if(flag == 0){
        saved[pos] = ch;
        return 1;
    }

    return 0;
}

static char *bubble_sort(char *v, int dim) {
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

static char *conv_to_uppercase(char *v, int dim) {
    for(int i=0; i<dim; i++) {
        v[i] = toupper(v[i]);
    }

    return v;
}

static char *conv_to_lowercase(char *v, int dim) {
    for(int i=0; i<dim; i++) {
        v[i] = tolower(v[i]);
    }

    return v;
}

char *insert_numbers(char *v, int *dim)
{
    int *vnumb=NULL, bugfix;
    char trash;
    int i, dim_tmp, tmp;

    dim_tmp=15; //arbitrary
    vnumb = malloc(dim_tmp*sizeof(int));
    if(vnumb == NULL) {
        err_pointer(-15);
    }

    fprintf(stdout, "\nInsert 'q' when you want to end.\n\n");

    for(i=0; i<dim_tmp; i++){
        fprintf(stdout, "Insert number %d: ", i+1);
        bugfix = dim_tmp; //bug fix
        fscanf(stdin, "%1s", &trash);

        if(trash == 'q'){
            dim_tmp = i;
            break;
        }

        if(isdigit(trash)){
            vnumb[i] = trash - '0';
            if(i == dim_tmp - 1){
                vnumb = realloc(vnumb, (2*dim_tmp)*sizeof(int));
                if(vnumb == NULL) {
                    err_pointer(-16);
                }
                dim_tmp = dim_tmp*2;
            }
        }
        else{
            printf("Error: %c is not a number. Try again.\n", trash);
            i--;
        }
    }

    v = realloc(v, ((*dim)+dim_tmp)*sizeof(char));
    if(v == NULL) {
        err_pointer(-17);
    }

    tmp = (*dim);
    (*dim) = (*dim)+dim_tmp;

    for(i=0; i<dim_tmp; i++, tmp++) {
        v[tmp] = vnumb[i] + '0';
    }

    return v;
}

char *insert_special_chars(char *v, int *dim) {
    char spl[X] = {'"', '#', '$', '%', '&', '(', ')', '*', '+', ',', '-', '.', '/',
                   ':', ';', '<', '>', '=', '?', '@', '[', ']', '^', '_', '`', '~'};
    // Missing: '�', '�', '|', '�', '\', ''';
    int i, j, cnt=0, dimsaved=0, pos=0, flag=0, tmp=0, tmpX=X;
    int del[X]={-1};
    char *saved=NULL, trash;

    saved = malloc(X*sizeof(char));
    if(saved == NULL) {
        err_pointer(-22);
    }

    for(i=0; i<X; i++) {
        fprintf(stdout, "%d:%c  ", i, spl[i]);
    }

    fprintf(stdout, "\n\nInsert the character's number you want to delete.\n");
    fprintf(stdout, "\nInsert 'q' when you want to end.\n\n");

    for(i=0; i<X; i++){
        fprintf(stdout, "Remove n %d: ", i+1);
        fscanf(stdin, "%1s", &trash);

        if(trash == 'q') {
            break;
        }

        if(isdigit(trash)){
            if(control_saved(saved, dimsaved, pos, trash)){
                del[pos] = trash-'0';
                pos++;
                dimsaved++;
                cnt++;
            }
            else {
                fprintf(stdout, "Characters %c just removed.\n", trash);
            }
        }
        else {
            fprintf(stdout, "Error: %c is not a number. Try again.\n", trash);
            i--;
        }
    }

    v = realloc(v, ((*dim)+(tmpX-cnt))*sizeof(char));
    if(v == NULL) {
        err_pointer(-23);
    }

    tmp = (*dim);
    (*dim) = (*dim)+(tmpX-cnt);

    for(i=0; i<X; i++){
        flag=0;
        for(j=0; j<cnt && flag==0; j++) {
            if(i == del[j]) {
                flag=1;
            }
        }
        if(flag == 0){
            v[tmp] = spl[i];
            tmp++;
        }
    }

    free(saved);

    return v;
}

/// File [5]
void strcpy_format(char str1[], char str2[]) {
    int dim=strlen(str2);

    for(int i=dim-1; i<dim; i++) {
        if(str2[i]=='\n') {
            str2[i]='\0';
        }
    }

    strcpy(str1, str2);
}

/// Dictionary [6]
long int tot_dic(char *str) {
    int i, size=strlen(str);
    long int n_dic=0;

    for(i=0; i<size; i++){
        switch(tolower(str[i])){
            case 'o':
                n_dic++;
                break;
            case 'i':
                n_dic++;
                break;
            case 'e':
                n_dic++;
                break;
            case 'a':
                n_dic++;
                break;
            case 's':
                n_dic++;
                break;
            case 'g':
                n_dic++;
                break;
            case 't':
                n_dic++;
                break;
            case 'b':
                n_dic++;
                break;
            default:
                break;
        }
    }

    return n_dic;
}

/// All
// Signal
void sig_hand(int signo)
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

void explication() {
    fprintf(stdout, "[!] Remember:\n"
                    "[-] Creating a wordlist of large size, probably it will need some hours!\n"
                    "[-] You can put the extensions when insert the filename (.txt, .dat, etc..).\n"
                    "[-] The maximum string size can be 50.\n");

    fprintf(stdout, "\n");

    // Signal handler
    if(signal(SIGINT, sig_hand) == SIG_ERR || signal(SIGABRT, sig_hand) == SIG_ERR || signal(SIGTERM, sig_hand) == SIG_ERR){
        fprintf(stderr, "An error occurred while setting a signal handler.\n");
        pause();
        exit(EXIT_FAILURE);
    }
}

FILE *manage_file() {
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
                    break;
            }
        }
    }

    fprintf(stdout, "\n");

    return fp;
}

void print_count(int count, long int tot) {
    fprintf(stdout, "Wait: %d to %li\r", count, tot);
}

void end(int size) {
    fprintf(stdout, "\nAll the possible strings of size %d generated!\n", size);
    fprintf(stdout, "Use it wisely!\n\n");

    pause();

    fprintf(stdout, "Memory deallocation...\n");

    clear();
}

// Combinatorics
long int tot_arrangements_rep(int size, int base) {
    int i, j;
    long int tot=0, tmp=1;

    for(i=1; i<=size; i++){
        for(j=1; j<=i; j++){
            tmp = (long int) base*tmp;
        }
        tot += tmp;
        tmp=1;
    }

    if(tot <= 0) {
        // overflow
        return INT_MAX;
    }
    else {
        return tot;
    }
}

long int tot_arrangements(int n, int k) {
    int i, fact_n, fact_k;
    long int tot=0;

    fact_n = factorial(n);

    for(i=0; i<n; i++){
        fact_k = factorial(n-k);
        tot += (long int) (fact_n/fact_k);
        k--;
    }

    return tot;
}

static int factorial(int num) {
    int i, fact=num;

    if(num == 0) {
        return 1;
    }

    for(i=1; i<num; i++) {
        fact = fact*i;
    }

    return fact;
}

void err_pointer(int err) {
    fprintf(stderr, "Can't allocate memory.\nError %d\n", err);
    pause();
    exit(EXIT_FAILURE);
}

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

/* Alphabet [1] */
static char *init_alphabet(char *v, int upper, int lower);

/* Alphabet and Numbers [1 & 2] */
static int read_size(const char *question);

/* Guided [4] */
static int control_saved(char *saved, int dim_saved, int pos, char ch);
static char *bubble_sort(char *v, int dim);
static char *conv_to_uppercase(char *v, int dim);
static char *conv_to_lowercase(char *v, int dim);


/// Alphabet [1]
// Fills v with the uppercase letters, the lowercase ones, or both in that order.
static char *init_alphabet(char *v, int upper, int lower) {
    int bck=0;

    v = malloc(((upper ? A : 0) + (lower ? A : 0))*sizeof(char));
    if(v == NULL) {
        err_pointer(-1);
    }

    if(upper) {
        for(int i=0; i<A; i++) {
            v[bck++] = 'A' + i;
        }
    }

    if(lower) {
        for(int i=0; i<A; i++) {
            v[bck++] = 'a' + i;
        }
    }

    return v;
}

char *init_alphabet_uppercase(char *v) {
    return init_alphabet(v, 1, 0);
}

char *init_alphabet_lowercase(char *v) {
    return init_alphabet(v, 0, 1);
}

char *init_alphabet_uppercase_and_lowercase(char *v) {
    return init_alphabet(v, 1, 1);
}

/// Alphabet and Numbers [1 & 2]:
static int read_size(const char *question) {
    char tmp_size_char=' ';

    while(!isdigit(tmp_size_char) || tmp_size_char=='0'){
        fprintf(stdout, "\n%s", question);
        fscanf(stdin, " %c", &tmp_size_char);
        fflush(stdin);
        if(!isdigit(tmp_size_char) || tmp_size_char=='0') {
            fprintf(stdout, "Enter a single digit from 1 to 9.\n");
        }
    }

    return tmp_size_char - '0';
}

int *manage_size(int *min_size, int *max_size, int *sol) {
    (*min_size) = read_size("Enter minimum size string to generate: ");

    do {
        (*max_size) = read_size("Enter maximum size string to generate: ");
        if((*max_size) < (*min_size)) {
            fprintf(stdout, "The maximum size can't be smaller than the minimum one (%d).\n", (*min_size));
        }
    } while((*max_size) < (*min_size));

    sol = malloc((*max_size)*sizeof(int));
    if(sol == NULL) {
        err_pointer(-2);
    }

    return sol;
}

/// Str (Strings and Numbers) [3]
char **init_str(char **str, int *dim) {
    int i;
    char str_tmp[S], **tmp=NULL;

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
            tmp = realloc(str, (2*(*dim))*sizeof(char*));
            if(tmp == NULL){
                err_pointer(-7);
            }
            str = tmp;
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
        fscanf(stdin, " %c", &oper);
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
        fscanf(stdin, " %c", &oper);
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
        fscanf(stdin, " %c", &trash);
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
    int *vnumb=NULL;
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
        fscanf(stdin, " %c", &trash);

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
        fscanf(stdin, " %c", &trash);

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
    size_t dim=strlen(str2);

    // An empty string (e.g. a line starting with a NUL byte, common in real password dumps)
    // would make dim-1 wrap and touch str2[-1], corrupting the caller's stack.
    if(dim > 0 && str2[dim-1]=='\n') {
        str2[dim-1]='\0';
    }

    strcpy(str1, str2);
}

/// Dictionary [6]
// Returns the digit the character can be swapped with, or ' ' when there is none.
char get_dic(char ch) {
    char dic=' ';

    switch(tolower(ch)){
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
        default:
            dic = ' ';
            break;
    }

    return dic;
}

unsigned long long tot_dic(char *str) {
    int i, size=strlen(str);
    unsigned long long n_dic=0;

    for(i=0; i<size; i++){
        if(get_dic(str[i]) != ' ') {
            n_dic++;
        }
    }

    return n_dic;
}

/// All
char **chars_to_tokens(const char *v, int dim) {
    char **tok=NULL, *buf=NULL;

    if(dim <= 0) {
        return NULL;
    }

    tok = malloc(dim*sizeof(char*));
    buf = malloc((2*dim)*sizeof(char)); // one "c\0" pair per character

    if(tok == NULL || buf == NULL) {
        err_pointer(-25);
    }

    for(int i=0; i<dim; i++){
        buf[2*i] = v[i];
        buf[2*i+1] = '\0';
        tok[i] = &buf[2*i];
    }

    return tok;
}

void free_char_tokens(char **tok) {
    if(tok == NULL) {
        return;
    }

    free(tok[0]); // single backing buffer, shared by every token
    free(tok);
}

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
            flag=1;
        }
        else{
            fclose(fp);
            fprintf(stdout, "\nThere is a file with the same name.\n"
                            "Do you want to (1)overwrite or (2)create a new one? ");
            scanf(" %c", &oper);
            switch(oper){
                case '1':
                    flag=1;
                    break;
                case '2':
                    break;
                default:
                    fprintf(stdout, "Are you kidding me? Come on please serious.\n");
                    break;
            }
        }

        if(flag==1){
            fp = fopen(name, "w");
            if(fp==NULL){
                fprintf(stderr, "Can't open file %s for writing. Try another name.\n", name);
                flag=0;
            }
        }
    }

    fprintf(stdout, "\n");

    return fp;
}

void print_count(unsigned long long count, unsigned long long tot) {
    fprintf(stdout, "Wait: %llu to %llu\r", count, tot);
}

void end(int min_size, int max_size) {
    if(min_size == max_size) {
        fprintf(stdout, "\nAll the possible strings of size %d generated!\n", max_size);
    }
    else {
        fprintf(stdout, "\nAll the possible strings of size from %d to %d generated!\n", min_size, max_size);
    }
    fprintf(stdout, "Use it wisely!\n\n");

    pause();

    fprintf(stdout, "Memory deallocation...\n");

    clear();
}

// Combinatorics
// Both return ULLONG_MAX if the total doesn't fit
// base^min_size + base^(min_size+1) + ... + base^max_size
unsigned long long tot_arrangements_rep(int min_size, int max_size, int base) {
    unsigned long long tot=0, tmp=1;

    for(int i=1; i<=max_size; i++){
        if(base != 0 && tmp > ULLONG_MAX/base) {
            return ULLONG_MAX;
        }
        tmp *= base;
        if(i < min_size) {
            continue;
        }
        if(tot > ULLONG_MAX-tmp) {
            return ULLONG_MAX;
        }
        tot += tmp;
    }

    return tot;
}

// n!/(n-1)! + n!/(n-2)! + ... + n!/(n-k)!
unsigned long long tot_arrangements(int n, int k) {
    unsigned long long tot=0, tmp=1;

    for(int i=0; i<k; i++){
        if(tmp > ULLONG_MAX/(n-i)) {
            return ULLONG_MAX;
        }
        tmp *= (n-i);
        if(tot > ULLONG_MAX-tmp) {
            return ULLONG_MAX;
        }
        tot += tmp;
    }

    return tot;
}

WL_NORETURN void err_pointer(int err) {
    fprintf(stderr, "Can't allocate memory.\nError %d\n", err);
    pause();
    exit(EXIT_FAILURE);
}

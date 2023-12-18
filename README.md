# Wordlist Generator

Make customised wordlist for penetration testing practice (e.g. brute force attack, dictionary attack, etc.). It is possible to generate different wordlist using different methods, choose your favourite one and enjoy your wordlist!

### Disclaimer

- All the information provided on this repo are for educational purposes only. The repo and author of the repo is no way responsible for any misuse of the information.
- The term "wordlist-generator" just represents the name of the repo and is not a repo that provides any illegal information. This repo is related to Information Security, Computer Security and Penetration Testing and not a repo/site that promotes hacking/cracking/software piracy.
- This repo is totally meant for providing information on Computer Security, Information Security, Computer Programming, Penetration Testing and other related topics and is no way related towards the terms “CRACKING” or “HACKING” (Unethical).
- The Software's and Scripts provided by the this repo should only be used for education purposes. The repo or the author can not be held responsible for the misuse of them by the users.

### Demo

[![Watch the video](https://img.youtube.com/vi/stTbTtPT40s/maxresdefault.jpg)](https://youtu.be/stTbTtPT40s)

# Tables of Contents

- [Usage](#wordlist-generator#usage)
- [Wordlist](#wordlist-generator#wordlist)
  - [Alphabet wordlist](#wordlist-generator#alphabet-wordlist)
  - [Digits wordlist](#wordlist-generator#digits-wordlist)
  - [Custom wordlist](#wordlist-generator#custom-wordlist)
  - [Guided wordlist](#wordlist-generator#guided-wordlist)
  - [Dictionary wordlist](#wordlist-generator#dictionary-wordlist)
  - [Wordlist from data file](#wordlist-generator#wordlist-from-data-file)
  - [Info](#wordlist-generator#info)
- [Files](#wordlist-generator#files)

# Usage

1. Clone the repo and change directory

       git clone https://github.com/J4NN0/wordlist-generator.git
       cd wordlist-generator

2. Compile the files

       make

3. Run the program

       make run

4. Choose the method you prefer and create your wordlist

5. If you want to cleanup all files

       make clean

# Wordlist

The wordlist will contain strings with length from `1` character to the max size (decided by you). Keep in mind that the higher will be the string size the more will be the time needed in order to generate the wordlist.

### Alphabet wordlist

You have to choose only the max size of the strings that will be generated. The strings will be composed by the whole alphabet (lower case, upper case or both).

For instance, with a maximum string size set at `3`:

- *`Uppercase`* mode: it will generate a total of `18278` strings.
- *`Lowercase`* mode: it will generate a total of `18278` strings.
- *`Both`* mode: it will generate a total of `143364` strings.

e.g. `lowercase` mode:

    a aa aaa aab aac aad aae aaf aag aah aai aaj aak ... zzo zzp zzq zzr zzs zzt zzu zzv zzw zzx zzy zzz

### Digits wordlist

You have to choose only the max size of the strings that will be generated. The strings will be composed by only numbers.

For instance, with a maximum string size set at `3`, it will generate a total of `1110` strings:

    0 00 000 001 002 003 004 005 006 007 008 009 01 010 011 012 013 ... 988 989 99 990 991 992 993 994 995 996 997 998 999

 ### Custom wordlist

Just insert manually strings, characters and/or numbers that will compose the wordlist. Then choose the max size of the strings that will be generated.

### Guided wordlist

It's a guided version to generate your customized wordlist. You can chose, step by step, if you want insert:

- Some or all characters of the alphabet.
- Some or all numbers.
- Some or all special characters.

### Dictionary wordlist

Insert the string you want to modify for dictionary attack.

For instance, the word `hello` as input will generate the following wordlist:

    h3llo
    h3ll0
    hell0

### Wordlist from data file

Enter the file's path containing the strings that will be combined for the wordlist.

### Info

For more info about methods above and more.

# Files
        
- `main.c`: the main menu.
- `More` folder: it contains some basic information about WEP, WPA2, developer and more.
- `System` folder: it contains system call (based on current OS) to clean (and pause) the screen.
- `Wordlist` folder: it contains all the functions to generate the wordlist.

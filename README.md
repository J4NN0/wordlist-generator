# Wordlist Generator

Make customised wordlist for penetration testing practice (e.g. brute force attack, dictionary attack, etc.). It is possible to generate different wordlist using different methods, choose your favourite one and enjoy your wordlist!

> [!CAUTION]
> This tool is for education and authorized security testing only. Use it only against systems  you own or have explicit permission to test. The author is not responsible for any misuse or damage caused by this software.

### Demo

[![Watch the video](https://img.youtube.com/vi/stTbTtPT40s/maxresdefault.jpg)](https://youtu.be/stTbTtPT40s)

# Tables of Contents

- [Usage](#usage)
- [Wordlist](#wordlist)
  - [Alphabet wordlist](#alphabet-wordlist)
  - [Digits wordlist](#digits-wordlist)
  - [Custom wordlist](#custom-wordlist)
  - [Guided wordlist](#guided-wordlist)
  - [Dictionary wordlist](#dictionary-wordlist)
  - [Wordlist from data file](#wordlist-from-data-file)
  - [Info](#info)
- [Files](#files)

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

The wordlist will contain strings with length from the `min` size to the `max` size (both decided by you). Setting a minimum size is handy when the target has a known password policy: with a minimum of `8` all the shorter combinations are skipped and never written to the file. Keep in mind that the higher will be the string size the more will be the time needed in order to generate the wordlist.

### Alphabet wordlist

You have to choose only the `min` and the `max` size of the strings that will be generated. The strings will be composed by the whole alphabet (lower case, upper case or both).

| Mode | `min` 1 - `max` 3 | `min` 3 - `max` 3 |
| --- | --- | --- |
| *`Uppercase`* | `18278` strings | `17576` strings |
| *`Lowercase`* | `18278` strings | `17576` strings |
| *`Both`* | `143364` strings | `140608` strings |

e.g. *`lowercase`* mode with `min` 1 and `max` 3:

    a
    aa
    aaa
    aab
    ...
    zzx
    zzy
    zzz

### Digits wordlist

You have to choose only the `min` and the `max` size of the strings that will be generated. The strings will be composed by only numbers.

e.g. `min` 1 and `max` 3, a total of `1110` strings (raising `min` to 3 it generates only the `1000` strings of exactly 3 digits):

    0
    00
    000
    001
    ...
    997
    998
    999

### Custom wordlist

Just insert manually strings, characters and/or numbers that will compose the wordlist. Then choose how many times each one can be repeated inside the same string.

e.g. the strings `red` and `12` with 1 repetition:

    red
    red12
    12
    12red

### Guided wordlist

It's a guided version to generate your customized wordlist. You can chose, step by step, if you want insert:

- Some or all characters of the alphabet.
- Some or all numbers.
- Some or all special characters.

Then, as for the other methods, you choose the `min` and the `max` size of the strings that will be generated.

### Dictionary wordlist

Insert the string you want to modify for dictionary attack.

e.g. the word `hello`:

    h3llo
    h3ll0
    hell0

### Wordlist from data file

Enter the file's path containing the strings that will be combined for the wordlist. Each line of the file is used at most once per generated string.

e.g. a file containing `aa`, `bb` and `cc`:

    aa
    aabb
    aabbcc
    aacc
    ...
    ccaabb
    ccbb
    ccbbaa

### Info

For more info about methods above and more.

# Files
        
- `main.c`: the main menu.
- `More` folder: it contains some basic information about WEP, WPA2, developer and more.
- `System` folder: it contains system call (based on current OS) to clean (and pause) the screen.
- `Wordlist` folder: it contains all the functions to generate the wordlist.

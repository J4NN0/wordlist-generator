# Wordlist Generator

Make customized wordlist through a variety of methods. Choose your favourite method and enjoy your wordlist!

### Note that:

- All the information provided on this repo are for educational purposes only. The repo and author of the repo is no way responsible for any misuse of the information.
- "wordlist-generator" are just a term that represents the name of the repo and is not a repo that provides any illegal information. Wordlist Generator is a repo related to Information Security, Computer Security and Penetration Testing and not a site that promotes hacking/cracking/software piracy.
- This repo is totally meant for providing information on Computer Security, Information Security, Computer Programming, Penetration Testing and other related topics and is no way related towards the terms “CRACKING” or “HACKING” (Unethical).
- The Software's and Scripts provided by the site should only be used for education purposes. The repo or the author can not be held responsible for the misuse of them by the users. 


#### Chechout this demonstration video

[![Watch the video](https://img.youtube.com/vi/stTbTtPT40s/maxresdefault.jpg)](https://youtu.be/stTbTtPT40s)

# Usage

The wordlist will containt strings with length from 1 character to the max size (decided by you). Keep in mind that the more will be the size of string the more time the toll will take to generate the wordlist.

Different ways to create your wordlist:
   
   - Wordlist with whole alphabet (a-zA-z)
   
      You have to choose only the max size of the strings that will be generated. The strings will be composed by the whole alphabet (lower case, upper case or both).
      
      For examplee, with a max string size of 3:
      
      - Mode *'Uppercase'* will generate a total of 18278 strings
      - Mode *'Lowercase'* will generate a total of 18278 strings
      - Mode *'Both'* will generate a total of 143364 strings
         
      i.e. lowercase
      
         a aa aaa aab aac aad aae aaf aag aah aai aaj aak ... zzo zzp zzq zzr zzs zzt zzu zzv zzw zzx zzy zzz
        
   - Wordlist with only numbers (0-9)
   
      You have to choose only the max size of the strings that will be generated. The strings will be composed by only numbers.
      
      With a string size of 3 the total strings will be 1110, i.e.
      
         0 00 000 001 002 003 004 005 006 007 008 009 01 010 011 012 013 ...
   
   - Wordlist with strings, characters and numbers
   
      Just insert manually strings, characters and numbers that will compose the wordlist. Then choose the max size of the strings that will be generated.
         
   - Guided wordlist
   
      It's a guided version to make your customized wordlist. You can chose, step by step, if you want insert:
      
      - Some or all characters of the alphabet 
      - Some or all number 
      - Some or all special characters
        
   - Dictionary wordlist
   
      Insert the string you want to modify for dictionary attack. 
      
      For example, the word 'hello' will generate the following strings:
      
         h3llo
         h3ll0
         hell0
         
   - Wordlist from data file
   
      Put the filaneme of the file containing the strings that will be combined for the wordlist.
         
   - Info
   
      For more info about this methods and more.
      
# Makefile

To compile, run

      make
        
To cleanup, run

      make clean
        
Files: 
   - *main.c*: the main menu
   - *wordlist.c*: contains the functions to generate the wordlists
   - *more.c*: contains information about WEP, WPA2, developer and more

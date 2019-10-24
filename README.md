# Wordlist

Make customized wordlist through a variety of methods. Choose your favourite method and enjoy your wordlist!

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
   - *wordlist.c*: contains the functions to generate the wordlists (combinatorial and recursive approach)
   - *more.c*: contains informations about WEP, WPA2, developer and more

# Note
   
For bugs or suggestions send me an email or do a pull-request.

# Wordlist

Make customized wordlist through a variety of methods. Choose your favourite method and enjoy your wordlist!

# Usage

The wordlist will containt strings with length from 1 character to the max size (decided by you).
You can choose how each string have to be composed through the following methods:
   
   - Wordlist with whole alphabet (a-zA-z)
   
        You have to choose only the max size of the strings that will be generated. The strings will be composed by the whole alphabet (lower case, upper case or both).
        
   - Wordlist with only numbers (0-9)
   
        You have to choose only the max size of the strings that will be generated. The strings will be composed by only numbers.
         
   - Wordlist with strings, characters and numbers
   
        Just insert manually strings, characters or numbers that will compose the wordlist. Then choose the max size of the strings that will be generated.
         
   - Guided wordlist (Alphabet || Numbers || Special Characters)
   
        It's a guided version to make your customized wordlist. You can chose, step by step, if you want insert some or all characters of the alphabet, some number and/or special characters.
        
   - Dictionary wordlist
   
        Insert the string you want to modify for dictionary attack. For example the word 'hello' becomes 'h3ll0'.
         
   - Wordlist from data file
   
        Put the filaneme of the file contains the words that will be combined for the wordlist.
         
   - Info
   
        For more info about this methods and more.
      
# Files

   - wordlist.c    
   
            contains the functions to generate customized wordlists (combinatorial and recursive functions)
   
   - more.c  
            
            contains informations about WEP, WPA2, developer and more
   
   - main.c 
   
            the main menu
   
   Compile the \*.c with gcc (or others compilers linking both file .c and .h) and enjoy!

# Note
   
For bugs or suggestions send me an email or do a pull-request.

Copyright (c) 2017 Federico Gianno

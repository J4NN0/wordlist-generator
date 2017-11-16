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
#include "more.h"

static int letmesee(int miss);
static void pause();

void info_wep()
{
    system("clear");

    fprintf(stdout, "Source: https://en.wikipedia.org/wiki/Wired_Equivalent_Privacy\n\n");

    //Encryption details
    fprintf(stdout, "\4 Encryption details:\n"
            "WEP was included as the privacy component of the original IEEE 802.11 standard\n"
            "ratified in 1997. WEP uses the stream cipher RC4 for confidentiality, and\n"
            "the CRC-32 checksum for integrity. It was deprecated in 2004 and is\n"
            "documented in the current standard.\n\n");

    if((letmesee(10+6+9))==0) return;

    //64-bit
    fprintf(stdout, "\n\4 64-bit:\n"
            "A 64-bit WEP key is usually entered as a string of 10 hexadecimal (base 16)\n"
            "characters (0-9 and A-F). Each character represents 4 bits,\n"
            "10 digits of 4 bits each gives 40 bits; adding the 24-bit IV produces the\n"
            "complete 64-bit WEP key (4 bits x 10 + 24 bits IV = 64 bits of WEP key).\n"
            "Most devices also allow the user to enter the key as 5 ASCII characters\n"
            "(0-9, a-z, A-Z), each of which is turned into 8 bits using the character's\n"
            "byte value in ASCII (8 bits x 5 + 24 bits IV = 64 bits of WEP key); however,\n"
            "this restricts each byte to be a printable ASCII character, which is only\n"
            "a small fraction of possible byte values, greatly reducing the space\n"
            "of possible keys.\n\n");

    if((letmesee(6+9))==0) return;

    //128-bit
    fprintf(stdout, "\n\4 128-bit:\n"
            "A 128-bit WEP key is usually entered as a string of 26 hexadecimal\n"
            "characters. 26 digits of 4 bits each gives 104 bits; adding the 24-bit\n"
            "IV produces the complete 128-bit WEP key\n"
            "(4 bits x 26 + 24 bits IV = 128 bits of WEP key).\n"
            "Most devices also allow the user to enter it as 13 ASCII characters\n"
            "(8 bits x 13 + 24 bits IV = 128 bits of WEP key).\n\n");

    if((letmesee(9))==0) return;

    //152-bit
    fprintf(stdout, "\n\4 152-bit:\n"
            "A 152-bit and a 256-bit WEP systems are available from some vendors.\n"
            "As with the other WEP variants, 24 bits of that is for the IV,\n"
            "leaving 128 or 232 bits for actual protection.\n"
            "These 128 or 232 bits are typically entered as 32 or 58 hexadecimal characters\n"
            "(4 bits x 32 + 24 bits IV = 152 bits of WEP key,\n"
            "4 bits x 58 + 24 bits IV = 256 bits of WEP key).\n"
            "Most devices also allow the user to enter it as 16 or 29 ASCII characters\n"
            "(8 bits x 16 + 24 bits IV = 152 bits of WEP key,\n"
            "8 bits x 29 + 24 bits IV = 256 bits of WEP key).\n\n");

    pause();
    system("clear");
}

void info_wpa()
{
    system("clear");

    fprintf(stdout, "Source: https://en.wikipedia.org/wiki/Wi-Fi_Protected_Access\n\n");

    //WPA
    fprintf(stdout, "\4 WPA:\n"
            "The WPA protocol implements much of the IEEE 802.11i standard.\n"
            "Specifically, the Temporal Key Integrity Protocol (TKIP) was adopted for WPA.\n"
            "WEP used a 64-bit or 128-bit encryption key that must be manually entered \n"
            "on wireless access points and devices and does not change.\n"
            "TKIP employs a per-packet key, meaning that it dynamically generates a new\n"
            "128-bit key for each packet and\n"
            "thus prevents the types of attacks that compromised WEP.\n\n");

    if((letmesee(6+11))==0) return;

    //WPA2
    fprintf(stdout, "\n\4 WPA2:\n"
            "WPA2 replaced WPA. WPA2, which requires testing and certification\n"
            "by the Wi-Fi Alliance, implements the mandatory elements of IEEE 802.11i.\n"
            "In particular, it includes mandatory support for CCMP, an AES-based\n"
            "encryption mode with strong security. Certification began in September, 2004;\n"
            "from March 13, 2006, WPA2 certifications mandatory for all new devices\n"
            "to bear the Wi-Fi trademark.\n\n");

    if((letmesee(11))==0) return;

    //Security issues
    fprintf(stdout, "\n\4 Security issues:\n"
            "Pre-shared key WPA and WPA2 remain vulnerable to password\n"
            "cracking attacks if users rely on a weak password or passphrase.\n"
            "To protect against a brute force attack, a truly random passphrase\n"
            "of 20 characters (selected from the set of 95 permitted characters)\n"
            "is probably sufficient. Brute forcing of simple passwords can be\n"
            "attempted using he Aircrack Suite starting from the four-way\n"
            "authentication handshake exchanged during association or periodic\n"
            "re-authentication. To further protect against intrusion, the network's\n"
            "SSID should not match any entry in the top 1,000 SSIDs as downloadable\n"
            "rainbow tables have been pre-generated for them and a multitude\n"
            "of common passwords.\n\n");

    pause();
    system("clear");
}

void info_GNU_license()
{
    system("clear");

    fprintf(stdout, "Source: http://www.gnu.org/licenses/\n\n");

    fprintf(stdout, "    Copyright 2017 Federico Gianno\n\n"

                        "This file is part of wordlist.\n\n"

                        "wordlist is free software: you can redistribute it and/or modify\n"
                        "it under the terms of the GNU General Public License as published by\n"
                        "the Free Software Foundation, either version 3 of the License, or\n"
                        "(at your option) any later version.\n\n"

                        "wordlist is distributed in the hope that it will be useful,\n"
                        "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
                        "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
                        "GNU General Public License for more details.\n\n"

                        "You should have received a copy of the GNU General Public License\n"
                        "along with wordlist.\n\n");


    pause();
    system("clear");
}

void info_wl()
{
    system("clear");

    fprintf(stdout, "[1] Generate a wordlist with whole alphabet [1]\n\n");
    fprintf(stdout, "Generate a wordlist composed by the entire alphabet.\n"
            "Each line of the created file will have a provisions repeated\n"
            "of alphabet letters of user-defined size.\n\n");

    if((letmesee(3+3+3+3+3))==0) return;

    fprintf(stdout, "[2] Generate a wordlist with only numbers [2]\n\n");
    fprintf(stdout, "Generate a wordlist composed by numbers.\n"
            "Each line of the created file will have a provisions repeated\n"
            "of numbers of user-defined size.\n\n");

    if((letmesee(3+3+3+3))==0) return;

    fprintf(stdout, "[3] Generate a customized wordlist [3]\n\n");
    fprintf(stdout, "Generate a wordlist composed by characters that you choose.\n"
        "Each line of the created file will have a provisions repeated\n"
        "of these characters of user-defined size.\n\n");

    if((letmesee(3+3+3))==0) return;

    fprintf(stdout, "[4] Generate a wordlist with strings, character and numbers [4]\n\n");
    fprintf(stdout, "Generate a wordlist composed by provisions of string,\n"
            "character and numbers. Each line of the created file will have a\n"
            "provisions of these strings, character and numbers.\n\n");

    if((letmesee(3+3))==0) return;

    fprintf(stdout, "[5] Guided wordlist [5]\n\n");
    fprintf(stdout, "Generate a wordlist composed by alphabet letters,\n"
            "numbers and special characters. Each line of the created file will have\n"
            "a provisions repeated of these characters of user-defined size.\n\n");

    if((letmesee(3))==0) return;

    fprintf(stdout, "[6] Generate a wordlist from data file [6]\n\n");
    fprintf(stdout, "Generate a wordlist composed by provisions of file strings.\n"
            "Each line of the created file will have a provisions of\n"
            "these strings of user-defined size.\n\n");

    pause();
    system("clear");
}

void develop()
{
    fprintf(stdout, "Developed by J4NN0.\n");
    fprintf(stdout, "My real name is Federico and i'm computer\n"
            "engineering student at the Polytechnic of Turin.\n\n");

    fprintf(stdout, "For report bug:\n");
    fprintf(stdout, "Twitter: @giannofederico\n"
            "Please enter as object of email 'wordlist'\n");

    fprintf(stdout, "Ty for supporting.\n");

    pause();
    system("clear");
}

///Static function
int letmesee(int miss)
{
    char trash[1];

    fflush(stdin);
    fprintf(stdout, "Still %d lines.\n"
            "Enter 'q' to exit, other to continue: ", miss);
    fscanf(stdin, "%1s", trash);

    if(trash[0]=='q')
        return 0;
    else
        return 1;
}

void pause()
{
    fflush(stdin);
    fprintf(stdout, "Press enter to continue...");
    getc(stdin);
    fflush(stdin);
}

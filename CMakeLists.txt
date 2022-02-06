cmake_minimum_required(VERSION 3.19)
project(wordlist_generator C)

set(CMAKE_C_STANDARD 99)

add_executable(wordlist_generator main.c Wordlist/wordlist.h Wordlist/wordlist.c More/more.c More/more.h System/system.c System/system.h Wordlist/Util/util.c Wordlist/Util/util.h)

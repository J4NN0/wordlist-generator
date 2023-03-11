# Compiler to use
CC = gcc

# Flags
CFLASG = -Wall

# Libraries to use (-lm, -lefence, etc)
LDFLAGS = 

# Object files that are part of the final program
OBJFILES = main.o More/more.o Wordlist/wordlist.o Wordlist/Util/util.o System/system.o

# Name of the program
TARGET = wordlist_generator

all : $(TARGET)

$(TARGET) : $(OBJFILES)
	$(CC) $(FLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean : 
	rm -f $(OBJFILES) $(TARGET) *~

run :
	./$(TARGET)

#
#  Makefile
#

# rm
RM = rm -f
ifeq ($(OS),Windows_NT)
    RM = del
endif

# target file
TARGET = example.exe

# source list
SRCS = example.c

# .obj list
OBJS = ${SRCS:.c=.o}

# header list
HEADERS = ../optarg.h

# compiler/linker
CC = gcc
CCFLAGS = -Wall
LD = gcc
LDFLAGS =
LIBS = -L../ -loptarg

# target <- obj
$(TARGET) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(TARGET) $(LIBS)

# *.o <- *.c
.c.o :
	$(CC) $(CCFLAGS) -c $<

# dependence (relationship)
$(OBJS) : $(HEADERS) Makefile

# make clean
clean :
	$(RM) $(TARGET) $(OBJS) *~

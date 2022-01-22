TARGET = main.c
CC = gcc
LIBS = /home/hpcuser041/lib
# LDLIBS = $(shell pkg-config --libs gtk+-3.0)
#INCLUDE = /home/hpcuser041/include
FLAGS = -O2 -lm

FractalExplorermake : $(TARGET)
        $(CC) $(TARGET) -I$(INCLUDE) -L$(LIBS) -o $@ $(FLAGS)

##############################
##############################

CC = gcc
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj
CFLAGS = -c -Wall -I$(INC_DIR)
EXE = project

SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/file1.c#Everything to bouild in
OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/file1.o#Everything to bouild out

main : clean build

build:  $(OBJS)
  	$(CC)   $(OBJS) -o $(EXE)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
        $(CC) $(CFLAGS) -c $< -o $@

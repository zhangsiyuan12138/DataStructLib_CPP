CC = g++
CFLAGS = -g
OUTPUT = ./Output/output.o
RM = rm -fr
SOURCE = $(shell find ./ -name "*.cpp")
INCLUDE_DEPEND = $(shell find ./ -name "*.h")
INCLUDE_DIR = -I./List/ -I./TopClass/ -I./Exception/ -I./Array/ -I./SmartPointer/ -I./Stack/ -I./Queue -I./Stack_Queue -I./String -I./Other -I./Sort -I./Tree -I./Graph
#INCLUDE_DIR = $(dirname $(INCLUDE_DEPEND):%./=-I%./)
MEDDIATE = $(shell find ./ -name "*.o")

$(OUTPUT) : $(SOURCE) $(INCLUDE_DEPEND)
	$(CC) $(CFLAGS) $(SOURCE) $(INCLUDE_DIR) -o $(OUTPUT) 

run:
	$(OUTPUT) 

clean:
	$(RM) $(MEDDIATE)



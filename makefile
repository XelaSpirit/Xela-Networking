SHELL = /bin/bash
CC = g++
ALLFLAGS = -I./Headers -fPIC -fvisibility=hidden -w -D XELANETWORKING_EXPORTS
OFLAGS = -I./Headers -w -fPIC -fvisibility=hidden
TFLAGS = -shared -pedantic -march=native -ggdb3 -O2 -fwhole-program -Wl,-soname,libxelanetworking.so

TARGET = libxelanetworking.so
SRC_PATH = Source/
OBJ_PATH = ./
HEADER_PATH = Headers/
SOURCES = $(shell echo $(SRC_PATH)*/*.cpp)
HEADERS = $(shell echo $(HEADER_PATH)*.h)
OBJECTS_TMP = $(SOURCES:.cpp=.o)
OBJECTS = $(shell echo $(OBJECTS_TMP) | sed 's_$(SRC_PATH).*/_$(OBJ_PATH)_g')

PREFIX = $(DESTDIR/usr/local)
BINDIR = $(PREFIX/bin)

all: $(TARGET)

$(OBJECTS): $(SOURCES)
	$(CC) -c $(OFLAGS) $(ALLFLAGS) $(SOURCES)

$(TARGET): $(OBJECTS)
	$(CC) $(TFLAGS) $(ALLFLAGS) -o $(TARGET) *.o

.PHONY : clean
clean:
	rm *.o

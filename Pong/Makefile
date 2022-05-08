CC = g++

SOURCES = testing.cpp Pong.cpp Paddle.cpp
INCLUDES = Pong.h Paddle.h

CXXFLAGS = -Wall -Wpedantic -g -std=c++17

OBJECTS = $(SOURCES:.cpp=.o)

LIBRARIES = -lSDL2 -lSDL2_image

TARGET = Pong

all: $(OBJECTS) 
	$(CC) $(OBJECTS) $(INCLUDES) $(LIBRARIES) $(CXXFLAGS) -o $(TARGET)



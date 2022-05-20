CC = g++

CFLAGS = --std=c++17 -lGL -lGLEW -lglfw

TARGET = build/grocery_run

SRC = main.cpp
SRC += $(wildcard API/*.cpp)
SRC += $(wildcard GameFiles/*.cpp)
SRC += $(wildcard GameObjects/*.cpp)
SRC += $(wildcard 3rd_party/stb_image/*.cpp)

install:
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -vrf $(TARGET)

.PHONY = clean install

APP = RTX
CC = g++
FLAGS =	-c -W -Wall -ansi -pedantic
LINKS = -lSDL2
RM = rm -rf

SOURCE = $(wildcard ./source/*/*.cpp)
INCLUDE = $(wildcard ./source/*/*.hpp)
OBJECTS = $(subst .cpp,.o,$(subst source/*,build/objects,$(SOURCE)))

all: build/$(APP)

./build/$(APP): $(OBJECTS)
	@ echo 'Building binary $@'
	$(CC) $^ $(LINKS) -o $@

./build/objects/%.o: ./source/%.cpp ./source/%.hpp
	@ echo 'Building target $<'
	$(CC) $< $(FLAGS) $(LINKS) -o $@

./build/objects/main.o: ./source/main.cpp
	@ echo 'Building target $<'
	$(CC) $< $(FLAGS) $(LINKS) -o $@

clean:
	@ $(RM) ./source/*/*.o ./build/$(APP) *~

run:
	./build/$(APP)

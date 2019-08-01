APP = RTX
CC = g++
FLAGS =	-W -Wall -ansi -pedantic
LINKS = -lSDL2 -lpthread -pthread -std=c++11
RM = rm -rf

SOURCE = 	$(wildcard ./source/BRDF/*.cpp) \
			$(wildcard ./source/Cameras/*.cpp) \
			$(wildcard ./source/GeometricObjects/*.cpp) \
			$(wildcard ./source/Light/*.cpp) \
			$(wildcard ./source/Main/*.cpp) \
			$(wildcard ./source/Materials/*.cpp) \
			$(wildcard ./source/Samplers/*.cpp) \
			$(wildcard ./source/Tracers/*.cpp) \
			$(wildcard ./source/Utilities/*.cpp) \
			$(wildcard ./source/Window/*.cpp) \
			$(wildcard ./source/World/*.cpp) \

OBJECTS = $(SOURCE: .cpp = .o)

all: ./build/$(APP)

./build/$(APP): $(OBJECTS)
	@ echo 'Building binary $@'
	$(CC) $^ $(FLAGS) $(LINKS) -o $@

clean:
	@ $(RM) ./build/$(APP) 

run:
	./build/$(APP)
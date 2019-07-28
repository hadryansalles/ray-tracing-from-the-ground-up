OBJS = source/files/*.cpp

OBJ_NAME = RTX

all: $(OBJS)
		g++ $(OBJS) -w -lSDL2 -o $(OBJ_NAME)

run: 
	./$(OBJ_NAME)

clean: 
	rm -f $(OBJ_NAME)

bin/sfmlgame: src/*.cpp
	g++ src/*.cpp -Isrc -I/opt/homebrew/opt/sfml@2/include -std=c++17 -o bin/sfmlgame -O3 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -L/opt/homebrew/opt/sfml@2/lib

# to compile and run in one command type:
# make run

# define which compiler to use
CXX		:= g++
OUTPUT	:= sfmlgame
OS		:= $(shell uname)
SRC_DIR	:= ./src

# linux compiler / linker flags
ifeq ($(OS), Linux)
	CXX_FLAGS	:= -03 -std=c++23 -Wno-unused-result -Wno-deprecated-declarations
	INCLUDE 	:= -I$(SRC_DIR) -I$(SRC_DIR)/ingui
	LDFLAGS		:= -03 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lGL
endif

# mac osx compiler / linker flags
ifeq ($(OS), Darwin)
	SFML_DIR	:= /opt/homebrew/Cellar/sfml/3.0.2
	CXX_FLAGS	:= -03 -std=c++23 -Wno-unused-result -Wno-deprecated-declarations
	INCLUDES	:= -I$(SRC_DIR) -I$(SRC_DIR)/ingui -I$(SFML_DIR)/include
	LDFLAGS		:= -03 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -L$(SFML_DIR)/lib -framework OpenGL
endif

# the source files for the ecs game engine
SRC_FILES	:= $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/imgui/*.cpp)
OBJ_FILES	:= $(SRC_FILES:.cpp=.o)

# Include dependency files
DEP_FILES	:= $(OBJ_FILES:.o=.d)
-include $(DEP_FILES)

# all of these targets will be made if you just type make 
all: $(OUTPUT)

#define the main executable requirements / command 
$(OUTPUT): $(OBJ_FILES) Makefile
	$(CXX) $(OBJ_FILES) $(LDFLAGS) -o ./bin/$@

# specifies how the object files are compiled from cpp files
%.o: %.cpp
	$(CXX) -MMD -MP -c $(CXX_FLAGS) $(INCLUDES) $< -o $@

# typing 'make clean' will remove all intermediate build files 
clean: 
	rm -f $(OBJ_FILES) $(DEP_FILES) ./bin/$(OUTPUT)

# typing 'make run' will compile and run the program
run: $(OUTPUT)
	cd bin $$ ./$(OUTPUT) && cd ..

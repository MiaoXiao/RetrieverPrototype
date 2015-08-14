CFLAGS = -Wall -w -ansi -pedantic
FP_MAIN = ./src/main.cpp
FP_ENTITY = ./src/Entity.cpp
FP_CHARACTER = ./src/Character.cpp
FP_PLAYER = ./src/Player.cpp
FP_FIGMENT = ./src/Figment.cpp
FP_BATTLE = ./src/Battle.cpp
FP_GLOBALS = ./src/Globals.cpp
OUTPATH = ./bin/debug

all: game 
game:
	mkdir -p ./bin
	g++ $(CFLAGS) $(FP_MAIN) $(FP_ENTITY) $(FP_CHARACTER) $(FP_PLAYER) $(FP_FIGMENT) $(FP_BATTLE) $(FP_GLOBALS) -o $(OUTPATH)$
clean:
	rm -rf ./bin

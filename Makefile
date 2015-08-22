#flags
MAINFLAGS = -Wall -w -ansi -pedantic
CLASSFLAGS = -Wall -w -ansi -pedantic -c

#paths
OUTPATH = ./bin/
OBJPATH = ./obj/
SRCPATH = ./src/

#Filepaths for cpp
MAINCPP = $(SRCPATH)main.cpp
GLOBALSCPP = $(SRCPATH)Globals.cpp
ENTITYCPP = $(SRCPATH)Entity.cpp
CHARACTERCPP =$(SRCPATH)Character.cpp
PLAYERCPP = $(SRCPATH)Player.cpp
FIGMENTCPP = $(SRCPATH)Figment.cpp
BATTLECPP = $(SRCPATH)Battle.cpp
ABILITIYCPP = $(SRCPATH)Ability.cpp

#Filepaths for h
GLOBALSH = $(SRCPATH)Globals.h
ENTITYH = $(SRCPATH)Entity.h
CHARACTERH =$(SRCPATH)Character.h
PLAYERH = $(SRCPATH)Player.h
FIGMENTH = $(SRCPATH)Figment.h
BATTLEH = $(SRCPATH)Battle.h
ABILITIYH = $(SRCPATH)Ability.h

#Filepaths for o
MAINO = $(OBJPATH)Main.o
GLOBALSO = $(OBJPATH)Globals.o
ENTITYO = $(OBJPATH)Entity.o
CHARACTERO =$(OBJPATH)Character.o
PLAYERO = $(OBJPATH)Player.o
FIGMENTO = $(OBJPATH)Figment.o
BATTLEO = $(OBJPATH)Battle.o
ABILITIYO = $(OBJPATH)Ability.o

#final executable
EXE = $(OUTPATH)debug

game: create $(OUTPATH)debug run

create:
	mkdir -p ./bin/
	mkdir -p ./obj/
clean:
	rm -rf ./bin/
	rm -rf ./obj/
run:
	bin/debug

$(EXE): $(MAINO) 
	g++ $(MAINFLAGS) $(MAINO) $(GLOBALSO) $(ENTITYO) $(CHARACTERO) $(PLAYERO) $(FIGMENTO) $(BATTLEO) $(ABILITYO)  -o $(EXE)
$(MAINO): $(PLAYERO) $(FIGMENTO) $(BATTLEO) $(MAINCPP)
	g++ $(CLASSFLAGS) $(MAINCPP) -o $(MAINO)
$(GLOBALSO): $(GLOBALSCPP) $(GLOBALSH)
	g++ $(CLASSFLAGS) $(GLOBALSCPP) -o $(GLOBALSO)
$(ENTITYO): $(ENTITYCPP) $(ENTITYH)
	g++ $(CLASSFLAGS) $(ENTITYCPP) -o $(ENTITYO)
$(CHARACTERO): $(ENTITYO) $(ABILITYO) $(GLOBALSO) $(CHARACTERCPP) $(CHARACTERH)
	g++ $(CLASSFLAGS) $(CHARACTERCPP) -o $(CHARACTERO)
$(PLAYERO): $(CHARACTERO) $(PLAYERCPP) $(PLAYERH)
	g++ $(CLASSFLAGS) $(PLAYERCPP) -o $(PLAYERO)
$(FIGMENTO): $(CHARACTERO) $(FIGMENTCPP) $(FIGMENTH)
	g++ $(CLASSFLAGS) $(FIGMENTCPP) -o $(FIGMENTO)
$(BATTLEO): $(GLOBALSO) $(PLAYERO) $(FIGMENTO) $(BATTLECPP) $(BATTLEH)
	g++ $(CLASSFLAGS) $(BATTLECPP) -o $(BATTLEO)
$(ABILITYO): $(ENTITYO) $(ABILITYCPP) $(ABILITYH)
	g++ $(CLASSFLAGS) $(ABILITIESCPP) -o $(ABILITYO)


	

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
ABILITYCPP = $(SRCPATH)Ability.cpp
CHARGEDCPP = $(SRCPATH)Charged.cpp
ABILITYMANAGERCPP = $(SRCPATH)AbilityManager.cpp

#Filepaths for h
GLOBALSH = $(SRCPATH)Globals.h
ENTITYH = $(SRCPATH)Entity.h
CHARACTERH =$(SRCPATH)Character.h
PLAYERH = $(SRCPATH)Player.h
FIGMENTH = $(SRCPATH)Figment.h
BATTLEH = $(SRCPATH)Battle.h
ABILITYH = $(SRCPATH)Ability.h
CHARGEDH = $(SRCPATH)Charged.h
ABILITYMANAGERH = $(SRCPATH)AbilityManager.h

#Filepaths for o
MAINO = $(OBJPATH)Main.o
GLOBALSO = $(OBJPATH)Globals.o
ENTITYO = $(OBJPATH)Entity.o
CHARACTERO =$(OBJPATH)Character.o
PLAYERO = $(OBJPATH)Player.o
FIGMENTO = $(OBJPATH)Figment.o
BATTLEO = $(OBJPATH)Battle.o
ABILITYO = $(OBJPATH)Ability.o
CHARGEDO = $(OBJPATH)Charged.o
ABILITYMANAGERO = $(OBJPATH)AbilityManager.o

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
	g++ $(MAINFLAGS) $(MAINO) $(GLOBALSO) $(ENTITYO) $(CHARACTERO) $(PLAYERO) $(FIGMENTO) $(BATTLEO) $(ABILITYO) $(CHARGEDO) $(ABILITYMANAGERO) -o $(EXE)
$(MAINO): $(ABILITYMANAGERO) $(ABILITYO) $(PLAYERO) $(FIGMENTO) $(BATTLEO) $(MAINCPP) 
	g++ $(CLASSFLAGS) $(MAINCPP) -o $(MAINO)
$(GLOBALSO): $(GLOBALSCPP) $(GLOBALSH)
	g++ $(CLASSFLAGS) $(GLOBALSCPP) -o $(GLOBALSO)
$(ENTITYO): $(ENTITYCPP) $(ENTITYH)
	g++ $(CLASSFLAGS) $(ENTITYCPP) -o $(ENTITYO)
$(CHARACTERO): $(ENTITYO) $(GLOBALSO) $(CHARACTERCPP) $(CHARACTERH)
	g++ $(CLASSFLAGS) $(CHARACTERCPP) -o $(CHARACTERO)
$(PLAYERO): $(CHARACTERO) $(ABILITYO) $(PLAYERCPP) $(PLAYERH)
	g++ $(CLASSFLAGS) $(PLAYERCPP) -o $(PLAYERO)
$(FIGMENTO): $(GLOBALSO) $(CHARACTERO) $(ABILITYO) $(FIGMENTCPP) $(FIGMENTH)
	g++ $(CLASSFLAGS) $(FIGMENTCPP) -o $(FIGMENTO)
$(BATTLEO): $(GLOBALSO) $(PLAYERO) $(FIGMENTO) $(ABILITYMANAGERO) $(BATTLECPP) $(BATTLEH)
	g++ $(CLASSFLAGS) $(BATTLECPP) -o $(BATTLEO)
$(ABILITYO): $(ENTITYO) $(CHARACTERO) $(ABILITYCPP) $(ABILITYH)
	g++ $(CLASSFLAGS) $(ABILITYCPP) -o $(ABILITYO)
$(CHARGEDO): $(ABILITYO) $(CHARGEDCPP) $(CHARGEDH)
	g++ $(CLASSFLAGS) $(CHARGEDCPP) -o $(CHARGEDO)
$(ABILITYMANAGERO): $(ABILITYO) $(CHARGEDO) $(ABILITYMANAGERCPP) $(ABILITYMANAGERH)
	g++ $(CLASSFLAGS) $(ABILITYMANAGERCPP) -o $(ABILITYMANAGERO)

CXX=g++-5
CXXFLAGS=-std=c++14 -Wall -Werror=vla -g
EXEC=cc3k

GAMEOBJ = main.o game.o object.o
CHARACTEROBJ = character.o player.o enemy.o
PLAYEROBJ = shade.o drow.o vampire.o troll.o goblin.o
ENEMYOBJ = human.o dwarf.o halfling.o elf.o orc.o merchant.o dragon.o
ITEMOBJ = item.o gold.o potion.o ladder.o specificPotions.o
GENEROBJ = PlayerGenerator.o EnemyGenerator.o GoldGenerator.o LadderGenerator.o PotionGenerator.o

OBJECTS = ${GAMEOBJ} ${CHARACTEROBJ} ${PLAYEROBJ} ${ENEMYOBJ} ${ITEMOBJ} ${GENEROBJ} 

DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
        ${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean
clean:
        rm ${EXEC} ${OBJECTS} ${DEPENDS}
~

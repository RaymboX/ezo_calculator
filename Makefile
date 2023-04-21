
#\\           //#
# \\         // #
# |\\       //| #
# ||\\     //|| #
# || RAYMBOX || #		MAKEFILE
# ||//     \\|| #		EZO CALCULATOR
# |//       \\| #
# //         \\ #
#//           \\#

#PROGRAM NAME-------------------------------------------------------------------

NAME 			=	ezoCalc

#PROJECT EXPLANATION------------------------------------------------------------
define EXPLANATION
--------------------------------------------------------------------------------
EZO_CALCULATOR - Calculatrice par chaîne de caractères

Vous devez créer une application qui évalue une chaîne de caractères, 
comme si elle avait été entrée dans une calculatrice. 
Votre programme doit accepter une entrée et produire une réponse juste en sortie.

Réglements
Le programme doit:

Être écrit dans le langage orienté-objet de votre choix
Authoriser les nombres à virgule flotante et les nombres négatifs
Supporter au moins les opérateurs de base (+, -, * et /)
Supporter un ou plusieurs espaces entre les opérateurs et les nombres
Respecter la priorité des opérateurs
Avoir un code propre qui respecte les principes de programmation OO
Vous ne pouvez pas:

Copier du code sur Internet
Utiliser du code produit par quelqu'un d'autre
Limitation

L'architecture doit être belle et propre
Le code doit être beau et propre

--------------------------------------------------------------------------------
endef
export EXPLANATION


#TOOLS--------------------------------------------------------------------------
define TOOLS
--------------------------------------------------------------------------------
OUTILS INCLUS DISPONIBLES
make goal		-> Vulgarisation du but de l'exercice
make rules 		-> Ouvre le github des consignes
make leak		-> Execute le programme avec "leaks -- atExit -- " en premice
make valgrind		-> Execute le programme avec "valgrind --leak-check=full " en premice
make tools		-> Affiche les outils disponibles (ceci)
--------------------------------------------------------------------------------
endef
export TOOLS


#FILES AND DIR DEFINE-----------------------------------------------------------------------
SRC_DIR := src
OBJ_DIR := obj
HEAD_DIR:= include
TEST_DIR:= test

DIRS = $(shell find $(SRC_DIR) -type d | sed 's/$(SRC_DIR)\///g' | sed -n '1!p') #list of file in src
SRC_DIRS := $(addprefix $(SRC_DIR)/, $(DIRS)) #src/DIRS
OBJ_DIRS := $(addprefix $(OBJ_DIR)/, $(DIRS)) #obj/DIRS

SRCS = $(wildcard $(SRC_DIR)/*.cpp) #main.cpp
SRCS += $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.cpp)) #all cpp in class

OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS)) #all srcs.cpp are now src.o

HEADERS = $(wildcard $(HEAD_DIR)/*.hpp) #in include
HEADERS += $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.hpp)) #in class

SRCS_TEST = $(wildcard $(TEST_DIR)/*.cpp) #fait la liste des testcase
SRCS_TEST += $(SRCS)	#Ajoute les SRCS
SRCS_TEST := $(filter-out $(SRC_DIR)/main.cpp, $(SRCS_TEST)) #enleve le main.cpp

#SYSTEM VAR---------------------------------------------------------------------

CFLAGS 			:= 	-Wall -Werror -Wextra
CC				:= 	g++
CC_DEBUG		:=	g++ -g

RM				:= 	rm -rf
MKDIR			:= 	mkdir -p
LEAK_CMD		:=	leaks --atExit --
VALGRIND_CMD	:=	valgrind --leak-check=full


R = $(shell tput -Txterm setaf 1)
G = $(shell tput -Txterm setaf 2)
W = $(shell tput -Txterm setaf 7)
C = $(shell tput -Txterm setaf 6)
Y = $(shell tput -Txterm setaf 3)
Z = $(shell tput -Txterm setaf 5)

#COMPILATION--------------------------------------------------------------------

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

#RULES--------------------------------------------------------------------------

all: 	init $(NAME)
.PHONY: all

$(NAME): $(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
			@echo "$G$(NAME) ready!$W"
			@make goal
			@make tools
			
init:
			@$(MKDIR) $(OBJ_DIR)
			@$(MKDIR) $(OBJ_DIRS)
.PHONY: init

clean:
			@$(RM) $(OBJ_DIR)
			@echo "$RObjects removed$W"
.PHONY: clean

fclean: clean
			@$(RM) $(NAME)
			@$(RM) $(NAME)_test
			@$(RM) $(NAME)_debug
			@$(RM) $(NAME)_debug.dSYM
			@echo "$RExecutable $(NAME) deleted$W"
.PHONY: fclean

tools:
			@echo "$C$$TOOLS$W"
.PHONY: tools

goal:
			@echo "$C$$EXPLANATION$W"
.PHONY: goal

leak:
			$(LEAK_CMD) ./$(NAME)
.PHONY: leak

test: fclean
			@$(CC) -D UTEST $(CFLAGS) $(SRCS_TEST) -o $(NAME)_test
			@echo "$GTest compiled....\n$W"
			./$(NAME)_test
			@$(RM) $(NAME)_test
			@echo "$RExecutable $(NAME)_test deleted$W"
.PHONY: test

run: all
	@./$(NAME)

rrun: re run
.PHONY: rrun

valgrind:
			$(VALGRIND_CMD) ./$(NAME)
.PHONY: valgrind

rules:
			@open https://github.com/EzoQC/DefiCode
.PHONY: rules

debug:	fclean
			@$(CC_DEBUG) $(CFLAGS) $(SRCS) -o $(NAME)_debug
			@echo "$YDebbuging executable ready!$W"
.PHONY: debug

re:			fclean all
.PHONY: re

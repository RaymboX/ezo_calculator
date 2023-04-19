
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
#CPP_LIST-----------------------------------------------------------------------
#  find ./*.cpp -type f | cut -c3- | sed 's/$/ \\/'

SRCS_FILES		=	main.cpp \
					Block/Block.cpp \
					Calc/Calc.cpp


#HPP_LIST-----------------------------------------------------------------------
#  find ./*.hpp -type f | cut -c3- | sed 's/$/ \\/'

HEADERS			=	src/Block/Block.hpp \
					src/Calc/Calc.hpp \
					include/colors.hpp



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

#TEST---------------------------------------------------------------------------

TEST_NAME		= 	

#TEST_CPP_LIST
TEST_SRCS		=	

TEST_FILES		=	

#MAINTEST-----------------------------------------------------------------------



#DIRECTORY----------------------------------------------------------------------

SRCS_DIR		=	src
OBJS_DIR		= 	obj

#SYSTEM VAR---------------------------------------------------------------------

CFLAGS 			= 	-Wall -Werror -Wextra
CC				= 	g++
CC_DEBUG		=	g++ -g

RM				= 	rm -rf
LEAK_CMD		=	leaks --atExit --
VALGRIND_CMD	=	valgrind --leak-check=full


R = $(shell tput -Txterm setaf 1)
G = $(shell tput -Txterm setaf 2)
W = $(shell tput -Txterm setaf 7)
C = $(shell tput -Txterm setaf 6)
Y = $(shell tput -Txterm setaf 3)
Z = $(shell tput -Txterm setaf 5)

#SRCS---------------------------------------------------------------------------
SRCS			=	$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))

#OBJ----------------------------------------------------------------------------

OBJS 			= 	$(SRCS:$(SRCS_DIR)%.cpp=$(OBJS_DIR)%.o)
#OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

$(OBJS_DIR)/%.o:%.cpp $(HEADERS)
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
			@mkdir -p $(OBJS_DIR)
.PHONY: init

clean:
			@$(RM) $(OBJS)
			@$(RM) $(OBJS_DIR)
			@echo "$RObjects removed$W"
.PHONY: clean

fclean: clean
			@$(RM) $(NAME)
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

test:
			
.PHONY: test

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

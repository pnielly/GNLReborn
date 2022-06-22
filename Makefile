# ------------- Executable
NAME = gnl

# ------------- Commands & Flags
FLAGS = -Wall -Wextra -Werror
CC = gcc
BUFFER_SIZE= -D BUFFER_SIZE=12

# ------------- SRC, OBJ and INC
SRC_PATH = srcs
HEADER_PATH = includes

SRC = $(wildcard $(SRC_PATH)/*.c)
HEADER = -I $(HEADER_PATH)
OBJ = $(SRC:.c=.o)

# ------------- Colors
BLACK:="\033[1;30m"
RED:="\033[1;31m"
GREEN:="\033[1;32m"
PURPLE:="\033[1;35m"
CYAN:="\033[1;36m"
WHITE:="\033[1;37m"
EOC:="\033[0;0m"

# ------------- Rules
all: $(NAME)
	@printf $(GREEN)"\n\n\t\t ${NAME} ready ! \n\n"$(EOC)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(BUFFER_SIZE)

%.o:%.c
	$(CC) $(FLAGS) $(HEADER) -c $< -o $@ $(BUFFER_SIZE)

clean:
	@rm -rf $(OBJ) *.gch

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
NAME = philo
SRC = philo.c funct.c
OBJ = philo.o funct.o

all : $(NAME)

$(NAME): $(SRC)
	@gcc -Wall -Wextra -Werror $(SRC) -c
	@gcc $(OBJ) -o $(NAME)

clean :
	@rm $(OBJ)

fclean : clean
	@rm $(NAME)
re : fclean all
run : re
	@./$(NAME)
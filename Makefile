SRC = pipex.c utils.c

OBJS = ${SRC:.c=.o}

NAME = pipex

HEADER = pipex.h

LIB = libft/libft.a

OPTION_FLAG = -fsanitize=address

RM = rm -rf

CC = cc

W = -Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${OBJS}
#in windowns/some linux systems "\033[0m" is needed instead of "\e[0m" in order to reset fonts color to default (@echo "\033[33m----Compiling!----\e[0m")
	@echo "\033[33m----Compiling!----\033[0m" 
	@make -C libft
	@${CC} ${W} ${OPTION_FLAG} ${OBJS} ${LIB} -o ${NAME}
	@echo "\033[32m----Pipex Compiled!----\n\033[0m"


%.o : %.c ${HEADER}
	@${CC} ${W} -c $< -o $@

clean : 
	@echo "\033[31m----Cleaning objectes!----\033[0m"
	@make clean -C libft
	@${RM} ${OBJS}
	@echo "\033[32m----Clean!----\033[0m"

fclean : clean
	@echo "\033[31m----cleaning binaries!----\033[0m"
	@make fclean -C libft
	@${RM} ${NAME}
	@echo "\033[32m----All clean!----\033[0m" 

re : fclean all

.SILENT: all clean fclean ${NAME} ${OBJS} ${OPTION_FLAG} ${LIB}

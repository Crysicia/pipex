CC				= gcc
CFLAGS 			= -g -Wall -Wextra -Werror
RM 				= rm -f
HEADERS 		= -I./includes
NAME			= pipex

RAW_SRCS		= main.c \
				  parsing.c \
				  error.c \
				  execution.c \
				  pipes_and_redirections.c \
				  free.c \
				  init.c \
				  lib_split.c \
				  lib_strings.c \
				  lib_utils.c
SRCS			= $(addprefix srcs/, $(RAW_SRCS))
OBJS 			= $(SRCS:.c=.o)

RST				= "\e[0m"
RED				= "\e[31m"
GREEN			= "\e[32m"

.c.o:
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@echo $(GREEN)"Compiling pipex executable ..."$(RST)
	@$(CC) $(OBJS) -o $(NAME)
	@echo $(GREEN)"pipex is ready !\nEnter \"./pipex\" for execution."$(RST)

clean:
	@echo $(RED)"Removing objects and librairies ..."$(RST)
	@$(RM) $(OBJS)

fclean: clean
	@echo $(RED)"Removing pipex..."$(RST)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

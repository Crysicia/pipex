CC				= gcc
CFLAGS 			= -g -Wall -Wextra -Werror
RM 				= rm -f
HEADERS 		= -I./includes -I./libft
LIBS			= -Llibft -lft
LIBFT 			= libft/libft.a
NAME			= pipex

RAW_SRCS		= main.c \
				  parsing.c
SRCS			= $(addprefix srcs/, $(RAW_SRCS))
OBJS 			= $(SRCS:.c=.o)

RST				= "\e[0m"
RED				= "\e[31m"
GREEN			= "\e[32m"

.c.o:
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo $(GREEN)"Compiling pipex executable ..."$(RST)
	@$(CC) $(OBJS) $(LIBS) -o $(NAME)
	@echo $(GREEN)"pipex is ready !\nEnter \"./pipex\" for execution."$(RST)

$(LIBFT):
	@echo $(GREEN)"Compiling libft ..."$(RST)
	@$(MAKE) bonus -C libft

clean:
	@echo $(RED)"Removing objects and librairies ..."$(RST)
	@$(RM) $(OBJS)
	@$(MAKE) fclean -C libft

fclean: clean
	@echo $(RED)"Removing pipex..."$(RST)
	@$(RM) $(NAME) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re

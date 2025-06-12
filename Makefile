CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Files
FILES =   minishell.c utils.c strtok.c expand.c get_env.c unset.c
# Object files
OBJ = $(FILES:.c=.o)

# libft
LIBFT_PATH	= libft
LIBFT		= $(LIBFT_PATH)/libft.a


# Name
NAME = minishell

# Header
HEADER =  includes/minishell.h


# Rules
all: $(NAME) 

$(LIBFT) :
	@make -C $(LIBFT_PATH)

$(NAME): $(OBJ) $(HEADER) $(LIBFT)
	@$(CC) $(FLAGS) $(OBJ)  $(LIBFT) -lreadline  -o $(NAME)

clean:
	@rm -f $(OBJ)
	@make clean -C $(LIBFT_PATH)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH)
re: fclean all

.PHONY: all clean fclean re
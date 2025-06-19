CC			= cc
CFLAGS		= -g -Wall -Wextra -Werror

# Files

FILES		=   parsing/minishell.c parsing/utils.c parsing/tokenizer.c parsing/expand.c parsing/get_env.c \
				parsing/unset.c parsing/split_n_insert.c parsing/rr_quotes.c parsing/export.c

# Object files

OBJ			= $(FILES:.c=.o)

# libft

LIBFT_PATH	= includes/libft
LIBFT		= $(LIBFT_PATH)/libft.a


# Name

NAME 		= minishell

# Header

HEADER 		=  includes/minishell.h


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
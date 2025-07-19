
CC			= cc
CFLAGS		= -g -Wall -Wextra -Werror

# Files
FILES		=   minishell.c \
				parsing/tokenizer.c parsing/expand.c parsing/split_n_insert.c parsing/rr_quotes.c parsing/randomize.c \
				utils/utils00.c utils/utils01.c utils/utils02.c utils/utils03.c utils/utils04.c utils/utils05.c \
				utils/cleaner.c utils/free_all.c \
				builtins/env.c \
				execution/execution.c \
				execution/flow.c execution/fix_path.c execution/pipe.c execution/redirection.c execution/flow_tools.c \
				execution/herdoc.c execution/one_cmd.c  execution/pipe_tools.c \
				#builtins/cd.c builtins/echo.c builtins/export.c builtins/env.c builtins/pwd.c builtins/unset.c \

# Object files

OBJ			= $(FILES:.c=.o)

# Name
NAME 		= minishell

# Header
HEADER 		=  includes/minishell.h


# Rules
all: $(NAME) 

$(NAME): $(OBJ) $(HEADER)
	@$(CC) $(FLAGS) $(OBJ) -lreadline  -o $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
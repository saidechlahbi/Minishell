CC			= cc
CFLAGS		= -g -Wall -Wextra -Werror

# Files
FILES		=   minishell.c \
				parsing/tokenizer.c parsing/expand.c parsing/split_n_insert.c parsing/rr_quotes.c parsing/randomize.c \
				utils/utils00.c utils/utils01.c utils/utils02.c utils/utils03.c utils/utils04.c utils/utils05.c utils/utils06.c \
				utils/cleaner.c utils/free_all.c \
				execution/execution.c \
				execution/flow.c execution/fix_path.c execution/pipe.c execution/redirection.c execution/flow_tools.c \
				execution/herdoc.c execution/one_cmd.c  execution/pipe_tools.c execution/ambiguous.c\
				execution/execute_built_in.c builtins/echo.c builtins/pwd.c builtins/unset.c builtins/env.c \
				builtins/export.c builtins/cd.c builtins/exit.c

OBJ_DIR		= obj
OBJ			= $(FILES:.c=.o)
OBJ			:= $(patsubst %.o, $(OBJ_DIR)/%.o, $(OBJ))

NAME 		= minishell
HEADER 		= includes/minishell.h

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@$(CC) $(CFLAGS) $(OBJ) -lreadline -o $(NAME)

$(OBJ_DIR)/%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

#CC			= cc
#CFLAGS		= -g -Wall -Wextra -Werror

# Files
#FILES		=   minishell.c \
				parsing/tokenizer.c parsing/expand.c parsing/split_n_insert.c parsing/rr_quotes.c parsing/randomize.c \
				utils/utils00.c utils/utils01.c utils/utils02.c utils/utils03.c utils/utils04.c utils/utils05.c utils/utils06.c \
				utils/cleaner.c utils/free_all.c \
				execution/execution.c \
				execution/flow.c execution/fix_path.c execution/pipe.c execution/redirection.c execution/flow_tools.c \
				execution/herdoc.c execution/one_cmd.c  execution/pipe_tools.c \
				execution/execute_built_in.c builtins/echo.c builtins/pwd.c builtins/unset.c builtins/env.c \
				builtins/export.c \
				#builtins/cd.c  builtins/exit.c \

# Object files

#OBJ			= $(FILES:.c=.o)

# Name
#NAME 		= minishell

# Header
#HEADER 		=  includes/minishell.h


# Rules
#all: $(NAME) 

#$(NAME): $(OBJ) $(HEADER)
#	@$(CC) $(FLAGS) $(OBJ) -lreadline  -o $(NAME)

#clean:
#	@rm -f $(OBJ)

#fclean: clean
#	@rm -f $(NAME)

#re: fclean all

#.PHONY: all clean fclean re
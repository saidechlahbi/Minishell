CC			= cc
CFLAGS		= -g -Wall -Wextra -Werror

#Files
FILES		=   minishell.c \
				parsing/tokenizer.c parsing/lexing.c parsing/expand.c parsing/split_n_insert.c parsing/rr_quotes.c \
				parsing/exdoc.c parsing/randomize.c parsing/validate_input.c parsing/handlamb.c parsing/has_dollar.c \
				utils/utils00.c utils/utils01.c utils/utils02.c utils/utils03.c utils/utils04.c utils/utils05.c utils/utils06.c \
				utils/utils07.c utils/cleaner.c utils/free_all.c utils/prompt.c \
				builtins/echo.c builtins/pwd.c builtins/unset.c builtins/env.c builtins/export.c \
				builtins/export_error.c builtins/print_export.c builtins/cd.c builtins/exit.c \
				execution/execution.c \
				execution/execute_built_in.c  execution/flow.c execution/fix_path.c execution/pipe.c execution/redirection.c \
				execution/flow_tools.c  execution/flow_tools2.c execution/herdoc.c execution/one_cmd.c \
				execution/pipe_tools.c execution/pipe_tools2.c

#Object files
OBJ			= $(FILES:.c=.o)

#Name
NAME 		= minishell

#Header
HEADER 		=  includes/minishell.h

#Rules
all: $(NAME) 

$(NAME): $(OBJ) $(HEADER)
	@$(CC) $(FLAGS) $(OBJ) -lreadline  -o $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
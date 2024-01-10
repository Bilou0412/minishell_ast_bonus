SRCS_DIR	=	srcs
OBJS_DIR	=	objs
LIBFT_DIR	=	libft

NAME		=	minishell
SRCS		=	srcs/built-in/cd.c \
				srcs/built-in/env.c \
				srcs/built-in/pwd.c \
				srcs/built-in/export.c \
				srcs/built-in/unset.c \
				srcs/built-in/exit.c \
				srcs/built-in/echo.c \
				srcs/built-in/clear.c \
				srcs/env/own_env.c \
				srcs/env/t_env_utils.c \
				srcs/parser/tokens_utils.c \
				srcs/parser/token_maker.c \
				srcs/parser/token_maker_utils.c \
				srcs/parser/build_ast.c \
				srcs/parser/build_ast_utils.c \
				srcs/parser/heredoc.c \
				srcs/read_and_exec/read_ast.c \
				srcs/read_and_exec/exec.c \
				srcs/read_and_exec/exec_utils.c \
				srcs/read_and_exec/exec_builtins.c \
				srcs/read_and_exec/inits_cmd.c \
				srcs/read_and_exec/inits_cmd_files.c \
				srcs/read_and_exec/inits_cmd_utils.c \
				srcs/read_and_exec/expand.c \
				srcs/read_and_exec/expand_utils.c\
				srcs/error_handler.c \
				srcs/print.c \
				srcs/free.c \
				srcs/main.c \
				srcs/signals_functions.c \

OBJS		=	$(SRCS:$(SRCS)/%.c=$(OBJS_DIR)/%.o)
LIBFT		=	libft/libft.a

CPPFLAGS	=	-I./inc -I./libft/inc
CFLAGS		=	-Wall -Werror -Werror -g3 -lreadline

$(NAME):		$(OBJS)
					$(MAKE) -C $(LIBFT_DIR)
					cc $(CFLAGS) $(CPPFLAGS) $(OBJS) -o $(NAME) $(LIBFT)


$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

all:			$(NAME)

clean:
				$(MAKE) clean -C $(LIBFT_DIR)

fclean:			clean
					rm -f $(NAME)
					rm -f $(LIBFT)

re:				fclean all

# leaks:			all
#     				valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=del.supp ./minishell

.PHONY:			all clean fclean re

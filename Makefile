SRCS_DIR	=	srcs
SRCS_DIR_BONUS = srcs_bonus
OBJS_DIR	=	objs
OBJS_DIR_BONUS = objs_bonus
LIBFT_DIR	=	libft

NAME		=	minishell
NAME_BONUS = minishell_bonus
SRCS		=	srcs/built-in/cd.c \
				srcs/built-in/env.c \
				srcs/built-in/pwd.c \
				srcs/built-in/export.c \
				srcs/built-in/unset.c \
				srcs/built-in/exit.c \
				srcs/built-in/echo.c \
				srcs/env/own_env.c \
				srcs/env/t_env_utils.c \
				srcs/parser/tokens_utils.c \
				srcs/parser/token_maker.c \
				srcs/parser/token_maker_utils.c \
				srcs/parser/build_ast.c \
				srcs/parser/build_ast_utils.c \
				srcs/parser/heredoc.c \
				srcs/parser/heredoc_utils.c \
				srcs/read_and_exec/read_ast.c \
				srcs/read_and_exec/exec.c \
				srcs/read_and_exec/exec_utils.c \
				srcs/read_and_exec/exec_builtins.c \
				srcs/read_and_exec/inits_cmd.c \
				srcs/read_and_exec/inits_cmd_files.c \
				srcs/read_and_exec/inits_cmd_utils.c \
				srcs/read_and_exec/expand.c \
				srcs/read_and_exec/expand_utils.c\
				srcs/read_and_exec/expand_utils_2.c\
				srcs/error_handler.c \
				srcs/print.c \
				srcs/nice_prints.c \
				srcs/free.c \
				srcs/main.c \
				srcs/signals_functions.c \

SRCS_BONUS		=	srcs_bonus/built-in/cd.c \
					srcs_bonus/built-in/env.c \
					srcs_bonus/built-in/pwd.c \
					srcs_bonus/built-in/export.c \
					srcs_bonus/built-in/unset.c \
					srcs_bonus/built-in/exit.c \
					srcs_bonus/built-in/echo.c \
					srcs_bonus/env/own_env.c \
					srcs_bonus/env/t_env_utils.c \
					srcs_bonus/parser/tokens_utils.c \
					srcs_bonus/parser/token_maker.c \
					srcs_bonus/parser/token_maker_utils.c \
					srcs_bonus/parser/build_ast.c \
					srcs_bonus/parser/build_ast_utils.c \
					srcs_bonus/parser/heredoc.c \
					srcs_bonus/parser/heredoc_utils.c \
					srcs_bonus/read_and_exec/read_ast.c \
					srcs_bonus/read_and_exec/exec.c \
					srcs_bonus/read_and_exec/exec_utils.c \
					srcs_bonus/read_and_exec/exec_builtins.c \
					srcs_bonus/read_and_exec/inits_cmd.c \
					srcs_bonus/read_and_exec/inits_cmd_files.c \
					srcs_bonus/read_and_exec/inits_cmd_utils.c \
					srcs_bonus/read_and_exec/expand.c \
					srcs_bonus/read_and_exec/expand_utils.c\
					srcs_bonus/read_and_exec/expand_utils_2.c\
					srcs_bonus/error_handler.c \
					srcs_bonus/print.c \
					srcs_bonus/nice_prints.c \
					srcs_bonus/free.c \
					srcs_bonus/main.c \
					srcs_bonus/signals_functions.c \

OBJS		=	$(SRCS:$(SRCS)/%.c=$(OBJS_DIR)/%.o)
OBJS_BONUS		=	$(SRCS_BONUS:$(SRCS_BONUS)/%.c=$(OBJS_DIR_BONUS)/%.o)
LIBFT		=	libft/libft.a

CPPFLAGS	=	-I./inc -I./libft/inc
CFLAGS		=	-Wall -Werror -Werror -g3 -lreadline

$(NAME):		$(OBJS)
					$(MAKE) -C $(LIBFT_DIR)
					cc $(CFLAGS) $(CPPFLAGS) $(OBJS) -o $(NAME) $(LIBFT)

$(NAME_BONUS):		$(OBJS_BONUS)
					$(MAKE) -C $(LIBFT_DIR)
					cc $(CFLAGS) $(CPPFLAGS) $(OBJS_BONUS) -o $(NAME_BONUS) $(LIBFT)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJS_DIR_BONUS)/%.o: $(SRCS_DIR_BONUS)/%.c | $(OBJS_DIR_BONUS)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

all:			$(NAME)

bonus:			$(NAME_BONUS)

clean:
				$(MAKE) clean -C $(LIBFT_DIR)

fclean:			clean
					rm -f $(NAME)
					rm -f $(NAME_BONUS)
					rm -f $(LIBFT)

re:				fclean all

# leaks:			all
#     				valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=del.supp ./minishell

.PHONY:			all clean fclean re

SRCS_DIR	=	srcs
OBJS_DIR	=	objs
LIBFT_DIR	=	libft

NAME		=	minishell
SRCS		=	srcs/parser/tokens_utils.c \
				srcs/parser/token_maker.c \
				srcs/parser/token_maker_utils.c \
				srcs/parser/fill_ast.c \
				srcs/parser/fill_ast_utils.c \
				srcs/read_and_exec/read_ast.c \
				srcs/read_and_exec/read_ast_utils.c \
				srcs/read_and_exec/pipex.c \
				srcs/read_and_exec/inits.c \
				srcs/read_and_exec/inits_utils.c \
				srcs/read_and_exec/builtin_exec.c \
				srcs/built-in/cd.c \
				srcs/built-in/env.c \
				srcs/built-in/pwd.c \
				srcs/built-in/export.c \
				srcs/built-in/unset.c \
				srcs/print.c \
				srcs/free.c \
				srcs/main.c \

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

.PHONY:			all clean fclean re

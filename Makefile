SRCS_DIR	=	srcs
OBJS_DIR	=	objs
LIBFT_DIR	=	libft

NAME		=	minishell
SRCS		=	srcs/parser/tokens_utils.c \
				srcs/parser/token_maker.c \
				srcs/parser/token_maker_utils.c \
				srcs/parser/fill_ast.c \
				srcs/parser/fill_ast_utils.c \
				srcs/print.c \
				srcs/main.c \
				srcs/free.c \

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
				$(MAKE) fclean -C $(LIBFT_DIR)

fclean:			clean
					rm -f $(NAME)

re:				fclean all

.PHONY:			all clean fclean re

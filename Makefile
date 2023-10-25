SRC_DIR			=		srcs
OBJ_DIR			=		objs
LIBFT_DIR		=		libft

NAME			=		minishell
SRC				=		srcs/scanner/list_utils.c \
						srcs/scanner/tok_mak.c \
						srcs/scanner/tok_utils.c \
						srcs/print.c \
						srcs/fill_ast.c \
						srcs/main.c \
						srcs/free.c \

OBJ				=		$(SRC:$(SRC)/%.c=$(OBJ_DIR)/%.o)
LIBFT			=		libft/libft.a

CPPFLAGS		=		-I./include -I./libft/include
CFLAGS			=		-Wall -Werror -Werror -g3 -lreadline

$(NAME):				$(OBJ)
							$(MAKE) -C $(LIBFT_DIR)
							cc $(CFLAGS) $(CPPFLAGS) $(OBJ) -o $(NAME) $(LIBFT)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

all:					$(NAME)
						
clean:
						$(MAKE) fclean -C $(LIBFT_DIR)

fclean:					clean
							rm -f $(NAME)

re:						fclean all

.PHONY:					all clean fclean re

NAME		=	minishell

HEADER		=	inc/

LIBFT		=	libft/libft.a

CC			=	gcc

CFLAGS		=	-Werror -Wall -Wextra -g -I $(HEADER)  #-fsanitize=address

SRCS		=	srcs/scanner/list_utils.c \
				srcs/scanner/tok_mak.c \
				srcs/scanner/tok_utils.c \
				srcs/main.c \
				srcs/free.c \


OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(LIBFT) $(HEADER)
				$(CC) $(CFLAGS) $(OBJS) -lreadline -o  $(NAME) $(LIBFT)

$(LIBFT)	:
				make -C ./libft

clean		:
				rm -rf $(OBJS)
				make clean -C ./libft

fclean		:	clean
				rm $(NAME)
				make fclean -C ./libft

re			:	fclean all

#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmoudach <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/04 19:39:31 by bmoudach          #+#    #+#              #
#    Updated: 2023/05/13 14:28:11 by bmoudach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	ft_isalnum.c ft_isprint.c ft_memcmp.c  ft_putchar_fd.c ft_split.c \
			ft_strlcat.c ft_strncmp.c ft_substr.c ft_atoi.c ft_isalpha.c \
			ft_itoa.c ft_memcpy.c  ft_putendl_fd.c ft_strchr.c  ft_strlcpy.c \
			ft_strnstr.c ft_tolower.c ft_bzero.c ft_isascii.c \
			ft_memmove.c ft_putnbr_fd.c  ft_strdup.c ft_strlen.c ft_strrchr.c \
			ft_toupper.c ft_calloc.c ft_isdigit.c ft_memchr.c ft_memset.c  \
			ft_putstr_fd.c ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_striteri.c \
			ft_printf.c ft_putchar.c ft_puthexa.c ft_putnbr.c ft_putptr.c ft_putstr.c \
			ft_put_text.c ft_put_unsigned.c get_next_line.c ft_last_index.c ft_free_tab.c \
			ft_free_third_tab.c ft_print_third_tab.c ft_print_tab.c get_next_line_utils.c \


OBJS		=	$(SRCS:.c=.o)

BONUS		=	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
			ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
			ft_lstmap.c ft_lstnew.c ft_lstsize.c

TRY		=	ft_isalnum.c ft_isprint.c ft_memcmp.c ft_putchar_fd.c \
			ft_strncmp.c ft_isalpha.c ft_calloc.c ft_strjoin.c ft_strtrim.c \
			ft_strchr.c ft_memmove.c ft_memcpy.c ft_strlcat.c ft_itoa.c \
			ft_tolower.c ft_bzero.c   ft_isascii.c ft_substr.c \
			ft_strlen.c  ft_strrchr.c ft_strlcpy.c ft_strnstr.c ft_striteri.c \
			ft_toupper.c ft_isdigit.c ft_memchr.c ft_strdup.c ft_putnbr_fd.c \

BONUS_OBJS	=	$(BONUS:.c=.o)

TRY_OBJS	=	$(TRY:.c=.o)

CC		= 	gcc

RM		= 	rm -f

CFLAGS		= -g3 -Wall -Wextra -Werror -I.

NAME		=	libft.a

all:			$(NAME)

$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)
clean:
				$(RM) $(OBJS) $(BONUS_OBJS)
so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRCS)
	gcc -nostartfiles -shared -o libft.so $(OBJS)
fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

bonus:			$(OBJS) $(BONUS_OBJS)
				ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)
try:			$(TRY_OBJS)
				ar rcs $(NAME) $(TRY_OBJS)

.PHONY:			all clean fclean re bonus

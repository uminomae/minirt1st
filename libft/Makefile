# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/27 04:23:00 by hioikawa          #+#    #+#              #
#    Updated: 2023/01/28 03:14:29 by uminomae         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= libft.a
CC			:= cc
RM			:= rm -f
CFLAGS		:= -Wall -Wextra -Werror
SRCS		:= 	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_isblank.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c \

#SRCS_B		:=	ft_lstnew.c \
#	ft_lstadd_front.c \
#	ft_lstsize.c \
#	ft_lstlast.c \
#	ft_lstadd_back.c \
#	ft_lstdelone.c \
#	ft_lstclear.c \
#	ft_lstiter.c \
#	ft_lstmap.c \

OBJS	= $(SRCS:%.c=%.o)

#B_OBJS	= $(SRCS_B:%.c=%.o)

#ifdef WITH_BONUS
#	OBJS += $(B_OBJS)
#endif

all:		$(NAME)

$(NAME):	$(OBJS)
	ar rcs  $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS) $(B_OBJS)

fclean:	clean
	$(RM) $(NAME)

re: fclean all

#bonus: 
#	make WITH_BONUS=1

.PHONY: all clean fclean re
#.PHONY: all clean fclean re bonus

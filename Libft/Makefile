# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/12 15:06:17 by kmaeda            #+#    #+#              #
#    Updated: 2025/06/27 15:10:52 by kmaeda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I. -I$(GNL_DIR) -I$(PRINTF_DIR)

GNL_DIR = get_next_line
GNL_SRCS = $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c \
	   $(GNL_DIR)/get_next_line_bonus.c $(GNL_DIR)/get_next_line_utils_bonus.c

PRINTF_DIR = ft_printf
PRINTF_SRCS = $(PRINTF_DIR)/ft_printf.c $(PRINTF_DIR)/ft_printnbr.c \
	      $(PRINTF_DIR)/ft_printptr.c $(PRINTF_DIR)/ft_printstr.c \
	      $(PRINTF_DIR)/ft_printunbr.c $(PRINTF_DIR)/ft_puthex_fd.c

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
	ft_atoi.c ft_strdup.c ft_calloc.c ft_itoa.c ft_substr.c ft_split.c \
	ft_strjoin.c ft_strtrim.c ft_strmapi.c ft_striteri.c ft_putstr_fd.c \
	ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c $(GNL_SRCS) $(PRINTF_SRCS)

BONUS_SRCS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS = $(SRCS:%.c=%.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

bonus:	$(OBJS) $(BONUS_OBJS)
	ar -rcs $(NAME) $(OBJS) $(BONUS_OBJS)

%.o: %.c libft.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

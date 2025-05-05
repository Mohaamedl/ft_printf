# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/05 14:08:57 by mhaddadi          #+#    #+#              #
#    Updated: 2025/05/05 14:20:14 by mhaddadi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                              ft_printf MAKEFILE                              #
# **************************************************************************** #

NAME			= libftprintf.a

cc				= cc
CFLAGS		= -Wall -Wextra -Werror
ARFLAGS		= rcs
RM				= rm -f

#sources

SRCS			= ft_printf.c ft_printnbr.c ft_printunbr.c ft_printchar.c \
						ft_printnchar.c ft_printstr.c ft_parse_format.c ft_printptr \
						ft_conversion_handler.c 

OBJS			= $(SRCS :.c=.o)


all: $(NAME)

$(NAME):
	ar $(ARFLAGS) $@ $^

%.o : %.c
	$(CC) -c $(CFLAGS) $^ -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:fclean all

.PHONY: all clean fclean re

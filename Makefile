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

NAME				= libftprintf.a

CC					= cc
CFLAGS			= -Wall -Wextra -Werror
ARFLAGS			= rcs
RM					= rm -rf

#sources

SRCS				= ft_printf.c ft_printnbr.c ft_printunbr.c ft_printchar.c \
							ft_putnchar.c ft_printstr.c ft_parse_format.c ft_printptr.c \
							ft_conversion_handler.c ft_printpercent.c \
							ft_printhex.c ft_uitoa.c

TEST				= test.c

OBJS_DIR		= objs
OBJS				= $(SRCS:.c=.o)

LIBFT_PATH	= ./libft
LIBFT				= $(LIBFT_PATH)/libft.a

%.o : %.c
	$(CC) -c $(CFLAGS) $^  -o $@

all: $(NAME)

bonus: all

$(NAME): $(LIBFT) $(OBJS)
	cp	$(LIBFT) $(NAME)
			ar $(ARFLAGS) $(NAME) $(OBJS)

$(LIBFT): 
	make -C $(LIBFT_PATH) all
$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$()

clean:
	make -C $(LIBFT_PATH) clean
	$(RM) $(OBJS)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	$(RM) $(NAME)
test : $(NAME)
	git fetch originArch
	git checkout FETCH_HEAD -- test.c
	$(CC) $(CFLAGS) $(TEST) $(NAME) -o test
		./test

re:fclean all

.PHONY: all bonus clean fclean re libft

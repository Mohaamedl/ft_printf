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

# **************************************************************************** #
#                                CONFIGURATION                                 #
# **************************************************************************** #

NAME        = libftprintf.a
CC          = cc
CFLAGS      = -Wall -Wextra -Werror

SRC_DIR     = src
OBJ_DIR     = obj
LIBFT_DIR   = libft
TEST_DIR    = test
UNITY_DIR   = unity
BUILD_DIR   = build

SRC         = \
	$(SRC_DIR)/ft_printf.c \
	$(SRC_DIR)/ft_conversion_handler.c \
	$(SRC_DIR)/ft_parse_format.c \
	$(SRC_DIR)/ft_printchar.c \
	$(SRC_DIR)/ft_printhex.c \
	$(SRC_DIR)/ft_printnbr.c \
	$(SRC_DIR)/ft_printpercent.c \
	$(SRC_DIR)/ft_printptr.c \
	$(SRC_DIR)/ft_printstr.c \
	$(SRC_DIR)/ft_printunbr.c \
	$(SRC_DIR)/ft_putnchar.c \
	$(SRC_DIR)/ft_uitoa.c

OBJ         = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

LIBFT_A     = $(LIBFT_DIR)/libft.a

TEST_SRC    = $(TEST_DIR)/test_printf.c
TEST_BIN    = $(BUILD_DIR)/test.out

# **************************************************************************** #
#                                BUILD RULES                                   #
# **************************************************************************** #

all: $(NAME)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -I$(SRC_DIR) -c $< -o $@

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT_A)
	ar rcs $(NAME) $(OBJ)

# **************************************************************************** #
#                                 CLEAN RULES                                  #
# **************************************************************************** #

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(BUILD_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

bonus: all

# **************************************************************************** #
#                                 TEST RULES                                   #
# **************************************************************************** #

.PHONY: test init-unity

init-unity:
	@if [ ! -f "$(UNITY_DIR)/src/unity.c" ]; then \
		echo "Initializing Unity submodule..."; \
		git submodule update --init --recursive; \
	fi

test: init-unity $(TEST_BIN)
	@./$(TEST_BIN)

$(TEST_BIN): $(TEST_SRC) $(SRC) $(LIBFT_A) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(UNITY_DIR)/src -I$(SRC_DIR) -I$(LIBFT_DIR) \
		$(UNITY_DIR)/src/unity.c $(TEST_SRC) $(SRC) $(LIBFT_A) -o $(TEST_BIN)


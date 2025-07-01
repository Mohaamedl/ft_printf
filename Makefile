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
# === Project Configuration ===
NAME				=	libftprintf.a
CC					=	cc
CFLAGS			=	-Wall -Wextra -Werror

SRC_DIR     =	src
LIBFT_DIR   =	libft
BUILD_DIR   =	build
TEST_EXEC		=	run_tests
TEST_DIR		=	test
UNITY_DIR		=	unity
UNITY_URL		= https://github.com/ThrowTheSwitch/Unity.git
LIBFT				= libft
TEST_SRC = \
	$(TEST_DIR)/test_printf.c

UNITY_SRC = \
	$(UNITY_DIR)/src/unity.c

TEST_OBJ = \
	$(BUILD_DIR)/test_printf.o

UNITY_OBJ = \
	$(BUILD_DIR)/unity.o

# === Source Files ===

SRC_MAIN = \
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
	$(SRC_DIR)/ft_uitoa.c \
	$(SRC_DIR)/ft_hex_helper.c

SRC_LIBFT = \
	$(LIBFT_DIR)/ft_bzero.c \
	$(LIBFT_DIR)/ft_isdigit.c \
	$(LIBFT_DIR)/ft_atoi.c \
	$(LIBFT_DIR)/ft_strlen.c \
	$(LIBFT_DIR)/ft_strdup.c \
	$(LIBFT_DIR)/ft_itoa.c

SRC = $(SRC_MAIN)
#$(SRC_LIBFT)

# === Object Files ===

OBJ_MAIN = $(SRC_MAIN:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
OBJ_LIBFT = $(SRC_LIBFT:$(LIBFT_DIR)/%.c=$(BUILD_DIR)/libft_%.o)
OBJ = $(OBJ_MAIN)
#$(OBJ_LIBFT)

#build/test_printf.o: test/test_printf.c | build 
#	$(CC) $(CFLAGS) -I$(SRC_DIR) -I$(LIBFT_DIR) -Iunity/src -c $< -o $@

#build/main.o: test/main.c | build
#	$(CC) $(CFLAGS) -I$(SRC_DIR) -I$(LIBFT_DIR) -Iunity/src -c $< -o $@

#build/test_utils.o: test/test_utils.c | build
#	$(CC) $(CFLAGS) -I$(SRC_DIR) -I$(LIBFT_DIR) -Iunity/src -c $< -o $@

#build/unity.o: unity/src/unity.c | build
#	$(CC) $(CFLAGS) -Iunity/src -c $< -o $@

# === Rules ===

all: $(NAME)

bonus: all

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFT)
	ar rcs $(NAME) $(OBJ)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(LIBFT) -c $< -o $@

$(BUILD_DIR)/libft_%.o: $(LIBFT_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

test: pull_tests unity_init $(NAME) $(TEST_OBJ) $(UNITY_OBJ) compile_tests
	./$(TEST_EXEC)

build/test_printf.o: test/test_printf.c | build 
	$(CC) $(CFLAGS) -I$(SRC_DIR) -I$(LIBFT) -Iunity/src -c $< -o $@

build/unity.o: unity/src/unity.c | build
	$(CC) $(CFLAGS) -Iunity/src -c $< -o $@

compile_tests:
	$(CC) $(CFLAGS) $(TEST_SRC) $(UNITY_OBJ) $(NAME) $(LIBFT_DIR)/$(LIBFT).a -o $(TEST_EXEC)

pull_tests:
	git fetch origin test
	git checkout origin/test -- test

unity_init:
	git submodule add $(UNITY_URL) $(UNITY_DIR)
	git submodule update --init --recursive unity

clean:
	rm -rf $(BUILD_DIR)

fclean: clean clean_tests
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT) fclean
	
re: fclean all

clean_tests:
	rm -fr $(TEST_EXEC) $(TEST_OBJ) $(UNITY_OBJ) $(TEST_DIR) $(BUILD_DIR) $(UNITY_DIR)

.PHONY: all clean fclean re test compile_tests clean_tests


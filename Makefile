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

TEST_SRC = \
	$(TEST_DIR)/test_printf.c

UNITY_SRC = \
	$(UNITY_DIR)/src/unity.c

TEST_OBJ = \
	$(BUILD_DIR)/test_printf.o

UNITY_OBJ = \
	$(BUILD_DIR)/unity.o

# === Source Files ===

SRC = \
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


# === Object Files ===

OBJ = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# === Rules ===

all: $(NAME)

bonus: all

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFT_DIR)
	ar rcs l$(NAME) $(OBJ)
	ar x l$(NAME)
	ar x $(LIBFT_DIR)/libft.a
	ar rcs $(NAME) *.o



$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -I$(SRC_DIR) -c $< -o $@


$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

test: pull_tests unity_init $(NAME) $(TEST_OBJ) $(UNITY_OBJ) compile_tests
	./$(TEST_EXEC)

build/test_printf.o: test/test_printf.c | build 
	$(CC) $(CFLAGS) -I$(SRC_DIR) -I$(LIBFT_DIR) -Iunity/src -c $< -o $@

build/unity.o: unity/src/unity.c | build
	$(CC) $(CFLAGS) -Iunity/src -c $< -o $@

compile_tests:
	$(CC) $(CFLAGS) $(TEST_SRC) $(UNITY_OBJ) $(NAME) $(LIBFT_DIR)/libft.a -o $(TEST_EXEC)

pull_tests:
	git remote add originHome https://github.com/Mohaamedl/ft_printf.git
	git fetch originHome main
	git checkout originHome/main -- test unity 

unity_init:	
	git rm -rf $(UNITY_DIR) 
	git submodule add $(UNITY_URL) $(UNITY_DIR) 
	git submodule update --init --recursive $(UNITY_DIR)


$(UNITY_DIR):
	mkdir -p $(UNITY_DIR)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean clean_tests
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	
re: fclean all

clean_tests:
	rm -fr $(TEST_EXEC) $(TEST_OBJ) $(UNITY_OBJ) $(TEST_DIR) $(BUILD_DIR) $(UNITY_DIR)

.PHONY: all clean fclean re test compile_tests clean_tests

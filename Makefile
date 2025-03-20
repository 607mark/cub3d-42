# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/05 12:31:45 by rkhakimu          #+#    #+#              #
#    Updated: 2025/03/20 09:31:40 by rkhakimu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project and Compiler Settings
NAME = cub3d

# Directories
INC_DIR		= ./inc
SRC_DIR		= ./src
ERROR_DIR	= $(SRC_DIR)/error_handling
PARSE_DIR	= $(SRC_DIR)/parsing
LIBFT_DIR	= ./lib/Libft
MLX42_DIR	= ./lib/MLX42
FREE_DIR	= $(SRC_DIR)/freeing

# Source Files
SRCS =		$(SRC_DIR)/main.c \
			$(ERROR_DIR)/error_handling.c \
			$(PARSE_DIR)/flood_fill.c \
			$(PARSE_DIR)/parsing.c \
			$(PARSE_DIR)/parsing_color.c \
			$(PARSE_DIR)/reading_map.c \
			$(PARSE_DIR)/validation.c \
			$(PARSE_DIR)/loading_textures.c \
			$(FREE_DIR)/freeing.c

OBJS		= $(SRCS:.c=.o)

# Compiler Flags
CFLAGS		= -g -Wall -Werror -Wextra
INCLUDES	= -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX42_DIR)/include

# Platform-specific library linking
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	LDFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX42_DIR)/build -lmlx42 -ldl -lglfw -pthread -lm
else ifeq ($(UNAME_S), Darwin)
	LDFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX42_DIR)/build -lmlx42 -lglfw -framework Cocoa -framework OpenGL -framework IOKit
endif

# Library Targets
LIBFT		= $(LIBFT_DIR)/libft.a
MLX42		= $(MLX42_DIR)/build/libmlx42.a

RM			= rm -rf

.PHONY: all clean fclean re

# Default target
all: $(LIBFT) $(MLX42) $(NAME)

$(LIBFT):
	@echo "Building Libft library..."
	@make -C $(LIBFT_DIR) --no-print-directory

$(MLX42):
	@echo "Building MLX42 library..."
	@if [ ! -d "$(MLX42_DIR)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX42_DIR); \
	fi
	cmake -S $(MLX42_DIR) -B $(MLX42_DIR)/build
	make -C $(MLX42_DIR)/build -j4 --no-print-directory

$(NAME): $(OBJS)
	@echo "Compiling cub3d..."
	@cc $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "Success!"

%.o: %.c
	@cc $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "Deleting object files..."
	@$(RM) $(OBJS)
	@make clean -C $(LIBFT_DIR) --no-print-directory
	@$(RM) $(MLX42_DIR)/build

fclean: clean
	@echo "Deleting cub3d and libraries..."
	@$(RM) $(NAME) $(LIBFT)
	@$(RM) $(MLX42_DIR)

re: fclean all
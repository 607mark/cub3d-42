# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/05 12:31:45 by rkhakimu          #+#    #+#              #
#    Updated: 2025/03/24 11:18:05 by rkhakimu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project and Compiler Settings
NAME        := cub3D
CC          := cc
CFLAGS      := -Wall -Wextra -ggdb3

# Directories
SRC_DIR     := src
OBJ_DIR     := obj
LIB_DIR     := lib

# Libraries and Includes
MLX_DIR     := $(LIB_DIR)/MLX42
LIBFT_DIR   := $(LIB_DIR)/Libft
MLX         := $(MLX_DIR)/build/libmlx42.a
LIBFT       := $(LIBFT_DIR)/libft.a

HEADERS     := -I ./inc -I $(MLX_DIR)/include/MLX42 -I $(LIBFT_DIR)

# Platform-specific library linking
UNAME_S     := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
    LIBS := -L$(LIBFT_DIR) -lft $(MLX) -ldl -lglfw -pthread -lm
else ifeq ($(UNAME_S), Darwin)
    LIBS := -L$(LIBFT_DIR) -lft $(MLX) -lglfw -L/opt/homebrew/Cellar/glfw/3.4/lib/ -pthread -lm
endif

# Source files
SRC         := main.c \
			error_handling/error_handling.c \
			parsing/flood_fill.c \
			parsing/parsing.c \
			parsing/parsing_color.c \
			parsing/reading_map.c \
			parsing/validation.c \
			parsing/loading_textures.c \
			freeing/freeing.c \
			graphics/render.c \
			graphics/drawing.c 
               
SRCS        := $(addprefix $(SRC_DIR)/, $(SRC))
OBJ         := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Phony targets
.PHONY: all clean fclean re

# Default target
all: $(NAME)

# Build the executable
$(NAME): $(LIBFT) $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) $(HEADERS) -o $@

# Rule to create the object directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

# Library building rules
$(LIBFT):
	@echo "Building Libft library..."
	@make -C $(LIBFT_DIR)

$(MLX):
	@echo "Building MLX42 library..."
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR); \
	fi
	cmake $(MLX_DIR) -B $(MLX_DIR)/build
	make -C $(MLX_DIR)/build -j4

# Clean up object files and intermediate build directories
clean:
	rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)
	# @make clean -C $(MLX_DIR)/build
	@echo "Object files and build directories cleaned."

# Full clean, including libraries and binaries
fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)
	# rm -rf $(MLX_DIR)
	@echo "Fully cleaned project, including libraries and executable."

# Rebuild everything from scratch
re: fclean all

help:
	@echo "Available targets:"
	@echo "  all     - Build the executable"
	@echo "  clean   - Remove object files and build directories"
	@echo "  fclean  - Clean everything including libraries and executable"
	@echo "  re      - Rebuild everything from scratch"
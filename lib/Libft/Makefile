# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/25 13:18:21 by rkhakimu          #+#    #+#              #
#    Updated: 2025/03/20 12:17:18 by rkhakimu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler Settings
NAME		= libft.a
CC			= cc
CFLAGS		= -Wall -Wextra -Werror

# Directories
SRC_DIR		= .
OBJ_DIR		= obj

# Source Files
SRCS = \
	ft_isascii.c ft_memcpy.c ft_strlcat.c ft_strrchr.c ft_bzero.c \
	ft_isdigit.c ft_memmove.c ft_strlcpy.c ft_tolower.c ft_calloc.c \
	ft_isprint.c ft_memset.c ft_strlen.c ft_toupper.c ft_isalnum.c \
	ft_memchr.c ft_strchr.c ft_strncmp.c ft_isalpha.c ft_memcmp.c \
	ft_strdup.c ft_strnstr.c ft_atoi.c ft_substr.c \
	ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
	ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	ft_putnbr_fd.c ft_printchar.c ft_printf.c ft_printhex.c \
	ft_printhex_ptr.c ft_printnbr.c ft_printstr.c ft_printunbr.c \
	get_next_line_bonus.c get_next_line_utils_bonus.c \
	ft_isspace.c ft_strcmp.c ft_realloc.c \
	ft_abs.c ft_min.c ft_max.c ft_custom_puts.c

SRCS_BONUS = \
	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

# Object Files
OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)
OBJS_BONUS	= $(SRCS_BONUS:%.c=$(OBJ_DIR)/%.o)

# Phony Targets
.PHONY: all clean fclean re bonus

# Default Target
all: $(NAME)

# Library Creation
$(NAME): $(OBJS)
	@ar -rcs $(NAME) $(OBJS)
	@echo "Libft is ready"

# Bonus Target
bonus: $(OBJS) $(OBJS_BONUS)
	@ar -rcs $(NAME) $(OBJS) $(OBJS_BONUS)
	@echo "Libft with bonus is ready"

# Object File Compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Create Object Directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Clean Object Files
clean:
	@rm -rf $(OBJ_DIR)
	@echo "Object files removed"

# Full Clean
fclean: clean
	@rm -f $(NAME)
	@echo "Libft fully cleaned"

# Rebuild
re: fclean all

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amwahab <amwahab@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/21 21:54:46 by amwahab           #+#    #+#              #
#    Updated: 2025/07/22 00:43:41 by amwahab          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fdf

CC		= cc
CFLAGS	= -Wall -Wextra -Werror

SRC		= fdf.c pasring.c controls.c draw.c gnl/get_next_line.c gnl/get_next_line_utils.c 
OBJ		= $(SRC:.c=.o)

LIBFT_DIR	= Libft
LIBFT		= $(LIBFT_DIR)/libft.a

MLX		= -Lmlx -lmlx -lXext -lX11

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)
	@echo "libft ok"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(MLX) -lm
	@echo "fdf ok"

gnl_ok:
	@echo "gnl ok"

clean:
	@$(MAKE) -s clean -C $(LIBFT_DIR)
	@rm -f $(OBJ)

fclean: clean
	@$(MAKE) -s fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
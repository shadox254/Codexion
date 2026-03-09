# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/06 11:16:38 by rruiz             #+#    #+#              #
#    Updated: 2026/03/09 10:09:40 by rruiz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	codexion
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -pthread
RM		=	rm -rf

INC_DIR	=	includde
SRC_DIR	=	src
OBJ_DIR	=	obj

MAIN	=	main.c

SRC		=	codexion.c \
			parsing/args_verification.c \
			parsing/rules_management.c \
			parsing/create_struct.c \
			utils/debug.c \
			utils/error.c

SRCS	=	$(MAIN) $(addprefix $(SRC_DIR)/, $(SRC))
OBJS	=	$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SILENT:
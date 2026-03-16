# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/06 11:16:38 by rruiz             #+#    #+#              #
#    Updated: 2026/03/16 17:04:20 by rruiz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	codexion
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -pthread
RM		=	rm -rf

INC_DIR	=	-I coders/include
SRC_DIR	=	coders
OBJ_DIR	=	obj

SRC		=	main.c \
			codexion.c \
			engine/action.c \
			engine/monitoring.c \
			engine/mutex.c \
			engine/thread.c \
			init/data.c \
			init/init_coders_dongles.c \
			parsing/args_verification.c \
			parsing/rules_management.c \
			schedulers/fifo.c \
			schedulers/fifo_utils.c \
			utils/debug.c \
			utils/error.c \
			utils/time.c \
			utils/utils.c

SRCS	=	$(MAIN) $(addprefix $(SRC_DIR)/, $(SRC))
OBJS	=	$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SILENT:
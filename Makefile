# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/06 11:16:38 by rruiz             #+#    #+#              #
#    Updated: 2026/03/21 10:57:53 by rruiz            ###   ########.fr        #
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
			init/initialization.c \
			parsing/args_verification.c \
			parsing/rules_management.c \
			schedulers/edf.c \
			schedulers/fifo.c \
			utils/debug.c \
			utils/edf_utils.c \
			utils/error.c \
			utils/fifo_utils.c \
			utils/heap_utils.c \
			utils/time.c \
			utils/utils.c

SRCS	=	$(MAIN) $(addprefix $(SRC_DIR)/, $(SRC))
OBJS	=	$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

GREEN			=	\033[32m
BLUE			=	\033[34m
RESET			=	\033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(BLUE)codexion compiled$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(GREEN)$< compiled$(RESET)"
	@$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)
	@echo "$(BLUE)Objects cleaned$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(BLUE)Executable cleaned$(RESET)"

re: fclean all

.PHONY: all clean fclean re
.SILENT:
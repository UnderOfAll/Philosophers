# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: karocha- <karocha-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/09 19:21:18 by karocha-          #+#    #+#              #
#    Updated: 2025/06/20 20:44:55 by karocha-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo
CC		=	@cc
CFLAGS	=	-Wall -Wextra -Werror -pthread #-fsanitize=thread -g

SOURCE	=	source/
OBJ_DIR	=	obj/

SRC 	=	main.c \
			parser.c \
			helpers.c \
			init.c \
			threads.c \
			thread_utils.c 
OBJ		=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

#COLORS
RESET	= \033[0m
BOLD	= \033[1m
YELLOW	= \033[33m
RED		= \033[31m
GREEN	= \033[32m
CYAN 	= \033[36m
BLUE	= \033[34m
MAGENTA	= \033[35m

all: $(NAME)

$(OBJ_DIR):
	@echo "$(BOLD)$(BLUE)Making objects..$(RESET)\n"
	@mkdir -p $(OBJ_DIR) || { echo "$(RED)ERROR: Failed creating objects.$(RESET)"; exit 1; }
	@echo "$(GREEN)Objects created!$(RESET)\n"

$(OBJ_DIR)%.o: $(SOURCE)%.c | $(OBJ_DIR)
	@echo "$(BOLD)$(MAGENTA)Compiling..$(RESET)\n"
	$(CC) $(CFLAGS) -c $< -o $@ || { echo "$(RED)ERROR: Compilation error.$(RESET)"; exit 1; }

$(NAME): $(OBJ)
	@echo "$(BOLD)$(MAGENTA)Working on program..$(RESET)\n"	
	$(CC) $(CFLAGS) $(OBJ) -o $@ || { echo "$(RED)ERROR: Program creation error.$(RESET)"; exit 1; }
	@echo "$(BOLD)$(GREEN)Program created succesfully!$(RESET)\n"
clean:
	@echo "$(BOLD)$(YELLOW)Cleaning objects..$(RESET)\n"
	@rm -rf $(OBJ_DIR)
	@echo "$(BOLD)$(CYAN)All object files were cleaned$(RESET)\n"

fclean: clean
	@echo "$(BOLD)$(YELLOW)Cleaning all files...$(RESET)\n"	
	@rm -rf $(NAME)
	@echo "$(BOLD)$(CYAN)All files were cleaned$(RESET)\n"

re: fclean all

.PHONY: all re clean fclean
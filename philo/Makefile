# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fraalmei <fraalmei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/23 13:16:54 by fraalmei          #+#    #+#              #
#    Updated: 2023/07/21 13:49:51 by fraalmei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##Colors #
RED		= @echo "\033[0;31m"
GREEN	= @echo "\033[0;32m"
BLUE	= @echo "\033[0;33m"
PURPLE	= @echo "\033[0;34m"
CYAN	= @echo "\033[0;35m"
RESET	= "\033[1;0m"

#	file's name
NAME	= philo

#	compilation
CC		= gcc

#	options to force the remove
RM		= /bin/rm -f

#	flags
#------------------------------------------------------------------------------
CFLAGS	= -Wall -Werror -Wextra #-pedantic

#EXTRA_FLAGS = -S #create the program or archive to assembler

LEAK_FLAGS	= -fsanitize=thread -g3 #-fsanitize=address 

INCLUDES	= -I $(INCLUDE_DIR) -pthread

#------------------------------------------------------------------------------

# Directories
BIN_DIR		= bin
SRC_DIR		= srcs
SRCS		= main.c util.c philosophers.c threads.c parse.c
INCLUDE_DIR	= include		# path to headers

# Convert source files to binary
OBJS = $(SRCS:%.c=$(BIN_DIR)/%.o) $(UTILS:%.c=$(BIN_DIR)/%.o)

all: $(NAME)

restart: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) -o $(NAME)

$(NAME): $(BIN) $(OBJS)
	@echo "\033[0;32mCompiling philo..."
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) -o $(NAME)
	@echo "\n\033[0mDone !"

#	Objects construction
$(OBJS): $(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@printf "\033[0;33mGenerating philo objects... %-33.33s\r" $@
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

re: fclean all

releaks: fclean leaks

leaks: $(BIN) $(OBJS)
	@echo "\033[0;32mCompiling philo with sanitizer..."
	$(CC) $(CFLAGS) $(LEAK_FLAGS) $(OBJS) $(INCLUDES) -o $(NAME)
	@echo "\n\033[0mDone !"

clean:
	@echo "\nRemoving binaries..."
	@$(RM) $(OBJS)
	@$(RM) -r $(BIN_DIR)
	@echo "\033[0m"

fclean: clean
	@echo "\nDeleting executable..."
	@$(RM) $(NAME)
	@echo "\033[0m"

show:
	@printf "NAME		: $(NAME)\n"
	@printf "CC  		: $(CC)\n"
	@printf "CFLAGS		: $(CFLAGS)\n"
	@printf "SRCS		: $(SRCS)\n"
	@printf "OBJS		: $(OBJS)\n"

.PHONY: $(LIBFT) all clean fclean re

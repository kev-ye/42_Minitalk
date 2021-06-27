# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/27 13:39:40 by kaye              #+#    #+#              #
#    Updated: 2021/06/27 15:32:32 by kaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COMPILATION

CC		= clang
CFLAGS 	= -Wall -Wextra -Werror
LFLAGS	= -L./libft -lft
IFLAGS 	= -I./libft/inc -I./incs

# DIRECTORIES

BUILD 			:= .build
INC_DIR			:= incs
SRC_DIR 		:= srcs
LFT_DIR			:= libft
OBJ_DIR 		:= $(BUILD)/obj
DIRS			:= $(OBJ_DIR) $(addprefix $(OBJ_DIR)/, $(SUB_DIR))

# FILES

SERVER			:= server
CLIENT			:= client
SRC_SERVER		:= server.c
SRC_CLIENT		:= client.c
OBJ_SERVER		:= $(SRC_SERVER:%.c=$(OBJ_DIR)/%.o)
OBJ_CLIENT		:= $(SRC_CLIENT:%.c=$(OBJ_DIR)/%.o)

# COLORS

DEFAULT_COLOR	= \033[0m
BLACK_COLOR		= \033[1;30m
RED_COLOR		= \033[1;31m
GREEN_COLOR		= \033[1;32m
YELLOW_COLOR	= \033[1;33m
BLUE_COLOR		= \033[1;34m
MAGENTA_COLOR 	= \033[1;35m
CYAN_COLOR 		= \033[1;36m

# MAKEFILE

$(SERVER): $(OBJ_SERVER) $(OBJ_CLIENT)
	@$(MAKE) -C $(LFT_DIR)
	@echo "Creating $(RED_COLOR) $(SERVER) $(DEFAULT_COLOR)..."
	@$(CC) $(CFLAG) $(OBJ_SERVER) $(IFLAGS) $(LFLAGS) -o $(SERVER)
	@echo "$(GREEN_COLOR)Compilation $(YELLOW_COLOR)of $(RED_COLOR)$(SERVER) $(BLUE_COLOR)done$(DEFAULT_COLOR)"
	@echo "Creating $(RED_COLOR) $(CLIENT) $(DEFAULT_COLOR)..."
	@$(CC) $(CFLAG) $(OBJ_CLIENT) $(IFLAGS) $(LFLAGS) -o $(CLIENT)
	@echo "$(GREEN_COLOR)Compilation $(YELLOW_COLOR)of $(RED_COLOR)$(CLIENT) $(BLUE_COLOR)done$(DEFAULT_COLOR)"

all: $(SERVER)

clean:
	@$(MAKE) -C $(LFT_DIR) clean >/dev/null
	rm -Rf $(BUILD)
fclean: clean
	@$(MAKE) -C $(LFT_DIR) fclean >/dev/null
	rm -Rf server
	rm -Rf client

re: fclean all

.PHONY: all clean fclean re

$(BUILD):
	@echo "Creating $(RED_COLOR)$@ $(DEFAULT_COLOR)..."
	@mkdir $@ $(DIRS);

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c | $(BUILD)
	@echo "Compiling $(CYAN_COLOR)$< $(DEFAULT_COLOR)..."
	@$(CC) $(CFLAG) $(IFLAGS) -c $< -o $@
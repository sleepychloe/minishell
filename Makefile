# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/24 15:50:04 by yhwang            #+#    #+#              #
#    Updated: 2023/08/21 21:11:23 by yhwang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RESET		:= $(shell tput -Txterm sgr0)
YELLOW		:= $(shell tput -Txterm setaf 3)

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
RM = rm -f

LIBFT_DIR = ./libft
LIBFT_NAME = libft.a
LIBFT = $(addprefix $(LIBFT_DIR)/, $(LIBFT_NAME))

FILES =	main \
		signal \
		parse \
		parse_token_error_1 \
		parse_token_error_2 \
		parse_pos_error \
		parse_dollar_quote \
		parse_env_variable \
		parse_utils \
		lib_utils

INCS_DIR = ./incs

SRCS_DIR = ./srcs

SRCS = $(addprefix $(SRCS_DIR)/, $(addsuffix .c, $(FILES)))
OBJS = $(addprefix $(SRCS_DIR)/, $(addsuffix .o, $(FILES)))

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCS_DIR)

all: $(LIBFT_NAME) $(NAME)

$(LIBFT_NAME):
	@make -C $(LIBFT_DIR)
	@echo "$(YELLOW)libft compiled!$(RESET)"

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@ -I$(INCS_DIR) -lreadline
	@echo "$(YELLOW)🐥 minishell compiled 🐥$(RESET)"

clean:
	@make clean -C $(LIBFT_DIR)
	@echo "$(YELLOW)deleted object files for libft$(RESET)"
	$(RM) $(OBJS)
	@echo "$(YELLOW)deleted object files for minishell$(RESET)"

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@echo "$(YELLOW)deleted libft executable$(RESET)"
	$(RM) $(NAME)
	@echo "$(YELLOW)deleted minishell executable$(RESET)"

re: fclean all

.PHONY : all clean fclean re

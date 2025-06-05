# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/19 10:26:16 by vtrofyme          #+#    #+#              #
#    Updated: 2025/05/19 10:26:19 by vtrofyme         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex
NAME_BONUS	= pipex_bonus
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g3

SRCS		= main.c forks.c path_command.c
SRCS_BONUS	= src_bonus/main_bonus.c src_bonus/forks_bonus.c \
				src_bonus/path_command_bonus.c src_bonus/here_doc_bonus.c

OBJS		= $(SRCS:.c=.o)
OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C libft
	$(CC) $(OBJS) -L libft -lft -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	$(MAKE) -C libft
	$(CC) $(OBJS_BONUS) -L libft -lft -o $(NAME_BONUS)

clean:
	$(MAKE) -C libft clean
	@rm -f	$(OBJS)
	@rm -f	$(OBJS_BONUS)

fclean: clean
	$(MAKE) -C libft fclean
	@rm -f	$(NAME)
	@rm -f	$(NAME_BONUS)

re: fclean all

.PHONY: clean fclean re all bonus

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
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g3

SRCS		=	main.c forks.c path_command.c

OBJS		=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C libft
	$(CC) $(OBJS) -L libft -lft -o $(NAME)

clean:
	$(MAKE) -C libft fclean
	@rm -f	$(OBJS)

fclean: clean
	$(MAKE) -C libft fclean
	@rm -f	$(NAME)libft

re: fclean all

.PHONY: clean fclean re all bonus

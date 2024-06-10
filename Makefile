# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/10 12:46:50 by amakela           #+#    #+#              #
#    Updated: 2024/06/10 12:46:53 by amakela          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	=	philo

INCLUDE =	philo.h

CC		=	cc
CFLAGS 	=	-Wall -Wextra -Werror

CFILES	=	main.c

OFILES	= $(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $(NAME)

clean:
	@rm -rf $(OFILES)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

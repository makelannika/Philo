# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/10 12:46:50 by amakela           #+#    #+#              #
#    Updated: 2024/06/18 19:56:32 by amakela          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	=	philo

INCLUDE =	include/philo.h

CC		=	cc
CFLAGS 	=	-Wall -Wextra -Werror

CFILES	=	src/main.c		src/arg_validation.c	\
			src/utils.c		src/initialization.c	\
			src/routine.c	src/threading.c			

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

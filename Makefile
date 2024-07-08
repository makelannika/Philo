# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/10 12:46:50 by amakela           #+#    #+#              #
#    Updated: 2024/07/08 16:06:15 by amakela          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	=	philo

INCLUDE =	-I ./include

CC		=	cc
CFLAGS 	=	-Wall -Wextra -Werror

CFILES	=	src/main.c			src/arg_validation.c	\
			src/utils.c			src/initialization.c	\
			src/routine.c		src/threading.c			\
			src/supervisor.c	src/cleaning.c

OFILES	= $(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $(NAME)
	
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

clean:
	@rm -rf $(OFILES)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

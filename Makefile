# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oqatim <oqatim@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/29 17:51:02 by oqatim            #+#    #+#              #
#    Updated: 2022/10/03 16:13:31 by oqatim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

HEADER = philosof.h

CC = gcc

FLAGS = -Wall -Wextra -Werror 

SRC =	philo.c utils.c creat_philo.c utils_philo.c
	
OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME) : $(OBJ) $(HEADER)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	@rm -f *.o 

fclean: clean
	@rm -f philo

re: fclean all
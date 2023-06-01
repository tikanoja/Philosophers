# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tuukka <tuukka@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/24 13:00:33 by ttikanoj          #+#    #+#              #
#    Updated: 2023/03/20 13:34:55 by ttikanoj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = ./philosophers.c philosophers_utils.c routine.c routine_utils.c ft_atoi.c

OBJ = ./philosophers.o philosophers_utils.o routine.o routine_utils.o ft_atoi.o

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	cc $(FLAGS) $(OBJ) -pthread -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

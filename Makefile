# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 15:14:03 by dabae             #+#    #+#              #
#    Updated: 2024/04/25 07:20:43 by dabae            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo
SRC= $(wildcard src/*.c)
OBJ= $(SRC:.c=.o)
CFLAGS= -Wall -Wextra -Werror
CC= gcc -g -lpthread -fsanitize=thread

all: $(NAME)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(NAME): $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
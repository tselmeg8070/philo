# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/05 16:51:42 by tadiyamu          #+#    #+#              #
#    Updated: 2023/05/27 21:03:13 by tadiyamu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
FILES = main \
		ft_atoi_check \
		ft_atoi \
		philo_actions \
		philo_loop \
		philo_loop_conditions \
		philo_parser

SRCS = $(addsuffix .c, $(FILES))
OBJS = $(addsuffix .o, $(FILES))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS)  -fsanitize=thread -g -o $(NAME) $^

.c.o: $(SRCS)
	$(CC) $(CFLAGS)  -fsanitize=thread -g -c -o $@ $<

clean:
	rm -f $(OBJS) $(OBJS_B)

fclean: clean
	rm -f $(NAME) $(NAME_B)

re: fclean all

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 13:01:45 by ichaiq            #+#    #+#              #
#    Updated: 2023/03/28 13:23:29 by ichaiq           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = pipex
HDRS = pipex.h
LIB = libft/libft.a
SRC = pipex.c utils.c parse_utils.c 
	

OBJECTS = $(SRC:.c=.o)

CC = cc
CFLAGS += -Wall -Wextra -Werror

all: $(NAME) pipex.h

$(LIB):
	make bonus -C libft 
	make clean

$(NAME) : $(OBJECTS) $(LIB)
	$(CC) $(CFLAGS) $^ -o $@ 

%.o: %.c $(LIB)
	$(CC) -c $< -o $@ $(CFLAGS) 


clean:
	make clean -C libft/
	rm -f $(OBJECTS)

fclean: clean
	make fclean -C libft/
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re run 
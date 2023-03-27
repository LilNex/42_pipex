
NAME = pipex
HDRS = pipex.h
SOURCES = pipex.c
LIB= libft/libft.a
SRC =utils.c file_utils.c parse_utils.c pipex.c 
	

OBJECTS = $(SRC:.c=.o)

CC = cc
CFLAGS += -Wall -Wextra -Werror

all: $(NAME)

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
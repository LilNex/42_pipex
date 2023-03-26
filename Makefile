
NAME = pipex
HDRS = pipex.h
SOURCES = pipex.c
LIB= libft/libft.a
GNL= gnl/get_next_line_bonus.c gnl/get_next_line_utils_bonus.c
SRC =utils.c file_utils.c parse_utils.c pipex.c 
	

OBJECTS = $(SRC:.c=.o)

CC = cc
CFLAGS += -Wall -Wextra -Werror

all: $(NAME) pipex.h

$(LIB):
	make -C libft 
	make clean

$(NAME) : $(OBJECTS) $(LIB)
	$(CC) $(CFLAGS) $^ -o $@ 


# build: pipex.h
# 	cd $(LIB) && make bonus
# 	cp $(LIB)libft.a .
# 	gcc $(SRC) $(GNL) libft.a $(CFLAGS) -o $(NAME)
# 	# clear

%.o: %.c $(LIB)
	$(CC) -c $< -o $@ $(CFLAGS) 


clean:
	rm -f $(OBJECTS) $(BOBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all bonus

.PHONY: all bonus clean fclean re run 
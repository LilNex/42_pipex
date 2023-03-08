
NAME = pipex.out
HDRS = pipex.h
SOURCES = pipex.c
LIB= libft/
GNL= gnl/get_next_line_bonus.c gnl/get_next_line_utils_bonus.c
	

OBJECTS = $(SOURCES:.c=.o)

CC = cc
CFLAGS += -Wall -Wextra -Werror

all: build $(NAME)


build:
	cd $(LIB) && make bonus
	cp $(LIB)libft.a .
	gcc pipex.c utils.c file_utils.c $(GNL) libft.a $(CFLAGS)
	clear



run: build 
	clear
	./a.out

debug: 
	echo "Debbugging mode ..."
	sleep 1
	run
	sleep 3
	clear
	debug

# %.o: %.c $(HDRS)
# 	$(CC) -c  $(CFLAGS) $<

clean:
	rm -f $(OBJECTS) $(BOBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all bonus

.PHONY: all bonus clean fclean re run 
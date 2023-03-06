
NAME = pipex.out
HDRS = pipex.h
SOURCES = pipex.c
LIB= libft/
	

OBJECTS = $(SOURCES:.c=.o)

CC = cc
CFLAGS += -Wall -Wextra -Werror

all: build $(NAME)


build:
	cd $(LIB) && make bonus
	cp $(LIB)libft.a .
	gcc pipex.c utils.c file_utils.c libft.a $(CFLAGS)
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
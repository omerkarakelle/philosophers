SRCS= philosophers.c checkargs.c main.c utils.c
CC= gcc
CFLAGS= -Wall -Werror -Wextra
NAME=philo

SRCS = checkargs.c \
	dead_check.c \
	main.c \
	utils.c \
	philosophers.c

OBJS = $(SRCS:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) 

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm $(OBJS)

fclean: clean
	rm $(NAME)

re: fclean all

.PHONY:	all clean fclean re
SRCS= philosophers.c checkargs.c main.c utils.c
CC= gcc
CFLAGS= -Wall -Werror -Wextra
NAME=philo
LIB=philo.h
RM= rm -rf

SRCS = checkargs.c \
	dead_check.c \
	main.c \
	utils.c \
	philosophers.c \
	init.c

OBJS = $(SRCS:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) 

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re

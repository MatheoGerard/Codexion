NAME = codexion

SRCS = srcs/ft_atoi.c srcs/parsing.c srcs/ft_strcmp.c\
       srcs/validate.c srcs/error.c srcs/validate_utils.c\
       srcs/init_coders.c srcs/init_table.c\
       srcs/init_dongle.c srcs/routine.c\
       main.c
HEADER = header
OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I $(HEADER) -c $< -o $@ -g

clean: 
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

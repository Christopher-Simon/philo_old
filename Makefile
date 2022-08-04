NAME =	philo
CC=gcc
CFLAGS=	-Wall -Wextra -Werror -g3 -g -pthread 

SRCS=	main.c \
sc_threading.c\
sc_time.c\

RM= rm -f
OBJ= $(SRCS:.c=.o)

INCS= -I inc

all : $(MY_LIB) $(NAME)

$(NAME) :  $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(INCS)

.c.o :
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@ 

testv : all
	valgrind ./$(NAME)

clean :	
	$(RM) $(OBJ) $(BOBJ)

fclean : clean
	$(RM) $(NAME)

re : 	
		make fclean
		make all

.PHONY : all clean fclean re bonus

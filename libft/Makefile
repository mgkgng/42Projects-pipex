SRCS =	ft_bzero.c ft_calloc.c ft_putchar_fd.c ft_putendl_fd.c ft_putstr_fd.c \
		ft_split.c ft_strchr.c ft_strcmp.c ft_strdup.c ft_strjoin.c ft_strlen.c \
		ft_strncmp.c ft_strcat.c ft_realloc.c ft_memcpy.c get_next_line.c 

NAME = libft.a

INCLUDE = -I../includes/

OBJS = ${SRCS:.c=.o}

CFLAG = -Wextra -Wall -Werror

all:		${NAME}

${NAME}:	${OBJS}
			ar rc ${NAME} ${OBJS}
			
.c.o:
			gcc ${CFLAG} ${INCLUDE} -c $< -o ${<:.c=.o}
			
clean:	
			rm -f ${OBJS} ${BOJS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:	all clean fclean re

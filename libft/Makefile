NAME = libft.a

LIB_SRC	=	../libft

SRC = ft_atoi.c \
			ft_bzero.c \
			ft_countwords.c \
			ft_memalloc.c \
			ft_strjoin.c \
			ft_strsplit.c \
			ft_putstr.c	\
			ft_strstr.c \
			ft_strlen.c	\
			ft_strsub.c \
			ft_strcat.c	\
			ft_memcpy.c	\
			ft_strchr.c	\
			ft_memdel.c \
			ft_strcpy.c	\
			ft_strncpy.c \
			ft_putchar.c \
			ft_strdel.c	\
			ft_strndup.c \
			ft_strdup.c	\
			ft_putendl.c \
			ft_strnew.c \
			ft_lstnew.c \
			ft_lstadd.c \
			ft_get_next_line.c \
			ft_free.c \
			ft_memset.c \
			ft_strcmp.c \
			ft_strupper.c \
			ft_toupper.c \
			ft_isdigit.c

OBJ = $(addprefix $(LIB_SRC)/, $(SRC:.c=.o))

INC = ../libft

all: $(NAME)

$(NAME): $(OBJ) 
	@ar rcs $(NAME) $(OBJ)
	@ranlib $(NAME)

$(LIB_SRC)/%.o: $(LIB_SRC)/%.c $(INC)/libft.h
	@gcc -c -Wall -Werror -Wextra $< -o $@ -I $(INC)

clean:
	@/bin/rm -f $(OBJ)

fclean:
	@/bin/rm -f $(NAME) $(OBJ)

re: fclean all

.PHONY: re all clean fclean
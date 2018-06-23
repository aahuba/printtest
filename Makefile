NAME =				libftprintf.a

CC =				gcc
FLAGS =				-Wall -Werror -Wextra

FT_SRC_DIR =		./libft
PRINTF_SRC_DIR =	./ftprintf
OBJDIR =			objs/


HEADER =			$(FT_SRC_DIR)libft.h
PRINTF_SRC_HEADER =	$(PRINTF_SRC_DIR)ft_printf.h

FT_COMPILED =		ft_atoi.o \
			ft_bzero.o \
			ft_countwords.o \
			ft_memalloc.o \
			ft_strjoin.o \
			ft_strsplit.o \
			ft_putstr.o	\
			ft_strstr.o \
			ft_strlen.o	\
			ft_strsub.o \
			ft_strcat.o	\
			ft_memcpy.o	\
			ft_strchr.o	\
			ft_memdel.o \
			ft_strcpy.o	\
			ft_strncpy.o \
			ft_putchar.o \
			ft_strdel.o	\
			ft_strndup.o \
			ft_strdup.o	\
			ft_putendl.o \
			ft_strnew.o \
			ft_lstnew.o \
			ft_lstadd.o \
			ft_get_next_line.o \
			ft_free.o \
			ft_memset.o \
			ft_strcmp.o \
			ft_strupper.o \
			ft_toupper.o \
			ft_isdigit.o

PRINTF_COMPILED =	ft_printf.o ft_format_s.o ft_format_percent.o ft_format.o ft_format_p.o ft_itoa_base.o
COMPILED =			$(FT_COMPILED) $(PRINTF_COMPILED)
OBJECTS = $(addprefix ${OBJDIR}, ${COMPILED})

all: $(NAME)

$(NAME): $(COMPILED)
	@ar rc $(NAME) $(COMPILED)
	@ranlib $(NAME)
	@echo "made" $(NAME)

$(FT_COMPILED): %.o: $(FT_SRC_DIR)/%.c
	@$(CC) -c $(FLAGS) -I $(FT_SRC_DIR) $< -o $@

$(PRINTF_COMPILED): %.o: $(PRINTF_SRC_DIR)/%.c
	@$(CC) -c $(FLAGS) -I $(FT_SRC_DIR) -I $(PRINTF_SRC_DIR) $< -o $@

clean:
	@-/bin/rm -f $(COMPILED)
	@ make clean -C libft/

fclean: clean
	@-/bin/rm -f $(NAME)
	@-/bin/rm -f $(COMPILED)
	@ make fclean -C libft/

re: fclean all

.PHONY: all re fclean
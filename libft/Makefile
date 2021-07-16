NAME		= libft.a

SRCS =		ft_atoi.c \
			ft_itoa.c \
			ft_count_char.c \
			ft_endline.c \
			ft_isdigit.c \
			ft_putchar.c \
			ft_putendl.c \
			ft_putstr.c \
			ft_simbcount.c \
			ft_split.c \
			ft_strchr.c \
			ft_strcpy.c \
			ft_strdup.c \
			ft_strjoin.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strnstr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_trim.c \
			ft_strncmp.c \
			get_next_line.c

OBJS		= $(SRCS:.c=.o)

AR			= ar rc

RM			= rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
			$(AR) $(NAME) $(OBJS)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

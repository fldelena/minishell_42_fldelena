NAME		=	minishell

SRCFD		=	srcs
PARSER_PATH	=	folder_check_comm

SRC			=	minishell.c \
				make_arguments.c \
				work_command.c \
				work_command_utils.c \
				ft_echo.c \
				ft_env.c \
				ft_cd.c \
				ft_export.c \
				mallocs.c \
				pipe.c \
				binary_work.c \
				free.c

PARSER_FILE	=	check_command.c \
				dollar_main.c \
				dollar_utils.c

SRCS 	= $(addprefix $(SRCFD)/, $(SRC)) $(addprefix $(PARSER_PATH)/, $(PARSER_FILE))

OBJS		=	$(SRCS:.c=.o)
LIBFT		=	libft.a

CC			=	gcc
CFLAGS		=	-g -Wall -Wextra -Werror
INCLUDES	=	-I libft/ -I includes/
FTFLAGS		=	-lft

RM			=	rm -f

all:		$(NAME)

$(NAME):	$(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) -I includes/ -L . $(FTFLAGS) -lreadline

$(LIBFT): libft/
			@$(MAKE) -C libft/
			@mv libft/$(LIBFT) .

clean:
			$(RM) $(OBJS) 
			$(MAKE) -C libft/ fclean
			$(RM) $(LIBFT)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re


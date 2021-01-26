NAME		=	minishell

HEADER		=	./includes/

LIBFT		=	libft/libft.a

CC			=	gcc

FLAGS		=	-Werror -Wall -Wextra -I $(HEADER) -fsanitize=address

SRCS		=	srcs/main.c \
				srcs/parsing/sep.c \
				srcs/parsing/pip.c \
				srcs/parsing/cmdargs.c \
				srcs/parsing/protec.c \
				srcs/parsing/redir.c \
				srcs/shell/pipe.c \
				srcs/shell/system.c \
				srcs/shell/execution.c \

OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(LIBFT) $(HEADER)
				$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LIBFT)

$(LIBFT)	:
				make -C ./libft

clean		:
				rm -rf $(OBJS)
				make clean -C ./libft

fclean		:	clean
				rm $(NAME)
				make fclean -C ./libft

re			:	fclean all

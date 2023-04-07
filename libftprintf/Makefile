# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/14 17:56:37 by maserrie          #+#    #+#              #
#    Updated: 2023/03/31 20:21:07 by maserrie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#ALIAS

CFLAGS = -Wall -Werror -Wextra -g
CC = gcc
RM = rm -fr
INC = -I ${LIBFT_PATH}/inc -I ./inc/
NAME = libftprintf.a
LIBFT_PATH = ./libft/
LIBFT = libft/libft.a

#COLOR

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

#SRCS

PRE_SRC =	ft_printf.c\
			ft_printf_funct.c\
			ft_putunsigned.c\
			ft_putchar.c\
			ft_putstr.c\
			ft_putnbr.c\
			ft_puthexa.c\
			ft_atoi_printf.c\

SRCS = $(addprefix src/, ${PRE_SRC})
OBJS = $(patsubst src%, obj%, $(SRCS:.c=.o))

#COMMANDES

all: obj ${NAME}

${NAME}:: ${LIBFT}

${NAME}:: ${OBJS}
	@ar rc ${NAME} ${OBJS}
	@ranlib ${NAME}

${LIBFT}:
	@make -sC ${LIBFT_PATH} all
	@cp ${LIBFT} ${NAME}

bonus: all

obj:
	@mkdir obj

obj/%.o: src/%.c
	@${CC} ${CFLAGS} ${INC} -o $@ -c $<

clean:
	@make -sC ${LIBFT_PATH} fclean
	@${RM} obj

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY = all clean fclean re

all: obj ${NAME}

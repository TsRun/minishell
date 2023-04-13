# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/14 17:56:37 by maserrie          #+#    #+#              #
#    Updated: 2023/04/13 02:11:09 by maserrie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#ALIAS

CFLAGS = -Wall -Werror -Wextra -g
CC = gcc
RM = rm -fr
INC = -I ./inc
NAME = libft.a

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

FUNCT_1 =	ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_memchr.c\
			ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strdup.c ft_strlcat.c\
			ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c\
			ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c\
			ft_toupper.c ft_tolower.c ft_calloc.c

FUNCT_2 =	ft_striteri.c ft_strmapi.c ft_substr.c ft_strjoin.c ft_strtrim.c\
			ft_split.c ft_itoa.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c\
			ft_putnbr_fd.c

FUNCT_BONUS = ft_lstnew.c ft_lstdelone.c ft_lstclear.c ft_lstadd_front.c ft_lstadd_back.c\
			  ft_lstsize.c ft_lstlast.c ft_lstiter.c ft_lstmap.c\

PART_1 = $(addprefix part1/, $(FUNCT_1))
PART_2 = $(addprefix part2/, $(FUNCT_2))
PART_BONUS = $(addprefix bonus/, ${FUNCT_BONUS})
OBJS_PART1 = $(patsubst part1%, obj%, $(PART_1:.c=.o))
OBJS_PART2 = $(patsubst part2%, obj%, $(PART_2:.c=.o))
OBJS_BONUS = $(patsubst bonus%, obj%, $(PART_BONUS:.c=.o))

#COMMANDES

all: obj ${NAME}

${NAME}::${OBJS_PART1}
	@ar rc ${NAME} ${OBJS_PART1}

${NAME}:: ${OBJS_PART2}
	@ar rcs ${NAME} ${OBJS_PART2}
	@ranlib ${NAME}

${NAME}::${OBJS_BONUS}
	@ar rcs ${NAME} $^
	@ranlib ${NAME}

clean:
	@${RM} ${OBJS_BONUS}
	@${RM} obj

obj:
	@mkdir -p obj

fclean: clean
	@${RM} ${NAME}

obj/%.o: part1/%.c
	@${CC} ${CFLAGS} ${INC} -o $@ -c $<

obj/%.o: bonus/%.c
	@${CC} ${CFLAGS} ${INC} -o $@ -c $<

obj/%.o: part2/%.c
	@${CC} ${CFLAGS} ${INC} -o $@ -c $<

re: fclean all

.PHONY = all clean fclean re

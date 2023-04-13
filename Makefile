# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/14 17:56:37 by maserrie          #+#    #+#              #
#    Updated: 2023/04/13 04:21:30 by maserrie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#ALIAS

INC			= -I ./inc -I ./libftprintf/inc -I ./libftprintf/libft/inc
CC 			= cc
RM 			= rm -fr
NAME 		= ./minishell
CFLAGS 		= -Wall -Werror -Wextra -g
PRINTF 		= ./libftprintf/libftprintf.a
LIB			= -L./libftprintf -lftprintf

ifeq ($(shell uname), Linux)
	CFLAGS += -lreadline
	LIB += -lreadline
else
	INC += -I/usr/local/opt/readline/include
	LIB += -L/usr/local/opt/readline/lib -lreadline
endif

#COLOR

DEF_COLOR	=	\033[0;39m
ORANGE		=	\033[0;33m
GRAY		=	\033[0;90m
RED		=		\033[0;91m
GREEN		=	\033[1;92m
YELLOW		=	\033[1;93m
BLUE		=	\033[0;94m
MAGENTA		=	\033[0;95m
CYAN		=	\033[0;96m
WHITE		=	\033[0;97m

#SRCS

MAIN =	main.c ft_parse.c ft_free.c ft_memory.c ft_chained.c ft_command.c\
		ft_create_word.c ft_signal.c ft_chained2.c ft_utils.c ft_free2.c\
		ft_env.c ft_command2.c ft_env2.c ft_gest_redir.c

SRCS = $(addprefix srcs/, ${MAIN})

OBJS = $(patsubst srcs%, obj%, $(SRCS:.c=.o))

#COMMANDES

all: obj ${NAME}

obj/%.o: srcs/%.c ${NAME}_functs
	@${CC} ${CFLAGS} ${INC} -o $@ -c $<
	@echo "Compiling ${CYAN}$< ${DEF_COLOR}"

obj:
	@mkdir -p obj/

${NAME}:: ${PRINTF}

${PRINTF}::
	@echo "${GREEN}Compiling ftprintf [...]${DEF_COLOR}"

${PRINTF}::
	@make -sC ./libftprintf

${PRINTF}::
	@echo "${GREEN}${PRINTF}${DEF_COLOR} created"

${NAME}:: ${OBJS}
	@${CC} -o ${NAME} ${CFLAGS} ${OBJS} ${LIB}

${NAME}::
	@echo "${GREEN}${NAME}${DEF_COLOR} created"

bonus: all

clean:
	@${RM} ${OBJS}
	@${RM} obj
	@echo "${MAGENTA}Cleaning philo"
	@make -sC ./libftprintf fclean

fclean: clean
	@${RM} ${NAME}

clean_doss:
	@${RM} ${OBJS}
	@${RM} obj
	@${RM} ${NAME}

rere: clean_doss all

re: fclean all

.PHONY = all clean fclean re

#LIBRAIRIES

%functs:
	@printf "${ORANGE} 🏁 🏁 Compiling $@ [...]${DEF_COLOR}\n"

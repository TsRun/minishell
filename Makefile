# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/14 17:56:37 by maserrie          #+#    #+#              #
#    Updated: 2023/04/16 19:47:38 by maserrie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#ALIAS

INC			= -I ./inc -I ./libftprintf/inc -I ./libftprintf/libft/inc
CC 			= cc
RM 			= rm -fr
NAME 		= ./minishell
CFLAGS 		= -g -Wall -Werror -Wextra
PRINTF 		= ./libftprintf/libftprintf.a
LIB			= -L./libftprintf -lftprintf -lreadline

ifeq ($(shell uname), Linux)
	CFLAGS += -lreadline
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

UTILS = ft_free.c ft_free2.c ft_memory.c ft_str_realloc.c ft_utils.c ft_chained.c ft_chained2.c

PARSE = ft_parse.c ft_create_word.c ft_wildcard.c ft_wildcard_utils.c ft_binary_tree.c

EXECUTE =	ft_command.c ft_command2.c ft_execute_command.c ft_compute_tree.c ft_compute_tree_utils.c\
			ft_builtin_cd.c ft_builtin.c ft_builtin_echo.c ft_env.c ft_env2.c

MAIN =	main.c ft_signal.c ${addprefix utils/, ${UTILS}} ${addprefix parse/, ${PARSE}} ${addprefix execute/, ${EXECUTE}}

SRCS = $(addprefix srcs/, ${MAIN})

OBJS = $(patsubst srcs%, obj%, $(SRCS:.c=.o))

#COMMANDES

all: obj ${NAME}

obj/%.o: srcs/%.c ${NAME}_functs
	@${CC} ${CFLAGS} ${INC} -o $@ -c $<
	@echo "Compiling ${CYAN}$< ${DEF_COLOR}"

obj:
	@mkdir -p obj/
	@mkdir -p obj/utils/
	@mkdir -p obj/parse/
	@mkdir -p obj/execute/

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

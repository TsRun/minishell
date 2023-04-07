/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:12:13 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/07 20:09:55 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>

# define RESET	"\033[0;39m"
# define ORANGE		"\033[0;33m"
# define GRAY		"\033[0;90m"
# define RED			"\033[0;91m"
# define GREEN		"\033[1;92m"
# define YELLOW		"\033[1;93m"
# define BLUE		"\033[0;94m"
# define MAGENTA		"\033[0;95m"
# define CYAN		"\033[0;96m"
# define WHITE		"\033[0;97m"

typedef struct s_string
{
	char	*str;
	int		mal_len;
	int		r_len;
	int		is_redir;
}	t_string;

typedef struct s_arg
{
	char			*str;
	int				redir;
	int				num;
	struct s_arg	*next;
	struct s_arg	*prev;
}	t_arg;

typedef struct s_env
{
	t_arg		*list;
	char		lastchar;
	int			j;
	int			k;
	int			len;
	int			mal_len;
	char		*line;
	t_string	word;
	char		**env;
	char		**args;
	char		*cmd;
}	t_env;

t_env	*ft_parse(char *line, char **env);

void	ft_end(t_env *split);

void	ft_add_rline(t_env *split, char c);

void	ft_realline(t_env *split);

void	ft_free(t_env *split);

void	ft_realloc_tab(t_env *split, char *word);

int		main(int ac, char **av, char **env);

void	ft_env_addback(t_env *split, t_string str);

void	ft_reset_word(t_env *split);

void	ft_print_env(t_env *split);

void	ft_error(t_env *split, char *str);

void	ft_add_squote(t_env *split, int first);

void	ft_add_dquote(t_env *split, int first);

void	ft_free_chained(t_env *split);

void	ft_execute(t_env *split, t_arg *arg);

void	ft_getenv(t_env *split);

void	ft_reset(t_env *split);

int		ft_lst_size(t_env *split);

void	gest_signal(void);

int		ft_index_lst(t_env *lst, char *str);

void	ft_pipe(t_env *split);

void	ft_remove(t_env *env, int num);

void	ft_lauch(t_env *split);

t_arg	*ft_get_str(t_env *split, int i);

t_arg	*ft_elem(t_arg *lst, int i);

void	rfree(void *ptr);

#endif

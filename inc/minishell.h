/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 01:12:35 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/16 22:43:40 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "execute.h"
# include <signal.h>
# include <termios.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>

# define RESET		"\033[0;39m"
# define ORANGE		"\033[0;33m"
# define GRAY		"\033[0;90m"
# define RED		"\033[0;91m"
# define GREEN		"\033[1;92m"
# define YELLOW		"\033[1;93m"
# define BLUE		"\033[0;94m"
# define MAGENTA	"\033[0;95m"
# define CYAN		"\033[0;96m"
# define WHITE		"\033[0;97m"

typedef struct s_string
{
	char	*str;
	int		mal_len;
	int		r_len;
	int		is_redir;
	int		prio;
}	t_string;

typedef struct s_node
{
	int				type;
	struct s_node	*left;
	struct s_node	*right;
	struct s_node	*parent;
	char			**args;
	int				in;
	int				out;
}	t_node;

typedef struct s_arg
{
	char			*str;
	int				redir;
	int				num;
	int				prio;
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
	char		**path;
	int			last_state;
	char		*last_cmd;
	char		**rdline;
	int			end;
	int			ret;
	t_node		*tree;
	t_exe		exe;
	char		*exe_path;
}	t_env;

void	**ft_add_tab(void **tab, void *ne);

t_env	*ft_parse(char *line, t_env *split);

void	ft_end(t_env *split);

void	ft_add_rline(t_env *split, char c);

void	ft_realline(t_env *split);

void	ft_free(t_env *split);

void	ft_realloc_tab(t_env *split, char *word);

int		main(int ac, char **av, char **env);

void	ft_env_addback(t_env *split, t_string str);

void	ft_reset_word(t_env *split);

void	ft_print_args(t_env *split);

void	ft_error(t_env *split, char *str);

void	ft_add_squote(t_env *split, int first);

void	ft_add_dquote(t_env *split, int first);

void	ft_free_chained(t_env *split);

char	*ft_execute(t_env *split, char **cmd_split, char *input);

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

void	ft_create_command(t_env *split);

void	ft_lauch_cmd(t_env *split);

void	ft_reset_split(t_env *split);

void	ft_free_tab(void **tab);

char	*get_env(t_env *split, char *var);

void	ft_remove_env(t_env *split, char *var);

void	ft_addenv(t_env *split, char *var);

void	ft_create_env(t_env *split, char **env);

void	rl_replace_line(const char *text, int clear_undo);

void	ft_cd(t_env *env, char *path);

void	ft_print_env(t_env *split);

void	ft_unset(t_env *split);

int		ft_chose_command(t_env *split);

void	ft_lauch_cmd(t_env *split);

void	ft_add_env(t_env *split);

void	ft_create_word(t_env *split);

void	ft_gest_redir(t_env *split, t_arg *arg);

int		ft_what_redir(t_arg *tmp, t_env *split);

void	ft_home(t_arg *tmp, t_env *split);

void	ft_str_realloc(char **str, char *str2);

void	ft_create_tree(t_env *split, t_node **where, int start, int end);

void	ft_print_binary(t_node *node);

void	print_tree(t_node *root, int depth, char *prefix, int is_left);

void	ft_free_btree(t_node *tree);

void	ft_add_home(t_env *split);

void	ft_wildcard(t_env *split, char *str);

size_t	ft_strlen_wild(char *str);

void	ft_sort_wild(char **new);

void	ft_lauch(t_env *split);

int		ft_is_separator(t_env *split, char c);

void	ft_add_redir(t_env *split, int i);

int		ft_is_space(char c);

#endif

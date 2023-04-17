/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 21:00:30 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/17 18:59:26 by adrienmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

typedef struct s_env	t_env;
typedef struct s_node	t_node;

typedef struct s_exe
{
	char	*last_out;
	int		last_outcode;
	char	*executable;
	t_node	*node;
}	t_exe;

char	*ft_compute_tree(t_env *env, t_node *top, char *input);
char	*find_executable_from_path(char *cmd, char **paths);
int		ft_is_builtin(char *cmd);
int		ft_execute_builtin(t_env *env, char **cmd_split);
int		ft_builtin_cd(t_env *env, char **cmd_split);
void	ft_builtin_echo(t_env *env, char **cmds);
void	ft_builtin_pwd(t_env *env, char **cmds);
int		ft_builtin_env(t_env *env, char **cmds);
int		ft_builtin_export(t_env *env, char **cmds);
void	ft_builtin_unset(t_env *env, char **cmds);
void	print_all_env_variables(char **env);
int		ft_builtin_env(t_env *env, char **cmds);
void	ft_builtin_unset(t_env *env, char **cmds);
int		ft_builtin_export(t_env *env, char **cmds);
void	free_outs(char *left, char *right);
char	*write_to_file(t_node *tree, char *input, int append);
char	*read_stdin_to_delim(char *delim);

#endif

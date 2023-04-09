/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 22:35:51 by maserrie          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/04/09 23:22:07 by maserrie         ###   ########.fr       */
=======
/*   Updated: 2023/04/08 09:41:42 by adrienmori       ###   ########.fr       */
>>>>>>> 1156db6743f3eb74de3b4d8108e0979dc906aeb8
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_create_args(t_env *split)
{
	int		i;
	t_arg	*tmp;

	split->args = ft_calloc(ft_lst_size(split) + 1, sizeof(char *));
	if (!split->args)
		ft_end(split);
	i = 0;
	tmp = split->list;
	while (tmp && tmp->redir == 0)
	{
		split->args[i++] = tmp->str;
		tmp = tmp->next;
	}
}

void	ft_create_command(t_env *split)
{
	t_arg	*arg;

	if (!split->list)
		return ;
	arg = split->list;
	while (arg && arg->redir == 0)
		arg = arg->next;
	if (!arg)
		ft_execute(split, split->list);
}

void	ft_execute(t_env *split, t_arg *arg)
{
	int		pid;

	if (split->list && ft_strcmp(arg->str, "exit") == 0)
		ft_end(split);
	ft_create_args(split);
	if (ft_cmd_is_builtin(split->cmd))
		return (ft_execute_builtin(split, arg));
	pid = fork();
	if (pid == 0)
		ft_lauch_cmd(split);
	waitpid(pid, NULL, 0);
	rfree(split->cmd);
	rfree(split->args);
	split->cmd = NULL;
	split->args = NULL;
}

void	ft_lauch_cmd(t_env *split)
{
	int		i;
	char	*str;

	split->path = ft_split(get_env(split, "PATH"), ':');
	i = 0;
	while (split->path && split->path[i])
	{
		str = ft_strjoin(split->path[i++], "/");
		if (!str)
			ft_end(split);
		split->cmd = ft_strjoin(str, split->list->str);
		rfree(str);
		execve(split->cmd, split->args, split->env);
	}
	while (split->path && i >= 0)
		rfree(split->path[i--]);
	rfree(split->path);
	execve(split->list->str, split->args, split->env);
	ft_printf("minishell: command not found: %s\n", split->list->str);
	exit(0);
}

void	ft_pipe(t_env *split)
{
	int		pid;
	int		fd[2];
	int		i;

	i = 0;
	(void) i;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		exit(0);
	}
	else
	{
		dup2(fd[0], 0);
		close(fd[1]);
	}
	while (ft_index_lst(split, "|") != -1)
		ft_remove(split, 0);
	waitpid(pid, NULL, 0);
}

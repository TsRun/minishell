/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 22:35:51 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/07 20:31:39 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_create_args(t_arg *tmp, t_env *split)
{
	int		i;

	split->args = ft_calloc(ft_lst_size(split) + 1, sizeof(char *));
	if (!split->args)
		ft_end(split);
	i = 0;
	while (tmp)
	{
		split->args[i++] = tmp->str;
		tmp = tmp->next;
	}
	ft_print_env(split);
}

void	ft_execute(t_env *split, t_arg *arg)
{
	int		pid;

	if (split->list && ft_strncmp(split->list->str, "exit", 4) == 0)
		ft_end(split);
	pid = fork();
	if (pid == 0)
	{
		execve(split->cmd, split->args, split->env);
		ft_printf("minishell: command not found: %s\n", split->list->str);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	rfree(split->cmd);
	rfree(split->args);
	split->cmd = NULL;
	split->args = NULL;
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

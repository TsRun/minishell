/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gest_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 04:20:03 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/13 19:18:01 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_stdinout(t_env *split, int stdi, int stdou)
{
	int	old_stdin;
	int	old_stdout;

	old_stdin = dup(STDIN_FILENO);
	old_stdout = dup(STDOUT_FILENO);
	if (stdi != -1)
		dup2(stdi, STDIN_FILENO);
	if (stdou != -1)
		dup2(stdou, STDOUT_FILENO);
	ft_execute(split, split->list);
	dup2(old_stdin, STDIN_FILENO);
	dup2(old_stdout, STDOUT_FILENO);
}

void	ft_gest_redir(t_env *split, t_arg *arg)
{
	int		fd_out;
	t_arg	*tmp;
	int		fd_in;

	tmp = arg;
	fd_in = -1;
	fd_out = -1;
	if (tmp->redir == 3)
		fd_in = open(tmp->str, O_RDONLY);
	else if (tmp->redir == 1)
		fd_out = open(tmp->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (tmp->redir == 2)
		fd_out = open(tmp->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
}

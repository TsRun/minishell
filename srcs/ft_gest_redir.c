/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gest_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 04:20:03 by maserrie          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/04/13 20:44:12 by adrienmori       ###   ########.fr       */
=======
/*   Updated: 2023/04/13 20:20:06 by maserrie         ###   ########.fr       */
>>>>>>> b4e935fd234c42473a36d04733f0d50cfb581f1c
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_stdinout(t_env *split, int stdi, int stdou)
{
	int	old_stdin;
	int	old_stdout;

	(void)split;
	old_stdin = dup(STDIN_FILENO);
	old_stdout = dup(STDOUT_FILENO);
	if (stdi != -1)
		dup2(stdi, STDIN_FILENO);
	if (stdou != -1)
		dup2(stdou, STDOUT_FILENO);
	ft_execute(split, split->list->str, NULL);
	dup2(old_stdin, STDIN_FILENO);
	dup2(old_stdout, STDOUT_FILENO);
}

void	ft_gest_redir(t_env *split, t_arg *arg)
{
	int		fd_out;
	t_arg	*tmp;
	(void)split;
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
<<<<<<< HEAD
	(void)fd_out;
	(void)fd_in;
=======
	ft_stdinout(split, fd_in, fd_out);
>>>>>>> b4e935fd234c42473a36d04733f0d50cfb581f1c
}

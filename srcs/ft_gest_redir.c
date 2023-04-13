/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gest_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 04:20:03 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/13 17:57:25 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_gest_redir(t_env *split, t_arg *arg)
{
	int		fd;
	t_arg	*tmp;
	int		old_stdout;

	tmp = arg;
	fd = -1;
	old_stdout = dup(STDOUT_FILENO);
	if (tmp->redir == 1)
		fd = open(tmp->str, O_RDONLY);
	else if (tmp->redir == 2)
		fd = open(tmp->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (tmp->redir == 3)
		fd = open(tmp->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		ft_error(split, "File not found");
	else
		dup2(fd, STDOUT_FILENO);
	ft_execute(split, split->list);
	dup2(old_stdout, STDOUT_FILENO);
	close(old_stdout);
}

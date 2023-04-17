/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:19:38 by adrienmori        #+#    #+#             */
/*   Updated: 2023/04/16 19:46:54 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_builtin_echo(t_env *env, char **cmds)
{
	int	i;
	int	breakline;
	int	first;

	(void)env;
	if (!cmds || !*cmds)
		return ;
	i = 0;
	breakline = 1;
	first = 1;
	while (cmds[++i])
	{
		if (ft_strncmp(cmds[i], "-n", 2) == 0)
			breakline = 0;
		else
		{
			if (!first)
				ft_printf(" ");
			first = 0;
			ft_printf("%s", cmds[i]);
		}
	}
	if (breakline)
		ft_printf("\n");
	else
		ft_printf("\033[1;30m\033[47m%%\033[0m\n");
}

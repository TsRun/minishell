/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 01:37:09 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/12 23:38:34 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_print_env(t_env *split)
{
	int	i;

	i = 0;
	while (split->env[i])
		printf("%s\n", split->env[i++]);
}
void	ft_unset(t_env *split)
{
	int	i;

	i = 1;
	while (split->args[i])
		ft_remove_env(split, split->args[i++]);
}

void	ft_add_env(t_env *split)
{
	int	i;
	int	j;

	i = 1;
	while (split->args[i])
	{
		j = 0;
		while (split->args[i][j] && split->args[i][j] != '=')
			j++;
		if (split->args[i][j] == '=')
		{
			ft_remove_env(split, split->args[i]);
			ft_addenv(split, split->args[i]);
		}
		else
			printf("minishell: export: `%s': not a valid identifier\n", split->args[i]);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 01:37:09 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/17 18:48:34 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void	ft_addenv(t_env *split, char *var)
{
	int		i;
	int		test;
	char	*tmp;

	i = 0;
	tmp = ft_strchr(var, '=');
	while (split->env[i])
	{
		if (ft_strcmp_env(split->env[i], var) == 0)
		{
			if (tmp && tmp[1])
			{
				rfree(split->env[i]);
				split->env[i] = ft_strdup(var);
			}
			test = 1;
		}
		i++;
	}
	if (!test)
		ft_addenv2(split, var);
}

void	ft_add_home(t_env *split)
{
	char	*str;
	int		i;

	i = 0;
	str = get_env(split, "HOME");
	split->j++;
	if (str == NULL)
		ft_add_rline(split, '~');
	else
		while (str[i])
			ft_add_rline(split, str[i++]);
	rfree(str);
}

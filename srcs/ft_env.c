/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 09:13:58 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/09 23:21:30 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_strcmp_env(char *s1, char *var)
{
	int	i;

	i = 0;
	while (s1[i] && var[i] && s1[i] == var[i])
		i++;
	if (s1[i] == '=' && var[i] == '\0')
		return (0);
	return (1);
}

char	*get_env(t_env *split, char *var)
{
	int	i;

	i = 0;
	while (split->env[i])
	{
		if (ft_strcmp_env(split->env[i], var) == 0)
			return (ft_strdup(split->env[i] + ft_strlen(var) + 1));
		i++;
	}
	return (NULL);
}

void	ft_addenv(t_env *split, char *var)
{
	int		i;
	char	**tmp;

	i = 0;
	while (split->env[i])
		i++;
	tmp = ft_calloc(i + 2, sizeof(char *));
	if (!tmp)
		ft_end(split);
	i = 0;
	while (split->env[i])
	{
		tmp[i] = ft_strdup(split->env[i]);
		i++;
	}
	tmp[i] = ft_strdup(var);
	rfree(split->env);
	split->env = tmp;
}

void	ft_remove_env(t_env *split, char *var)
{
	int	i;

	i = 0;
	while (split->env[i])
	{
		if (ft_strcmp_env(split->env[i], var) == 0)
		{
			rfree(split->env[i]);
			split->env[i] = split->env[i + 1];
			while (split->env[i + 1])
			{
				split->env[i] = split->env[i + 1];
				i++;
			}
			split->env[i] = NULL;
			return ;
		}
		i++;
	}
}

void	ft_create_env(t_env *split, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	split->env = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	if (!split->env)
		ft_error(split, "malloc() error");
	while (env[i])
	{
		split->env[i] = ft_strdup(env[i]);
		if (!split->env[i])
			ft_error(split, "malloc() error");
		i++;
	}
}

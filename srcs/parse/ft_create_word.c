/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:58:23 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/17 21:05:38 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_add_squote(t_env *split, int first)
{
	split->lastchar = '\'';
	if (first)
		split->j++;
	while (!ft_strchr("\'", split->line[split->j]))
	{
		ft_add_rline(split, split->line[split->j]);
		if (split->line[split->j])
			split->j++;
	}
	if (split->line[split->j])
		split->j++;
	if (split->line[split->j] == '\"')
		return (ft_add_dquote(split, 1));
	if (split->line[split->j] == '\'')
		return (ft_add_squote(split, 1));
	if (!ft_strchr(" ", split->line[split->j]))
		return (ft_create_word(split));
}

void	ft_add_dquote(t_env *split, int first)
{
	split->lastchar = '\"';
	if (first)
		split->j++;
	while (!ft_strchr("\"", split->line[split->j]))
	{
		if (split->line[split->j] == '$')
		{
			if (split->line[split->j + 1] == '?')
				ft_add_rline(split, -2 + (0 * split->j++ + 0 * split->j++));
			else
				ft_getenv(split);
		}
		else
			ft_add_rline(split, split->line[split->j++]);
	}
	if (split->line[split->j])
		split->j++;
	if (split->line[split->j] == '\"')
		return (ft_add_dquote(split, 1));
	if (split->line[split->j] == '\'')
		return (ft_add_squote(split, 1));
	if (!ft_strchr(" ", split->line[split->j]))
		return (ft_create_word(split));
}

void	ft_getenv_word(t_env *split, char c)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	i = split->j;
	while (split->line[split->j] != c && split->line[split->j])
		split->j++;
	tmp = ft_substr(split->line, i, split->j - i);
	if (!tmp)
		ft_error(split, "malloc() error");
	tmp2 = get_env(split, tmp);
	if (tmp2)
	{
		i = 0;
		while (tmp2[i])
			ft_add_rline(split, tmp2[i++]);
	}
	rfree(tmp2);
	rfree(tmp);
}

void	ft_getrt(t_env *split)
{
	char	*tmp;
	int		i;

	split->j++;
	i = 0;
	tmp = ft_itoa(split->ret);
	if (!tmp)
		ft_error(split, "malloc() error");
	while (tmp[i])
		ft_add_rline(split, tmp[i++]);
	rfree(tmp);
}

void	ft_getenv(t_env *split)
{
	char	c;

	split->j++;
	if (split->line[split->j] == '?')
		ft_getrt(split);
	else if (ft_strchr("{[(", split->line[split->j]) && split->line[split->j])
	{
		split->j++;
		if (split->line[split->j] == '{')
			c = '}';
		else if (split->line[split->j] == '[')
			c = ']';
		else
			c = ')';
		if (!ft_is_separator(split, c))
			c = split->lastchar;
		ft_getenv_word(split, c);
		if (split->line[split->j])
			split->j++;
	}
	else
		ft_getenv_word(split, split->lastchar);
}

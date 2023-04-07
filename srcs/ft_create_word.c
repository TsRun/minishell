/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:58:23 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/07 10:25:58 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_add_squote(t_env *split, int first)
{
	split->word.is_redir = 0;
	split->lastchar = '\"';
	if (first)
		split->j++;
	while (!ft_strchr("\'", split->line[split->j]))
	{
		ft_add_rline(split, split->line[split->j]);
		if (split->line[split->j])
			split->j++;
	}
	if (!split->line[split->j])
	{
		free(split->line);
		split->line = readline("quote>");
		ft_add_rline(split, '\n');
		split->j = 0;
		return (ft_add_squote(split, 0));
	}
	split->j++;
	if (split->line[split->j] == '\"')
		return (ft_add_dquote(split, 1));
	if (split->line[split->j] == '\'')
		return (ft_add_squote(split, 1));
}

void	ft_add_dquote(t_env *split, int first)
{
	split->word.is_redir = 0;
	if (first)
		split->j++;
	while (!ft_strchr("\"", split->line[split->j]))
	{
		if (split->line[split->j] == '$')
			ft_getenv(split);
		else
			ft_add_rline(split, split->line[split->j++]);
	}
	if (!split->line[split->j])
	{
		free(split->line);
		split->line = readline("dquote>");
		ft_add_rline(split, '\n');
		split->j = 0;
		return (ft_add_dquote(split, 0));
	}
	split->j++;
	if (split->line[split->j] == '\"')
		return (ft_add_dquote(split, 1));
	if (split->line[split->j] == '\'')
		return (ft_add_squote(split, 1));
}

void	ft_getenv(t_env *split)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	c;

	i = 0;
	if (split->line[split->j + 1] == '{')
	{
		c = split->lastchar;
		split->lastchar = '}';
		split->j++;
	}
	while (!ft_strchr(" ", split->line[++split->j]) && split->line[split->j] != split->lastchar)
		i++;
	if (split->lastchar == '}')
		split->lastchar = c;
	tmp = ft_substr(split->line, split->j - i, i);
	if (!tmp)
		ft_end(split);
	tmp2 = getenv(tmp);
	if (!tmp2)
		return (free(tmp), ft_error(split, "env not found"));
	i = 0;
	while (tmp2[i])
		ft_add_rline(split, tmp2[i++]);
	free(tmp);
}

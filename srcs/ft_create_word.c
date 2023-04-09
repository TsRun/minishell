/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:58:23 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/09 23:47:52 by maserrie         ###   ########.fr       */
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
	char	*tmp;
	char	*tmp2;
	char	c;

	if (split->line[split->j + 1] == '{')
	{
		c = split->lastchar;
		split->lastchar = '}';
		split->j++;
	}
	while (!ft_strchr(" ", split->line[++split->j])
		&& split->line[split->j] != split->lastchar)
		split->k++;
	if (split->lastchar == '}')
		split->lastchar = c;
	tmp = ft_substr(split->line, split->j - split->k, split->k);
	if (!tmp)
		ft_error(split, "malloc() error");
	tmp2 = get_env(split, tmp);
	if (!tmp2)
		return (free(tmp), ft_error(split, "env not found"));
	split->k = 0;
	while (tmp2[split->k])
		ft_add_rline(split, tmp2[split->k++]);
	free(tmp);
}

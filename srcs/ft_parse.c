/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 23:50:35 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/13 21:27:45 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_create_word(t_env *split)
{
	split->word.is_redir = 0;
	while (!ft_strchr("><|() ", split->line[split->j]))
	{
		if (split->line[split->j] == '$')
			ft_getenv(split);
		else
			ft_add_rline(split, split->line[split->j++]);
	}
}

void	ft_add_redir(t_env *split)
{
	if (split->line[split->j] == '>')
	{
		split->word.is_redir = 1;
		if (split->line[split->j + 1] == '>')
		{
			split->word.is_redir = 2;
			split->j++;
		}
	}
	else if (split->line[split->j] == '<')
	{
		split->word.is_redir = 3;
		if (split->line[split->j + 1] == '<')
		{
			split->word.is_redir = 4;
			split->j++;
		}
	}
	else if (split->line[split->j] == '|')
		split->word.is_redir = 5;
	else if (split->line[split->j] == '(')
		split->word.is_redir = 6;
	else if (split->line[split->j] == ')')
		split->word.is_redir = 7;
	split->j++;
}

void	ft_realline(t_env *split)
{
	while (split->line[split->j])
	{
		while (split->line[split->j] == ' ')
			split->j++;
		if (split->line[split->j] == '\"')
			ft_add_dquote(split, 1);
		else if (split->line[split->j] == '\'')
			ft_add_squote(split, 1);
		else if (ft_strchr("><|()", split->line[split->j]))
			ft_add_redir(split);
		else
			ft_create_word(split);
		ft_env_addback(split, split->word);
		ft_reset_word(split);
	}
}

t_env	*ft_parse(char *line, t_env *split)
{
	split->line = line;
	split->lastchar = ' ';
	ft_realline(split);
	ft_create_tree(split, &split->tree, 0, ft_lst_size(split));
	ft_print_binary(split->tree);
	return (split);
}

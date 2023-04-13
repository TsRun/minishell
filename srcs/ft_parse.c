/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 23:50:35 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/13 23:40:24 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_create_word(t_env *split)
{
	while (!ft_strchr("><|() ", split->line[split->j]))
	{
		if (split->line[split->j] == '$')
			ft_getenv(split);
		else
			ft_add_rline(split, split->line[split->j++]);
	}
}

void	ft_add_redir2(t_env *split)
{
	if (split->line[split->j] == '|')
	{
		split->word.prio = 3;
		split->word.is_redir = 2;
	}
	if (split->line[split->j] == '(')
		split->word.is_redir = 6;
	else if (split->line[split->j] == ')')
		split->word.is_redir = 7;
	if (ft_strncmp(split->line + split->j, "&&", 2) == 0)
	{
		split->word.prio = 4;
		split->word.is_redir = 0;
		split->j++;
	}
	if (ft_strncmp(split->line + split->j, "||", 2) == 0)
	{
		split->word.prio = 5;
		split->word.is_redir = 1;
		split->j++;
	}
}

void	ft_add_redir(t_env *split)
{
	if (split->line[split->j] == '>')
	{
		split->word.prio = 1;
		split->word.is_redir = 3;
		if (split->line[split->j + 1] == '>')
		{
			split->word.is_redir = 4;
			split->j++;
		}
	}
	else if (split->line[split->j] == '<')
	{
		split->word.is_redir = 6;
		split->word.prio = 2;
		if (split->line[split->j + 1] == '<')
		{
			split->word.is_redir = 7;
			split->j++;
		}
	}
	ft_add_redir2(split);
	split->j++;
}

void	ft_realline(t_env *split)
{
	while (split->line[split->j])
	{
		ft_reset_word(split);
		while (split->line[split->j] == ' ')
			split->j++;
		if (split->line[split->j] == '\"')
			ft_add_dquote(split, 1);
		else if (split->line[split->j] == '\'')
			ft_add_squote(split, 1);
		else if (ft_strchr("><|()&", split->line[split->j]))
			ft_add_redir(split);
		else
			ft_create_word(split);
		ft_env_addback(split, split->word);
	}
	ft_reset_word(split);
}

t_env	*ft_parse(char *line, t_env *split)
{
	split->line = line;
	split->lastchar = ' ';
	ft_realline(split);
	ft_create_tree(split, &split->tree, 0, ft_lst_size(split));
	print_tree(split->tree, 0, "", 0);
	return (split);
}

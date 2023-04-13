/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 23:50:35 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/13 05:13:37 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_create_word(t_env *split)
{
	split->word.is_redir = 1;
	while (!ft_strchr(" ", split->line[split->j]))
	{
		if (split->line[split->j] == '$')
			ft_getenv(split);
		else
			ft_add_rline(split, split->line[split->j++]);
	}
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
		else
			ft_create_word(split);
		if (split->word.str)
			ft_env_addback(split, split->word);
		ft_reset_word(split);
	}
}

void	ft_redir(t_env *split)
{
	t_arg	*tmp;
	int		last;
	int		test;

	tmp = split->list;
	last = 0;
	test = 0;
	while (tmp)
	{
		while (tmp && !ft_what_redir(tmp, split))
		{
			if (test)
			{
				tmp->redir = last;
				test--;
			}
			else
				tmp->redir = 0;
			tmp = tmp->next;
		}
		if (tmp)
		{
			last = ft_what_redir(tmp, split);
			test = 1;
			tmp = tmp->next;
			ft_remove(split, tmp->num - 1);
		}
	}
}

t_env	*ft_parse(char *line, t_env *split)
{
	split->line = line;
	split->lastchar = ' ';
	ft_realline(split);
	ft_redir(split);
	return (split);
}

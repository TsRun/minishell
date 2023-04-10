/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 23:50:35 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/10 21:05:55 by maserrie         ###   ########.fr       */
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

void	ft_home(t_arg *tmp)
{
	char	*home;

	home = getenv("HOME");
	if (!tmp->str[1])
	{
		rfree(tmp->str);
		tmp->str = ft_strdup(home);
		rfree(home);
	}
}

void	ft_redir(t_env *split)
{
	t_arg	*tmp;

	tmp = split->list;
	while (tmp)
	{
		if (tmp->redir)
		{
			if (ft_strncmp(tmp->str, ">", 2) == 0)
				tmp->redir = 1;
			else if (ft_strncmp(tmp->str, ">>", 3) == 0)
				tmp->redir = 2;
			else if (ft_strncmp(tmp->str, "<", 3) == 0)
				tmp->redir = 3;
			else if (ft_strcmp(tmp->str, "<<") == 0)
				tmp->redir = 4;
			else if (tmp->str[0] == '~')
				ft_home(tmp);
			else
				tmp->redir = 0;
		}
		tmp = tmp->next;
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

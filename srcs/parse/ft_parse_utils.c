/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:49:05 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/17 09:26:09 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_is_separator(t_env *split, char c)
{
	int	i;

	i = 1;
	while (split->line[split->j + i])
	{
		if (split->line[split->j + i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_print_redir(t_env *split)
{
	char	*str;

	ft_putstr_fd("minishell : parse error near \'", 2);
	if (split->word.is_redir == 0)
		str = "&&";
	else if (split->word.is_redir == 1)
		str = "||";
	else if (split->word.is_redir == 2)
		str = "|";
	else if (split->word.is_redir == 3)
		str = ">";
	else if (split->word.is_redir == 4)
		str = ">>";
	else if (split->word.is_redir == 5)
		str = "&";
	else if (split->word.is_redir == 6)
		str = "<";
	else if (split->word.is_redir == 7)
		str = "<<";
	else if (split->word.is_redir == 8)
		str = "(";
	else if (split->word.is_redir == 9)
		str = ")";
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\'\n", 2);
}

void	ft_add_redir3(t_env *split)
{
	t_arg	*tmp;

	tmp = split->list;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!tmp && split->word.is_redir <= 7)
	{
		ft_print_redir(split);
		ft_error(split, NULL);
	}
	if (tmp && (tmp->redir >= 0 && tmp->redir <= 8))
	{
		ft_print_redir(split);
		ft_error(split, NULL);
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
		split->word.is_redir = 8;
	else if (split->line[split->j] == ')')
		split->word.is_redir = 9;
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

void	ft_add_redir(t_env *split, int i)
{
	if (!split->line[split->j])
		return ;
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
			split->word.is_redir = 7 + split->j++ * 0;
	}
	ft_add_redir2(split);
	split->j++;
	if (i)
		ft_add_redir3(split);
}


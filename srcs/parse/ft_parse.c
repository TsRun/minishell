/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 23:50:35 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/16 23:33:45 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_create_word(t_env *split)
{
	while (!ft_strchr("><|() \"\'&\t", split->line[split->j]))
	{
		if (split->line[split->j] == '$')
			ft_getenv(split);
		else if (split->line[split->j] == '*')
		{
			split->j++;
			ft_add_rline(split, -1);
		}
		else if (split->line[split->j] == '~')
			ft_add_home(split);
		else
			ft_add_rline(split, split->line[split->j++]);
	}
	if (split->line[split->j] == '\"')
		return (ft_add_dquote(split, 1));
	if (split->line[split->j] == '\'')
		return (ft_add_squote(split, 1));
}

int	ft_is_space(char c)
{
	return (c == ' ' || c == '\t');
}

void	ft_realline(t_env *split)
{
	while (split->line[split->j])
	{
		ft_reset_word(split);
		while (ft_is_space(split->line[split->j]))
			split->j++;
		if (!split->line[split->j])
			break ;
		if (split->line[split->j] == '\"' && ft_is_separator(split, '\"'))
			ft_add_dquote(split, 1);
		else if (split->line[split->j] == '\'' && ft_is_separator(split, '\''))
			ft_add_squote(split, 1);
		else if (ft_strchr("><|()&", split->line[split->j]))
			ft_add_redir(split, 1);
		else
			ft_create_word(split);
		if (split->word.is_redir == -1 && !split->word.str)
			split->word.str = ft_strdup("");
		ft_wildcard(split, split->word.str);
	}
	ft_reset_word(split);
}

t_env	*ft_parse(char *line, t_env *split)
{
	split->tree = ft_calloc(1, sizeof(t_node));
	if (!split->tree)
		ft_error(split, "Error: malloc failed");
	split->line = line;
	split->lastchar = ' ';
	ft_realline(split);
	if (split->list)
		ft_create_tree(split, &split->tree, 0, ft_lst_size(split));
	print_tree(split->tree, 0, "", 0);
	return (split);
}

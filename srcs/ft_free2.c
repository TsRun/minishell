/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 09:04:04 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/13 02:57:25 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_reset_split(t_env *split)
{
	if (!split)
		return ;
	rfree(split->line);
	rfree(split->word.str);
	rfree(split->args);
	ft_free_chained(split);
	split->line = NULL;
	split->args = NULL;
	split->j = 0;
	split->k = 0;
	split->lastchar = 0;
	split->word.str = 0;
	split->word.mal_len = 0;
	split->word.r_len = 0;
	split->word.is_redir = 0;
	split->list = NULL;
	split->path = NULL;
	split->cmd = NULL;
	split->len = 0;
	split->mal_len = 0;
}

void	ft_free_tab(void **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		rfree(tab[i++]);
	rfree(tab);
}

void	rfree(void *ptr)
{
	if (ptr)
		free(ptr);
}

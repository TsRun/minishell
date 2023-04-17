/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:18:17 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/16 19:46:21 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_add_rline(t_env *split, char c)
{
	int		i;
	char	*tmp;

	i = -1;
	if (!split->word.str)
	{
		split->word.str = ft_calloc(1000, sizeof(char));
		if (!split->word.str)
			ft_end(split);
		split->word.mal_len = 1000;
	}
	split->word.r_len++;
	if (split->word.r_len >= split->word.mal_len)
	{
		tmp = ft_calloc(split->word.mal_len + 1000, sizeof(char));
		if (!tmp)
			ft_end(split);
		while (++i < split->word.r_len)
			tmp[i] = split->word.str[i];
		split->word.mal_len += 1000;
		free(split->word.str);
		split->word.str = tmp;
	}
	split->word.str[split->word.r_len - 1] = c;
}

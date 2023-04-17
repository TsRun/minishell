/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 18:31:19 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/16 19:46:32 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_sort_wild(char **new)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	if (!new)
		return ;
	while (new[i])
	{
		j = i + 1;
		while (new[j])
		{
			if (ft_strcmp(new[i], new[j]) > 0)
			{
				tmp = new[i];
				new[i] = new[j];
				new[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

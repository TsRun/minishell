/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:14:29 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/14 19:23:00 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_wildcard(t_env *split, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == -1)
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chained2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:38:20 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/07 19:51:31 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_arg	*ft_get_str(t_env *split, int i)
{
	int		j;
	t_arg	*tmp;

	j = 0;
	tmp = split->list;
	while (j < i && tmp && tmp->next)
	{
		tmp = tmp->next;
		j++;
	}
	return (tmp);
}

int	ft_index_lst(t_env *lst, char *str)
{
	int		i;
	t_arg	*tmp;

	i = 0;
	tmp = lst->list;
	while (tmp)
	{
		if (ft_strcmp(tmp->str, str) == 0 && tmp->redir != 0)
			return (i);
		tmp = tmp->next;
		i++;
	}
	return (-1);
}

t_arg	*ft_elem(t_arg *lst, int i)
{
	int		j;
	t_arg	*tmp;

	j = 0;
	tmp = lst;
	while (j < i && tmp && tmp->next)
	{
		tmp = tmp->next;
		j++;
	}
	return (tmp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chained.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 01:10:04 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/16 19:46:13 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_print_args(t_env *split)
{
	t_arg	*tmp;

	tmp = split->list;
	while (tmp)
	{
		printf("%s %d\n", tmp->str, tmp->redir);
		tmp = tmp->next;
	}
}

void	ft_env_addback(t_env *split, t_string str)
{
	t_arg	*tmp;
	t_arg	*new;

	new = ft_calloc(1, sizeof(t_arg));
	if (!new)
		ft_error(split, "malloc error");
	new->str = str.str;
	new->redir = str.is_redir;
	new->prio = str.prio;
	if (!split->list)
	{
		new->num = 0;
		new->prev = NULL;
		split->list = new;
		return ;
	}
	tmp = split->list;
	while (tmp->next)
		tmp = tmp->next;
	new->num = tmp->num + 1;
	tmp->next = new;
	new->prev = tmp;
}

void	ft_free_chained(t_env *split)
{
	t_arg	*tmp;
	t_arg	*tmp2;

	tmp = split->list;
	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp->str);
		free(tmp);
		tmp = tmp2;
	}
}

int	ft_lst_size(t_env *split)
{
	t_arg	*tmp;
	int		i;

	i = 0;
	tmp = split->list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	ft_remove(t_env *env, int num)
{
	int		i;
	t_arg	*tmp;
	t_arg	*tmp2;

	i = 0;
	tmp = env->list;
	if (!tmp)
		return ;
	while (i++ < num && tmp->next)
		tmp = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (!tmp->prev)
		env->list = tmp->next;
	tmp2 = tmp->next;
	free(tmp->str);
	free(tmp);
	while (tmp2)
	{
		tmp2->num--;
		tmp2 = tmp2->next;
	}
}

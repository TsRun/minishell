/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compute_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrienmori <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 21:11:54 by adrienmori        #+#    #+#             */
/*   Updated: 2023/04/13 22:34:16 by adrienmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_compute_tree(t_env *env, t_node *top)
{
	ft_execute(env, "ls -la", NULL);
	return (1);
}

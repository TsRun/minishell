/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compute_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrienmori <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 21:11:54 by adrienmori        #+#    #+#             */
/*   Updated: 2023/04/14 00:07:02 by adrienmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_compute_tree(t_env *env, t_node *top, char *input)
{
	char	*right_out;
	char	*left_out;
	char	*out;

	right_out = NULL;
	left_out = NULL;
	if (!top)
		return (NULL);
	if (top->left)
		left_out = ft_compute_tree(env, top->left, input);
	if (!top->right && top->left)
		return (left_out);
	// type &&
	if (top->type == 0)
		right_out = ft_compute_tree(env, top->right, NULL);
	// type ||
	if (top->type == 1 && env->exe.last_outcode != 0)
		right_out = ft_compute_tree(env, top->right, NULL);
	// type |, >, >>
	if (top->type == 2 || top->type == 3 || top->type == 4)
		right_out = ft_compute_tree(env, top->right, left_out);
	
	if (top->args && top->type == -1 && (!top->parent || (top->parent->type != 4 && top->parent->type != 3) || top == top->parent->left))
		return (ft_execute(env, top->args, input));
	if (top->type != 2 && top->type != 3 && top->type != 4)
	{
		out = ft_strjoin(left_out, right_out);
		//rfree(left_out);
		//rfree(right_out);
		return (out);
	}
	//if (left_out)
		//free(left_out);
	return (right_out);
}

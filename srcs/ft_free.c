/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:56:45 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/13 03:09:17 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free(t_env *split)
{
	if (!split)
		return ;
	rfree(split->line);
	rfree(split->word.str);
	rfree(split->args);
	ft_free_tab((void **)split->rdline);
	ft_free_tab((void **)split->env);
	ft_free_chained(split);
	free(split);
}

void	ft_reset_word(t_env *split)
{
	split->word.str = NULL;
	split->word.r_len = 0;
	split->word.mal_len = 0;
	split->word.is_redir = 0;
}

void	ft_end(t_env *split)
{
	ft_free(split);
	exit(0);
}

void	ft_reset(t_env *split)
{
	ft_free(split);
	main(1, NULL, split->env);
}

void	ft_error(t_env *split, char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	ft_end(split);
}

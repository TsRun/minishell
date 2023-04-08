/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_display_directory.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrienmori <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 09:13:08 by adrienmori        #+#    #+#             */
/*   Updated: 2023/04/08 09:22:36 by adrienmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_set_display_directory(t_dirs *dirs, char *start, char *end)
{
	int	i;
	int	len;
	int	start_len;
	int	end_len;

	start_len = ft_strlen(start);
	end_len = ft_strlen(end);
	i = ft_strlen(dirs->directory);
	len = 0;
	while (i >= 0 && dirs->directory[i] != '/' && ++len)
		i --;
	if (i != 0)
		len --;
	i = -1;
	while (start[++i])
		dirs->display[i] = start[i];
	i = -1;
	while (++i <= end_len)
		dirs->display[i + start_len + len] = end[i];
	i = ft_strlen(dirs->directory) - 1;
	while (len > 0 && i >= 0)
		dirs->display[start_len + len-- - 1]
			= dirs->directory[i--];
}

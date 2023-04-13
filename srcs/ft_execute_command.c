/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrienmori <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:59:43 by adrienmori        #+#    #+#             */
/*   Updated: 2023/04/13 20:05:09 by adrienmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#define READ_OUTPUT_BUFFER_SIZE 128

static void	read_output(char **out, int pipes[2][2])
{
	char	*buffer;
	int		size;

	*out = NULL;
	buffer = (char *)malloc(sizeof(char) * (READ_OUTPUT_BUFFER_SIZE + 1));
	if (!buffer)
		return ;
	size = read(pipes[1][0], buffer, READ_OUTPUT_BUFFER_SIZE);
	while (size > 0)
	{
		buffer[size] = 0;
		if (!(*out) && buffer[0] == ' ')
			ft_str_realloc(out, buffer + 1);
		else
			ft_str_realloc(out, buffer);
		size = read(pipes[1][0], buffer, READ_OUTPUT_BUFFER_SIZE);
	}
	free(buffer);
}

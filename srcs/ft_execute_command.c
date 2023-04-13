/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrienmori <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:59:43 by adrienmori        #+#    #+#             */
/*   Updated: 2023/04/13 21:15:29 by adrienmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#define READ_OUTPUT_BUFFER_SIZE 128

void	ft_execute(t_env *env, char *cmd, char *input)
{
	char	*out;
	char	**cmd_with_args;

	
	out = NULL;
	if (!cmd || ft_strlen(cmd) < 1)
		return ;
	if (ft_strncmp(cmd, "exit", 4) == 0)
		exit(0);
	cmd_with_args = ft_split(cmd, ' ');
	if (!cmd_with_args)
		return ;
	ft_printf("ok");
	return ;
}

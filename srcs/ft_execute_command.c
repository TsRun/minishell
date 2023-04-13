/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrienmori <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:59:43 by adrienmori        #+#    #+#             */
/*   Updated: 2023/04/13 22:41:18 by adrienmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#define READ_OUTPUT_BUFFER_SIZE 128

void	ft_real_execute(t_env *env, char **cmd_split, char *input)
{
	if (env->exe.last_out)
		free(env->exe.last_out);
	env->exe.last_out = NULL;
	if (!cmd_split || !*cmd_split)
		return ;
}

void	ft_execute(t_env *env, char *cmd, char *input)
{
	char	*out;

	env->path = ft_split(get_env(env, "PATH"), ':');
	ft_printf("\n######## mes printfs #######\n");
	ft_real_execute(env, ft_split(cmd, ' '), input);	
	ft_printf("\n############################\n");
	rfree(env->path);
	return ;
}

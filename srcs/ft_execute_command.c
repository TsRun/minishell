/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrienmori <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:59:43 by adrienmori        #+#    #+#             */
/*   Updated: 2023/04/13 21:14:01 by adrienmori       ###   ########.fr       */
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

static void	start_execve(t_env *env, char **cmd, int pipes[2][2], char *input)
{
	close(pipes[0][1]);
	close(pipes[1][0]);
	if (input)
		dup2(pipes[0][0], STDIN_FILENO);
	dup2(pipes[1][1], STDOUT_FILENO);
	close(pipes[0][0]);
	close(pipes[1][1]);
	write(STDOUT_FILENO, " ", 1);
}

void	execute_builtin_function(t_env *env, char **cmd_with_args)
{
	return ;
}
int	is_builtin(char *cmd)
{
	return (1);
}

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
	if (is_builtin(cmd_with_args[0]))
		execute_builtin_function(env, cmd_with_args);
	ft_printf("ok");
	return ;
}

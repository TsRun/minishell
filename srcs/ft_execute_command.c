/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrienmori <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:59:43 by adrienmori        #+#    #+#             */
/*   Updated: 2023/04/14 02:27:10 by adrienmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#define BUFFER_SIZE 128

char	*read_output(char **out, int pipes[2][2])
{
	char	*buffer;
	int		size;

	buffer = (char *)ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	size = read(pipes[1][0], buffer, BUFFER_SIZE);
	while (size > 0)
	{
		buffer[size] = 0;
		ft_str_realloc(out, buffer);
		size = read(pipes[1][0], buffer, BUFFER_SIZE);
	}
	free(buffer);
	return (*out);
}

static void	start_execve(t_env *env, char **cmd_split,
	int pipes[2][2], char *input)
{
	close(pipes[0][1]);
	close(pipes[1][0]);
	printf("%d %d\n", env->exe.node->in, env->exe.node->out);
	if (input)
		dup2(pipes[0][0], STDIN_FILENO);
	if (env->exe.node->out)
		dup2(pipes[1][1], STDOUT_FILENO);
	close(pipes[0][0]);
	close(pipes[1][1]);
	execve(env->exe.executable, cmd_split, env->env);
	ft_printf("Execve error D:\n");
	exit(0);
}

char	*start_pipe(t_env *env, char **cmd_split, char *input)
{
	int		pipes[2][2];
	int		pid;
	char	*out;

	out = NULL;
	if (pipe(pipes[0]) || pipe(pipes[1]))
		return (ft_printf("Erreur de pipe :C\n"), NULL);
	pid = fork();
	if (pid == -1)
		return (ft_printf("Erreur pid ://\n"), NULL);
	if (pid == 0)
		start_execve(env, cmd_split, pipes, input);
	close(pipes[0][0]);
	close(pipes[0][0]);
	close(pipes[1][1]);
	if (input)
		write(pipes[0][1], input, ft_strlen(input));
	close(pipes[0][1]);
	wait(&pid);
	read_output(&out, pipes);
	return (out);
}

char	*ft_execute(t_env *env, char **cmd_split, char *input)
{
	char	*out;

	env->path = ft_split(get_env(env, "PATH"), ':');
	out = NULL;
	if (!cmd_split || !*cmd_split)
		return (NULL);
	env->exe.executable = find_executable_from_path(cmd_split[0], env->path);
	if (!env->exe.executable)
		return (ft_printf("Command not found :D\n"), NULL);
	out = start_pipe(env, cmd_split, input);
	if (env->exe.executable)
		free(env->exe.executable);
	rfree(env->path);
	env->exe.last_outcode = 1;
	env->exe.last_out = out;
	return (out);
}

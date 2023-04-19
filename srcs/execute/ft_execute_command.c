/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:59:43 by adrienmori        #+#    #+#             */
/*   Updated: 2023/04/19 23:30:07 by maserrie         ###   ########.fr       */
/*   Updated: 2023/04/17 20:23:03 by amori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
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

static int	start_execve(t_env *env, char **cmd_split,
	int pipes[2][2], char *input)
{
	close(pipes[0][1]);
	close(pipes[1][0]);
	if (input)
		dup2(pipes[0][0], STDIN_FILENO);
	if (env->exe.node->out)
		dup2(pipes[1][1], STDOUT_FILENO);
	close(pipes[0][0]);
	close(pipes[1][1]);
	if (env->exe.executable && !ft_is_builtin(cmd_split[0]))
		execve(env->exe.executable, cmd_split, env->env);
	else
		return (ft_execute_builtin(env, cmd_split), exit(0), 0);
	ft_printf("Execve error : %s D:\n", *cmd_split);
	exit(EXIT_FAILURE);
	return (0);
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
	waitpid(pid, &(env->exe.last_outcode), 0);
	read_output(&out, pipes);
	return (out);
}

static int	builtin_exception_but_exception_in_french(t_env *env,
	char **cmd_split)
{
	if (ft_strncmp(cmd_split[0], "cd", 2) == 0)
		return (ft_builtin_cd(env, cmd_split), 1);
	if (ft_strncmp(cmd_split[0], "export", 6) == 0
		&& cmd_split[0] && cmd_split[1])
		return (ft_builtin_export(env, cmd_split), 1);
	if (ft_strncmp(cmd_split[0], "unset", 5) == 0)
		return (ft_builtin_unset(env, cmd_split), 1);
	return (0);
}

char	*ft_execute(t_env *env, char **cmd_split, char *input)
{
	char	*out;
	char	*path;

	out = NULL;
	if (!cmd_split || !*cmd_split || replace_outcode(env, &cmd_split)
		|| builtin_exception_but_exception_in_french(env, cmd_split))
		return (NULL);
	path = get_env(env, "PATH");
	if (path)
		env->path = ft_split(path, ':');
	rfree(path);
	env->exe.executable = find_executable_from_path(cmd_split[0], env->path);
	if (!env->exe.executable && !ft_is_builtin(cmd_split[0]) && sout(env))
		return (ft_printf("Command not found : %s\n", *cmd_split),
			ft_free_tab((void **)env->path), NULL);
	out = start_pipe(env, cmd_split, input);
	if (env->exe.executable)
		free(env->exe.executable);
	ft_free_tab((void **)env->path);
	env->exe.last_out = out;
	return (out);
}

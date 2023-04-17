/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:59:43 by adrienmori        #+#    #+#             */
/*   Updated: 2023/04/17 19:45:40 by adrienmori       ###   ########.fr       */
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
	ft_printf("Execve error D:\n");
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

int	replace_str_outcode(t_env *env, char **str)
{
	char	*tmp;
	char	*num;
	int	i;
	int	j;

	ft_printf("d %d\n", env->exe.last_outcode);
	num = ft_itoa(env->exe.last_outcode);
	if (!num)
		return (0);
	tmp = (char *)ft_calloc(sizeof(char), ft_strlen(num) + ft_strlen(*str) - 1);
	if (!tmp)
		return (free(num), 0);
	i = -1;
	j = 0;
	while ((*str)[++i])
	{
		if ((*str)[i] == -2)
		{
			ft_memcpy(tmp + j, (void *)num, ft_strlen(num));
			j += ft_strlen(num);
		}
		else
			tmp[j++] = *str[i];
	}
	free(num);
	if (*str)
		free(*str);
	*str = tmp;
	return (0);
}

int	replace_outcode(t_env *env, char ***cmd_split)
{
	int	i;
	int	j;

	i = 0;
	if (!cmd_split)
		return (0);
	while ((*cmd_split)[i])
	{
		j = 0;
		while ((*cmd_split)[i][j])
		{
			if ((*cmd_split)[i][j] == -2)
				replace_str_outcode(env, &((*cmd_split)[i]));
			j ++;
		}
		i ++;
	}
	return (0);
}

char	*ft_execute(t_env *env, char **cmd_split, char *input)
{
	char	*out;
	char	*path;

	out = NULL;
	env->exe.last_outcode = 127;
	if (!cmd_split || !*cmd_split || replace_outcode(env, &cmd_split)
		|| builtin_exception_but_exception_in_french(env, cmd_split))
		return (NULL);
	path = get_env(env, "PATH");
	env->path = ft_split(path, ':');
	if (path)
		free(path);
	env->exe.executable = find_executable_from_path(cmd_split[0], env->path);
	if (!env->exe.executable && !ft_is_builtin(cmd_split[0]))
		return (ft_printf("Command not found :D\n"),
			ft_free_tab((void **)env->path), NULL);
	out = start_pipe(env, cmd_split, input);
	if (env->exe.executable)
		free(env->exe.executable);
	ft_free_tab((void **)env->path);
	env->exe.last_out = out;
	return (out);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:10:43 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/16 19:02:06 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*rdline(t_env *split, char *path)
{
	char	*tmp2;

	tmp2 = readline("minishell> ");
	split->exe_path = ft_strdup(path);
	return (tmp2);
}

size_t	ft_strlen_wild(char *str)
{
	int		i;

	i = 0;
	while (str[i] != -1 && str[i])
		i++;
	return (i);
}

void	ft_gest_line(t_env *split, char *line)
{
	if (!line)
	{
		ft_putstr_fd("exit\n", 1);
		line = ft_strdup("exit");
	}
	if (!line)
		ft_error(split, "malloc() error");
	if (ft_strlen(line) > 0)
		add_history(line);
	ft_parse(line, split);
}

void	ft_lauch(t_env *split)
{
	char	path[256];
	char	*line;

	while (!split->end)
	{
		getcwd(path, 256);
		line = rdline(split, path);
		ft_gest_line(split, line);
		ft_create_command(split);
		ft_reset_split(split);
	}
}

int	main(int ac, char **av, char **env)
{
	t_env	*split;

	(void)ac;
	(void)av;
	split = ft_calloc(1, sizeof(t_env));
	if (!split)
		ft_error(split, "malloc() error");
	ft_create_env(split, env);
	gest_signal();
	ft_lauch(split);
	ft_free(split);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:10:43 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/14 00:27:57 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*rdline(t_env *split, char *path)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp2 = readline("minishell> ");
	return (tmp2);
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

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_env	*split;
	char	path[256];

	(void)ac;
	(void)av;
	split = ft_calloc(1, sizeof(t_env));
	if (!split)
		ft_error(split, "malloc() error");
	ft_create_env(split, env);
	gest_signal();
	while (!split->end)
	{
		getcwd(path, 256);
		line = rdline(split, path);
		ft_gest_line(split, line);
		ft_create_command(split);
		ft_reset_split(split);
	}
	ft_free(split);
}

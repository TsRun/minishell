/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:10:43 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/10 21:15:30 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*rdline(t_env *split, char *path)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(BLUE, ft_strrchr(path, '/') + 1);
	if (!tmp)
		ft_error(split, "malloc() error");
	tmp2 = ft_strjoin(tmp, RESET);
	if (!tmp2)
		ft_error(split, "malloc() error");
	free(tmp);
	tmp = ft_strjoin(tmp2, "> ");
	if (!tmp)
		ft_error(split, "malloc() error");
	rfree(tmp2);
	tmp2 = readline(tmp);
	rfree(tmp);
	return (tmp2);
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
	while (1)
	{
		gest_signal();
		getcwd(path, 256);
		line = rdline(split, path);
		add_history(line);
		split = ft_parse(line, split);
		ft_create_command(split);
		ft_reset_split(split);
	}
	ft_free(split);
}

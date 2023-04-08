/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:10:43 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/08 09:24:13 by adrienmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_env	*split;
	t_dirs	dirs;

	(void)ac;
	(void)av;
	while (1)
	{
		gest_signal();
		getcwd(dirs.directory, 1024);
		ft_set_display_directory(&dirs, BLUE, "\033[0;39m> ");
		line = readline(dirs.display);
		add_history(line);
		split = ft_parse(line, env);
		ft_execute(split, 0);
		ft_free(split);
	}
}

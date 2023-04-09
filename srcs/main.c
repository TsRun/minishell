/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:10:43 by maserrie          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/04/09 23:27:10 by maserrie         ###   ########.fr       */
=======
/*   Updated: 2023/04/08 09:24:13 by adrienmori       ###   ########.fr       */
>>>>>>> 1156db6743f3eb74de3b4d8108e0979dc906aeb8
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
	return (readline(tmp));
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_env	*split;
	t_dirs	dirs;

	(void)ac;
	(void)av;
	split = ft_calloc(1, sizeof(t_env));
	if (!split)
		ft_error(split, "malloc() error");
	ft_create_env(split, env);
	while (1)
	{
		gest_signal();
<<<<<<< HEAD
		getcwd(path, 256);
		line = rdline(split, path);
=======
		getcwd(dirs.directory, 1024);
		ft_set_display_directory(&dirs, BLUE, "\033[0;39m> ");
		line = readline(dirs.display);
>>>>>>> 1156db6743f3eb74de3b4d8108e0979dc906aeb8
		add_history(line);
		split = ft_parse(line, split);
		ft_create_command(split);
		ft_reset_split(split);
	}
	ft_free(split);
}

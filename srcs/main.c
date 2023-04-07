/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:10:43 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/07 19:54:01 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_env	*split;
	char	path[256];

	(void)ac;
	(void)av;
	while (1)
	{
		gest_signal();
		getcwd(path, 256);
		ft_printf("%s%s%s", BLUE, ft_strrchr(path, '/') + 1, RESET);
		line = readline("> ");
		add_history(line);
		split = ft_parse(line, env);
		ft_execute(split, 0);
		ft_free(split);
	}
}

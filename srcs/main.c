/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:10:43 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/13 05:16:55 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*rdline(t_env *split, char *path)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp3 = get_env(split, "HOME");
	if (ft_strcmp(tmp3, path) == 0)
		tmp = ft_strjoin(BLUE, "~ ");
	else
		tmp = ft_strjoin(BLUE, ft_strrchr(path, '/') + 1);
	rfree(tmp3);
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
	split->rdline = (char **)ft_add_tab((void **)split->rdline, (void *)tmp);
	if (!split->rdline)
		ft_error(split, "malloc() error");
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

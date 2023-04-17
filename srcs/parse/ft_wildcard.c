/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:14:29 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/16 19:45:57 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**ft_find_in_dir(t_env *split, char *str)
{
	DIR				*dir;
	struct dirent	*sd;
	char			**new;

	new = NULL;
	dir = opendir(split->exe_path);
	if (dir == NULL)
		return (NULL);
	sd = readdir(dir);
	while (sd != NULL)
	{
		if (!ft_strncmp(str, sd->d_name, ft_strlen_wild(str))
			&& ft_strncmp(".", sd->d_name, 1))
			new = (char **)ft_add_tab((void **)new, ft_strdup(sd->d_name));
		sd = readdir(dir);
	}
	closedir(dir);
	return (new);
}

char	*ft_next_wildcard(char *str, char *new, char *old_new)
{
	int		i;
	int		test;

	i = 0;
	while (str[i] != -1 && str[i])
		i++;
	if (str[i])
	{
		str[i] = '\0';
		new = ft_strnstr(new, str, ft_strlen(new));
		str[i] = -1;
	}
	else
	{
		test = ft_strrncmp(new, str, i);
		if (test)
			new = NULL;
		else
			new = old_new - 1;
	}
	return (new);
}

int	ft_is_ok(char *new, char *str)
{
	int		i;
	int		test;
	char	*tmp;

	i = 0;
	test = 1;
	tmp = NULL;
	while (str[i])
	{
		if (str[i] == -1)
		{
			if (!tmp)
				tmp = new + i;
			tmp = ft_next_wildcard(str + i + 1, tmp, new);
			if (tmp == new - 1)
				test = 1;
			if (!tmp)
				test = 0;
		}
		if (!test)
			break ;
		i++;
	}
	return (test);
}

int	ft_add_new(t_env *split, char *str, char **new, int test)
{
	int		i;

	i = 0;
	if (test == 0)
	{
		ft_sort_wild(new);
		while (new && new[i])
		{
			if (ft_is_ok(new[i++], str))
			{
				ft_reset_word(split);
				split->word.str = new[i - 1];
				ft_env_addback(split, split->word);
				test = 1;
			}
		}
	}
	else if (test == 1)
		ft_env_addback(split, split->word);
	if (!test)
		ft_error(split, "No match");
	return (test);
}

void	ft_wildcard(t_env *split, char *str)
{
	int			i;
	char		**new;
	int			test;

	i = 0;
	new = NULL;
	test = 1;
	while (str && str[i] != -1 && str[i])
		i++;
	if (str && str[i] == -1)
	{
		test = 0;
		new = ft_find_in_dir(split, str);
	}
	i = 0;
	test = ft_add_new(split, str, new, test);
	rfree(new);
}

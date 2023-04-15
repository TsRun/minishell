/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:14:29 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/14 21:53:05 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**ft_find_in_dir(t_env *split, char *str)
{
	DIR				*dir;
	struct dirent	*sd;
	int				i;
	char			**new;

	i = 0;
	new = NULL;
	dir = opendir(split->exe_path);
	if (dir == NULL)
		return (NULL);
	while ((sd = readdir(dir)) != NULL)
	{
		if (!ft_strncmp(str, sd->d_name, ft_strlen(str)))
		{
			new = (char **)ft_add_tab((void **)new, ft_strdup(sd->d_name));
			i++;
		}
	}
	closedir(dir);
	return (new);
}

void	ft_wildcard(t_env *split, char *str)
{
	int			i;
	char		**new;

	i = 0;
	new = NULL;
	while (str[i] != -1 && str[i])
		i++;
	if (str[i] == -1)
	{
		str[i] = '\0';
		new = ft_find_in_dir(split, str);
	}
	i = 0;
	while (new && new[i])
	{
		ft_reset_word(split);
		split->word.str = new[i++];
		ft_env_addback(split, split->word);
	}
	if (!new)
		ft_env_addback(split, split->word);
	ft_free_tab((void **)new);
}

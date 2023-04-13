/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 21:00:30 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/13 22:40:46 by adrienmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

typedef struct s_env	t_env;
typedef struct s_node	t_node;

typedef struct s_exe
{
	char	*last_out;
}	t_exe;

int	ft_compute_tree(t_env *env, t_node *top);
char	*find_executable_fron_path(char *cmd, char **paths);

#endif

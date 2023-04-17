/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:23:15 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/17 21:08:12 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_signal(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

void	gest_signal(void)
{
	struct sigaction	sa;
	struct sigaction	sb;

	sa.sa_handler = ft_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sb.sa_handler = ft_signal;
	sigemptyset(&sb.sa_mask);
	sb.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sb, NULL);
}

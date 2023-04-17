/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 11:34:56 by maserrie          #+#    #+#             */
/*   Updated: 2023/04/16 19:25:48 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strrncmp(const char *s1, const char *s2, size_t n)
{
	int		i;
	int		j;
	size_t	k;

	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (1);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	k = 0;
	if (n == 0)
		return (0);
	while (i >= 0 && j >= 0 && s1[i] == s2[j] && k < n + 1)
	{
		i--;
		j--;
		k++;
	}
	if (i >= 0 && j >= 0)
		return ((unsigned char)s1[i] - (unsigned char)s2[j]);
	else
		return (k < n + 1);
}

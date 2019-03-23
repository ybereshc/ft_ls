/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybereshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 12:25:10 by ybereshc          #+#    #+#             */
/*   Updated: 2018/10/26 12:25:11 by ybereshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(char *str, char chr)
{
	size_t	wc;
	char	**res;
	char	*tmp;

	if (!str || !chr || !(wc = ft_strchrcount(str, chr)))
		return (0);
	if (!(res = malloc(sizeof(char*) * (wc + 2))))
		return (0);
	wc = 0;
	while (*str)
	{
		tmp = str;
		while (*str && *str != chr)
			str++;
		res[wc] = ft_memcpy(0, tmp, str - tmp);
		res[wc++][str - tmp] = '\0';
		if (!*str)
			break ;
		str++;
	}
	res[wc] = 0;
	return (res);
}

char	**ft_strfsplit(char *str, char chr)
{
	size_t	wc;
	char	**res;

	if (!str || !chr || !(wc = ft_strchrcount(str, chr)))
		return (0);
	if (!(res = malloc(sizeof(char*) * (wc + 2))))
		return (0);
	wc = 0;
	while (*str)
	{
		res[wc++] = str;
		while (*str && *str != chr)
			str++;
		if (!*str)
			break ;
		*str++ = '\0';
	}
	res[wc] = 0;
	return (res);
}

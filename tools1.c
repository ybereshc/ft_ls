/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybereshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 16:42:05 by ybereshc          #+#    #+#             */
/*   Updated: 2019/02/04 16:42:07 by ybereshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_width(t_finfo *row)
{
	int		i;
	int		len;

	i = -1;
	while (++i < COLUMNS)
	{
		len = ft_strlen((*((char**)row + i)));
		if (g_ls.width[i] < len)
			g_ls.width[i] = len;
	}
}

char	*ls_color(char *attr)
{
	if (attr[0] == 'd')
	{
		if (attr[8] == 'w')
			return ("\e[43;30m");
		return ("\033[34m");
	}
	if (attr[0] == 'l')
		return ("\e[35m");
	if (attr[3] == 's' || attr[6] == 's')
		return (attr[3] == 's' ? "\e[41;30m" : "\e[46;30m");
	if (attr[9] == 'x' || attr[9] == 't')
		return ("\e[31m");
	return (0);
}

void	ls_sort(t_finfo **ary, int n)
{
	if (g_f & f)
		return ;
	sort_by_ascii(ary, n);
	if (g_f & S)
		sort_by_size(ary, n);
	else if (g_f & t)
		sort_by_time(ary, n);
}

void	ls_free(t_finfo *finfo)
{
	int	i;

	i = -1;
	while (++i < 10)
		free(*((char**)finfo + i));
	free(finfo);
}
